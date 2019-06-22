#ifndef QUICKSORTEXTERNO_H
#define QUICKSORTEXTERNO_H
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define TAMAREA 3
#define TRUE 1
#define FALSE 0
typedef int TipoApontador;
typedef float TipoChave;
typedef struct TipoItem 
{
    long Mat;
    TipoChave Nota;
    char Estado[3];
    char Cidade[51];
    char Curso[31];
}TipoItem;

typedef struct TipoCelula 
{
    TipoItem Item;
    TipoApontador Prox, Ant;
}TipoCelula;

typedef struct TipoArea 
{
    TipoCelula Itens[TAMAREA];
    TipoApontador CelulasDisp, Primeiro, Ultimo;
    int NumCelOcupadas;
}TipoArea;

typedef TipoItem TipoRegistro;

void FAVazia(TipoArea *Area);
int ObterNumCelOcupadas(TipoArea *Area);
void InsereItem(TipoItem Item, TipoArea *Area);
void RetiraPrimeiro(TipoArea *Area, TipoItem *Item);
void RetiraUltimo(TipoArea *Area, TipoItem *Item);
void LeSup(FILE **ArqLEs, TipoRegistro *UltLido, int *Ls, short *OndeLer);
void LeInf(FILE **ArqLi,  TipoRegistro *UltLido, int *Li, short *OndeLer);
void InserirArea(TipoArea *Area, TipoRegistro *UltLido, int *NRArea);
void EscreveMax(FILE **ArqLEs, TipoRegistro R, int *Es);
void EscreveMin(FILE **ArqEi,  TipoRegistro R, int *Ei);
void RetiraMax(TipoArea *Area,  TipoRegistro *R, int *NRArea);
void RetiraMin(TipoArea *Area, TipoRegistro *R, int *NRArea);
void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j);
void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir);

#endif