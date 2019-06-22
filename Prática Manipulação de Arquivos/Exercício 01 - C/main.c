/*
	Feito por: Felipe Fontenele de Ávila Magalhães
	Data: 21/04/2016
	Disciplina: BCC 203 - Estrutura de Dados II
	Prof.: Guilherme Tavares de Assis
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct
{
	float nota1,nota2,nota3;
	char mat[4],nome[31];
}Aluno;

int main()
{
	char opcao;
	Aluno aluno;

	FILE *arq ;
	if((arq = fopen("alunos.bin" , "wb")) == NULL)
	{
		printf("Erro na criacao do arquivo.\n");
		exit(1);
	}
	do{
		printf("\nDigite o numero de matricula do aluno(maximo 03 caracteres):\n");
		scanf("%s",aluno.mat);
		fflush(stdin);
		printf("\nDigite o nome do aluno(maximo 30 caracteres):\n");
		scanf("%[A-Z a-z]",aluno.nome);
		printf("\nDigite a primeira nota do aluno:\n");
		scanf("%f",&aluno.nota1);
		printf("\nDigite a segunda nota do aluno:\n");
		scanf("%f",&aluno.nota2);
		printf("\nDigite a terceira nota do aluno:\n");
		scanf("%f",&aluno.nota3);
		fwrite(&aluno,sizeof(aluno),1,arq);
		printf("\nDeseja adicionar mais dados de alunos? (S/N)\n");
		fflush(stdin); 
		scanf("%c",&opcao);
	}while(toupper(opcao)!='N');
	fclose(arq);	
	
	FILE *arq2;
	float media;
	if((arq2 = fopen("alunos.bin" , "r"))==NULL)
	{
		printf("\nErro na abertura do arquivo.\n");
		return 0;
	}
	while(fread(&aluno,sizeof(aluno),1,arq2) == 1)
	{
		media = (aluno.nota1 + aluno.nota2 + aluno.nota3)/3;
		printf("\nMATRICULA: %s\n",aluno.mat);
		printf("NOME: %s\n",aluno.nome);
		printf("MEDIA: %.1f\n",media);
		if(media>=8.5)
		{
			printf("CONCEITO: EXCELENTE\n");
		}
		else
		{
			if(media>=7.0)
			{
				printf("CONCEITO: BOM\n");
			}
			else
			{
				printf("CONCEITO: PREOCUPANTE\n");
			}
		}
	}
	fclose(arq2);
	return 0;
}