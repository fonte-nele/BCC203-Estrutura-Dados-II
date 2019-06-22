#include "BM.h"

int maximo(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

void heuristicaOcorrencia(TipoPadrao tipoPadrao, int tamPadrao, int ocorrencia[MAXCHAR]){
    int i;
    for (i = 0; i < MAXCHAR; i++)
        ocorrencia[i] = -1;

    for (i = 0; i < tamPadrao; i++)
        ocorrencia[(int) tipoPadrao[i]] = i;
}

int BM(TipoTexto tipoTexto, int tamTexto, TipoPadrao tipoPadrao, int tamPadrao, long *comp, long *desloc){

    int ocorrencia[MAXCHAR], achou = 0;

    heuristicaOcorrencia(tipoPadrao, tamPadrao, ocorrencia);

    long pos = 0;

    while (pos <= (tamTexto - tamPadrao)){
        int j = tamPadrao - 1;

        while (j >= 0 && tipoPadrao[j] == tipoTexto[pos + j]){
            (*comp)++;
            j--;
        }

        if (j < 0){
            printf(" - - Casamento na posicao %ld\n", pos+1);
            achou = 1;

            pos += (pos + tamPadrao < tamTexto) ? tamPadrao - ocorrencia[tipoTexto[pos + tamPadrao]] : 1;
        }
        else{
            (*desloc)++;
            pos += maximo(1, j - ocorrencia[tipoTexto[pos + j]]);
        }
    }
    return achou;
}
