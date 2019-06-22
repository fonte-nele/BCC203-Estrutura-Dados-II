#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tape.h"
#include "file.h"

/*
Função: createTape
  - Aloca memória para um conjunto de fitas

Parâmetros:
  - tape : Endereço de um ponteiro para o tipo fita
  - num: Indica que será alocado um espaço suficiente para armazenar "num" fitas

Retorno:
  - Nenhum.
*/

void createTape(tTape **tape, short num)
{
  *tape = (tTape *) malloc(sizeof(tTape) * num);
}

/*
Função: initializeTape
  - Inicia campos da variável que representa uma fita

Parâmetros:
  - tape: Fita que será iniciada
  - id: Número identificador da fita

Retorno:
  - Nenhum.
*/

void initializeTape(tTape *tape, short id)
{
  char auxId[3];

  sprintf(auxId, "%d", id);
  strcpy(tape->name, "tape_");
  strcat(tape->name, auxId);
  strcat(tape->name, ".txt");

  tape->id = id;
  tape->length = tape->numReads = 0;
  tape->status = 1;

  tape->file = fopen(tape->name, "w");
}

/*
Função: insertTape
  - Responsável por escrever um registro numa fita.

Parâmetros:
  - tape: Fita alvo da escrita.
  - student: Registro que será escrito

Retorno:
  - 0, caso a escrita ocorra com sucesso.
  - valor > 0, caso a escrita não seja realizada.
*/

short insertTape(tTape *tape, tStudent student)
{
  if (tape->file != NULL)
  {
    /*fprintf(tape->file, "%08d %05.1f %s %-50s %-30s\n",
            student.id, student.grade, student.state,
            student.city, student.course);*/

    writeStudent(tape->file, student);

    if (ferror(tape->file))
      return 2;
    else
    {
      incTapeLength(tape);

      return 0;
    }
  }
  else
    return 1;
}

/*
Função: readTape
  - Função que realiza a leitura de um registro (estudante) de uma fita.

Parâmetros:
  - tape: Fita alvo da leitura.
  - student: Variável que será preenchida com os dados lidos da fita.

Retorno:
  - 0, caso a leitura ocorra com sucesso.
  - valor > 0, caso ocorra a leitura não seja realizada.
*/

short readTape(tTape *tape, tStudent *student)
{
  if (tape->file == NULL)
  {
    return 1;
  }
  else
  {
    readStudent(&(tape->file), student);

    if (ferror(tape->file))
    {
      return 2;
    }
    else
    {      
      student->origin = tape->id;

      setNumReads(tape, getNumReads(tape) + 1);
      decTapeLength(tape);

      return 0;
    }
  }
}

/*
Função: getTapeLength
  - Retorna a quantidade de registros escritos na fita.

Parâmetros:
  - tape: Fita cuja quantidade de registros será retornada.

Retorno:
  - Quantidade de registros da fita.
*/

int getTapeLength(tTape *tape)
{
  return tape->length;
}

/*
Função: getTapeStatus
  - Retorna "status" da fita: 0 - inativa, 1 - ativa.

Parâmetros:
  - tape: Fita alvo

Retorno:
  - "Status" da fita.
*/

short getTapeStatus(tTape *tape)
{
  return tape->status;
}

/*
Função: setStatus
  - Define "status" da fita: 0 - inativa, 1 - ativa.

Parâmetros:
  - tape: Fita alvo.
  - status: Valor de "status", que será atribuído à fita.

Retorno:
  - Nenhum.
*/

void setStatus(tTape *tape, short status)
{
  tape->status = status;
}

/*
Função: incTapeLength
  - Incrementa (em 1 unidade) o contador de registros da fita.

Parâmetros:
  - tape: Fita que terá seu contador incrementado.

Retorno:
  - Nenhum.
*/

void incTapeLength(tTape *tape)
{
  (tape->length)++;
}

/*
Função: decTapeLength
  - Decrementa (em 1 unidade) o contador de registros da fita.

Parâmetros:
  - tape: Fita que terá seu contador decrementado.

Retorno:
  - Nenhum.
*/

void decTapeLength(tTape *tape)
{
  (tape->length)--;
}

/*
Função: openTape
  - Abre o arquivo vinculado à fita.

Parâmetros:
  - tape: Fita alvo.
  - mode: Modo de abertura do arquivo.

Retorno:
  - 0, caso não ocorra erro durante a abertura do arquivo.
  - valor diferente de 0, caso ocorra erro durante a abertura do arquivo.
*/

short openTape(tTape *tape, char mode[3])
{
  tape->file = fopen(tape->name, mode);

  return ferror(tape->file);
}

/*
Função: closeTape
  - Fecha o arquivo vinculado à uma fita.

Parâmetros:
  - tape: Fita alvo.

Retorno:
  - 0, caso não ocorra erro durante a abertura do arquivo.
  - valor diferente de 0, caso ocorra erro durante a abertura do arquivo.
*/

short closeTape(tTape *tape)
{
  fclose(tape->file);

  return 0;//ferror(tape->file);
}

/*
Função: getNumReads
  - Retorna o número de registros lidos de uma determinada fita.

Parâmetros:
  - tape: Fita alvo.

Retorno:
  - Quantidade de registros lidos.
*/

int getNumReads(tTape *tape)
{
  return tape->numReads;
}

/*
Função: setNumReads
  - Define valor do campo que controla a quantidade de registros lidos de uma
    determinada fita.

Parâmetros:
  - tape: Fita alvo.
  - reads: Número de registros lidos.

Retorno:
  - Nenhum.
*/

void setNumReads(tTape *tape, int reads)
{
  tape->numReads = reads;
}

/*
Função: freeTape
  - Libera memória alocada para um conjunto (vetor) de fitas

Parâmetros:
  - tape: Ponteiro para conjunto de fitas

Retorno:
  - Nenhum.
*/
void freeTape(tTape **tape)
{
  free(*tape);
  *tape = NULL;
}
