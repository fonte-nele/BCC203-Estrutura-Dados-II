/* TADs para ordenação externa */

#define NARQUIVOS 6
#define MIN_TAMANHO 20
#define CODIGO_ESC 27
#define CODIGO_DELETE 127
#define CODIGO_CONTROLE1 11
#define CODIGO_CONTROLE2 12

typedef struct _Palavra { 

	char *palavra;
	int flag;
	int narquivo;

}TpPalavra;

typedef struct _Heap {
	
	int flagAtual;
	TpPalavra **palavra;
	long tamanho;

}TpHeap;

typedef struct _Arquivo {

	char *nome;
	long nBlocos;
	FILE *arquivo;
	int ativo;
	
}TpArquivo;

TpArquivo **criaArquivo(TpArquivo **arquivos,int nfitas,int nome);

long calculaTamanho(FILE *arquivo); 

char *retornoString(FILE *arquivo);

TpPalavra **quebraEspaco(char *str, long *contador);

long calculaMemoria(int tamanho);  

char* leStringsInteirasDeArquivo(FILE *arq, long limite_tamanho);

int comparaString(TpPalavra *str1,TpPalavra *str2,int flagAtual);

void trocaString(char **str1, char **str2);

void trocaArquivoFlag(TpPalavra *palavraI,TpPalavra *palavraII);

void minHeapify(TpHeap *A,long i);

void constroiHeap(TpHeap *heap); 

void criaHeap(TpPalavra **str,long indice);

void heapSort(TpHeap *A); 

void heapInsereChave(TpHeap *heap, int i,TpPalavra *chave);

void heapMinInsere(TpHeap *heap, TpPalavra *chave);

TpPalavra *heapRemove(TpHeap *heap);

void freeHeap(TpHeap *heap);

void freeFitas(TpArquivo **arquivos);

void freePalavras(TpHeap *A1,TpHeap *A2);

void salvaBloco(TpHeap *heap, FILE *A);

long Parent(long i);

long Left(long i);

long Right(long i);

void retornoProximo(TpArquivo **arquivos,TpArquivo **fitas,TpHeap *heap1,TpHeap *heap2);

int retornoFimArquivos(TpArquivo **arquivos);

int Salva(TpHeap *heap, TpArquivo **arquivos,TpArquivo **destino,int narquivo);

int contadordeBlocos(TpArquivo **A,TpArquivo **B,TpHeap *heap,int k,int contador);

void resultado(TpArquivo **arquivos,TpHeap *heap);

void intercalacaoBalanceada(TpArquivo **A,TpArquivo **B,TpHeap *heap,TpHeap *hRemove);

void inserirPalavraHeap(char *palavra,TpHeap *A,int narquivo);

void heapNovo(TpArquivo **arquivos,TpHeap *heap);

void selecaoPorSubstituicao( TpHeap *heap,TpArquivo **arquivos,TpArquivo **fitas); 

int flagContrario(TpHeap *heap); 

int verificaFlag(TpHeap *heap);

TpPalavra *substituiMenor(TpHeap *heap, char *strI, int nArquivo);

void retornoProximoII( TpArquivo **arquivos );

void intercalacaoBalanceadaII(TpArquivo **arquivos, TpHeap* heap,TpHeap *hRemove);

void selecaoPorSubstituicaoFMaisUmaFita( TpHeap *heap,TpArquivo **arquivos);

int SalvaII(TpHeap *heap,TpArquivo **arquivos);

void redistribui( TpArquivo **arquivos);

TpArquivo **distribuiStrings(char *nomeArquivo);

void doisVezesFitas(char *argv);

void fMaisUmaFita(char *argv);
