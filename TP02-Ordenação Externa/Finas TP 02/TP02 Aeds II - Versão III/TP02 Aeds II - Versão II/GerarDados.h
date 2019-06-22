#ifndef GERARDADOS_H
#define GERARDADOS_H
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct Item 
{
    long mat;
    float nota;
    char estado[3];
    char cidade[51];
    char curso[31];
}Item;

int GerarArq(int, int);

#endif
