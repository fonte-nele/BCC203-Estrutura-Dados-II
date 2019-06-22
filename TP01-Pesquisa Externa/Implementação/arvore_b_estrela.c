#include "arvore_b_estrela.h"

void inicializarEstrela(ApontEstrela *Arvore)
{
	(*Arvore) = NULL;
}

void inserirPagina(ApontEstrela Ap,Reg dados, ApontEstrela ApDir, long *comp)
{
	int NaoAchouPosicao;
	int k;
	if(Ap->Pt == Interna)
	{
		k = Ap->UU.U0.ni;
		NaoAchouPosicao = (k > 0);
		while(NaoAchouPosicao) //Enquanto true
		{	
			(*comp)++;
			if(dados.chave >= Ap->UU.U0.ri[k-1])
			{
				NaoAchouPosicao = FALSE;
				break;
			}
			// Transfere a chave da posicao (k-1) para uma posicao k, e apontador tambem
			Ap->UU.U0.ri[k] = Ap->UU.U0.ri[k-1];
			Ap->UU.U0.pi[k+1] = Ap->UU.U0.pi[k];
			k--;
			if(k < 1)
			{
				NaoAchouPosicao = FALSE;
			}
		}
		Ap->UU.U0.ri[k] = dados.chave;	// Copia a nova chave para a posicao liberada acima
		Ap->UU.U0.pi[k+1] = ApDir;		// Atualiza o apontador direito dessa nova chave
		(Ap->UU.U0.ni)++; 				// Incrementa a quantidade de chaves na pagina
	}
	else
	{
		k = Ap->UU.U1.ne;
		NaoAchouPosicao = (k > 0);
		while(NaoAchouPosicao)
		{
			(*comp)++;
			if(dados.chave >= Ap->UU.U1.re[k-1].chave)
			{
				NaoAchouPosicao = FALSE;
				break;
			}
			Ap->UU.U1.re[k] = Ap->UU.U1.re[k-1];
			k--;
			if (k < 1)
			{
				NaoAchouPosicao = FALSE;
			}
		}
		Ap->UU.U1.re[k] = dados;
		(Ap->UU.U1.ne)++;
	}
}	

void insere(Reg dados,ApontEstrela *Ap,long *comp)
{
	short Cresceu;
	Reg RegRetorno;
	PaginaEstrela *ApRetorno, *ApTemp;
	insAux(dados, *Ap, &Cresceu, &RegRetorno, &ApRetorno, comp);
	
	if(Cresceu)
	{
		//Olhar!!
		ApRetorno= (PaginaEstrela*)malloc(sizeof(PaginaEstrela));
		ApRetorno->Pt = Externa;
		ApRetorno->UU.U1.ne = 1;
		ApRetorno->UU.U1.re[0] = RegRetorno;
		
		//printf("EI\n\n");
		ApTemp = (PaginaEstrela*)malloc(sizeof(PaginaEstrela));
		ApTemp->Pt = Interna;
		ApTemp->UU.U0.ni = 1;
		ApTemp->UU.U0.ri[0] = RegRetorno.chave;
		ApTemp->UU.U0.pi[1] = ApRetorno;
		ApTemp->UU.U0.pi[0] = *Ap;
		*Ap = ApTemp;
	}
}

void insAux(Reg dados,ApontEstrela Ap,short *Cresceu, Reg *RegRetorno, ApontEstrela *ApRetorno, long *comp)
{
	//printf("Volta aqui\n");
	long i=1,j;
	ApontEstrela ApTemp;
	Reg aux = dados;
	if(Ap == NULL || Ap->Pt == Externa)
	{	
		// Verifica se o apontador eh nulo ou aponta para uma pagina externa
		//printf("Aqui\n");
		(*Cresceu) = TRUE;
		(*RegRetorno) = dados;
		(*ApRetorno) = NULL;
		return;
	}
	if(Ap->Pt == Interna)
	{
		while(i < Ap->UU.U0.ni && dados.chave > Ap->UU.U0.ri[i-1])
		{
			//Enquanto i for menor que a quantidade de chaves desta pagina e enquanto a chave a ser inserida for maior do que uma das chaves presentes na pagina
			i++;
			(*comp)++;
			//printf("Entrei %ld \n",i);
		}
		if(dados.chave == Ap->UU.U0.ri[i-1])
		{
			//printf("Nao cresceu\n");
			(*Cresceu) = FALSE;
			return;
		}
		if(dados.chave < Ap->UU.U0.ri[i-1])
		{
			// Verifica se a chave do registro a ser inserido possui valor menor que a da ultima chave verificada na pagina
			i--;
			(*comp)++;
			//printf("Sai %ld \n",i);
		}	
		insAux(dados, Ap->UU.U0.pi[i], Cresceu, RegRetorno, ApRetorno,comp);//Chamada recursiva ate que uma pagina folha seja encontrada
		if(*Cresceu)
		{
			// Se nao encontrar, retorna pra quem chamou antes!
			//printf("Cresci\n");
			return;
		}	
		if(Ap->UU.U0.ni < NN)
		{
			//Confere se a pagina interna tem espaco para um novo registro
			//printf("Entrei pagina\n");
			inserirPagina(Ap, *RegRetorno, *ApRetorno,comp);
			(*Cresceu) = FALSE;
			return;
		}
		
		//Verifica se a quantidade de chaves presentes na pagina nao eh superior a maxima permitida
		ApTemp = (ApontEstrela)malloc(sizeof(PaginaEstrela));	// Cria uma nova pagina interna
		ApTemp->Pt = Interna;
		ApTemp->UU.U0.ni = 0;

		if(i<N+1)
		{
			aux.chave = Ap->UU.U0.ri[NN -1];
			inserirPagina(ApTemp, aux, Ap->UU.U0.pi[NN],comp);
			Ap->UU.U0.ni--;
			inserirPagina(Ap, *RegRetorno, *ApRetorno,comp);
		}
		else
		{
			inserirPagina(ApTemp, *RegRetorno, *ApRetorno,comp);
		}
		for(j = N+2; j <= NN; j++)
		{
			aux.chave = Ap->UU.U0.ri[j-1]; 
			inserirPagina(ApTemp, aux, Ap->UU.U0.pi[j],comp);
		}
		Ap->UU.U0.ni = N;						// Atualiza a quantidade de chaves na pagina
		ApTemp->UU.U0.pi[0] = Ap->UU.U0.pi[N+1];
		aux.chave = Ap->UU.U0.ri[N];			// Copia a chave do meio para a pAgina pai
		*RegRetorno = aux;
		*ApRetorno = ApTemp;
		
	}
	else
	{
		// A partir desse ponto a pagina eh externa
		if (Ap->UU.U1.ne < NN)
		{
			//Verifica se a quantidade de chaves presentes na pagina nao eh superior a maxima permitida
			inserirPagina(Ap, dados, *ApRetorno,comp);
			*Cresceu = FALSE;
			return;
		}
		//Cria uma nova pagina externa
		ApTemp = (ApontEstrela)malloc(sizeof(PaginaEstrela));
		ApTemp->Pt = Externa;
		ApTemp->UU.U1.ne = 0;
		
		if(i < (NN/2 + 1))
		{
			//Insere metade dos registros da pagina cheia para a nova pagina criada
			inserirPagina(ApTemp, Ap->UU.U1.re[NN-1], Ap,comp);
			(Ap->UU.U1.ne)--;
			inserirPagina(Ap, dados, *ApRetorno,comp);
		}
		else
		{
			inserirPagina(ApTemp, dados, *ApRetorno,comp);
		}	
		for(j = NN/2+1; j <= NN; j++)
		{
			inserirPagina(ApTemp, Ap->UU.U1.re[j-1], *ApRetorno,comp);
		}
		Ap->UU.U1.ne = NN/2; 				//Atualiza a quantidade de registros na pagina
		*RegRetorno = Ap->UU.U1.re[NN/2+1];	//Copia o registro do meio para a pagina pai
		*ApRetorno = ApTemp;
	}
}

int pesquisar_estrela(Reg *reg,ApontEstrela *apont, long *comp)
{
	int i;
	ApontEstrela pag;
	pag = *apont;
	if((*apont)->Pt == Interna)
	{
		i=1;
		while(i< pag->UU.U0.ni && reg->chave > pag->UU.U0.ri[i-1])
		{
			(*comp)++;
			i++;
		}
		(*comp)++;
		if(reg->chave>0 && reg->chave < pag->UU.U0.ri[i-1])
		{
			return pesquisar_estrela(reg,&pag->UU.U0.pi[i-1],comp);
		}
		else
		{
			return pesquisar_estrela(reg,&pag->UU.U0.pi[i],comp);
		}
	}
	i = 1;
	while(i < pag->UU.U1.ne && reg->chave > pag->UU.U1.re[i-1].chave)
	{
		(*comp)++;
		i++;
	}
	if(reg->chave == pag->UU.U1.re[i-1].chave)
	{
		*reg = pag->UU.U1.re[i-1];
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}