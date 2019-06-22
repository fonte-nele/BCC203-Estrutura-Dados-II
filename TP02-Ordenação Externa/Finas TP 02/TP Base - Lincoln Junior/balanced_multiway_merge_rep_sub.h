#ifndef BALANCED_MULTIWAY_MERGE_REP_SUB_H
#define BALANCED_MULTIWAY_MERGE_REP_SUB_H

#include <stdio.h>

#include "tape.h"
#include "ram.h"

int  sortedBlocks_withRepSub(FILE **, tTapeSet *, tRAM *RAM, int, long *,
                             long *, long *);
void mergeBlocks_withRepSub(tTapeSet *, tTapeSet *, short, short, tRAM *, int,
                            short, long *, long *, long *);

#endif
