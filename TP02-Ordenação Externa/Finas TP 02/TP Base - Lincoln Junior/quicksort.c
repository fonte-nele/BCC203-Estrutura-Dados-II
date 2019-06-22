#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#include "constants.h"
#include "file.h"
#include "quicksort.h"

/*
Função: externalQuickSort
  - Responsável por chamar as funções que realizam a ordenação via método
    Quicksort externo.

Parâmetro:
  - N: Quantidade de registros a ser considerado pelo método.

Retorno:
  - Nenhum
*/

short externalQuickSort(int N)
{  
  short RAM_SIZE_QS;
  long inCounter, outCounter, compCounter;
  double tTotal;
  tPartition p1, p2;
  tRAM RAM;  
  struct timeval t, t2;  
  FILE *p1_Read, *p1_Write, *p2_Read, *p2_Write;

  /*Define o tamanho da área de memória usada pelo método (pivô)*/
  RAM_SIZE_QS = log2(N);

  /*A área de memória é capaz de armazenar, no mínimo, 3 registros */
  if (RAM_SIZE_QS < 3)
    RAM_SIZE_QS = 3;

  /*Cria e inicia área de memória usada pelo método de ordenação (pivô)*/
  createRAM(&RAM, RAM_SIZE_QS);

  /*Tenta abrir arquivo de entrada*/
  p1_Read = fopen("PROVAO.txt", "r");

  if (p1_Read != NULL)
  {
    /*Caso não ocorra erro na abertura do arquivo, inicia demais ponteiros*/
    p1_Write = fopen("PROVAO.txt", "r+");
    p2_Read = fopen("PROVAO.txt", "r");
    p2_Write = fopen("PROVAO.txt", "r+");

    gettimeofday(&t, NULL);

    inCounter = outCounter = compCounter = 0;

    /*Chama função auxiliar do quick sort*/
    quickSort(0, N - 1, 0, N - 1, &RAM, &p1, &p2, RAM_SIZE_QS,
              p1_Read, p1_Write, p2_Read, p2_Write,
              &inCounter, &outCounter, &compCounter);

    /*Fecha o arquivo de entrada*/
    fclose(p1_Read);
    fclose(p1_Write);
    fclose(p2_Read);
    fclose(p2_Write);

    gettimeofday(&t2, NULL);

    tTotal = (t2.tv_sec + t2.tv_usec / 1000000.0) - (t.tv_sec + t.tv_usec / 1000000.0);

    puts("*** Resultado ***\n");
    printf("Numero de transferencias (leitura): %ld\n", inCounter);
    printf("Numero de transferencias (escrita): %ld\n", outCounter);
    printf("Numero de comparacoe de chave: %ld\n", compCounter);
    printf("Tempo de execucao: %.2lfs\n", tTotal);

    freeRAM(&RAM);

    return 0;
  }
  else
  {
    /*Indica erro ao abrir o arquivo a ser ordenado*/
    return 1;
  }
}

/*
Função: insertionSort
  - Responsável por aplicar o método de ordenação "insertion sort" na área de
    memória utilizada pelo método de ordenação.

Parâmetros:
  - RAM: Área de memória disponível pelo método de ordenação.

Retorno:
  - Nenhum.
*/

void insertionSort(tRAM *RAM, long *compCounter)
{
  short i, j;
  tStudent aux;

  /*Observação: Os registros são ordenados de forma descendente*/

  printf("RAM->start + 1: %d\n", RAM->start + 1);
  printf("RAM->end: %d\n", RAM->end);

  for (i = RAM->start + 1; i < RAM->end; i++)
  {
    aux = RAM->student[i];
    j = i;

    (*compCounter)++;

    printf("j - 1: %d\n", j - 1);

    while (aux.grade > RAM->student[j - 1].grade && j > 0)
    {
      RAM->student[j] = RAM->student[j - 1];
      j--;

      (*compCounter)++;
    }

    RAM->student[j] = aux;
  }
}

/*
Função: quickSort
  - Função principal do método de ordenação "Quicksort externo". Realiza as
    movimentos adequadas, gerando, à cada chamada, duas partições (sub-arquivos),
    de acordo com o conceito visto em sala de aula.

Parâmetros:
  - p1_R: Valor inteiro que indica o deslocamento necessário para o ponteiro
          de leitura na partição 1.
  - p2_R: Valor inteiro que indica o deslocamento necessário para o ponteiro
          de leitura na partição 2.
  - p1_W: Valor inteiro que indica o deslocamento necessário para o ponteiro
          de escrita na partição 1.
  - p2_W: Valor inteiro que indica o deslocamento necessário para o ponteiro
          de escrita na partição 2.
  - RAM: Área de memória disponível para o método de ordenação
  - p1: Variável de controle da partição 1 (contém seu tamanho e seu índice
        delimitador).
  - p2: Variável de controle da partição 2 (contém seu tamanho e seu índice
        delimitador).
  - RAM_SIZE_QS: Tamanho máximo da área disponível para o método de ordenação.
*/

void quickSort(int p1_R, int p2_R, int p1_W, int p2_W,
               tRAM *RAM, tPartition *p1, tPartition *p2,
               short RAM_SIZE_QS, FILE *pp1_Read, FILE *pp1_Write, FILE *pp2_Read,
               FILE *pp2_Write, long *inCounter, long *outCounter, long *compCounter)
{
  short nextRead, insPoint;
  int i, p1_size, p2_size, p1_delimiter, p2_delimiter;
  long p1_NextRead, p2_NextRead;
  float inferiorLimit, superiorLimit;
  tStudent auxItem;

  if (p2_R - p1_R < 1)
    return;

  cleanRAM(RAM);  

  /*Posiciona ponteiros, de acordo com valor dos delimitadores das partições*/
  fseek(pp1_Read, p1_R * LINE_SIZE, 0);
  fseek(pp1_Write, p1_W * LINE_SIZE, 0);
  fseek(pp2_Read, p2_R * LINE_SIZE, 0);
  fseek(pp2_Write, p2_W * LINE_SIZE, 0);

  /*Como o universo de dados não apresenta notas inferiores a 0 e nem notas
  superiores a 100, os valores abaixo podem ser usados como limites*/
  inferiorLimit = -1;
  superiorLimit = 101;

  /*Obtém posição dos ponteiros de leitura. Tal informação é usada para
  determinar o fim do laço principal, que acontece quando os ponteiros se cruzam.
  Isso indica que as partições foram geradas*/
  p1_NextRead = ftell(pp1_Read);
  p2_NextRead = ftell(pp2_Read);

  RAM->size = RAM->start = RAM->end = p1->size = p2->size = p1->delimiter =
  p2->delimiter = 0;
  /*Por convenção, a primeira leitura será realizada na partição 2*/
  nextRead = 2;

  insPoint = RAM_SIZE_QS - 1;

  while (p1_NextRead <= p2_NextRead)
  {
    if (nextRead == 1)
    {      
      /*Lê um registro do arquivo, utilizando o ponteiro para a partição 1*/
      readStudent(&pp1_Read, &auxItem);
      p1_NextRead = ftell(pp1_Read);

      /*Indica que a próxima leitura ocorrerá na partição 2*/
      nextRead = 2;         
    }
    else
    {      
      /*Lê um registro do arquivo, utilizando o ponteiro para a partição 2*/
      readStudent(&pp2_Read, &auxItem);
      fseek(pp2_Read, LINE_SIZE * -2, 1);      
      p2_NextRead = ftell(pp2_Read);

      /*Indica que a próxima leitura ocorrerá na partição 1*/
      nextRead = 1;
    }

    (*inCounter)++;

    if (RAM->size == RAM_SIZE_QS - 1)
    {
      if (auxItem.grade >= inferiorLimit && auxItem.grade <= superiorLimit)
      {
        /*Registro lido está entre limites inferior e superior - será inserido
        no pivô*/

        if (insPoint == 0)          
          RAM->start = insPoint;
        else          
          (RAM->end)++;

        RAM->student[insPoint] = auxItem;
        (RAM->size)++;

        /*Ordena pivô*/
        insertionSort(&(*RAM), compCounter);

        /*Com o pivô cheio, um registro deve ser removido*/
        if (p1->size < p2->size)
        {          
          /*Registro é escrito na partição 1 (maiores que o pivô)*/          
          writeStudent(pp1_Write, RAM->student[0]);

          /*Limite superior é atualizado*/
          superiorLimit = RAM->student[0].grade;
          (p1->size)++;
          RAM->start = 1;
          RAM->end = RAM_SIZE_QS;
          insPoint = 0;
        }
        else
        {
          /*Registro é escrito na partição 2 (menores que o pivô)*/          
          writeStudent(pp2_Write, RAM->student[RAM_SIZE_QS - 1]);
          fseek(pp2_Write, LINE_SIZE * -2, 1);

          /*Limite inferior é atualizado*/
          inferiorLimit = RAM->student[RAM_SIZE_QS - 1].grade;
          (p2->size)++;
          RAM->start = 0;
          RAM->end = RAM_SIZE_QS - 1;
          insPoint = RAM_SIZE_QS - 1;
        }                

        (RAM->size)--;
        (*compCounter)++;
      }
      else if (auxItem.grade > superiorLimit)
      {        
        /*Registro lido é maior ou igual ao limite superior - vai direto para a
        partição 1*/

        /*Escreve registro na posição adequada*/        
        writeStudent(pp1_Write, auxItem);

        (p1->size)++;
        *compCounter += 2;
      }
      else
      {        
        /*Registro lido é menor ou igual ao limite inferior - vai direto para a
        partição 2*/        
        writeStudent(pp2_Write, auxItem);
        fseek(pp2_Write, LINE_SIZE * -2, 1);

        (p2->size)++;
        *compCounter += 2;
      }

      (*outCounter)++;

      /*O ponteiro de escrita não pode ultrapassar o de leitura*/
      if (ftell(pp1_Write) == ftell(pp1_Read) && nextRead == 2)
        nextRead = 1;
      else if (ftell(pp2_Write) == ftell(pp2_Read) && nextRead == 1)
        nextRead = 2;
    }    
    else
    {
      /*Insere registro na posição adequada do pivô*/
      RAM->student[RAM->end] = auxItem;
      (RAM->size)++;
      (RAM->end)++;
    }
  }

  p1->delimiter = ftell(pp1_Write) / LINE_SIZE;

  if (p1->size > 0)
    p1->delimiter -= 1;

  p2->delimiter = p1->delimiter + RAM->size + 1;

  /*Ordena registros que ainda encontram-se no pivô após o término do laço*/
  insertionSort(&(*RAM), compCounter);

  /*Escreve, no arquivo, registros que estavam no pivô*/
  for (i = RAM->start; i < RAM->end; i++)
  {
    writeStudent(pp1_Write, RAM->student[i]);

    (*outCounter)++;
  }

  /*Ao final das movimentações geradas pelo processo de partição, é necessário
  fazer com que cada um dos ponteiros passem a enxergar o arquivo "atualizado".*/
  fflush(pp1_Read);
  fflush(pp1_Write);
  fflush(pp2_Read);
  fflush(pp2_Write);

  /*Armzena informações das partições para que o processo recursivo ocorra
  corretamente*/
  p1_delimiter = p1->delimiter;
  p2_delimiter = p2->delimiter;
  p1_size = p1->size;
  p2_size = p2->size;

  /*Chamada recursiva - Partição 1*/
  quickSort(p1_delimiter - p1_size + 1,
            p1_delimiter,
            p1_delimiter - p1_size + 1,
            p1_delimiter,
            RAM, p1, p2, RAM_SIZE_QS,
            pp1_Read, pp1_Write, pp2_Read, pp2_Write,
            inCounter, outCounter, compCounter);

  /*Chamada recursiva - Partição 2*/
  quickSort(p2_delimiter,
            p2_delimiter + p2_size - 1,
            p2_delimiter,
            p2_delimiter + p2_size - 1,
            RAM, p1, p2, RAM_SIZE_QS,
            pp1_Read, pp1_Write, pp2_Read, pp2_Write,
            inCounter, outCounter, compCounter);
}
