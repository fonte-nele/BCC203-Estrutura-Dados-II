#ifndef EXE04_H
#define EXE04_H
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
using namespace std;

void gerar_dados(ofstream&);
void leitura_votos(ifstream&,int*);
void verificar_votos(int*);

#endif