#ifndef BM_H
#define BM_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Cadeia.h"

int maximo(int, int);
void heuristicaOcorrencia(TipoPadrao, int, int*);
int BM(TipoTexto, int, TipoPadrao, int, long*, long*);

#endif
