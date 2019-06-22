#include "file.h"
#include "heap.h"
#include "balanced_multiway_merge_rep_sub.h"
#include "constants.h"

/*
Função: sortedBlocks_withRepSub
  - Responsável por gerar os blocos ordenados (com uso da técnica "substituição
    por seleção").

  - Observação: Essa função faz uso do carctere ";" para separar registros e do
    caractere "@" para separar blocos.

Parâmetros:
  - file: Arquivo de entrada
  - ptrIn: Fitas de entrada
  - RAM: Área de memória disponível para o método de ordenação
  - n: Quantidade de registros considerada durante ordenação

Retorno:
  - Número de blocos ordenados gerados
*/

int sortedBlocks_withRepSub(FILE **file, tTapeSet *ptrIn, tRAM *RAM, int n,
                            long *inCounter, long *outCounter, long *compCounter)
{
  short destTape, lastTape, readError, flagCount;
  int i, j, k, numBlocks;
  float lastGrade;
  tStudent student;

  destTape = readError = flagCount = numBlocks = 0;

  for (i = 0; i < RAM_SIZE; i++)
  {
    readStudent(file, &student);
    insertRAM(RAM, student, getSize(RAM));
    setPriority(RAM, getSize(RAM) - 1, 0);

    (*inCounter)++;
  }

  buildHeap(RAM, RAM_SIZE, compCounter);

  k = 0;

  do
  {
    /*Obtém o estudante com menor nota*/
    student = getStudent(RAM, 0);

    if (i >= n)
    {
      /*Troca primeiro registro com o último*/
      swapStudents(RAM, 0, RAM_SIZE - (k + 1));
      /*Remove registro da área de memória*/
      removeStudent(RAM, RAM_SIZE - (k + 1));

      k++;
    }
    else
      /*Remove primeiro estudante da RAM*/
      removeStudent(RAM, 0);

    /*Insere menor estudante (primeiro do heap) na fita apropriada*/
    insertTape(&(ptrIn->tape[destTape]), student);
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
          /*Registro lido é maior que o último registro escrito na fita. Tal
          registro deve ser "marcado".*/
          setPriority(RAM, 0, 1);

          /*Variável que conta quantidade de registros "marcados"*/
          flagCount++;
        }
        else
          /*Registro lido é menor que último registro escrita na fita.*/
          setPriority(RAM, 0, 0);

        if (flagCount == RAM_SIZE)
        {
          /*Insere separador de bloco*/
          fprintf(ptrIn->tape[destTape].file, "%c\n", '@');

          /*Quando todos os registros estão "marcados", todos são "desmarcados"
          e um novo bloco é iniciado. Tal bloco deverá ser armazenado numa nova
          fita.*/
          flagCount = 0;
          destTape++;
          numBlocks++;

          if (destTape == RAM_SIZE)
            destTape = 0;

          for (j = 0; j < RAM_SIZE; j++)
            setPriority(RAM, j, 0);
        }
        else
          /*Insere separador de linha*/
          fprintf(ptrIn->tape[destTape].file, "%c\n", ';');

        /*Reconstrói heap, considerando o tamanho máximo da RAM*/
        rebuildHeap(RAM, RAM_SIZE, compCounter);
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
            fprintf(ptrIn->tape[destTape].file, "%c\n", ';');
          else
            /*Se ainda não mudou de fita, usa '@' como separador*/
            fprintf(ptrIn->tape[destTape].file, "%c\n", '@');

          /*Só deve mudar de fita uma vez nesse ponto*/
          destTape = lastTape + 1;

          if (destTape == TAPE_SET_SIZE)
            destTape = 0;
        }
        else
          fprintf(ptrIn->tape[destTape].file, "%c\n", ';');
      }

      i++;

      /*Armazena o id da fita em uso quando a leitura do arquivo terminou*/
      if (i == n)
        lastTape = destTape;
    }
  } while (readError == 0 && getSize(RAM) > 0);

  /*Retrocede ponteiro de arquivo para substituir o caracter separador
  (Como este ponto indica o fim de um bloco, o caractere usado deve ser o "@")*/
  fseek(ptrIn->tape[destTape].file, -2, 1);
  fprintf(ptrIn->tape[destTape].file, "%c\n", '@');

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
Função: mergeBlocks_withRepSub
  - Responsável por intercalar os blocos ordenados

Parâmetros:
  - ptrIn: Fitas de entrada
  - ptrOut: Fitas de saída
  - idxIn: Primeiro id das fitas de entrada
  - idxOut: Primeiro id das fitas de saída
  - RAM: Área de memória disponível para o método de ordenação
  - numGroups: Número de grupos de blocos ordenados
  - lastMerge: Indica se o processo de intercalação corrente será o último

Retorno:
  - Nenhum
*/

void mergeBlocks_withRepSub(tTapeSet *ptrIn, tTapeSet *ptrOut, short idxIn,
                            short idxOut, tRAM *RAM, int numGroups,
                            short lastMerge, long *inCounter, long *outCounter,
                            long *compCounter)
{
  char separator, enter;
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

        /*Fita está ativa e possui registros*/
        if (readTape(&(ptrIn->tape[i]), &aux) == 0)
        {          
          /*Insere registro na área de memória disponível para o método*/
          insertRAM(RAM, aux, getSize(RAM));

          /*Lê caractere separador*/
          fscanf(ptrIn->tape[i].file, "%c %[\n]", &separator, &enter);

          if (separator == '@' || getTapeLength(&(ptrIn->tape[i])) == 0)
          {
            /*Caso o caractere identificado como separados seja um '@' ou a fita
            não possua mais registros, ela é inativada*/
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
      /*Obtém registro localizado na primeira posição da área de memória*/
      aux = getStudent(RAM, 0);
      /*Remove registro localizado na primeira posição da área de memória*/
      removeStudent(RAM, 0);
      /*Insere, na fita, registro removido da área de memória*/
      insertTape(&(ptrOut->tape[j]), aux);     

      (*outCounter)++;

      if (lastMerge == 0)
        /*Insere caractere separador*/
        fprintf(ptrOut->tape[j].file, "%c\n", ';');

      if (ptrIn->tape[aux.origin - idxIn].status == 1)
      {
        (*inCounter)++;

        /*Lê registro localizado na mesma fita que aquele que foi retirado da
        área de memória*/
        if (readTape(&(ptrIn->tape[aux.origin - idxIn]), &aux) == 0)
        {          
          insertRAM(RAM, aux, 0);
          /*Lê separador*/
          fscanf(ptrIn->tape[aux.origin - idxIn].file, "%c %[\n]", &separator,
                 &enter);
        }

        if (separator == '@' ||
            getTapeLength(&(ptrIn->tape[aux.origin - idxIn])) == 0)
        {
          /*Caso o caractere identificado como separados seja um '@' ou a fita
          não possua mais registros, ela é inativada*/
          setStatus(&(ptrIn->tape[aux.origin - idxIn]), 0);
          setNumReads(&(ptrIn->tape[aux.origin - idxIn]), 0);
        }
      }

      i++;
    }

    if (lastMerge == 0)
    {
      fseek(ptrOut->tape[j].file, -2, 1);
      fprintf(ptrOut->tape[j].file, "%c\n", '@');
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
