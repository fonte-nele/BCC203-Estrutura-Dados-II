#ifndef POLYPHASE_H
#define POLYPHASE_H

#include <stdio.h>

#include "ram.h"
#include "tape.h"

int sortedBlocksPolyphase(FILE **, tTapeSet *, tRAM *, int, long *, long *,
                          long *compCounter);
int mergeBlocksPolyphase(tTapeSet *, short *, tRAM *, long *, long *,
                         long *compCounter);

#endif
