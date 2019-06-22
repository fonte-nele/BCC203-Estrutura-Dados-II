#include "gerador.h"
#include <iostream>
#include <stdio.h>
#include "arvoreBinaria.h"

using namespace std;

bool criaArvoreBinaria(int *numComparacoesIndice, int *numAcessoArquivoIndice, int situacao)
{
	FILE *arvore, *pfile;
	TDados dados;
	TBinaria registro;
	int i = 1; //i é o contador de registros na arvore e 1, no caso, é o nó raíz
	if ((arvore = fopen("arvore.bin", "w+b")) == NULL)
	{
		cout << "Falha na criacao do arquivo!" << endl;
		return false;
	}
	if ((pfile = fopen("dados.bin", "rb")) == NULL)
	{
		cout << "Falha na abertura do arquivo!" << endl;
		return false;
	}
	(*numAcessoArquivoIndice)++;
	fread(&dados, sizeof(TDados), 1, pfile);
	registro.no = dados;
	registro.esquerda = -1; //Nó esquerdo = NULL
	registro.direita = -1; //Nó direito = NULL
	fwrite(&registro, sizeof(TBinaria), 1, arvore); //Nó raiz
	while(fread(&dados, sizeof(TDados), 1, pfile))
	{
		(*numAcessoArquivoIndice)++;
		registro.no = dados;
		registro.esquerda = -1;
		registro.direita = -1;
		fseek(arvore, 0, SEEK_END);
		fwrite(&registro, sizeof(TBinaria), 1, arvore);
		if (situacao == 1 || situacao == 2) //Caso os dados estejam ordenados
		{
			fseek(arvore, -2*sizeof(TBinaria), SEEK_CUR);  //Volta ao penultimo nó da arvore
			fread(&registro, sizeof(TBinaria), 1, arvore);
			fseek(arvore, -1*sizeof(TBinaria), SEEK_CUR);  //Volta ao penultimo nó novamente
		}
		else
		{
			rewind(arvore);	// Retorna ao inicio da arvore
			fread(&registro, sizeof(TBinaria), 1, arvore);	//Le o nó raiz
			(*numAcessoArquivoIndice)++;
			rewind(arvore);
		}
		while(1)
		{
			//Verifica se o novo registro (nó) irá para a esquerda (se for menor) ou direita (se for maior)
			(*numComparacoesIndice)++;
			if (dados.chave < registro.no.chave)
			{
				if(registro.esquerda == -1)
				{
					registro.esquerda = i;
					fwrite(&registro, sizeof(TBinaria), 1, arvore); //Salva o nó modificado
					break; //Quebra o while
				}
				else
				{
					fseek(arvore, registro.esquerda*sizeof(TBinaria), SEEK_SET);
					fread(&registro, sizeof(TBinaria), 1, arvore);
					(*numAcessoArquivoIndice)++;
					fseek(arvore, -1*sizeof(TBinaria), SEEK_CUR); //Retorna ao inicio do nó encontrado no fseek anterior
				}
			}
			else
			{
				if(registro.direita == -1)
				{
					registro.direita = i;
					fwrite(&registro, sizeof(TBinaria), 1, arvore);
					break;
				}
				else
				{
					fseek(arvore, registro.direita*sizeof(TBinaria), SEEK_SET);
					fread(&registro, sizeof(TBinaria), 1, arvore);
					(*numAcessoArquivoIndice)++;
					fseek(arvore, -1*sizeof(TBinaria), SEEK_CUR);
				}
			}
		}	
		i++; //Incrementa a posição do ultimo registro da arvore
	}
	fclose(arvore);
	fclose(pfile);
	return true;
}

bool pesquisaArvoreBinaria(TDados *dados, int aux, int *numComparacoesPesquisa, int *numAcessoArquivoPesquisa)
{
	FILE *arvore;
	TBinaria registro;
	if ((arvore = fopen("arvore.bin", "rb")) == NULL)
	{
		cout << "Falha na abertura do arquivo!" << endl;
		return false;
	}
	while (fread(&registro, sizeof(TBinaria), 1, arvore))
	{
		(*numAcessoArquivoPesquisa)++;
		(*numComparacoesPesquisa)++;
		if (dados->chave == registro.no.chave)
		{
			if (aux == 1)
			{
				cout << registro.no.chave << ", ";
				fflush(stdout);
			}
			*dados = registro.no;
			fclose(arvore);
			return true;
		}
		else
		{
			(*numComparacoesPesquisa)++;
			if (dados->chave < registro.no.chave)
			{
				if (aux == 1)
				{
					cout << registro.no.chave << ", ";
					fflush(stdout);
				}
				if (registro.esquerda != -1)
					fseek(arvore, registro.esquerda*sizeof(TBinaria), SEEK_SET);
				else
				{
					fclose(arvore);
					return false;
				}
			}
			else
			{
				if (aux == 1)
					cout << registro.no.chave << ", ";
				if (registro.direita != -1)
					fseek(arvore, registro.direita*sizeof(TBinaria), SEEK_SET);
				else
				{
					fclose(arvore);
					return false;
				}
			}
		}
	}
	fclose(arvore);
	return true;
}
