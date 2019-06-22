/*
	Feito por: Felipe Fontenele de Ávila Magalhães
	Data: 21/04/2016
	Disciplina: BCC 203 - Estrutura de Dados II
	Prof.: Guilherme Tavares de Assis
*/
#include "exe04.h"

int main()
{
	printf("\n\n");
	printf("                                       EXERCICIO 4                                              \n");
	printf("   ============================================================================================ \n");
	printf("  || Neste programa, trabalha-se o conceito de arquivo.txt. Neste codigo eh aberto o arquivo  ||\n");
	printf("  || 'votos.txt' que antes foi gerado aleatoriamente os votos de 100 eleitores. O objetivo    ||\n");
	printf("  || eh determinar qual foi o candidato(1,2,3,4 ou 5) que obteve mais votos e menos votos,    ||\n");
	printf("  || seguido da quantidade de votos nulos.                                                    ||\n");
	printf("  ||                                                                   Felipe Fontenele       ||\n");
	printf("   ============================================================================================ \n\n");
	
	Votos* votos;
	votos =(Votos*)malloc(sizeof(Votos));
	FILE *arq;
	if((arq = fopen("votos.txt", "w+")) == NULL)
	{
		printf("Erro na criacao do arquivo!!!\n");
		exit(1);
	}
	gerar_dados(arq,votos);
	fclose(arq);
	
	if((arq = fopen("votos.txt", "r")) == NULL)
	{
		printf("Erro na abertura do arquivo!!!\n");
		exit(1);
	}
	/*
	TESTE SCANF E PRINTF
	printf("Valor do printf %d\n\n",temp);
	scanf("%d",&temp);
	printf("Valor do printf 2 - %d",temp);
	*/
	
	leitura_votos(arq,votos);
	verificar_votos(votos);
	
	fclose(arq);
	free(votos);
	return 0;
}