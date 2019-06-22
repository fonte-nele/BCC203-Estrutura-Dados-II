#include "exe04.h"

void gerar_dados(FILE *arq,Votos *votos)
{
	int i,temp;
	srand(time(NULL));
	for(i=0; i<100; i++)
	{
		temp = rand()%6 + 1;
		
		if(i != 99)
		{
			fprintf(arq,"%d\n",temp);
		}
		else
		{
			fprintf(arq,"%d",temp);
		}
	}
	//Inicializar contadores!!!
	votos->cont1 = 0;
	votos->cont2 = 0;
	votos->cont3 = 0;
	votos->cont4 = 0;
	votos->cont5 = 0;
	votos->cont6 = 0;
}

void leitura_votos(FILE *arq,Votos *votos)
{
	int i=0;
	while(fscanf(arq,"%d\n",&votos->v[i])!=EOF)
	{
		if(votos->v[i]==1)
		{
			votos->cont1 += 1;
		}
		else
		{
			if(votos->v[i]==2)
			{
				votos->cont2 += 1;
			}
			else
			{
				if(votos->v[i]==3)
				{
					votos->cont3 += 1;
				}
				else
				{
					if(votos->v[i]==4)
					{
						votos->cont4 += 1;
					}
					else
					{
						if(votos->v[i]==5)
						{
							votos->cont5 += 1;
						}
						else
						{
							votos->cont6 += 1;
						}
					}
				}
			}
		}
		i++;
	}
}

void verificar_votos(Votos *votos)
{
	printf("\n");
	printf("CANDIDATO MAIS VOTADO: \n");
	
	if(votos->cont1>votos->cont2 && votos->cont1>votos->cont3 && votos->cont1>votos->cont4 && votos->cont1>votos->cont5)
	{
		printf("Codigo: 1 Quantidades votos: %d\n",votos->cont1);
	}
	else
	{
		if(votos->cont2>votos->cont1 && votos->cont2>votos->cont3 && votos->cont2>votos->cont4 && votos->cont2>votos->cont5)
		{
			printf("Codigo: 2 Quantidades votos: %d\n",votos->cont2);
		}
		else
		{
			if(votos->cont3>votos->cont1 && votos->cont3>votos->cont2 && votos->cont3>votos->cont4 && votos->cont3>votos->cont5)
			{
				printf("Codigo: 3 Quantidades votos: %d\n",votos->cont3);
			}
			else
			{
				if(votos->cont4>votos->cont1 && votos->cont4>votos->cont2 && votos->cont4>votos->cont3 && votos->cont4>votos->cont5)
				{
					printf("Codigo: 4 Quantidades votos: %d\n",votos->cont4);
				}
				else
				{
					printf("Codigo: 5 Quantidades votos: %d\n",votos->cont5);
				}
			}
		}
	}
	
	printf("\n");
	printf("CANDIDATO MENOS VOTADO: \n");
	if(votos->cont1<votos->cont2 && votos->cont1<votos->cont3 && votos->cont1<votos->cont4 && votos->cont1<votos->cont5)
	{
		printf("Codigo: 1 Quantidades votos: %d\n",votos->cont1);
	}
	else
	{
		if(votos->cont2<votos->cont1 && votos->cont2<votos->cont3 && votos->cont2<votos->cont4 && votos->cont2<votos->cont5)
		{
			printf("Codigo: 2 Quantidades votos: %d\n",votos->cont2);
		}
		else
		{
			if(votos->cont3<votos->cont1 && votos->cont3<votos->cont2 && votos->cont3<votos->cont4 && votos->cont3<votos->cont5)
			{
				printf("Codigo: 3 Quantidades votos: %d\n",votos->cont3);
			}
			else
			{
				if(votos->cont4<votos->cont1 && votos->cont4<votos->cont2 && votos->cont4<votos->cont3 && votos->cont4<votos->cont5)
				{
					printf("Codigo: 4 Quantidades votos: %d\n",votos->cont4);
				}
				else
				{
					printf("Codigo: 5 Quantidades votos: %d\n",votos->cont5);
				}
			}
		}
	}
	
	printf("\n");
	printf("Quantidade de votos nulos: %d\n",votos->cont6);
}