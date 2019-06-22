#include <stdlib.h>
#include <time.h>

#include "file.h"
#include "heap.h"
#include "polyphase.h"
#include "constants.h"

/*
Função: sortedBlocksPolyphase
  - Responsável por gerar os blocos ordenados para o método de ordenação via
    Intercalação polifásica.

Parâmetros:
  - file: Arquivo de entrada
  - inputTapes: Fitas de entrada
  - RAM: Área de memória disponível para o método de ordenação
  - n: Quantidade de registros a ser considerada pelo processo de ordenação

Retorno:
  - numBlocks: Número de blocos ordenados gerados
  - -1: Indica erro na leitura do arquivo de entrada
*/

int sortedBlocksPolyphase(FILE **file, tTapeSet *inputTapes, tRAM *RAM, int n,
                          long *inCounter, long *outCounter, long *compCounter)
{
  short destTape, lastTape, readError, flagCount;
  int i, j, k, numBlocks;
  float lastGrade;
  tStudent student;

  readError = flagCount = numBlocks = 0;

  for (i = 0; i < POLYPHASE_TAPE_SET_SIZE - 1; i++)
  {
    readStudent(file, &student);
    insertRAM(RAM, student, getSize(RAM));
    setPriority(RAM, getSize(RAM) - 1, 0);

    (*inCounter)++;
  }

  buildHeap(RAM, POLYPHASE_TAPE_SET_SIZE - 1, compCounter);

  k = 0;

  srand(time(NULL));
  destTape = rand() % (POLYPHASE_TAPE_SET_SIZE - 1);

  do
  {
    /*Obtém o estudante com menor nota*/
    student = getStudent(RAM, 0);

    if (i >= n)
    {
      /*Troca primeiro com o último*/
      swapStudents(RAM, 0, POLYPHASE_TAPE_SET_SIZE - 1 - (k + 1));
      /*Retira estudante da RAM*/
      removeStudent(RAM, POLYPHASE_TAPE_SET_SIZE - 1 - (k + 1));

      k++;
    }
    else
      /*Remove primeiro estudante da RAM*/
      removeStudent(RAM, 0);

    /*Insere menor estudante (primeiro do heap) na fita apropriada*/
    insertTape(&(inputTapes->tape[destTape]), student);
    /*Armazena última nota escrita na fita*/
    lastGrade = student.grade;

    (*outCounter)++;

    if (i < n)
    {
      /*Lê próximo item de dado*/
      readError = readStudent(file, &student);

      (*inCounter)++;
    }

    if (readError == 0 || i >= n)
    {
      if (i < n)
      {
        /*Insere item lido na RAM*/
        insertRAM(RAM, student, 0);

        /*Define a prioridade do estudante recém adicionado à RAM*/
        if (getGrade(RAM, 0) > lastGrade)
        {
          setPriority(RAM, 0, 1);

          flagCount++;
        }
        else
          setPriority(RAM, 0, 0);

        if (flagCount == POLYPHASE_TAPE_SET_SIZE - 1)
        {
          /*Insere separador de bloco*/
          fprintf(inputTapes->tape[destTape].file, "%c\n", '@');

          destTape = rand() % (POLYPHASE_TAPE_SET_SIZE - 1);

          flagCount = 0;
          numBlocks++;

          for (j = 0; j < POLYPHASE_TAPE_SET_SIZE - 1; j++)
            setPriority(RAM, j, 0);
        }
        else
          /*Insere separador de linha*/
          fprintf(inputTapes->tape[destTape].file, "%c\n", ';');

        /*Reconstrói heap, considerando o tamanho máximo da RAM*/
        rebuildHeap(RAM, POLYPHASE_TAPE_SET_SIZE - 1, compCounter);
      }
      else
      {
        /*Reconstrói heap, considerando o tamanho atual da RAM*/
        rebuildHeap(RAM, getSize(RAM), compCounter);

        /*Verifica a prioridade do novo menor elemento*/
        if (getStudent(RAM, 0).priority == 1)
        {
          if (destTape != lastTape)
            /*Se já mudou de fita, usa ';' como separador*/
            fprintf(inputTapes->tape[destTape].file, "%c\n", ';');
          else
            /*Se ainda não mudou de fita, usa '@' como separador*/
            fprintf(inputTapes->tape[destTape].file, "%c\n", '@');

          /*Só deve mudar de fita uma vez nesse ponto*/
          destTape = lastTape + 1;

          if (destTape == POLYPHASE_TAPE_SET_SIZE - 1)
            destTape = 0;
        }
        else
          fprintf(inputTapes->tape[destTape].file, "%c\n", ';');
      }

      i++;

      /*Armazena o id da fita em uso quando a leitura do arquivo terminou*/
      if (i == n)
        lastTape = destTape;
    }   
  } while (readError == 0 && getSize(RAM) > 0);

  fseek(inputTapes->tape[destTape].file, -2, 1);
  fprintf(inputTapes->tape[destTape].file, "%c\n", '@');

  /*Contabiliza bloco formado por itens com prioridade igual a 0 que ainda
  estavam na RAM após a leitura do último item de dado*/
  numBlocks++;

  /*Se, após a leitura do último item de dado, ainda existir, na RAM, algum item
  com prioridade igual a 1, tal item será enviado para um novo bloco*/
  if (destTape != lastTape)
    numBlocks++;

  if (readError == 0)
    return numBlocks;
  else
    return -1;
}

/*
Função mergeBlocksPolyphase
  - Responsável por realizar a intercalação dos blocos ordenados.

Parâmetros:
  - ptrIn: Fitas de entrada
  - outTape: Número que indica qual será a fita de saída
  - RAM: Área de memória disponível para o método de ordenação

Retorno:
  - mergeAgain: Indica a necessidade de realizar mais uma intercalação
*/

int mergeBlocksPolyphase(tTapeSet *ptrIn, short *outTape, tRAM *RAM,
                         long *inCounter, long *outCounter, long *compCounter)
{
  char separator, enter;
  short i, newEmptyTape, mergeAgain;
  int tapeLength;
  tStudent aux;

  /*Antes do inicio do processo de intercalacao, apenas a fita de saída, cujo
  id foi recebido como parâmetro, está vazia.*/
  /*Indica o id da próxima fita de saída*/
  newEmptyTape = *outTape;    

  cleanRAM(RAM); 

  while (newEmptyTape == *outTape)
  {
    /*Indica se, após o processo de intercalação, ainda existe alguma fita que
    não está vazia*/
    mergeAgain = 0;

    for (i = 0; i < POLYPHASE_TAPE_SET_SIZE; i++)
    {
      tapeLength = getTapeLength(&(ptrIn->tape[i]));

      if (ptrIn->tape[i].status == 1 && tapeLength > 0 && i != *outTape)
      {
        (*inCounter)++;

        /*Lê registro da fita de entrada*/
        if (readTape(&(ptrIn->tape[i]), &aux) == 0)
        {
          /*Insere registro na área de memória disponível para o método*/
          insertRAM(RAM, aux, getSize(RAM));

          /*Lê caractere separador*/
          fscanf(ptrIn->tape[i].file, "%c %[\n]", &separator, &enter);

          tapeLength = getTapeLength(&(ptrIn->tape[i]));

          if (separator == '@' || tapeLength == 0)
          {
            /*Caso o caractere identificado como separados seja um '@' ou a fita
            não possua mais registros, ela é inativada*/
            setStatus(&(ptrIn->tape[i]), 0);
            setNumReads(&(ptrIn->tape[i]), 0);           
          }
        }
      }
    }

    i = 0;

    while (getSize(RAM) > 0)
    {
      /*Ordena área de memória disponível para o método de ordenação*/
      sortRAM(RAM, POLYPHASE_TAPE_SET_SIZE - 1, compCounter);
      /*Obtém registro localizado na primeira posição da área de memória*/
      aux = getStudent(RAM, 0);
      /*Remove registro localizado na primeira posição da área de memória*/
      removeStudent(RAM, 0);
      /*Insere registro na fita de saída*/
      insertTape(&(ptrIn->tape[newEmptyTape]), aux);

      (*outCounter)++;

      if (ptrIn->tape[aux.origin].status == 1)
      {
        (*inCounter)++;

        /*Lê registro da mesma fita que aquele que foi retirado*/
        if (readTape(&(ptrIn->tape[aux.origin]), &aux) == 0)
        {
          insertRAM(RAM, aux, 0);
          /*Lê caractere separador*/
          fscanf(ptrIn->tape[aux.origin].file, "%c %[\n]", &separator, &enter);
        }

        tapeLength = getTapeLength(&(ptrIn->tape[aux.origin]));

        if (separator == '@' || tapeLength == 0)
        {
          /*Caso o caractere identificado como separados seja um '@' ou a fita
          não possua mais registros, ela é inativada*/
          setStatus(&(ptrIn->tape[aux.origin]), 0);
          setNumReads(&(ptrIn->tape[aux.origin]), 0);
        }
      }

      i++;
    }

    for (i = 0; i < POLYPHASE_TAPE_SET_SIZE; i++)
      if (getTapeLength(&(ptrIn->tape[i])) > 0)
      {
        setStatus(&(ptrIn->tape[i]), 1);

        mergeAgain++;
      }
      else
      {
        newEmptyTape = i;
      }
  }

  /*Fecha antiga fita de saída*/
  closeTape(&(ptrIn->tape[*outTape]));
  /*Abre fita de saída, no modo "leitura"*/
  openTape(&(ptrIn->tape[*outTape]), "r\0");
  /*Atualiza fita de saída*/
  *outTape = newEmptyTape;
  /*Recria nova fita de saída*/
  closeTape(&(ptrIn->tape[*outTape]));
  initializeTape(&(ptrIn->tape[*outTape]), *outTape);

  return mergeAgain;
}
