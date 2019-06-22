#include "gerador.h"
#define mm 4
#include "arvoreB.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>


using namespace std;
void Inicializa(TApontador arvore)
{
    arvore = NULL;
}
void InsereNapagina(TApontador ap, TDados dados, TApontador apDir, int *indiceContComp)
{
	short NaoAchouPosicao;
	int k;
	k = ap->numItensPagina;
	NaoAchouPosicao = (k > 0);
	while (NaoAchouPosicao)
    {
		(*indiceContComp)++;
		if (dados.chave >= ap->dados[k-1].chave)	// Compara se a chave do dadosistro a ser inserido na p√°gina √© maior ou igual a √∫ltima chave presente na p√°gina
		{
			NaoAchouPosicao = false;
			break;
		}
		ap->dados[k] = ap->dados[k-1];	// Transfere o dadosistro da posi√ß√£o (k-1) para uma posi√ß√£o a frente,
		ap->ponteiro[k+1] = ap->ponteiro[k];	// consequentemente o apontador tamb√©m √© transferido
		k--;
		if (k < 1)
			NaoAchouPosicao = false;
	}
	ap->dados[k] = dados;	// Copia o novo dadosistro para a posiÁ„o liberada acima
	ap->ponteiro[k+1] = apDir;	// Atualiza o apontador direito desse novo dadosistro
	ap->numItensPagina++;	// Incrementa a quantidade de registros na pagina
}

void Ins(TDados dados, TApontador ap, short *cresceu, TDados *dadosRetorno, TApontador *apRetorno, int *indiceContComp)
{
	long i = 1;
	long j;
	TApontador apTemp;
	if (ap == NULL)// Verifica se ap √© NULL, caso seja, uma p√°gina folha foi atingida
	{
		*cresceu = true;
		(*dadosRetorno) = dados;
		(*apRetorno) = NULL;
		return;
	}
	while (i < ap->numItensPagina && dados.chave > ap->dados[i-1].chave)
    {	// Varre a p√°gina enquanto o dadosistrador i for menor que a quantidade de dadosistros dessa p√°gina e enquanto a chave a ser inserida for maior do que uma das chaves presentes na p√°gina
		i++;
		(*indiceContComp)++;
	}
	(*indiceContComp) += 2; //Incrementa a ultima comparacao feita no while juntamente com o if da proxima linha
	if (dados.chave == ap->dados[i-1].chave)
	{	// Verifica se o dadosistro a ser inserido j√° se encontra na √°rvore
		cout << "Erro: dado ja esta presente" << endl;
		*cresceu = false;
		return;
	}
	(*indiceContComp)++;
	if (dados.chave < ap->dados[i-1].chave)
        i--;	// Verifica se o dado a ser inserido possui chave menor que a do utimo dado verificado na p·gina
	Ins(dados, ap->ponteiro[i], cresceu, dadosRetorno, apRetorno, indiceContComp);	// Faz a chamada recursiva atÈ que uma p·gina folha seja atingida

	if (!*cresceu)	// Se a p·gina folha n„oo foi atingida retorna
		return;
	if (ap->numItensPagina < mm)	// Verifica se a p·gina tem espaÁo para inserÁ„o de um novo registro
	{
		InsereNapagina(ap, *dadosRetorno, *apRetorno, indiceContComp);
		*cresceu = false;
		return;
	}
	// A partir desse ponto, a p·gina folha È dividida, uma vez que seu tamanho maximo de dadosistros foi excedido
	apTemp = (TApontador)malloc(sizeof(TipoPagina));
	apTemp->numItensPagina = 0;
	apTemp->ponteiro[0] = NULL;
	if (i < (mm/2 + 1))
    {	// Insere metade dos dadosistros da p√°gina cheia para a nova p√°gina criada
		InsereNapagina(apTemp, ap->dados[mm -1], ap->ponteiro[mm], indiceContComp);
		ap->numItensPagina--;
		InsereNapagina(ap, *dadosRetorno, *apRetorno, indiceContComp);
	}
	else
		InsereNapagina(apTemp, *dadosRetorno, *apRetorno, indiceContComp);
	for(j = mm/2+2; j <=mm; j++)
		InsereNapagina(apTemp, ap->dados[j-1], ap->ponteiro[j], indiceContComp);
	ap->numItensPagina = mm/2;	// Atualiza a quantidade de dados na p·gina
	apTemp->ponteiro[0] = ap->ponteiro[mm/2+1];
	*dadosRetorno = ap->dados[mm/2];	// Retorna o registro do meio para a pagina pai
	*apRetorno = apTemp;
}

void InsereArvoreB(TDados dados, TApontador *ap, int *indiceContComp)
{
	short cresceu;
	TDados dadosRetorno;
	TipoPagina *apRetorno, *apTemp;
	Ins(dados, *ap, &cresceu, &dadosRetorno, &apRetorno, indiceContComp);
	if (cresceu)// Neste ponto a raiz È dividida e È gerada uma nova raiz. A altura da arvore aumenta.
    {
		apTemp = (TipoPagina*) malloc (sizeof(TipoPagina));
		apTemp->numItensPagina = 1;
		apTemp->dados[0] = dadosRetorno;
		apTemp->ponteiro[1] = apRetorno;
		apTemp->ponteiro[0] = *ap;
		*ap = apTemp;
	}
}
void PesquisaArvoreB(TDados *dados, TApontador ap, int aux, int *pesqContComp, int *ver)
{
	long i = 1;
	if (ap == NULL)
		return;
	//Varre a p·gina enquanto o n˙mero de registros presentes n„o seja extrapolado
	//...e enquanto a chave pesquisada n„o seja maior que a chave comparada na p·gina
	while (i < ap->numItensPagina && dados->chave > ap->dados[i-1].chave)
    {
		if (aux)
			cout << ap->dados[i-1].chave << ", ";
		i++;
		(*pesqContComp)++;
	}
	(*pesqContComp)++; // Incrementa a ultima comparacao feita no while
	if (aux)
		cout << ap->dados[i-1].chave << ", ";
	(*pesqContComp)++;
	if (dados->chave == ap->dados[i-1].chave)// Retorna o dado e a situaÁ„o de sucesso na pesquisa
	{
		*dados = ap->dados[i-1];
		*ver = 1;
		return;
	}
	(*pesqContComp)++;
	if (dados->chave < ap->dados[i-1].chave)	// Faz a chamada recursiva pelo lado esquerdo da Arvore
		PesquisaArvoreB(dados, ap->ponteiro[i-1], aux, pesqContComp, ver);
	else
		PesquisaArvoreB(dados, ap->ponteiro[i], aux, pesqContComp, ver);  // Faz a chamada recursiva pelo lado direito da Arvore
}



