#ifndef TAPE_H
#define TAPE_H

#include <stdio.h>

#include "student.h"

typedef struct
{
  char name[12];
  short status, id;
  int length, numReads; //número de students lidos no bloco corrente  
  FILE *file;
} tTape;

typedef struct
{
  tTape *tape;
} tTapeSet;

void createTape(tTape **, short);
void initializeTape(tTape *, short);
short insertTape(tTape *, tStudent);
short readTape(tTape *, tStudent *);
short openTape(tTape *, char [3]);
short closeTape(tTape *);
void incTapeLength(tTape *);
void decTapeLength(tTape *);
int getTapeLength(tTape *);
short getTapeStatus(tTape *tape);
void setStatus(tTape *, short);
void setNext(tTape *);
int getNumReads(tTape *);
void setNumReads(tTape *, int);
void freeTape(tTape **);

#endif
