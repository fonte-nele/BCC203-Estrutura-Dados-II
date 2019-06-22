/*
	Feito por: Felipe Fontenele de Ávila Magalhães
	Data: 21/04/2016
	Disciplina: BCC 203 - Estrutura de Dados II
	Prof.: Guilherme Tavares de Assis
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct
{
	char sexo,fumante;
	int idade;
}Quest;

int main()
{
	char opcao;
	Quest respostas;
	
	FILE *arq ;
	if((arq = fopen("resposta.bin" , "wb")) == NULL)
	{
		printf("Erro na criacao do arquivo.\n");
		return 0;
	}
	do{
		printf("\nDigite o sexo do entrevistado(M/F):\n");
		fflush(stdin);
		scanf("%c",&respostas.sexo);
		printf("\nDigite a idade do entrevistado:\n");
		fflush(stdin);
		scanf("%d",&respostas.idade);
		printf("\nO entrevistado eh fumante?(S/N)\n");
		fflush(stdin);
		scanf("%c",&respostas.fumante);
		fwrite(&respostas,sizeof(respostas),1,arq);
		printf("\nDeseja adicionar mais dados de alunos? (S/N)\n");
		fflush(stdin); 
		scanf("%c",&opcao);
	}while(toupper(opcao)!='N');
	fclose(arq);
	
	FILE *arq2;
	float cont1=0,cont2=0,cont3=0,cont4=0,cont5=0,total=0;
	if((arq2 = fopen("resposta.bin" , "r"))==NULL)
	{
		printf("\nErro na abertura do arquivo.\n");
		return 0;
	}
	while(fread(&respostas,sizeof(respostas),1,arq2) == 1)
	{
		if(toupper(respostas.fumante)=='S')
		{
			cont1++;
			if(toupper(respostas.sexo) =='F')
			{
				if(respostas.idade>40)
				{
					cont3++;
				}
			}
		}
		else
		{
			if(toupper(respostas.sexo)=='M')
			{
				if(respostas.idade<40)
				{
					cont5++;
				}
			}
		}
		if(toupper(respostas.sexo)=='F')
		{
			cont2++;
		}
		else
		{
			cont4++;
		}
		total++;
	}
	fclose(arq2);
	printf("\nPERCENTUAL DE FUMANTES EM RELACAO AO NUMERO TOTAL DE PESSOAS: %.1f\n", cont1/(total/100.0));
	printf("\nPERCENTUAL DE HOMENS NAO FUMANTES ABAIXO DE 40 ANOS EM RELACAO AO NUMERO TOTAL DE HOMENS: %.1f\n", cont5/(cont4/100.0));
	printf("\nPERCENTUAL DE MULHERES FUMANTES ACIMA DE 40 ANOS EM RELACAO AO NUMERO TOTAL DE MULHERES: %.1f\n", cont3/(cont2/100.0));
	return 0;
}
