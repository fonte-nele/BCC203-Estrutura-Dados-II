#include "Interc_Balanceada_Sub.h"

void construir_blocos_sub(FILE *arq, FILE **saida, int cont, int pos)
{
	int i,cont2=0;

	Bloco bloco;
	Registro reg;

	while(fread(&reg,sizeof(Registro),1,arq))
	{
		bloco.v[cont2] = reg;
		bloco.n = cont2+1;
		bloco.pertence[cont2] = pos;
		
		printf("Bloco, Matricula: %ld Nota: %.1f\n",bloco.v[cont2].mat,bloco.v[cont2].nota);
		printf("Pertence: %d\n",bloco.pertence[cont2]);
		
		cont2++;
		if(cont2==10)
		{
			break;
		}
	}
	printf("Saiu\n\n");
	//Insertion(&bloco,cont2);
	
	for(i=0; i<cont2; i++)
	{
		reg = bloco.v[i];
		fwrite(&bloco,sizeof(Bloco),1,saida[cont]);
	}
}
