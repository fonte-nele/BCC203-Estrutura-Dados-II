#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stdio.h>

#include "ram.h"
#include "student.h"

typedef struct
{
  int delimiter, size;
} tPartition;

short externalQuickSort(int);
void insertionSort(tRAM *, long *);
void quickSort(int, int, int, int, tRAM *, tPartition *, tPartition *, short,
               FILE *, FILE *, FILE *, FILE *, long *, long *, long *);

#endif
