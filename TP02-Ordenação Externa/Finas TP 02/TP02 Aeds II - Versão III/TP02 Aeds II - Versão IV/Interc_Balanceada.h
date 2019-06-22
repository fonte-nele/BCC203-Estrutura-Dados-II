#include <stdio.h>
#include <stdlib.h>

typedef struct TipoReg 
{
    long mat;
    float nota;
    char estado[3];
    char cidade[51];
    char curso[31];
}TipoReg;

typedef struct TipoBloco
{
	
	TipoReg v[10];
	int n;
	int pertence[10];
}TipoBloco;

void ordenar_blocos(FILE*,FILE**,int);
void Insertion(TipoBloco*,int);
void intercalar_blocos(FILE**,int);

