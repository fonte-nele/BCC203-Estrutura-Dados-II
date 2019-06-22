#include "QuicksortExterno.h"

/*Procedimentos de manipulacao da Area*/
void FAVazia(TipoArea *Area)
{
    int i;
    Area->NumCelOcupadas = 0;
    Area->Primeiro = -1;
    Area->Ultimo = -1;
    Area->CelulasDisp = 0;
    for(i=0; i<TAMAREA; i++) 
    {
        Area->Itens[i].Ant = -1;
        Area->Itens[i].Prox = i + 1;
    }
}

int ObterNumCelOcupadas(TipoArea *Area)
{
    return (Area->NumCelOcupadas);
}

void InsereItem(TipoItem Item, TipoArea *Area, TAnalise* desempenho)
{
    int Pos, Disp, IndiceInsercao;
    
    Disp = Area->CelulasDisp;
    Area->CelulasDisp = Area->Itens[Area->CelulasDisp].Prox;
    Area->Itens[Disp].Item = Item;
    Area->NumCelOcupadas++;

    if(Area->NumCelOcupadas == 1) 
    {
        /* Insercao do primeiro item */
        Area->Primeiro = Disp;
        Area->Ultimo = Area->Primeiro;
        Area->Itens[Area->Primeiro].Prox = -1;
        Area->Itens[Area->Primeiro].Ant = -1;	
		
        return;
    }
    Pos = Area->Primeiro;
	desempenho->Num_comparacoes++;
    if(Item.nota < Area->Itens[Pos].Item.nota)
    {
        /* Insercao realizada na primeira posicao */
        Area->Itens[Disp].Ant = -1;
        Area->Itens[Disp].Prox = Pos;
        Area->Itens[Pos].Ant = Disp;
		Area->Primeiro = Disp;
		
        return;
    }
    IndiceInsercao = Area->Itens[Pos].Prox;
    while(IndiceInsercao != -1 && Area->Itens[IndiceInsercao].Item.nota < Item.nota)
    { 
		desempenho->Num_comparacoes++;
        Pos = IndiceInsercao;
        IndiceInsercao = Area->Itens[Pos].Prox;
    }
    if(IndiceInsercao == -1)
    {
        /*Insercao realizada na ultima posicao*/
        Area->Itens[Disp].Ant = Pos;
        Area->Itens[Disp].Prox = -1;
        Area->Itens[Pos].Prox = Disp;
        Area->Ultimo = Disp;
		
        return;
    }

    Area->Itens[Disp].Ant = Pos;
    Area->Itens[Disp].Prox = Area->Itens[Pos].Prox;
    Area->Itens[Pos].Prox = Disp;
    Pos = Area->Itens[Disp].Prox;
    Area->Itens[Pos].Ant = Disp;
	
    /* Insercao realizada no meio de Area */
}

void RetiraPrimeiro(TipoArea *Area, TipoItem *Item)
{
    TipoApontador ProxTmp;
    *Item = Area->Itens[Area->Primeiro].Item;
    ProxTmp = Area->Itens[Area->Primeiro].Prox;
    Area->Itens[Area->Primeiro].Prox = Area->CelulasDisp;
    Area->CelulasDisp = Area->Primeiro;
    Area->Primeiro = ProxTmp;
    if((unsigned int)Area->Primeiro < TAMAREA)
    {
        Area->Itens[Area->Primeiro].Ant = -1;
        Area->NumCelOcupadas--;
    }
}

void RetiraUltimo(TipoArea *Area, TipoItem *Item)
{
    TipoApontador AntTmp;
    *Item = Area->Itens[Area->Ultimo].Item;
    AntTmp = Area->Itens[Area->Ultimo].Ant;
    Area->Itens[Area->Ultimo].Prox = Area->CelulasDisp;
    Area->CelulasDisp = Area->Ultimo;
    Area->Ultimo = AntTmp;
    if((unsigned int)Area->Ultimo < TAMAREA)
    {
        Area->Itens[Area->Ultimo].Prox = -1;
        Area->NumCelOcupadas--;
    }
}

/*Procedimentos utilizados pelo Particao do quicksort externo*/
void LeSup(FILE **ArqLEs, TipoRegistro *UltLido, int *Ls, short *OndeLer)
{
    /*Fseek por conta do arquivo que eh para Ls e Es.*/
    fseek(*ArqLEs, (*Ls - 1) * sizeof(TipoRegistro),SEEK_SET);
    fread(UltLido, sizeof(TipoRegistro), 1, *ArqLEs);
    (*Ls)--;
    *OndeLer = FALSE;
}

void LeInf(FILE **ArqLEi,  TipoRegistro *UltLido, int *Li, short *OndeLer)
{
    /*Fseek por conta do arquivo que eh para LI e Ei.*/
    fseek(*ArqLEi, (*Li - 1) * sizeof(TipoRegistro),SEEK_SET);
    fread(UltLido, sizeof(TipoRegistro), 1, *ArqLEi);
    (*Li)++;
    *OndeLer = TRUE;
}

void InserirArea(TipoArea *Area, TipoRegistro *UltLido, int *NRArea, TAnalise* desempenho)
{ 
    /*Insere UltLido de forma ordenada na Area*/
    InsereItem(*UltLido, Area,desempenho);
    *NRArea = ObterNumCelOcupadas(Area);
}

void EscreveMax(FILE **ArqLEs, TipoRegistro R, int *Es)
{
    fseek(*ArqLEs, (*Es - 1) * sizeof(TipoRegistro),SEEK_SET);
    fwrite(&R, sizeof(TipoRegistro), 1, *ArqLEs);
    (*Es)--;
}

void EscreveMin(FILE **ArqLEi,  TipoRegistro R, int *Ei)
{
    fseek(*ArqLEi, (*Ei - 1) * sizeof(TipoRegistro),SEEK_SET);
    fwrite(&R, sizeof(TipoRegistro), 1, *ArqLEi);
    (*Ei)++; 
}

void RetiraMax(TipoArea *Area,  TipoRegistro *R, int *NRArea)
{ 
    RetiraUltimo(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

void RetiraMin(TipoArea *Area, TipoRegistro *R, int *NRArea)
{
    RetiraPrimeiro(Area, R);
    *NRArea = ObterNumCelOcupadas(Area);
}

void Particao(FILE **ArqLEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j, TAnalise* desempenho)
{
	int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq,NRArea = 0;
	float Linf = INT_MIN, Lsup = INT_MAX;
    short OndeLer = TRUE;
    TipoRegistro UltLido, R;
    
    /*Inicializando com valores que nao existem*/
    *i = Esq - 1;
    *j = Dir + 1;
    while(Ls >= Li) 
    {
        if(NRArea < TAMAREA - 1) 
        {
            if(OndeLer)
            {
                LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
            }
            else
            {
                LeInf(ArqLEi, &UltLido, &Li, &OndeLer);
            }
            InserirArea(&Area, &UltLido, &NRArea,desempenho);
			desempenho->Num_transf_read++;
            continue;
        }
        if(Ls == Es)
		{
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        }
		else
        {
            if(Li == Ei)
			{
                LeInf(ArqLEi, &UltLido, &Li, &OndeLer);
            }
			else 
            {
                if(OndeLer){
                    LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
				}
				else
				{
                    LeInf(ArqLEi, &UltLido, &Li, &OndeLer);
				}
			}
        }
        
		if(UltLido.nota > Lsup) 
        {
            *j = Es;
            EscreveMax(ArqLEs, UltLido, &Es);
			desempenho->Num_transf_write++;
            continue;            
        }
        if(UltLido.nota < Linf) 
        {
			 *i = Ei;
            EscreveMin(ArqLEi, UltLido, &Ei);
			desempenho->Num_transf_write++;
            continue;
        }
		
		
        InserirArea(&Area, &UltLido, &NRArea,desempenho);
		desempenho->Num_transf_read++;
		
        if(Ei - Esq < Dir - Es) 
        {
            RetiraMin(&Area, &R, &NRArea);
            EscreveMin(ArqLEi, R, &Ei);
			desempenho->Num_transf_write++;
            Linf = R.nota;
        } 
        else
        {
            RetiraMax(&Area, &R, &NRArea);
            EscreveMax(ArqLEs, R, &Es);
			desempenho->Num_transf_write++;
            Lsup = R.nota;
        }
    }
    while(Ei <= Es) 
    {
        RetiraMin(&Area, &R, &NRArea);
        EscreveMin(ArqLEi, R, &Ei);
		desempenho->Num_transf_write++;  
	}
}

void QuicksortExterno(FILE **ArqLEi, FILE **ArqLEs, int Esq, int Dir,TAnalise* desempenho)
{
    int i, j;
    TipoArea Area;   /* Area de armazenamento interna*/
    if(Dir - Esq < 1)
        return;
    FAVazia(&Area);
    Particao(ArqLEi, ArqLEs, Area, Esq, Dir, &i, &j,desempenho);
    if(i - Esq <  Dir - j) 
    {   /*Ordenar primeiro o arquivo menor! */
        /*Condicao if acima garante de uma forma mais rápida uma parte já ordenada!*/
        /*OndeLer garante a leitura alternada Li e Ls.*/
        QuicksortExterno(ArqLEi, ArqLEs, Esq, i,desempenho);
        QuicksortExterno(ArqLEi, ArqLEs, j, Dir,desempenho);
    }
    else
    {
        QuicksortExterno(ArqLEi, ArqLEs, j, Dir,desempenho);
        QuicksortExterno(ArqLEi, ArqLEs, Esq, i,desempenho);
    }
}