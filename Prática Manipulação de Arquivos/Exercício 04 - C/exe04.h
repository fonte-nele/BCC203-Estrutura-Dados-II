#ifndef EXE04_H
#define EXE04_H
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct
{
	int v[100];
	int cont1,cont2,cont3,cont4,cont5,cont6;
}Votos;

void gerar_dados(FILE*,Votos*);
void leitura_votos(FILE*,Votos*);
void verificar_votos(Votos*);

#endif