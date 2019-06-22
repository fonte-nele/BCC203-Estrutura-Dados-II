#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct
{
	int chave;
	long dado1;
    char dado2[501];
}Dados_arv_bin;

typedef struct
{
	int esq;
	int dir;
	Dados_arv_bin no;
}TBinaria;

int inserir_arv_binaria(FILE*,TBinaria,Dados_arv_bin,int,int,long*,long*);
int pesquisar_arv_binaria(FILE*,TBinaria,Dados_arv_bin*,long*,long*);

#endif