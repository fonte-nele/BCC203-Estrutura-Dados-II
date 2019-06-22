#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "gerador.h"
#include <time.h>

using namespace std;

bool criaArquivo(int ordenacao, int numRegistros)
{
	FILE* pfile;
	srand(time(NULL));
	TDados dados;
	char letras[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	register int j;
	int registrosRestantes = numRegistros;
	int *vetor;
	float a = 0.5;
	fflush(stdout);
	if ((pfile = fopen("dados.bin", "wb")) == NULL)
		return false;
	switch (ordenacao)
	{
		case 1: //Ordenação ascendente
			for(int i=0; i<numRegistros; i++)
			{
				dados.chave = i;
				//dados.dado1 = ((float)rand()/(float)(RAND_MAX)) * a; //Gera floats aleatorios
				dados.dado2 = rand();
				for (j=0; j<499; j++)
					dados.dado3[j] = letras[rand() % 52];
				dados.dado3[j] = '\0';
				fwrite(&dados, sizeof(dados), 1, pfile);
			}
			break;
		case 2:	//Ordenação descendente
			for(int i=numRegistros-1; i>=0; i--)
			{
				dados.chave = i;
				//dados.dado1 = ((float)rand()/(float)(RAND_MAX)) * a; //Gera floats aleatorios
				dados.dado2 = rand();
				for (j=0; j<499; j++)
					dados.dado3[j] = letras[rand() % 52];
				dados.dado3[j] = '\0';
				fwrite(&dados, sizeof(dados), 1, pfile);
			}
			break;
		case 3:	//Desordenado
			//Geracao de um vetor ordenado
			vetor = (int*) calloc (numRegistros, sizeof(int));
			for(int i=0; i<numRegistros; i++)
				vetor[i]=i;
			while (registrosRestantes > 0)
			{
				//Embaralha o vetor
				int k = rand() % registrosRestantes;
				int temp = vetor[k];
				vetor[k] = vetor[registrosRestantes-1];
				vetor[registrosRestantes-1] = temp;
				registrosRestantes--;
			}
			for(int i=0; i<numRegistros; i++)
			{
				dados.chave = vetor[i]; //Atribui aos nós as chaves embaralhadas
				//dados.dado1 = ((float)rand()/(float)(RAND_MAX)) * a; //Gera floats aleatorios
				dados.dado2 = rand();
				for (j=0; j<499; j++)
					dados.dado3[j] = letras[rand() % 52];
				dados.dado3[j] = '\0';
				fwrite(&dados, sizeof(dados), 1, pfile);
			}
			break;
		default:
			return false;
			break;
    }
	fclose(pfile);
	free(vetor);
	return true;
}
