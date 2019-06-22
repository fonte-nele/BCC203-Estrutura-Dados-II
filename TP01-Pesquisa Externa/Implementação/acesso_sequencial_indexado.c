#include "acesso_sequencial_indexado.h"

int pesquisa(Indice *tab, int tam, Item *item, FILE *arq, long *comp, long *trans)
{
    Item pagina[NUM_ITENS_PAG];
    int i=0, quant;
    long desloc;
    
    while(i < tam && tab[i].chave_indice <= item->chave_item)
    {
        i++;
    }
    if(i==0)
    {
        return FALSE;
    }
    else
    {
        if((arq = fopen("numeros.bin", "rb")) == NULL)
        {
            return -1;
        }
        if(i<tam)
        {
            quant = NUM_ITENS_PAG;
        }
        else
        {
            fseek(arq, 0, SEEK_END);
            quant = (ftell(arq)/sizeof(Item)) % NUM_ITENS_PAG;
            //Pagina esta completa!
			if(quant == 0)
            {
                quant = NUM_ITENS_PAG;
            }
        }
		
        desloc = ((i-1)*NUM_ITENS_PAG) * sizeof(Item);
		fseek(arq, desloc, SEEK_SET);
        fread(&pagina, sizeof(Item), quant, arq);
        (*trans)++;
		fclose(arq);
        
		int pos = busca_binaria(item->chave_item,pagina,0,quant,comp);
		if(pos!= -1)
		{
			*item = pagina[pos];
			return TRUE;
		}
		//Nao encontrou a chave!
        return FALSE;
    }
}

int busca_binaria(int pesq,Item *vet,int esq,int dir, long *comp)
{
	int meio = (esq+dir)/2;
	if(vet[meio].chave_item!=pesq &&esq>=dir)
	{
		return -1;
	}
	else
	{
		if(pesq>vet[meio].chave_item)
		{
			(*comp)++;
			return busca_binaria(pesq,vet,meio+1,dir,comp);
		}
		else
		{
			if(pesq<vet[meio].chave_item)
			{
				(*comp)++;
				return busca_binaria(pesq,vet,esq,meio-1,comp);
			}
			else
			{
				(*comp)++;
				return meio;
			}
		}
	}
}