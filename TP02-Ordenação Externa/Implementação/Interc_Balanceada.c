#include "Interc_Balanceada.h"

void construir_blocos(FILE *arq, FILE **saida, int cont, int pos, Analise *desempenho)
{
	int i,cont2=0;
	TipoBloco bloco;
	TipoReg reg;

	while(fread(&reg,sizeof(TipoReg),1,arq))
	{
        desempenho->Num_transf_read++;
		bloco.v[cont2] = reg;
		bloco.n = cont2+1;
		bloco.pertence[cont2] = pos;
		
		//printf("Bloco, Matricula: %ld Nota: %.1f\n",bloco.v[cont2].mat,bloco.v[cont2].nota);
		//printf("Pertence: %d\n",bloco.pertence[cont2]);
		
		cont2++;
		if(cont2==10)
		{
			break;
		}
	}
	//printf("Saiu\n\n");
	Insertion(&bloco,cont2,desempenho);
	
	for(i=0; i<cont2; i++)
	{
		reg = bloco.v[i];
		fwrite(&bloco,sizeof(TipoBloco),1,saida[cont]);
        desempenho->Num_transf_write++;
	}
}

void Insertion(TipoBloco *bloco,int tam, Analise *desempenho)
{
	int i,j,temp;
	TipoReg aux;
	//Sem sentinela.
	for(i=1;i<tam;i++)
	{
		aux = bloco->v[i];
		temp = bloco->pertence[i];
		j = i-1;
		
        desempenho->Num_comparacoes++;
		while(j>=0 && aux.nota > bloco->v[j].nota)
		{
            desempenho->Num_comparacoes++;
			bloco->v[j+1] = bloco->v[j];
			bloco->pertence[j+1] = bloco->pertence[j];
			j--;
		}
		bloco->v[j+1]= aux;
		bloco->pertence[j+1] = temp;
	}
}

void intercalar_blocos(FILE **fitas,int tam, Analise *desempenho)
{
	int i,j=0;
	TipoReg reg;
	TipoBloco bloco;
	
	for(i=0; i<tam; i++)
	{
		fread(&reg,sizeof(TipoReg),1,fitas[i]);
        desempenho->Num_transf_read++;
		bloco.v[j] = reg;
		bloco.pertence[j] = j;
		//printf("Bloco, Matricula: %ld Nota: %.1f\n",bloco.v[j].mat,bloco.v[j].nota);
		//printf("Pertence: %d\n",bloco.pertence[j]);
		if(j==9)
		{
			j=0;
		}
	}
	Insertion(&bloco, 10,desempenho);
	/*printf("\n\nPertence: %d\n",bloco.pertence[0]);
	printf("Pertence: %d\n",bloco.pertence[5]);*/
	i=0;
	for(i=0; i<tam; i++)
	{
		reg = bloco.v[i];
		fwrite(&reg,sizeof(TipoReg),1,fitas[11]);
        desempenho->Num_transf_write++;

		//printf("Bloco Saida, Matricula: %ld Nota: %.1f\n",reg.mat,reg.nota);
	}
}