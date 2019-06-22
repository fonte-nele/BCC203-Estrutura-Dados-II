#ifndef GERAR_DADOS_H
#define GERAR_DADOS_H
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct
{
    int chave;
    long dado1;
    char dado2[501];
}Dados;

void gerar_arq(FILE*,int,int);
void inverter_char_numero(char*,int);
void num_extenso(char*,char*);
void um_digito(char*,char*,int*,int*);
void dois_digitos(char*,char*,int*,int*);
void tres_digitos(char*,char*,int*,int*);
void quatro_digitos(char*,char*,int*,int*);
void cinco_digitos(char*,char*,int*,int*);
void seis_digitos(char*,char*,int*,int*);
void sete_digitos(char*,char*,int*,int*);

#endif