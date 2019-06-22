/*
	Feito por: Felipe Fontenele de Ávila Magalhães
	Data: 22/04/2016
	Disciplina: BCC 203 - Estrutura de Dados II
	Prof.: Guilherme Tavares de Assis
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct
{
    int chave;
    char nome[30];
    float valor[4];
}Dados;

int main()
{
    FILE *arq;
    if((arq = fopen("dados.bin","wb")) == NULL)
    {
        printf("Erro na criacao do arquivo!!!");
        return 0;
    }
    Dados dados;
    char opcao;
    do{
		printf("Digite a chave do registro:\n");
		fflush(stdin);
		scanf("%d",&dados.chave);
		printf("\nDigite o nome do registro:\n");
		fflush(stdin);
		scanf("%s",dados.nome);
		printf("\nDigite dado vetor 1\n");
		fflush(stdin);
		scanf("%f",&dados.valor[0]);
        printf("\nDigite dado vetor 2\n");
		fflush(stdin);
		scanf("%f",&dados.valor[1]);
        printf("\nDigite dado vetor 3\n");
		fflush(stdin);
		scanf("%f",&dados.valor[2]);
        printf("\nDigite dado vetor 4\n");
		fflush(stdin);
		scanf("%f",&dados.valor[3]);
		fwrite(&dados,sizeof(dados),1,arq);
		printf("\nDeseja adicionar mais dados de alunos? (S/N)\n");
		fflush(stdin); 
		scanf("%c",&opcao);
	}while(toupper(opcao)=='S');
    fclose(arq);
    
    FILE *arq2,*arq3;
    if((arq2 = fopen("dados.bin","rb")) == NULL)
    {
        printf("Erro na abertura do arquivo");
        return 0;
    }
    if((arq3 = fopen("temp.bin","wb")) == NULL)
    {
        printf("\nErro na criacao do arquivo temp.bin!\n");
        return 0;
    }
    int chave_desejada,cont2=0;
    printf("Digite a chave que deseja procurar no arquivo.\n");
    scanf("%d",&chave_desejada);
    while(fread(&dados,sizeof(dados),1,arq2) == 1)
    {
        if(dados.chave != chave_desejada)
        {
            fwrite(&dados,sizeof(dados),1,arq3);
        }
        else
        {
            cont2++;
        }
    }
    if(cont2>0)
    {
        printf("\nTRUE. Dados removidos do registro.\n");
    }
    else
    {
        printf("\nFALSE. Chave digitada nao existente nos registros.\n");
    }
    fclose(arq2);
    fclose(arq3);
    remove("dados.bin");
    rename("temp.bin","dados.bin");
    return 0;
}