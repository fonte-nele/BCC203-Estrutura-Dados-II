#define MM 100
#include <iostream>
#include <cstdlib>
#include "gerador.h"
#include "arvoreBEstrela.h"

using namespace std;

void inicializaBEstrela(TApEstrela Ap)
{
	Ap = NULL;
}

void insereNaPagina(TApEstrela Ap, TDados dados, TApEstrela ApDir, int *numComparacoesIndice)
{
	bool NaoAchouPosicao;
	int k;
	if (Ap->Pt == Interna)
	{  // Pagina Interna
		k = Ap->UU.U0.ni;
		NaoAchouPosicao = (k > 0);
		while (NaoAchouPosicao) //Enquanto true
		{
			(*numComparacoesIndice)++;
			if (dados.chave >= Ap->UU.U0.ri[k-1])
			{	// Verifica se a chave de busca eh maior ou igual a ultima da pagina
				NaoAchouPosicao = false;
				break;
			}
			Ap->UU.U0.ri[k] = Ap->UU.U0.ri[k-1];	// Transfere a chave da posicao (k-1) para uma posicao k,
			Ap->UU.U0.pi[k+1] = Ap->UU.U0.pi[k];	// Transfere o apontador tambem
			k--;
			if (k < 1)
				NaoAchouPosicao = false;
		}
		Ap->UU.U0.ri[k] = dados.chave;	// Copia a nova chave para a posicao liberada acima
		Ap->UU.U0.pi[k+1] = ApDir;	// Atualiza o apontador direito dessa nova chave
		(Ap->UU.U0.ni)++; // Incrementa a quantidade de chaves na pagina
	}
	else
	{	// Pagina Externa
		k = Ap->UU.U1.ne;
		NaoAchouPosicao = (k > 0);
		while (NaoAchouPosicao)
		{
			(*numComparacoesIndice)++;
			if (dados.chave >= Ap->UU.U1.re[k-1].chave)
			{	// Verifica se a chave de busca eh maior ou igual a ultima da pagina
				NaoAchouPosicao = false;
				break;
			}
			Ap->UU.U1.re[k] = Ap->UU.U1.re[k-1];
			k--;
			if (k < 1)
				NaoAchouPosicao = false;
		}
		Ap->UU.U1.re[k] = dados;
		(Ap->UU.U1.ne)++;
	}
}

void insereBEstrela(TDados dados, TApEstrela *Ap, int *numComparacoesIndice)
{
	short Cresceu;
	TDados RegRetorno;
	TPaginaEstrela *ApRetorno, *ApTemp;
	insere(dados, *Ap, &Cresceu, &RegRetorno, &ApRetorno, numComparacoesIndice);
	if (Cresceu)
	{	//A raiz eh dividida e eh gerada uma nova raiz sem aumentar a arvore.
		ApRetorno= (TPaginaEstrela*) malloc (sizeof(TPaginaEstrela));
		ApRetorno->Pt = Externa;
		ApRetorno->UU.U1.ne = 1;
		ApRetorno->UU.U1.re[0] = RegRetorno;
		
		ApTemp = (TPaginaEstrela*) malloc (sizeof(TPaginaEstrela));
		ApTemp->Pt = Interna;
		ApTemp->UU.U0.ni = 1;
		ApTemp->UU.U0.ri[0] = RegRetorno.chave;
		ApTemp->UU.U0.pi[1] = ApRetorno;
		ApTemp->UU.U0.pi[0] = *Ap;
		*Ap = ApTemp;
	}
}

void insere(TDados dados, TApEstrela Ap, short *Cresceu, TDados *RegRetorno, TApEstrela *ApRetorno, int *numComparacoesIndice)
{
	long i = 1; 
	long j;
	TApEstrela ApTemp;
	TDados aux = dados;
	if (Ap == NULL || Ap->Pt == Externa)
	{	// Verifica se o apontador eh nulo ou aponta para uma pagina externa
		*Cresceu = true;
		(*RegRetorno) = dados;
		(*ApRetorno) = NULL;
		return;
	}
	if (Ap->Pt == Interna)
	{
		while (i < Ap->UU.U0.ni && dados.chave > Ap->UU.U0.ri[i-1])
		{	//Enquanto i for menor que a quantidade de chaves desta pagina
			//...e enquanto a chave a ser inserida for maior do que uma das chaves presentes na pagina
			i++;
			(*numComparacoesIndice)++;
		}
		(*numComparacoesIndice) +=2; //Incrementa a ultima comparacao feita no while junto com o if da proxima linha
		
		if (dados.chave < Ap->UU.U0.ri[i-1]) // Verifica se a chave do registro a ser inserido possui valor menor que a da ultima chave verificada na pagina
			i--;
			
		insere(dados, Ap->UU.U0.pi[i], Cresceu, RegRetorno, ApRetorno, numComparacoesIndice);//Chamada recursiva ate que uma pagina folha seja encontrada
		if (*Cresceu)	// Se nao encontrar, retorna void
			return;
			
		if (Ap->UU.U0.ni < MM)
		{	//Confere se a pagina interna tem espaco para um novo registro
			insereNaPagina(Ap, *RegRetorno, *ApRetorno, numComparacoesIndice);
			*Cresceu = false;
			return;
		}
		if (Ap->UU.U0.ni >= MM)
		{	//Verifica se a quantidade de chaves presentes na pagina nao eh superior a maxima permitida
			ApTemp = (TApEstrela)malloc(sizeof(TPaginaEstrela));	// Cria uma nova pagina interna
			ApTemp->Pt = Interna;
			ApTemp->UU.U0.ni = 0;

			if (i < (MM/2 + 1))
			{	// Insere metade das chaves da pagina cheia para a nova pagina criada
				aux.chave = Ap->UU.U0.ri[MM -1];
				insereNaPagina(ApTemp, aux, Ap->UU.U0.pi[MM], numComparacoesIndice);
				Ap->UU.U0.ni--;
				insereNaPagina(Ap, *RegRetorno, *ApRetorno, numComparacoesIndice);
			}
			else
				insereNaPagina(ApTemp, *RegRetorno, *ApRetorno, numComparacoesIndice);
			
			for(j = MM/2+2; j <= MM; j++)
			{
				aux.chave = Ap->UU.U0.ri[j-1]; 
				insereNaPagina(ApTemp, aux, Ap->UU.U0.pi[j], numComparacoesIndice);
			}
			Ap->UU.U0.ni = MM/2;	// Atualiza a quantidade de chaves na pagina
			ApTemp->UU.U0.pi[0] = Ap->UU.U0.pi[MM/2+1];
			aux.chave = Ap->UU.U0.ri[MM/2];	// Copia a chave do meio para a pAgina pai
			*RegRetorno = aux;
			*ApRetorno = ApTemp;
		}
		
	}
	else
	// A partir desse ponto a pagina eh externa
	if (Ap->UU.U1.ne < MM)
	{	//Verifica se a quantidade de chaves presentes na pagina nao eh superior a maxima permitida
		insereNaPagina(Ap, dados, *ApRetorno, numComparacoesIndice);
		*Cresceu = false;
		return;
	}
	ApTemp = (TApEstrela)malloc(sizeof(TPaginaEstrela)); // Cria uma nova pagina externa
	ApTemp->Pt = Externa;
	ApTemp->UU.U1.ne = 0;
	
	if (i < (MM/2 + 1))
	{	// Insere metade dos registros da pagina cheia para a nova pagina criada
		insereNaPagina(ApTemp, Ap->UU.U1.re[MM-1], Ap, numComparacoesIndice);
		(Ap->UU.U1.ne)--;
		insereNaPagina(Ap, dados, *ApRetorno, numComparacoesIndice);
	}
	else
		insereNaPagina(ApTemp, dados, *ApRetorno, numComparacoesIndice);
		
	for(j = MM/2+1; j <= MM; j++)
		insereNaPagina(ApTemp, Ap->UU.U1.re[j-1], *ApRetorno, numComparacoesIndice);
	Ap->UU.U1.ne = MM/2; //Atualiza a quantidade de registros na pagina
	*RegRetorno = Ap->UU.U1.re[MM/2+1];	//Copia o registro do meio para a pagina pai
	*ApRetorno = ApTemp;
}

void pesquisaBEstrela (TDados *dados, TApEstrela *Ap, int *ver, int *numComparacoesPesquisa, int aux)
{
	int i;
	TApEstrela Pag;
	Pag = *Ap;
	if ((*Ap)->Pt == Interna)
	{
		i=1;
		while (i < Pag->UU.U0.ni && dados->chave > Pag->UU.U0.ri[i-1])
		{	//Enquanto i for menor que a quantidade de chaves desta pagina
			//...e enquanto a chave a ser inserida for maior do que uma das chaves presentes na pagina
			if (aux)
				cout << Pag->UU.U0.ri[i-1] << ", ";
			(*numComparacoesPesquisa)++;
			i++;
		}
		(*numComparacoesPesquisa)++;
		if (aux)
			cout << Pag->UU.U0.ri[i-1] << ", ";
		if (dados->chave < Pag->UU.U0.ri[i-1])
			pesquisaBEstrela (dados, &Pag->UU.U0.pi[i-1], ver, numComparacoesPesquisa, aux); //Chamada recursiva do lado esquerdo da arvore
		else
			pesquisaBEstrela (dados, &Pag->UU.U0.pi[i], ver, numComparacoesPesquisa, aux);	//Chamada recursiva do lado direito da arvore
		return;
	}
	i=1;
	// A partir daqui a pagina eh externa
	while (i < Pag->UU.U1.ne && dados->chave > Pag->UU.U1.re[i-1].chave)
	{	//Enquanto i for menor que a quantidade de chaves desta pagina
		//...e enquanto a chave a ser inserida for maior do que uma das chaves presentes na pagina
		if (aux)
			cout << Pag->UU.U0.ri[i-1] << ", ";
		(*numComparacoesPesquisa)++;
		i++;
	}
	(*numComparacoesPesquisa)++;
	cout << Pag->UU.U0.ri[i-1] << ", ";
	if (dados->chave == Pag->UU.U1.re[i-1].chave)
	{
		*dados = Pag->UU.U1.re[i-1];
		*ver = 1;
	}
}
