#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "balanced_multiway_merge.h"
#include "constants.h"
#include "file.h"

/*
Função: sortedBlocks_withoutRepSub
  - Responsável por gerar os blocos ordenados (sem uso da técnica "substituição
    por seleção").

Parâmetros:
  - file: Arquivo de entrada
  - ptrIn: Fitas de entrada
  - RAM: Área de memória disponível para o método de ordenação
  - n: Quantidade de registros considerada durante ordenação

Retorno:
  - Número de blocos ordenados gerados
*/

int sortedBlocks_withoutRepSub(FILE **file, tTapeSet *ptrIn, tRAM *RAM, int n,
                               long *inCounter, long *outCounter,
                               long *compCounter)
{
  short destTape;
  int i, j, numBlocks;
  tStudent student;

  i = destTape = numBlocks = 0;

  (*inCounter)++;

  /*Gera blocos ordenados*/
  while (readStudent(file, &student) == 0 && i < n)    
  {        
    /*Registro foi lido do arquivo de entrada*/
    if (getSize(RAM) < RAM_SIZE)
      insertRAM(RAM, student, getSize(RAM));
    else
    {
      /*Ordena área de memória*/
      sortRAM(RAM, RAM_SIZE, compCounter);
      /*Insere bloco ordenado na fita de entrada, indicada por "destTape"*/
      for (j = 0; j < RAM->size; j++)
      {
        insertTape(&(ptrIn->tape[destTape]), getStudent(RAM, j));

        (*outCounter)++;
      }

      /*"Limpa" área de memória*/
      cleanRAM(RAM);
      /*Insere registro lido na área de memória*/
      insertRAM(RAM, student, getSize(RAM));
      /*Variável que controla qual fita de entrada receberá o bloco*/
      destTape++;
      /*Variável que controla número de blocos ordenados gerados*/
      numBlocks++;
      /*"Reseta" índice da fita de entrada, a fim de evitar acesso em posição
      inválida*/
      if (destTape == TAPE_SET_SIZE)
        destTape = 0;
    }

    i++;

    (*inCounter)++;
  }

  if (getSize(RAM) > 0)
    numBlocks++;

  /*Ordena elementos da área de memória disponível para o método*/
  sortRAM(RAM, RAM_SIZE, compCounter);

  for (i = 0; i < getSize(RAM); i++)
  {
    insertTape(&(ptrIn->tape[destTape]), getStudent(RAM, i));

    (*outCounter)++;
  }

  return numBlocks;
}

/*
Função: mergeBlocks_withoutRepSub
  - Responsável por intercalar os blocos ordenados

Parâmetros:
  - ptrIn: Fitas de entrada
  - ptrOut: Fitas de saída
  - idxIn: Primeiro id das fitas de entrada
  - idxOut: Primeiro id das fitas de saída
  - RAM: Área de memória disponível para o método de ordenação
  - blockSize: Tamanho dos blocos ordenados
  - numGroups: Número de grupos de blocos ordenados

Retorno:
  - Nenhum
*/

void mergeBlocks_withoutRepSub(tTapeSet *ptrIn, tTapeSet *ptrOut, short idxIn,
                               short idxOut, tRAM *RAM, short blockSize,
                               int numGroups, long *inCounter, long *outCounter,
                               long *compCounter)
{
  short i, j;
  tStudent aux;

  cleanRAM(RAM);

  for (i = 0; i < TAPE_SET_SIZE; i++)
  {
    openTape(&(ptrIn->tape[i]), "r\0");
    initializeTape(&(ptrOut->tape[i]), i + idxOut);
  }

  j = 0;

  while (numGroups > 0)
  {    
    for (i = 0; i < TAPE_SET_SIZE; i++)
      if (ptrIn->tape[i].status == 1 && getTapeLength(&(ptrIn->tape[i])) > 0)
      {
        (*inCounter)++;

        /*Fita está ativa e possui registro(s)*/
        if (readTape(&(ptrIn->tape[i]), &aux) == 0)
        {                   
          /*Insere registros na área de memória*/
          insertRAM(RAM, aux, getSize(RAM));

          if (ptrIn->tape[i].numReads == blockSize ||
              getTapeLength(&(ptrIn->tape[i])) == 0)
          {
            /*Fita é invativada*/
            setStatus(&(ptrIn->tape[i]), 0);
            setNumReads(&(ptrIn->tape[i]), 0);
          }
        }
      }

    i = 0;

    while (getSize(RAM) > 0)
    {
      /*Ordena área de memória*/
      sortRAM(RAM, RAM_SIZE, compCounter);
      /*Obtém primeiro registro da área de memória*/
      aux = getStudent(RAM, 0);
      /*Remove registro da primeira posição da área de memória*/
      removeStudent(RAM, 0);
      /*Insere registro lido da área de memória na fita de saída adequada*/
      insertTape(&(ptrOut->tape[j]), aux);

      (*outCounter)++;

      if (ptrIn->tape[aux.origin - idxIn].status == 1)
      {
        (*inCounter)++;

        /*Lê o próximo registro daquela mesma fita*/
        if (readTape(&(ptrIn->tape[aux.origin - idxIn]), &aux) == 0)
          insertRAM(RAM, aux, 0);

        if (ptrIn->tape[aux.origin - idxIn].numReads == blockSize ||
            getTapeLength(&(ptrIn->tape[aux.origin - idxIn])) == 0)
        {
          /*Fita é invativada*/
          setStatus(&(ptrIn->tape[aux.origin - idxIn]), 0);
          setNumReads(&(ptrIn->tape[aux.origin - idxIn]), 0);
        }
      }

      i++;
    }

    for (i = 0; i < TAPE_SET_SIZE; i++)
      if (getTapeLength(&(ptrIn->tape[i])) > 0)
        setStatus(&(ptrIn->tape[i]), 1);

    numGroups--;
    j++;

    if (j == TAPE_SET_SIZE)
      j = 0;
  }

  for (i = 0; i < TAPE_SET_SIZE; i++)
  {
    closeTape(&(ptrIn->tape[i]));
    closeTape(&(ptrOut->tape[i]));
  }
}
