#ifndef EXE03_H
#define EXE03_H
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define n 121

typedef struct
{
	float v[n];
	float menor;
	float maior;
	float soma;
}Temp;

void gerar_dados(FILE*,Temp*);
void leitura_temp(FILE*,Temp*);
void verificar_temp(Temp*);

#endif