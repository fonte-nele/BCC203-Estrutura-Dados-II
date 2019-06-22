#define MM 100

typedef enum {Interna, Externa} TIntExt;
typedef struct TPaginaEstrela* TApEstrela;

typedef struct TPaginaEstrela
{
	TIntExt Pt;
	union
	{
		struct
		{
			int ni;
			int ri[MM];
			TApEstrela pi[MM+1];
		}
		U0;
		struct
		{
			int ne;
			TDados re[MM/2];
		}U1;
	}UU;
}TPaginaEstrela;

void inicializaBEstrela(TApEstrela);
void insereNaPagina(TApEstrela, TDados, TApEstrela, int *);
void insereBEstrela(TDados, TApEstrela *, int *);
void insere(TDados, TApEstrela, short *, TDados *, TApEstrela *, int *);
void pesquisaBEstrela(TDados *, TApEstrela *, int *, int *, int);
