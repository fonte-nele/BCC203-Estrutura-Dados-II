#ifndef RAM_H
#define RAM_H

#include "student.h"

typedef struct
{
  //os campos start e end são usados apenas pelo método quicksort externo
  short size, start, end;
  tStudent *student;
} tRAM;

void createRAM(tRAM *, short size);
void insertRAM(tRAM *, tStudent, short);
short getSize(tRAM *);
void cleanRAM(tRAM *);
tStudent getStudent(tRAM *, short);
void removeStudent(tRAM *, short);
void sortRAM(tRAM *, short, long *);
short getPriority(tRAM *, short);
void setPriority(tRAM *, short, short);
float getGrade(tRAM *, short);
void swapStudents(tRAM *, short, short);
void freeRAM(tRAM *);

#endif
