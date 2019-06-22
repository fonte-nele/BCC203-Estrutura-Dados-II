/*
	Feito por: Felipe Fontenele de Ávila Magalhães
	Data: 22/04/2016
	Disciplina: BCC 203 - Estrutura de Dados II
	Prof.: Guilherme Tavares de Assis
*/
#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE *arq ;
	if((arq = fopen("numeros.bin" , "wb")) == NULL)
	{
		printf("Erro na criacao do arquivo.\n");
		return 0;
	}
    for(int i=0; i<=100; i++)
    {
        fwrite(&i,sizeof(i),1,arq);
    }
    fclose(arq);
    
    //Abertura do arquivo transferindo os numeros pares!!!
    FILE *arq2,*arq3;
    int temp;
    if((arq2 = fopen("numeros.bin", "rb")) == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        return 0;
    }
    if((arq3 = fopen("pares.bin", "wb")) == NULL)
    {
        printf("Erro na criacao do arquivo pares.bin \n");
        return 0;
    }
    while(fread(&temp,sizeof(temp),1,arq2) == 1)
    {
        //printf("%d\n",temp);
        if(temp%2 == 0)
        {
            fwrite(&temp,sizeof(temp),1,arq3);
        }
    }
    fclose(arq2);
    fclose(arq3);
    return 0;
}
