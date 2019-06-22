/*
--------------------------------------------------------------------------------------------------------------------------------------------

Programa implementado em linguagem C para implementação referente a ordenação externa de arquivos. Com os seguintes métodos : Intercalação Balanceada com Seleção por Substituição com os seguintes requisitos :

-> Número de caminhos f, igual a 6;
-> Utilizando arquivos para simular as fitas de entrada/saída;
-> A ordenação será repetida duas vezes, com 2 * fitas e , em seguida f+1, para o mesmo arquivo;
-> Será medido o tempo para cada execução de ordenação;
-> Dados ordenados será armazenado em um arquivo de saída;
-> Apresentando na tela o tempo gasto para a ordenação em cada uma das execuções.

--------------------------------------------------------------------------------------------------------------------------------------------

curso: Ciência da Computação
Data: 14 de fevereiro de 2013
Disciplina: Estrutura de Dados II
Aluna : Silvana Trindade
e-mail : syletri@gmail.com

--------------------------------------------------------------------------------------------------------------------------------------------
*/
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include "order.h"


int main(int argc, char *argv[]) 
{
	if(argc < 2)
	{
		printf("Arquivo não especificado\n\n");
		exit(1);
	}
	FILE *teste = fopen(argv[1],"r");
	
	if(teste == NULL)
	{
		printf("Arquivo não existe ou não tem permissão para leitura\n\n");
		exit(1);
	}
	doisVezesFitas(argv[1]);
	
	//fMaisUmaFita(argv[1]); 
		
	return 0;
}
