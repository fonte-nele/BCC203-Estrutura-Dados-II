/*
	Execução do programa: pesquisa <metodo> <quantidade> <situacao> <chave> [-P]
		pesquisa:		nome do arquivo;
		<metodo>:		1 à 4, de acordo com os metodos implementados;
		<quantidade>:	quantidade de registros no arquivo;
		<situacao>:		1 (ordenado ascendente); 2 (ordenado descendente); 3 (desordenado aleartóriamente);
		<chave>:		Chave a ser pesquisada;
		[-P]:			Argumento opcional, representa que as chaves de pesquisa dos registros do arquivo apareçam na tela;

	Métodos:
		- SEQUENTIAL_INDEX:	1
		- BINARY_SEARCH:	2
		- B_TREE:			3
		- B_STAR_TREE:		4

	Situacao:
		- ORDENADO CRESCENTE:		1
		- ORDENADO DECRESCENTE:		2
		- ALEARTÒRIO:				3
*/

#include "Utility.h"
#include "Sequential_Access.h"
#include "arvoreBin.h"
#include "B_Tree.h"

int main(int argc, char const *argv[]) {
	
	/*	Função que verifica os argumentos de entrada do sistema */
	if(!argumentsOk(argc, argv)) {
		cout << "ERROR CODE 568x4T0A - Please check System Docs to understand what it means !" << endl;
		return 1;
	}

	/* Atribuindo os parametros para as variáveis */
	int method	 	= atoi(argv[1]);
	int amount		= atoi(argv[2]);
	int situation	= atoi(argv[3]);
	int key			= atoi(argv[4]);
	//bool showAll 	= (argc == 6) ? true : false;
	FILE *file 		= chooseFile(situation);
	
	TRegistro reg;
	int nTransfer = 0;
	int nCompare = 0;

	/*	Variaveis usadas na busca sequencial indexada	*/
	int sizeTable = 0;

	/*	Inicializando os valores do registro para verificações futuras	*/
	reg.chave = 0;

	clock_t start, end;
	double middle;

	//Escolhendo o metodo que irá rodar no arquivo
	switch(method) {
		case SEQUENTIAL_INDEX:
			if (situation == 1) {
				TIndice tabIndice[MAX_TABELA];
				sizeTable = fillUpTIndex(file, tabIndice, amount);
				start = clock();
				Sequential_Search(tabIndice, sizeTable, &reg, file, key, &nTransfer, &nCompare);	
				end = clock();
				middle = getTimeExecution(end, start);
			} else {
				cout << "ERROR CODE 2342X36 - Impossible to use SEQUENTIAL SEARCH INDEX METHOD with no Sorted Crescent File  !" << endl;
				return 1;
			}

			if (reg.chave > 0 && sizeTable > 0) {
				cout << "REGISTRO ENCONTRADO NO ARQUIVO: " << endl;
				cout << "Chave..........: " << reg.chave << endl;
				cout << "Dado 01........: " << reg.dado1 << endl;
				cout << "Dado 02........: " << reg.dado2 << endl;
				cout << "Numero de transferencias (leitura) de itens da memoria externa e interna: " << nTransfer << endl;
				cout << "Numero de comparacoes entre chaves de pesquisa: " << nCompare << endl;
				cout << "Tempo de execucao: " << setprecision(10) << fixed << middle << " segundos" <<endl;
			} else {
				cout << "ERRO 3301X84 - Register not found !" << endl;
			}

			break;
		case BINARY_TREE:
			criaArvore(file, amount, &nTransfer, &nCompare);
			
			pesquisaArvore(&reg, key, &nTransfer, &nCompare);
			
			if (reg.chave > 0) {
				cout << "REGISTRO ENCONTRADO NO ARQUIVO: " << endl;
				cout << "Chave..........: " << reg.chave << endl;
				cout << "Dado 01........: " << reg.dado1 << endl;
				cout << "Dado 02........: " << reg.dado2 << endl;
				cout << "Numero de transferencias (leitura) de itens da memoria externa e interna: " << nTransfer << endl;
				cout << "Numero de comparacoes entre chaves de pesquisa: " << nCompare << endl;
				//cout << "Tempo de execucao: " << setprecision(10) << fixed << middle << " segundos" <<endl;
			} else {
				cout << "ERRO 3301X84 - Register not found !" << endl;
			}
			
			break;
		case B_TREE:
			TipoApontador Tree;
			
			New_Tree(&Tree);
			Mount_Tree(file, amount, &Tree);
			start = clock();
			Search_Tree(&reg, Tree, key, &nTransfer, &nCompare);
			end = clock();
			middle = getTimeExecution(end, start);

			if (reg.chave > 0) {
				cout << "REGISTRO ENCONTRADO NO ARQUIVO: " << endl;
				cout << "Chave..........: " << reg.chave << endl;
				cout << "Dado 01........: " << reg.dado1 << endl;
				cout << "Dado 02........: " << reg.dado2 << endl;
				cout << "Numero de transferencias (leitura) de itens da memoria externa e interna: " << nTransfer << endl;
				cout << "Numero de comparacoes entre chaves de pesquisa: " << nCompare << endl;
				cout << "Tempo de execucao: " << setprecision(10) << fixed << middle << " segundos" <<endl;
			} else {
				cout << "ERRO 3301X84 - Register not found !" << endl;
			}

			break;
		case B_STAR_TREE:
			/*TipoApontador Tree;

			New_BStar(&Tree);
			Mount_Tree(file, amount, &Tree);
			start = clock();
			Search_BStar(&reg, Tree, key, &nTransfer, &nCompare);
			end = clock();
			middle = getTimeExecution(end, start);

			if (reg.chave > 0) {
				cout << "REGISTRO ENCONTRADO NO ARQUIVO: " << endl;
				cout << "Chave..........: " << reg.chave << endl;
				cout << "Dado 01........: " << reg.dado1 << endl;
				cout << "Dado 02........: " << reg.dado2 << endl;
				cout << "Numero de transferencias (leitura) de itens da memoria externa e interna: " << nTransfer << endl;
				cout << "Numero de comparacoes entre chaves de pesquisa: " << nCompare << endl;
				cout << "Tempo de execucao: " << setprecision(10) << fixed << middle << " segundos" <<endl;
			} else {
				cout << "ERRO 3301X84 - Register not found !" << endl;
			}*/
			break;
		default:
			cout << "ERROR CODE 568x4T0F - Please check System Docs to understand what it means !" << endl;
			return 1;
			break;
	}
	return 0;
}