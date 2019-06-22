#include "exe03.h"

void gerar_dados(FILE *arq,Temp *temperatura)
{
	int i;
	double temp1,temp2,temp3;
	srand(time(NULL));
	for(i=0; i<n; i++)
	{
		temp1 = rand()%24 +15;
		if(temp1==15 || temp1==39)
		{
			if(temp1==15)
			{
				temp2 = rand()%5 + 5;
			}
			else
			{
				temp2 = rand()%8;
			}
		}
		else
		{
			temp2 = rand()%10;
		}
		temp3 = temp1 + (temp2/10);
		if(i!=n)
		{
			fprintf(arq,"%.1f\n",temp3);
		}
		else
		{
			fprintf(arq,"%.1f",temp3);
		}
	}
	//Inicializando variaveis da struct!!!
	temperatura->menor = 0;
	temperatura->maior = 0;
	temperatura->soma = 0;
}

void leitura_temp(FILE *arq,Temp *temperatura)
{
	int i=0;
	while(fscanf(arq,"%f\n",&temperatura->v[i])!=EOF)
	{
		if(i==0)
		{
			temperatura->menor = temperatura->v[i];
		}
		if(temperatura->maior < temperatura->v[i])
		{
			temperatura->maior = temperatura->v[i];
		}
		if(temperatura->menor > temperatura->v[i])
		{
			temperatura->menor = temperatura->v[i];
		}
		temperatura->soma += temperatura->v[i];
		i++;
	}
}

void verificar_temp(Temp *temperatura)
{
	int i,cont1=0,cont2=0;
	float media;
	media = temperatura->soma / n;
	for(i=0; i<n; i++)
	{
		if(temperatura->v[i] < media)
		{
			cont1++;
		}
		else
		{
			cont2++;
		}
	}
	
	printf("\n\n");
	printf("A menor temperatura ocorrida foi: %.1f\n\n",temperatura->menor);
	printf("A maior temperatura ocorrida foi: %.1f\n\n",temperatura->maior);
	printf("A temperatura media foi: %.1f\n\n",media);
	printf("O numero de dias nos quais a temperatura foi inferior a media foi: %d\n\n",cont1);
	printf("O numero de dias nos quais a temperatura foi superior a media foi: %d\n\n",cont2);
}