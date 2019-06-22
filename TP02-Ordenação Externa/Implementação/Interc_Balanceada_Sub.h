#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    long mat;
    float nota;
    char estado[3];
    char cidade[51];
    char curso[31];
    int marcado;
}Registro;

typedef struct
{
	Registro v[10];
	int n;
	int pertence[10];
	int status;
}Bloco;

void construir_blocos_sub(FILE*,FILE**,int,int);
void ordenar_blocos_sub(FILE*,FILE**,int);
