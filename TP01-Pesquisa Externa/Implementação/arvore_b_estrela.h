#ifndef ARVORE_B_ESTRELA
#define ARVORE_B_ESTRELA
#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define N 2
#define NN 2*N

typedef struct
{
	int chave;
	long dado1;
    char dado2[501];
}Reg;

typedef enum{Interna,Externa} TipoIntExt;

typedef struct PaginaEstrela* ApontEstrela;

typedef struct PaginaEstrela
{
	TipoIntExt Pt;
	union
	{
		struct
		{
			int ni;
			int ri[NN];
			ApontEstrela pi[NN+1];
		}U0;
		struct
		{
			int ne;
			Reg re[NN];
		}U1;
	}UU;
}PaginaEstrela;

void inicializarEstrela(ApontEstrela*);
void inserirPagina(ApontEstrela,Reg,ApontEstrela,long*);
void insAux(Reg,ApontEstrela,short*,Reg*,ApontEstrela*,long*);
void insere(Reg,ApontEstrela*,long*);
int pesquisar_estrela(Reg*,ApontEstrela*,long*);

#endif