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

void InsereItem(TipoItem Item, TipoArea *Area)
{
    int Pos, Disp, IndiceInsercao;
    if(Area->NumCelOcupadas == TAMAREA) 
    {
        printf("Tentativa de insercao em lista cheia.\n");
        return;
    }
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
    if(Item.Nota < Area->Itens[Pos].Item.Nota)
    {
        /* Insercao realizada na primeira posicao */
        Area->Itens[Disp].Ant = -1;
        Area->Itens[Disp].Prox = Pos;
        Area->Itens[Pos].Ant = Disp;
        Area->Primeiro = Disp;
        return;
    }
    IndiceInsercao = Area->Itens[Pos].Prox;
    while(IndiceInsercao != -1 && Area->Itens[IndiceInsercao].Item.Nota < Item.Nota)
    {
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
    if (Area->NumCelOcupadas == 0) 
    {
        /* Area vazia */
        printf("Lista vazia\n");
        return;
    }
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
    if(Area->NumCelOcupadas == 0) 
    {
        /* Area vazia */
        printf("Lista vazia\n");
        return;
    }
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

void LeInf(FILE **ArqLi,  TipoRegistro *UltLido, int *Li, short *OndeLer)
{
    fread(UltLido, sizeof(TipoRegistro), 1, *ArqLi);
    (*Li)++;
    *OndeLer = TRUE;
}

void InserirArea(TipoArea *Area, TipoRegistro *UltLido, int *NRArea)
{ 
    /*Insere UltLido de forma ordenada na Area*/
    InsereItem(*UltLido, Area);
    *NRArea = ObterNumCelOcupadas(Area);
}

void EscreveMax(FILE **ArqLEs, TipoRegistro R, int *Es)
{
    fseek(*ArqLEs, (*Es - 1) * sizeof(TipoRegistro),SEEK_SET);
    fwrite(&R, sizeof(TipoRegistro), 1, *ArqLEs);
    (*Es)--;
}

void EscreveMin(FILE **ArqEi,  TipoRegistro R, int *Ei)
{
    fwrite(&R, sizeof(TipoRegistro), 1, *ArqEi);
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

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j)
{
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq,NRArea = 0;
	float Linf = INT_MIN, Lsup = INT_MAX;
    short OndeLer = TRUE;
    TipoRegistro UltLido, R;
    
    fseek(*ArqLi, (Li - 1)* sizeof(TipoRegistro), SEEK_SET);
    fseek(*ArqEi, (Ei - 1)* sizeof(TipoRegistro), SEEK_SET);
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
                LeInf(ArqLi, &UltLido, &Li, &OndeLer);
            }
            InserirArea(&Area, &UltLido, &NRArea);
            continue;
        }
        if(Ls == Es)
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
        else
        {
            if(Li == Ei)
                LeInf(ArqLi, &UltLido, &Li, &OndeLer);
            else 
            {
                if(OndeLer)
                    LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
                else
                    LeInf(ArqLi, &UltLido, &Li, &OndeLer);
            }
        }
        if(UltLido.Nota > Lsup) 
        {
            *j = Es;
            EscreveMax(ArqLEs, UltLido, &Es);
            continue;
        }
        if(UltLido.Nota < Linf) 
        {
            *i = Ei;
            EscreveMin(ArqEi, UltLido, &Ei);
            continue;
        }
        InserirArea(&Area, &UltLido, &NRArea);
        if(Ei - Esq < Dir - Es) 
        { 
            RetiraMin(&Area, &R, &NRArea);
            EscreveMin(ArqEi, R, &Ei);
            Linf = R.Nota;
        } 
        else 
        {
            RetiraMax(&Area, &R, &NRArea);
            EscreveMax(ArqLEs, R, &Es);
            Lsup = R.Nota;
        }
    }
    while(Ei <= Es) 
    {
        RetiraMin(&Area, &R, &NRArea);
        EscreveMin(ArqEi, R, &Ei);
    }
}

void QuicksortExterno(FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir)
{
    int i, j;
    TipoArea Area;   /* Area de armazenamento interna*/
    if(Dir - Esq < 1)
        return;
    FAVazia(&Area);
    Particao(ArqLi, ArqEi, ArqLEs, Area, Esq, Dir, &i, &j);
    if(i - Esq < Dir - j) 
    {   /*Ordenar primeiro o arquivo menor! */
        /*Condicao if acima garante de uma forma mais rápida uma parte já ordenada!*/
        /*OndeLer garante a leitura alternada Li e Ls.*/
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
    }
    else
    {
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, j, Dir);
        QuicksortExterno(ArqLi, ArqEi, ArqLEs, Esq, i);
    }
}