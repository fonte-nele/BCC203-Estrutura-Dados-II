#ifndef ACESSO_SEQUENCIAL_INDEXADO_H
#define ACESSO_SEQUENCIAL_INDEXADO_H
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define NUM_ITENS_PAG 100

typedef struct 
{
	int chave_indice;
}Indice;

typedef struct
{
    int chave_item;
    long dado1;
    char dado2[501];
}Item;

int pesquisa(Indice*,int,Item*,FILE*,long*,long*);
int busca_binaria(int,Item*,int,int,long*);


#endif