#define mm 4

typedef struct TipoPagina* TApontador;
typedef struct TipoPagina
{
    short numItensPagina;
    TDados dados[mm];
    TApontador ponteiro[mm+1];
} TipoPagina;

void Inicializa(TApontador);
void InsereNaPagina(TApontador, TDados, TApontador, int *);
void Ins(TDados, TApontador, short *, TDados *, TApontador *, int *);
void InsereArvoreB(TDados, TApontador *, int *);
void PesquisaArvoreB(TDados *, TApontador, int, int *, int *);
