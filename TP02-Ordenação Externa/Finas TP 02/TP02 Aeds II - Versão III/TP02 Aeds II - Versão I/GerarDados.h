#ifndef GERARDADOS_H
#define GERARDADOS_H
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef float Chave;
typedef struct Item 
{
    long Mat;
    Chave Nota;
    char Estado[3];
    char Cidade[51];
    char Curso[31];
}Item;


int GerarArq(int, int);

#endif
