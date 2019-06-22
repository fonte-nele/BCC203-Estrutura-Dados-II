#include "arvore_b.h"

void inicializar(Apont *Arvore)
{
	(*Arvore) = NULL;
}

void inserir_pagina(Apont apont,Registro reg,Apont ap_dir, long *comp)
{
	short verificar_pos;
	int k;
	k = apont->n;
	verificar_pos = (k>0);
	while(verificar_pos)
	{
		(*comp)++;
		if(reg.chave >= apont->registro[k-1].chave)
		{
			verificar_pos = FALSE;
			break;
		}
		apont->registro[k] = apont->registro[k-1];
		apont->pagina[k+1] = apont->pagina[k];
		k--;
		if(k<1)
		{
			verificar_pos = FALSE;
		}
	}
	apont->registro[k] = reg;
	apont->pagina[k+1] = ap_dir;
	apont->n++;
}

void ins_aux(Registro reg,Apont apont,short *cresce,Registro *reg_retorno,Apont *ap_retorno, long *comp)
{
	long i=1,j;
	Apont temp;
	if(apont == NULL)
	{
		(*cresce) = TRUE;
		(*reg_retorno) = reg;
		(*ap_retorno) = NULL;
		return;
	}
	while(i<apont->n && reg.chave > apont->registro[i-1].chave)
	{
		(*comp)++;
		i++;
	}
	(*comp)+=2; 	//Ultima comparação while
	if(reg.chave == apont->registro[i-1].chave)
	{
		(*cresce) = FALSE;
		return;
	}
	(*comp)++;
	if(reg.chave < apont->registro[i-1].chave)
	{
		i--;
	}
	ins_aux(reg,apont->pagina[i],cresce,reg_retorno,ap_retorno, comp);
	if(!(*cresce))
	{
		return;
	}
	if(apont->n < MM)
	{
		inserir_pagina(apont,*reg_retorno,*ap_retorno,comp);
		(*cresce) = FALSE;
		return;
	}
	//Pagina tem que ser dividida!
	temp = (Apont)malloc(sizeof(Pagina));
	temp->n = 0;
	temp->pagina[0] = NULL;
	
	if(i< M+1)
	{		
		inserir_pagina(temp,apont->registro[MM-1],apont->pagina[MM],comp);
		apont->n--;
		inserir_pagina(apont, *reg_retorno, *ap_retorno,comp);
	}
	else
	{
		inserir_pagina(temp, *reg_retorno, *ap_retorno,comp);
	}
	for(j = M+2; j<= MM; j++)
	{		
		inserir_pagina(temp, apont->registro[j-1], apont->pagina[j],comp);
	}
	apont->n = M;
	temp->pagina[0] = apont->pagina[M+1];
	*reg_retorno = apont->registro[M];
	*ap_retorno = temp;
}

void inserir(Registro reg,Apont *apont,long *comp)
{
	short cresceu;
	Registro reg_retorno;
	Pagina *ap_retorno, *ap_temp;
	ins_aux(reg, *apont, &cresceu, &reg_retorno, &ap_retorno, comp);

	if(cresceu)
	{
		ap_temp = (Pagina*)malloc(sizeof(Pagina));
		ap_temp->n = 1;
		ap_temp->registro[0] = reg_retorno;
		ap_temp->pagina[1] = ap_retorno;
		ap_temp->pagina[0] = *apont;
		*apont = ap_temp;
	}
}

int pesquisar(Registro *reg,Apont apont, long *comp)
{
	long i=1;
	if(apont == NULL)
	{
		//Nao encontrou o registro!
		return FALSE;
	}
	while(i<apont->n && reg->chave > apont->registro[i-1].chave)
	{
		(*comp)++;
		i++;
	}
	(*comp)++;
	if(reg->chave == apont->registro[i-1].chave)
	{
		(*reg) = apont->registro[i-1];
		return TRUE;
	}
	(*comp)++;
	if(reg->chave < apont->registro[i-1].chave)
	{
		return pesquisar(reg,apont->pagina[i-1],comp);
	}
	else
	{
		return pesquisar(reg,apont->pagina[i],comp);
	}
}

void caminhamento(Apont apont)
{
	int n=0;
	imprimir(apont,n);
}

void imprimir(Apont apont, int ramificacao)
{
	long i;
	if(apont == NULL)
	{
		return;
	}
	printf("Ramificacao %d : ",ramificacao);
	
	for(i=0; i<apont->n; i++)
	{
		printf("%d ",apont->registro[i].chave);
	}
	printf("\n");
	
	for(i=0; i<=apont->n; i++)
	{
		imprimir(apont->pagina[i],ramificacao+1);
	}
}

void imprimir(TipoApontador arvore)
{
	int i=0;
	
	if(arvore == NULL)
	{
		return;
	}
	//n à 0!
	//while(arvore->n => 0)
	while(i<=arvore->n)
	{
		imprimir(arvore->pagina[i]);
		if(i != arvore->n)
		{
			printf(arvore->registro[i].chave);
		}
		i++;
	}
}