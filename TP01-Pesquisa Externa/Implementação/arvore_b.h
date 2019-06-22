#ifndef ARVORE_B
#define ARVORE_B
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define M 2
#define MM M*2

typedef struct
{
	int chave;
	long dado1;
    char dado2[501];
}Registro;

typedef struct Pagina* Apont;

typedef struct Pagina
{
	short n;
	Registro registro[MM];
	Apont pagina[MM + 1];
}Pagina;

void inicializar(Apont*);
void inserir_pagina(Apont,Registro,Apont,long*);
void ins_aux(Registro,Apont,short*,Registro*,Apont*,long*);
void inserir(Registro,Apont*,long*);
int pesquisar(Registro*,Apont,long*);
void caminhamento(Apont);
void imprimir(Apont,int);

#endif