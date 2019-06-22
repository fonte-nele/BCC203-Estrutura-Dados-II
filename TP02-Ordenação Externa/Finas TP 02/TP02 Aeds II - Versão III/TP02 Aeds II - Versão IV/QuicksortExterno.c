#include "QuicksortExterno.h"

/*Procedimentos de manipulacao da Area*/
void FAVazia(TipoArea *Area)
{
    Area->NumCelOcupadas = 0;
    
}

int ObterNumCelOcupadas(TipoArea *Area)
{
    return (Area->NumCelOcupadas);
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

void InserirArea(TipoArea *Area, TipoRegistro *UltLido, int *NRArea)
{ 
    /*Insere UltLido de forma ordenada na Area*/
    Area->Itens[Area->NumCelOcupadas] = *UltLido;
	Area->NumCelOcupadas++;
    *NRArea = ObterNumCelOcupadas(Area);
}

void Insertion2(TipoArea *area)
{
	int i,j;
	TipoItem aux;
	//Sem sentinela.
	for(i=1;i<area->NumCelOcupadas;i++)
	{
		aux = area->Itens[i];
		j = i-1;
		
		while(j>=0 && aux.nota > area->Itens[j].nota)
		{
			area->Itens[j+1] = area->Itens[j];
			j--;
		}
		area->Itens[j+1]= aux;
	}
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
    Insertion2(Area);
	*R = Area->Itens[Area->NumCelOcupadas-1];
	Area->NumCelOcupadas--;
    *NRArea = ObterNumCelOcupadas(Area);
}

void RetiraMin(TipoArea *Area, TipoRegistro *R, int *NRArea)
{
    Insertion2(Area);
	*R = Area->Itens[0];
	int i;
	for (i=0; i<Area->NumCelOcupadas; i++)
	{
		Area->Itens[i] = Area->Itens[i+1];
	}
	Area->NumCelOcupadas--;
    *NRArea = ObterNumCelOcupadas(Area);
}

void Particao(FILE **ArqLEi, FILE **ArqLEs, TipoArea Area, int Esq, int Dir, int *i, int *j)
{
    printf("\n");
	int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq,NRArea = 0, Linf = INT_MIN, Lsup = INT_MAX;
    short OndeLer = TRUE;
    TipoRegistro UltLido, R;
    
    /*Inicializando com valores que nao existem*/
    *i = Esq - 1;
    *j = Dir + 1;
    while(Ls >= Li) 
    {
        if(NRArea < TAMAREA - 1) 
        {
			printf("Pssei\n");
            if(OndeLer)
            {
                LeSup(ArqLEs, &UltLido, &Ls, &OndeLer);
            }
            else
            {
                LeInf(ArqLEi, &UltLido, &Li, &OndeLer);
            }
            InserirArea(&Area, &UltLido, &NRArea);
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
			printf("LSUP\n");
            *j = Es;
            EscreveMax(ArqLEs, UltLido, &Es);
            continue;
        }
        if(UltLido.nota < Linf) 
        {
			printf("LINF\n");
            *i = Ei;
            EscreveMin(ArqLEi, UltLido, &Ei);
            continue;
        }
        InserirArea(&Area, &UltLido, &NRArea);
        if(Ei - Esq < Dir - Es) 
        { 
			printf("EI\n");
            RetiraMin(&Area, &R, &NRArea);
            EscreveMin(ArqLEi, R, &Ei);
            Linf = R.nota;
        } 
        else
        {
			printf("ES\n");		
            RetiraMax(&Area, &R, &NRArea);
            EscreveMax(ArqLEs, R, &Es);
            Lsup = R.nota;
        }
    }
    while(Ei <= Es) 
    {
        RetiraMin(&Area, &R, &NRArea);
        EscreveMin(ArqLEi, R, &Ei);
    }
}

void QuicksortExterno(FILE **ArqLEi, FILE **ArqLEs, int Esq, int Dir)
{
    int i, j;
    TipoArea Area;   /* Area de armazenamento interna*/
    if(Dir - Esq < 1)
        return;
    FAVazia(&Area);
    Particao(ArqLEi, ArqLEs, Area, Esq, Dir, &i, &j);
    if(i - Esq <  Dir - j) 
    {   /*Ordenar primeiro o arquivo menor! */
        /*Condicao if acima garante de uma forma mais rápida uma parte já ordenada!*/
        /*OndeLer garante a leitura alternada Li e Ls.*/
        QuicksortExterno(ArqLEi, ArqLEs, Esq, i);
        QuicksortExterno(ArqLEi, ArqLEs, j, Dir);
    }
    else
    {
        QuicksortExterno(ArqLEi, ArqLEs, j, Dir);
        QuicksortExterno(ArqLEi, ArqLEs, Esq, i);
    }
}