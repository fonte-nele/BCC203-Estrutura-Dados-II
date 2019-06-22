#include "ShiftAnd.h"

int ShiftAnd(TipoTexto texto, long tamTexto, TipoPadrao padrao, long tamPadrao, long *comp, long *desloc){
    long mascara[MAXCHAR], i, R = 0, achou = 0;
    for(i = 0; i < MAXCHAR; i++){
        mascara[i] = 0;
    }
    for(i = 1; i <= tamPadrao; i++){
        mascara[padrao[i-1] + 127] |= 1 << (tamPadrao - i);
    }
    for(i = 0; i < tamTexto; i++){
        (*desloc)++;
        R = ((((unsigned long)R) >> 1) | (1 << (tamPadrao - 1))) & mascara[texto[i] + 127];
        (*comp)++;
        if((R & 1) != 0){
            printf(" - - Casamento na posicao %ld\n", i - tamPadrao + 2);
            achou = 1;
        }
    }
    return achou;
}
