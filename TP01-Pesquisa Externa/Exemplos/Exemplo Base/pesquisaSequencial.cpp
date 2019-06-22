#define ITENSPAGINA 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include "gerador.h"
#include "pesquisaSequencial.h"

using namespace std;

int pesquisaSequencial (TIndice tabelaDePaginas[], int tam, TDados *dados, FILE *pfile, int aux, int *numComparacoesPesquisa, int *numAcessoArquivoPesquisa)
{
	TDados pagina[ITENSPAGINA];
	int i, quantitens;
	long desloc;
    int inicio = 0, fim = 0;
	i = 0;
	while (i < tam && tabelaDePaginas[i].chave <= dados->chave) //Vasculha as paginas em busca daquela onde a chave pode se encontrar
	{
		(*numComparacoesPesquisa)++;
		//cout << tabelaDePaginas[i].chave << ", "; //Bugando o cout de baixo
		i++;
	}
	if (i == 0)
		return 0;
	else
	{
		if (i < tam)
			quantitens = ITENSPAGINA;
		else
		{
			fseek(pfile, 0, SEEK_END);
			quantitens = (ftell(pfile)/sizeof(TDados))%ITENSPAGINA;
		}
		desloc = (tabelaDePaginas[i-1].posicao-1)*ITENSPAGINA*sizeof(TDados);
		fseek (pfile, desloc, SEEK_SET);
		fread (&pagina, sizeof(TDados), quantitens, pfile);
		*numAcessoArquivoPesquisa = *numAcessoArquivoPesquisa + quantitens;
		fim = quantitens;
		do{
            if((fim-inicio)%2 == 0)
                i = (fim+inicio)/2;
            else
                i = (fim+inicio+1)/2;
            if(pagina[i].chave == dados->chave){
                if(aux == 1){
                    cout << pagina[i].chave << endl;
                }
                *dados = pagina[i];
                *(numComparacoesPesquisa)++;
                return 1;
            }
            else if(dados->chave < pagina[i].chave){
                if(aux == 1){
                    cout << pagina[i].chave << ",";
                }
                fim = i;
                *(numComparacoesPesquisa)++;
            }
            else
                inicio = i;
            if(fim-inicio == 1){
            	if(pagina[inicio].chave == dados->chave){
            		if(aux == 1){
            			cout << pagina[inicio].chave << ",";
            		}
            		*dados = pagina[inicio];
            		*(numComparacoesPesquisa)++;
            		return 1;
            	}
            	else if(pagina[fim].chave == dados->chave){
            		if(aux == 1){
            			cout << pagina[fim].chave << ",";
            		}
            		*dados = pagina[fim];
            		*(numComparacoesPesquisa)++;
            		return 1;
            	}
            	return 0;
            }
		}while(1);
		return 0;
	}
}
