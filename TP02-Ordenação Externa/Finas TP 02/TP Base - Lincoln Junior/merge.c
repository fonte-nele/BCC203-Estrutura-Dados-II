#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "merge.h"
#include "constants.h"
#include "ram.h"
#include "tape.h"
#include "balanced_multiway_merge.h"
#include "balanced_multiway_merge_rep_sub.h"
#include "polyphase.h"

/*
Função: merge
  - Responsável por identificar qual dos 3 métodos de intercalação será
    utilizado (1 - Intercalação balanceada de vários caminhos, 2 - Intercalação
    balanceada de vários caminhos, com substituição por seleção, 3 - Intercalação
    polifásica), realizar os controles necessários à execução de cada método e
    chamar as funções que realizam a geração de blocos ordenados e a intercalação
    propriamente dita.

Parâmetros:
  - method: Número que representa o método de ordenação escolhido
  - N: Quantidade de registros a ser considerada pelo processo de ordenação

Retorno:
  - Nenhum
*/

int merge(short method, int N)
{  
  short posIn, posOut, posCtrl, idxIn, idxOut, idxCtrl, lastMerge, outTape,
        retorno;
  int i, blockSize, numBlocks, numGroups;
  long inCounter, outCounter, compCounter;
  double timeSorted, timeMerge;
  tTapeSet tapeSet[2], tapeSetPolyphase, *ptrIn, *ptrOut;
  tRAM RAM;
  FILE *file;
  struct timeval t1, t2;

  /*Contadores (leitura e escrita)*/
  inCounter = outCounter = compCounter = 0;

  /*Abre arquivo de entrada*/
  file = fopen("PROVAO.txt", "r");

  if (file != NULL)
  {
    /*Variáveis que controlam as referências as fitas entrada/saída*/
    posIn = idxIn = 0;
    posOut = posCtrl = 1;

    if (method == 1 || method == 2)
    {
      idxOut = idxCtrl = TAPE_SET_SIZE;

      /*Quantidade máxima de registro nos blocos ordenados*/
      blockSize = RAM_SIZE;
      /*Quantidade inicial de blocos ordenados*/
      numBlocks = N / RAM_SIZE;

      if (N % RAM_SIZE > 0)
        /*Ajusta quantidade inicial de blocos ordenados*/
        numBlocks++;

      /*Aloca memória para as fitas de entrada e saída*/
      createTape(&(tapeSet[posIn].tape), TAPE_SET_SIZE);
      createTape(&(tapeSet[posOut].tape), TAPE_SET_SIZE);

      /*Inicia campos das fitas de entrada*/
      for (i = 0; i < TAPE_SET_SIZE; i++)
        initializeTape(&(tapeSet[posIn].tape[i]), i);

      /*Aloca espaço para a área de memória disponível para o método*/
      createRAM(&RAM, RAM_SIZE);

      /*Armazena instante que precede a geração dos blocos ordenados*/
      gettimeofday(&t1, NULL);

      if (method == 1)
        /*Intercalacao balanceada de varios caminhos - 2f fitas
        (Sem substituicao por selecao)*/               
        numBlocks = sortedBlocks_withoutRepSub(&file, tapeSet, &RAM, N,
                                               &inCounter, &outCounter,
                                               &compCounter);
      else
        /*Intercalacao balanceada de varios caminhos - 2f fitas
        (Com substituicao por selecao)*/        
        numBlocks = sortedBlocks_withRepSub(&file, tapeSet, &RAM, N, &inCounter,
                                            &outCounter, &compCounter);

      /*Armazena instante que sucede a geração dos blocos ordenados*/
      gettimeofday(&t2, NULL);
      /*Cálculo do tempo gasto pela operação que gera blocos ordenados*/
      timeSorted = (t2.tv_sec + t2.tv_usec / 1000000.0) - (t1.tv_sec + t1.tv_usec / 1000000.0);

      /*Fecha fitas de saída*/
      for (i = 0; i < TAPE_SET_SIZE; i++)
        closeTape(&(tapeSet[posIn].tape[i]));

      /*Fecha arquivo de entrada*/
      fclose(file);

      if (method == 2 && numBlocks == 1)
        /*Como os blocos gerados possuem separadores (';' e '@'), preciso forçar
        ao menos 1 intercalação de blocos*/
        numBlocks = 2;

      gettimeofday(&t1, NULL);

      while (numBlocks > 1)
      {
        /*A variável tapeSet é um vetor para 2 conjuntos de fitas. Existem dois
        ponteiros (ptrIn e ptrOut) que apontam para tais conjuntos. A cada
        intercalação, os endereços apontados pelos ponteiros são invertidos.*/
        ptrIn = &tapeSet[posIn];
        ptrOut = &tapeSet[posOut];

        /*Armazena instante que precede a a operação de intercalação dos blocos*/
        numGroups = numBlocks / TAPE_SET_SIZE;

        if (numBlocks % TAPE_SET_SIZE > 0)
          numGroups++;

        //verifica se a próxima intercalação será a última
        if (numGroups == 1)
          lastMerge = 1;
        else
          lastMerge = 0;

        if (method == 1)
          mergeBlocks_withoutRepSub(ptrIn, ptrOut, idxIn, idxOut, &RAM, blockSize,
                                    numGroups, &inCounter, &outCounter,
                                    &compCounter);
        else
          mergeBlocks_withRepSub(ptrIn, ptrOut, idxIn, idxOut, &RAM, numGroups,
                                 lastMerge, &inCounter, &outCounter,
                                 &compCounter);

        posIn += posCtrl;
        posCtrl *= -1;
        posOut += posCtrl;

        idxIn += idxCtrl;
        idxCtrl *= -1;
        idxOut += idxCtrl;

        blockSize *= TAPE_SET_SIZE;

        numBlocks = numGroups;
      }

      /*Armazena instante que sucede a a operação de intercalação dos blocos*/
      gettimeofday(&t2, NULL);
      /*Cálculo do tempo gasto pela operação que intercala os blocos*/
      timeMerge = (t2.tv_sec + t2.tv_usec / 1000000.0) - (t1.tv_sec + t1.tv_usec / 1000000.0);

      freeRAM(&RAM);
      freeTape(&(tapeSet[posIn].tape));
      freeTape(&(tapeSet[posOut].tape));
    }
    else
    {
      /*First output tape is the last one*/
      outTape = POLYPHASE_TAPE_SET_SIZE - 1;

      //create and initialize tapes
      createTape(&(tapeSetPolyphase.tape), POLYPHASE_TAPE_SET_SIZE);

      for (i = 0; i < POLYPHASE_TAPE_SET_SIZE; i++)
        initializeTape(&(tapeSetPolyphase.tape[i]), i);

      //create and initialize RAM
      createRAM(&RAM, POLYPHASE_TAPE_SET_SIZE - 1);

      /*Intercalacao polifásica - f + 1 fitas
        (Com substituicao por selecao)*/

      /*Armazena instante que precede a geração dos blocos ordenados*/
      gettimeofday(&t1, NULL);

      numBlocks = sortedBlocksPolyphase(&file, &tapeSetPolyphase, &RAM, N,
                                        &inCounter, &outCounter, &compCounter);

      /*Armazena instante que sucede a geração dos blocos ordenados*/
      gettimeofday(&t2, NULL);
      /*Cálculo do tempo gasto pela operação que gera blocos ordenados*/
      timeSorted = (t2.tv_sec + t2.tv_usec / 1000000.0) - (t1.tv_sec + t1.tv_usec / 1000000.0);

      for (i = 0; i < POLYPHASE_TAPE_SET_SIZE; i++)
        closeTape(&(tapeSetPolyphase.tape[i]));

      /*Abre todas as fitas, no modo leitura*/
      for (i = 0; i < POLYPHASE_TAPE_SET_SIZE; i++)
        openTape(&(tapeSetPolyphase.tape[i]), "r\0");

      /*Recria nova fita de saída*/
      closeTape(&(tapeSetPolyphase.tape[outTape]));
      initializeTape(&(tapeSetPolyphase.tape[outTape]), outTape);

      retorno = numBlocks;

      /*Armazena instante que sucede a a operação de intercalação dos blocos*/
      gettimeofday(&t1, NULL);

      while (retorno > 1)
        retorno = mergeBlocksPolyphase(&tapeSetPolyphase, &outTape, &RAM,
                                       &inCounter, &outCounter, &compCounter);

      /*Armazena instante que sucede a a operação de intercalação dos blocos*/
      gettimeofday(&t2, NULL);
      /*Cálculo do tempo gasto pela operação que intercala os blocos*/
      timeMerge = (t2.tv_sec + t2.tv_usec / 1000000.0) - (t1.tv_sec + t1.tv_usec / 1000000.0);

      for (i = 0; i < POLYPHASE_TAPE_SET_SIZE; i++)
        closeTape(&(tapeSetPolyphase.tape[i]));

      freeRAM(&RAM);
      freeTape(&(tapeSetPolyphase.tape));
    }

    puts("*** Resultado ***\n");
    printf("Numero de transferencias (leitura): %ld\n", inCounter);
    printf("Numero de transferencias (escrita): %ld\n", outCounter);
    printf("Numero de comparacoes de chave: %ld\n", compCounter);
    printf("Tempo de execucao: %.2lfs\n", timeSorted + timeMerge);    

    return 0;
  }
  else
  {
    /*Não foi possível abrir arquivo de entrada*/
    return 1;
  }
}
