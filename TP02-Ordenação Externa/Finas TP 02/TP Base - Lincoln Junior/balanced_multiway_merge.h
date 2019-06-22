#ifndef BALANCED_MULTIWAY_MERGE_H
#define BALANCED_MULTIWAY_MERGE_H

#include <stdio.h>

#include "tape.h"
#include "ram.h"

int sortedBlocks_withoutRepSub(FILE **, tTapeSet *, tRAM *, int, long *, long *,
                               long *);
void mergeBlocks_withoutRepSub(tTapeSet *, tTapeSet *, short, short, tRAM *,
                               short, int, long *, long *, long *);

#endif

