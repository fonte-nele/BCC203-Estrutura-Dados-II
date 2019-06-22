#include "heap.h"

/*
Função: buildHeap
  - Responsável por transformar a área de memória na estrutura de dados "heap".

Parâmetros:
  - RAM: Área de memória disponível para o método de ordenação
  - size: Tamanho da área de memória

Retorno:
  - Nenhum
*/

void buildHeap(tRAM *RAM, int size, long *compCounter)
{
  int i, idxLargest, idxParent, idxTarget, idxLChild, idxRChild, swaps;
  tStudent aux;

  for (i = 0; i < size / 2;)
  {
    /*Índice do filho à esquerda*/
    idxLChild = 2 * i + 1;
    /*Índice do filho à direita*/
    idxRChild = 2 * i + 2;
    swaps = 0;        

    if (idxLChild >= 0 && idxLChild < size &&
        idxRChild >= 0 && idxRChild < size)
    {
      /*Índices de ambos os filhos fazem parte do vetor*/
      if (RAM->student[idxLChild].grade < RAM->student[idxRChild].grade)
        /*Filho à esquerda é menor que filho à direita*/
        idxLargest = idxRChild;
      else
        /*Filho à direita é menor que filho à esquerda*/
        idxLargest = idxLChild;

      (*compCounter)++;
    }
    else
      /*Índice do filho à direito está além dos limites do vetor
      (utiliza índice do filho à esquerda)*/
      idxLargest = idxLChild;

    if (RAM->student[i].grade < RAM->student[idxLargest].grade)
    {
      /*Troca pai com seu maior filho*/
      aux = RAM->student[i];
      RAM->student[i] = RAM->student[idxLargest];
      RAM->student[idxLargest] = aux;

      /*Verifica a necessidade de realizar trocas no sentido oposto
      (caso a propriedade do "heap" tenha sido violada após a troca)*/
      idxTarget = i;
      idxParent = (idxTarget - 1) / 2;

      (*compCounter)++;

      while (RAM->student[idxTarget].grade > RAM->student[idxParent].grade)
      {
        /*Pai é menor que filho - continua troca*/
        aux = RAM->student[idxTarget];
        RAM->student[idxTarget] = RAM->student[idxParent];
        RAM->student[idxParent] = aux;

        /*Atualiza índices utilizados nas comparações*/
        idxTarget = idxParent;
        idxParent = (idxTarget - 1) / 2;

        /*Controla o incremento da variável de laço "i"*/
        swaps++;

        (*compCounter)++;
      }
    }

    if (swaps == 0)
      /*Variável "i" não deve ser incrementada caso valor de RAM->student[i]
      tenha sido alterado. Isso é necessário para que a propriedade do "heap"
      seja mantida.*/
      i++;
  }
}

/*
Função: rebuildHeap
  - Responsável por reconstruir a estrutura de dados "heap".

Parâmetros:
  - RAM: Área de memória disponível para o método de ordenação
  - size: Tamanho da área de memória

Retorno:
  - Nenhum
*/

void rebuildHeap(tRAM *RAM, int size, long *compCounter)
{
  int idxNewRoot, idxMinor, idxLChild, idxRChild;
  tStudent aux;

  idxNewRoot = 0;

  while (2 * idxNewRoot + 1 < size)
  {
    idxLChild = 2 * idxNewRoot + 1;
    idxRChild = 2 * idxNewRoot + 2;

    if (idxLChild >= 0 && idxLChild < size &&
        idxRChild >= 0 && idxRChild < size)
    {
      //children's indexes are inside array

      if (RAM->student[idxLChild].priority > RAM->student[idxRChild].priority)
        //right child's priority is less than left child's priority
        idxMinor = idxRChild;
      else if (RAM->student[idxLChild].priority < RAM->student[idxRChild].priority)
        //left child's priority is less than right child's priority
        idxMinor = idxLChild;
      else if (RAM->student[idxLChild].grade < RAM->student[idxRChild].grade)
        //prioridades iguais (guarda o índice do estudante com a menor nota)
        idxMinor = idxRChild;
      else
        //prioridades iguais (guarda o índice do estudante com a menor nota)
        idxMinor = idxLChild;

      (*compCounter)++;
    }
    else
      //right child index is beyond array's bounds
      idxMinor = idxLChild;

    (*compCounter)++;

    //compares with parent (idxNewRoot)
    if (RAM->student[idxMinor].grade < RAM->student[idxNewRoot].grade &&
        RAM->student[idxNewRoot].priority == 0)
      break;

    (*compCounter)++;

    if (RAM->student[idxMinor].priority < RAM->student[idxNewRoot].priority ||
        (RAM->student[idxMinor].grade > RAM->student[idxNewRoot].grade &&
         RAM->student[idxMinor].priority == RAM->student[idxNewRoot].priority))
    {
      aux = RAM->student[idxNewRoot];
      RAM->student[idxNewRoot] = RAM->student[idxMinor];
      RAM->student[idxMinor] = aux;

      idxNewRoot = idxMinor;
    }
    else
      idxNewRoot++;
  }
}
