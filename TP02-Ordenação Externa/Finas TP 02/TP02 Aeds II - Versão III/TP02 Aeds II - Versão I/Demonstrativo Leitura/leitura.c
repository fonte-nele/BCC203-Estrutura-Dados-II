#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	long mat;
	float nota;
	char estado[3];
	char cidade[51];
	char curso[31];
}Dados;

int main()
{
	FILE *arq;
	Dados dados;
	if((arq = fopen("PROVAO.txt","r"))==NULL)
	{
		printf("\nErro abertura.\n\n");
		return 0;
	}
	int cont=0;
	while(fscanf(arq,"%ld %f %[A-Z a-z '-] %[A-Z a-z] %[A-Z a-z]\n",&dados.mat,&dados.nota,dados.estado,dados.cidade,dados.curso)!= EOF)
	{
		printf("Mat: %ld Curso: %s\n",dados.mat,dados.curso);
		cont++;
		if(cont == 100)
		{
			break;
		}
	}
	
	printf("FIM\n");
	fclose(arq);
	return 0;
}