#include "arvore_binaria.h"

int inserir_arv_binaria(FILE* arvore, TBinaria registro, Dados_arv_bin dados, int cont, int sit, long *transf, long *comp)
{
	//Registro a ser inserido na arvore!
	registro.no = dados;
	registro.esq = -1;
	registro.dir = -1;
	fseek(arvore, 0, SEEK_END);
	fwrite(&registro, sizeof(TBinaria), 1, arvore);
	
	long aux;
	
	if(sit == 1 || sit == 2)
	{
		//Trapaca na criacao da arvore! Dados crescentes ou decrescentes!
		//Volta ao penultimo no da arvore!
		aux = sizeof(TBinaria);
		fseek(arvore, -2*aux, SEEK_CUR);
		fread(&registro, sizeof(TBinaria), 1, arvore);
		(*transf)++;
		//Voltar novamente ao penultimo no!
		fseek(arvore, -aux, SEEK_CUR);
	}
	else
	{
		//Voltar ao inicio da arvore, lê o nó da raiz e voltar para o inicio!
		rewind(arvore);
		fread(&registro, sizeof(TBinaria), 1, arvore);
		(*transf)++;
		rewind(arvore);
	}
	
	while(TRUE)
	{
		//Verifica a posicao do novo regitro!
		(*comp)++;
		if(dados.chave < registro.no.chave)
		{
			if(registro.esq == -1)
			{
				registro.esq = cont;
				fwrite(&registro, sizeof(TBinaria), 1, arvore); //Salva o nó modificado
				break;
			}
			else
			{
				aux = sizeof(TBinaria);
				fseek(arvore, registro.esq*sizeof(TBinaria), SEEK_SET);
				fread(&registro, sizeof(TBinaria), 1, arvore);
				(*transf)++;
				fseek(arvore, -aux, SEEK_CUR); //Retorna ao inicio do nó encontrado no fseek anterior
			}
		}
		else
		{
			if(registro.dir == -1)
			{
				registro.dir = cont;
				fwrite(&registro, sizeof(TBinaria), 1, arvore);
				break;
			}
			else
			{
				aux = sizeof(TBinaria);
				fseek(arvore, registro.dir*sizeof(TBinaria), SEEK_SET);
				fread(&registro, sizeof(TBinaria), 1, arvore);
				(*transf)++;
				fseek(arvore, -aux, SEEK_CUR);
			}
		}
	}
	return TRUE;
}

int pesquisar_arv_binaria(FILE *arvore, TBinaria registro, Dados_arv_bin *dados, long *transf, long *comp)
{
	while(fread(&registro,sizeof(TBinaria),1,arvore)==1)
	{
		(*transf)++;
		if(dados->chave == registro.no.chave)
		{
			(*comp)++;
			*dados = registro.no;
			return TRUE;
		}
		else
		{
			if(dados->chave < registro.no.chave)
			{
				(*comp)++;
				if (registro.esq != -1)
				{
					fseek(arvore,registro.esq*sizeof(TBinaria),SEEK_SET);
				}
				else
				{
					//Atingiu nó folha!
					return FALSE;
				}
			}
			else
			{
				(*comp)++;
				if(registro.dir != -1)
				{	
					fseek(arvore,registro.dir*sizeof(TBinaria),SEEK_SET);
				}
				else
				{
					//Atingiu nó folha!
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}