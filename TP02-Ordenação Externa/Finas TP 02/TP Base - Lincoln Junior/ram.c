#include <stdlib.h>

#include "ram.h"

/*
Função: createRAM
  - Responsável por alocar memória para área de memória utilizada pelos métodos
    de ordenação.

Parâmetros:
  - RAM: Área de memória
  - size: Tamanho da área de memória.

Retorno:
  - Nenhum.
*/

void createRAM(tRAM *RAM, short size)
{
  RAM->size = 0;
  //RAM->student = (tStudent *) malloc(sizeof(tStudent) * RAM_SIZE);
  RAM->student = (tStudent *) malloc(sizeof(tStudent) * size);
}

/*
Função: insertRAM
  - Responsável por inserir um registro (estudante) na área de memória utilizada
    pelo método de ordenação.

Parâmetros:
  - RAM: Área de memória disponível para o método de ordenação.
  - student: Registro que será inserido.
  - pos: Posição onde o registro será inserido.

Retorno:
  - Nenhum.
*/

void insertRAM(tRAM *RAM, tStudent student, short pos)
{
  RAM->student[pos] = student;
  (RAM->size)++;
}

/*
Função: getSize
  - Retorna a quantidade de registros existentes na área de memória disponível
    para o método de ordenação.

Parâmetros:
  - RAM: Área de memória disponível para o método de ordenação.

Retorno:
  - Quantidade de registros existentes.
*/

short getSize(tRAM *RAM)
{
  return RAM->size;
}

/*
Função: cleanRAM
  - Faz um "reset" dos campos de controle da área de memória.

Parâmetros:
  - RAM: Área de memória disponível para o método de ordenação.

Retorno:
  - Nenhum.
*/

void cleanRAM(tRAM *RAM)
{
  RAM->size = 0;
  RAM->start = 0;
  RAM->end = 0;
}

/*
Função: getStudent
  - Retorna o registro localizado na posição "pos" da área de memória disponível
    para o método de ordenação.

Parâmetro:
  - RAM: Área de memória disponível para o método de ordenação.
  - pos: Posição do registro que será retornado.

Retorno:
  - Registro da posição "pos".
*/

tStudent getStudent(tRAM *RAM, short pos)
{
  return RAM->student[pos];
}

/*
Função: removeStudent
  - Remove um registro da área de memória utilizada pelo método de ordenação.

  - Observação: Aqui, uso o conceito de remoção lógica.

Parâmetros:
  - RAM: Área de memória disponível para método de ordenação.
  - pos: Posição onde se encontra o registro que será removido.

Retorno:
  - Nenhum.
*/

void removeStudent(tRAM *RAM, short pos)
{
  if (pos >= 0 && pos < RAM->size)
  {
    RAM->student[pos].grade = -1;
    (RAM->size)--;
  }
}

/*
Função: sortRAM
  - Responsável por ordenar, de acordo com o método "insertion sort", a área de
    memória disponível para o método de ordenação.

  - Observação: Os registros são ordenados descendentemente.

Parâmetros:
  - RAM: Área de memória disponível para o método de ordenação.
  - size: Tamanho da área de memória.

Retorno:
  - Nenhum.
*/

void sortRAM(tRAM *RAM, short size, long *compCounter)
{
  //insertion sort
  int i, j;
  tStudent aux;

  for (i = 1; i < size; i++)
  {
    j = i;
    aux = RAM->student[i];

    /*Para fazer com que o arquivo gerado ao final esteja ordenado de forma
    crescente, mude [primeiro] o sinal de comparação abaixo e também o valor
    que é atribuído ao registro quando ele deixa a RAM (-1 para 101, por exemplo)*/

    (*compCounter)++;

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
Função: getPriority
  - Retorno o valor do campo que representa a prioridade do registro. Apenas 2
    valores são considerados: 0 (maior prioridade) e 1 (menor prioridade).

Parâmetros:
  - RAM: Área de memória disponível para o método de ordenação.
  - pos: Posição onde se encontra o registro que terá sua prioridade retornada.

Retorno:
  - Prioridade o registro na posição "pos".
*/

short getPriority(tRAM *RAM, short pos)
{
  return RAM->student[pos].priority;
}

/*
Função: setPriority
  - Define a prioridade de um registro localizado na área de memóra disponível
    para o método de ordenação.

Parâmetros:
  - RAM: Área de memória disponível para o método de ordenação.
  - pos: Posição onde se encontra o registro que terá sua prioridade alterada.

Retorno:
  - Nenhum.
*/

void setPriority(tRAM *RAM, short pos, short priority)
{
  RAM->student[pos].priority = priority;
}

/*
Função: getGrade
  - Retorna a nota do estudante

Parâmetros:
  - RAM: Área de memória disponível para o método.
  - pos: Posição onde se encontra o estudante que terá sua nota retornada.

Retorno:
  - Nota do estudante.
*/

float getGrade(tRAM *RAM, short pos)
{
  return RAM->student[pos].grade;
}

/*
Função: swapStudents
  - Troca um registro pelo outro.

Parâmetros:
  - RAM: Área de memória disponível para o método de ordenação.
  - pos1: Posição onde se encontra o registro 1.
  - pos2: Posição onde se encontra o registro 2.

Retorno:
  - Nenhum.
*/

void swapStudents(tRAM *RAM, short pos1, short pos2)
{
  tStudent aux;

  aux = getStudent(RAM, pos1);
  RAM->student[pos1] = RAM->student[pos2];
  RAM->student[pos2] = aux;
}

/*

*
*/
void freeRAM(tRAM *RAM)
{
  free(RAM->student);
  RAM->student = NULL;
}
