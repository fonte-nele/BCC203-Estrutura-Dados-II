#include "ForcaBruta.h"

int ForcaBruta(TipoTexto texto, long tamTexto, TipoPadrao padrao, long tamPadrao, long *comp, long *desloc){
    long i, j, k, achou = 0;
    for(i = 1; i <= (tamTexto - tamPadrao + 1); i++){
        (*desloc)++ ;
        k = i;
        j = 1;
        (*comp)++;
        while(texto[k-1] == padrao[j-1] && j <= tamPadrao){
            (*comp)++;
            (*desloc)++;
            j++;
            k++;
        }
        if(j > tamPadrao){
            printf(" - - Casamento na posicao %ld\n", i);
            achou = 1;
        }
    }
    return achou;
}
