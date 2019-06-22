#define ITENSPAGINA 100
#define MAXTABELA 30000

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <cstring>
#include "gerador.h"
#include "pesquisaSequencial.h"
#include "arvoreBinaria.h"
#include "arvoreB.h"
#include "arvoreBEstrela.h"

using namespace std;

int main()
{
	int metodo, quantidade, situacao, chave;
	int aux = 0, ver = 0;
	char aux2[6];
	cout << "Informe os parametros: metodo, quantidade, situacao, chave" << endl;
	cin >> metodo >> quantidade >> situacao >> chave;
	fgets(aux2, 6, stdin);
	if(strcmp(aux2," [-P]") == 0 || strcmp(aux2," [-p]") == 0)
		aux = 1;
	TApontador Ap = NULL;
	TApEstrela Ap2 = NULL;
	TIndice tabela[MAXTABELA];
	FILE *pfile;
	TDados dados;
	clock_t indiceIni, indiceFim, pesqIni, pesqFim;
	int numComparacoesIndice=0, numComparacoesPesquisa=0, numAcessoArquivoIndice=0, numAcessoArquivoPesquisa=0;
	srand(time(NULL));
	fflush(stdout);
	switch (metodo)
	{
		case 1: // Pesquisa Sequencial
			if (situacao == 1)
			{
				if (criaArquivo(situacao, quantidade) == true)
				{
					if ((pfile = fopen("dados.bin", "rb")) == NULL)
					{
						cout << "Arquivo nao encontrado\n" << endl;
						return 0;
					}
					int posicao = 0, contador = 0;
					indiceIni = clock();
					while (fread(&dados, sizeof(TDados), 1, pfile) == 1)
					{
						numAcessoArquivoIndice++; // Nao ha um ++ fora do while pois sao apenas transferencias e nao checagens
						contador++;
						if (contador % ITENSPAGINA == 1)
						{
							tabela[posicao].chave = dados.chave;
							tabela[posicao].posicao = posicao + 1;
							posicao++;
						}
					}
					indiceFim = clock();
					dados.chave = chave;
					cout << "Chave procurada = " << dados.chave << endl;
					if (aux == 1)
						cout << "Chaves verificadas durante a pesquisa:" << endl;
					pesqIni = clock();
					if (pesquisaSequencial(tabela, posicao, &dados, pfile, aux, &numComparacoesPesquisa, &numAcessoArquivoPesquisa))
						cout << endl << "Chave encontrada: " << "\nDado 1: " << dados.dado2 << "\nDado 2: " <<dados.dado3 << endl;
					else
						cout << endl << "Chave inexistente." << endl;
					pesqFim = clock();
					fclose(pfile);
				}
				else
					cout << "Falha na criacao do arquivo." << endl;
			}
			else
			{
				cout << "Eh necessario um arquivo ordenado ascendentemente para esse metodo." << endl;
				return 0;
			}
			break;
		case 2: // Pesquisa Binaria
			if (criaArquivo(situacao, quantidade) == true)
			{
				indiceIni = clock();
				if (criaArvoreBinaria(&numComparacoesIndice, &numAcessoArquivoIndice, situacao) == true)
				{
					indiceFim = clock();
					dados.chave = chave;
					cout << "Chave procurada: " << dados.chave << endl;
					if (aux)
						cout << "Chaves verificadas durante a pesquisa:" << endl;
					pesqIni = clock();
					if (pesquisaArvoreBinaria(&dados, aux, &numComparacoesPesquisa, &numAcessoArquivoPesquisa) == true)
						cout << endl << "Chave encontrada: " << "\nDado 1: " << dados.dado2 << "\nDado 2: " <<dados.dado3 << endl;
					else
						cout << endl << "Chave inexistente." << endl;
					pesqFim = clock();
				}
				else
				{
					cout << "Falha na criacao da arvore" << endl;
					return 0;
				}
			}
			else
			{
				cout << "Falha na criacao do arquivo." << endl;
				return 0;
			}
			break;
		case 3: // Arvore B
			if (criaArquivo(situacao, quantidade) == true)
			{
				indiceIni = clock();
				Inicializa(Ap);
				if ((pfile = fopen("dados.bin", "rb")) == NULL)
				{
					cout << "Falha ao abrir arquivo de dados." << endl;
					return 0;
				}
				while(fread(&dados, sizeof(TDados), 1, pfile) == 1)
				{
					numAcessoArquivoIndice++;
					InsereArvoreB(dados, &Ap, &numComparacoesIndice);
				}
				indiceFim = clock();
				fclose(pfile);
				dados.chave = chave;
				cout << "Chave do registro desejado: " << dados.chave << endl;
				if (aux)
					cout << "Chaves verificadas durante a pesquisa:" << endl;
				pesqIni = clock();
				PesquisaArvoreB(&dados, Ap, aux, &numComparacoesPesquisa, &ver);
				if(ver){
					//cout << "Chave do registro desejado: " << dados.chave << endl;
					cout << endl << endl << "Dado encontrado: " << "\nDado 1: " << dados.dado2 << "\nDado 2: " << dados.dado3 << endl;
				}
				else
					cout << endl << endl << "Dado nao foi encontrado." << endl;
				pesqFim = clock();
			}
			else
			{
				cout << "Falha na cricao do arquivo." << endl;
				return 0;
			}
			break;
		case 4: // Ã?rvore B*
			if (criaArquivo(situacao, quantidade) == true)
			{
				indiceIni = clock();
				inicializaBEstrela(Ap2);
				if ((pfile = fopen("dados.bin", "rb")) == NULL)
				{
					cout << "Falha ao abrir arquivo de dados." << endl;
					return 0;
				}
				while(fread(&dados, sizeof(TDados), 1, pfile) == 1)
				{
					numAcessoArquivoIndice++;
					insereBEstrela(dados, &Ap2, &numComparacoesIndice);
				}
				indiceFim = clock();
				fclose(pfile);
				dados.chave = chave;
				cout << "Chave do registro desejado: " << dados.chave << endl;
				if (aux)
					cout << "Chaves verificadas durante a pesquisa:" << endl;
				pesqIni = clock();
				pesquisaBEstrela(&dados, &Ap2, &ver, &numComparacoesPesquisa, aux);
				if(ver)
					cout << endl << endl << "Dado encontrado: " << "\nDado 1: " << dados.dado2 << "\nDado 2: " << dados.dado3 << endl;
				else
					cout << endl << endl << "Dado nao foi encontrado." << endl;
				pesqFim = clock();
			}
			else
			{
				cout << "Erro ao gerar arquivo de dados, situacao dos dados incorreta." << endl;
				return 0;
			}
			break;
		default:
			cout << "Metodo inexistente." << endl;
			return 0;
	}

	cout << endl << "Estatisticas:" << endl;
	cout << "Numero de acessos ao arquivo na criacao dos indices: " << numAcessoArquivoIndice << "." << endl;
	cout << "Numero de acessos ao arquivo na pesquisa: " << numAcessoArquivoPesquisa << "." << endl;
	cout << "Tempo de criacao dos indices: " << (double)(indiceFim-indiceIni)*1000/CLOCKS_PER_SEC << "ms." << endl;
	cout << "Tempo de execucao da pesquisa: " << (double)(pesqFim-pesqIni)*1000/CLOCKS_PER_SEC << "ms." << endl;
	cout << "Numero de comparacoes entre chaves para criacao dos indices: " << numComparacoesIndice << "." << endl;
	cout << "Numero de comparacoes entre chaves durante a pesquisa: " << numComparacoesPesquisa << "." << endl;
	return 0;
}
