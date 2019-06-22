/*
	Feito por: Felipe Fontenele de Ávila Magalhães
	Data: 21/04/2016
	Disciplina: BCC 203 - Estrutura de Dados II
	Prof.: Guilherme Tavares de Assis
*/
#include "exe03.h"

int main()
{
	printf("\n\n");
	printf("                                       EXERCICIO 3                                              \n");
	printf("   ============================================================================================ \n");
	printf("  || Neste programa, trabalha-se o conceito de arquivo.txt. Neste codigo eh aberto o arquivo  ||\n");
	printf("  || 'temperat.txt' que antes foi gerado aleatoriamente as temperaturas de 121 dias.O objetivo||\n");
	printf("  || eh determinar qual foi a menor,a maior temperatura ocorrida e tambem a temperatura media ||\n");
	printf("  || seguido da quantidade de dias em que a temperatura foi acima e abaixo da media.          ||\n");
	printf("  ||                                                                   Felipe Fontenele       ||\n");
	printf("   ============================================================================================ \n\n");
	
	Temp *temperatura;
	temperatura = (Temp*)malloc(sizeof(Temp));
	FILE *arq;
	if((arq = fopen("temperat.txt", "w+")) == NULL)
	{
		printf("Erro na criacao do arquivo!!!\n");
		exit(1);
	}
	gerar_dados(arq,temperatura);
	fclose(arq);
	
	if((arq = fopen("temperat.txt", "r")) == NULL)
	{
		printf("Erro na abertura do arquivo!!!\n");
		exit(1);
	}
	leitura_temp(arq,temperatura);
	verificar_temp(temperatura);
	
	fclose(arq);
	free(temperatura);
	return 0;
}