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
	int status;
}TipoBloco;

typedef struct 
{
	long Num_transf_read;
	long Num_transf_write;
	long Num_comparacoes;
}Analise;

void construir_blocos(FILE*,FILE**,int,int,Analise*);
void Insertion(TipoBloco*,int,Analise*);
void intercalar_blocos(FILE**,int,Analise*);

