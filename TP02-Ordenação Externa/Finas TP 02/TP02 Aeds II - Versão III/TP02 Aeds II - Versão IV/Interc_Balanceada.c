#include "Interc_Balanceada.h"

void ordenar_blocos(FILE *arq, FILE **saida, int cont)
{
	int i,cont2=0;
	TipoBloco bloco;
	TipoReg reg;
	//printf("af");
	while(fread(&reg,sizeof(TipoReg),1,arq))
	{
		
		//printf("Reg: %ld \n",reg.mat);
		bloco.v[cont2] = reg;
		bloco.n = cont2+1;
		//printf("Bloco: %ld \n",bloco.v[cont2].mat);
		cont2++;
		if(cont2==10)
		{
			break;
		}
	}
	//printf("ante\n");
	Insertion(&bloco,cont2);

	//printf("Dep\n");
	for(i=0; i<cont2; i++)
	{
		reg = bloco.v[i];
		fwrite(&bloco,sizeof(TipoBloco),1,saida[cont]);
		//printf("Bloco: %ld \n",bloco.v[i].mat);
	}
}

void Insertion(TipoBloco *bloco,int tam)
{
	int i,j,temp;
	TipoReg aux;
	//Sem sentinela.
	for(i=1;i<tam;i++)
	{
		aux = bloco->v[i];
		temp = bloco->pertence[i];
		j = i-1;
		
		while(j>=0 && aux.nota > bloco->v[j].nota)
		{
			bloco->v[j+1] = bloco->v[j];
			bloco->pertence[j+1] = bloco->pertence[j];
			j--;
		}
		bloco->v[j+1]= aux;
		bloco->pertence[j+1] = temp;
	}
}

void intercalar_blocos(FILE **fitas,int tam)
{
	int i;
	TipoReg reg;
	TipoBloco bloco;
	
	for(i=0; i<tam; i++)
	{
		
		fread(&reg,sizeof(TipoReg),1,fitas[i]);
		bloco.v[i] = reg;
		bloco.pertence[i] = i;
		printf("Bloco, Matricula: %ld Nota: %.1f\n",bloco.v[i].mat,bloco.v[i].nota);
		printf("Pertence: %d\n",bloco.pertence[i]);
	}
	Insertion(&bloco, 10);
	/*printf("\n\nPertence: %d\n",bloco.pertence[0]);
	printf("Pertence: %d\n",bloco.pertence[5]);*/

	reg = bloco.v[0];
	
	fwrite(&reg,sizeof(TipoReg),1,fitas[11]);
	
	

	
	
}