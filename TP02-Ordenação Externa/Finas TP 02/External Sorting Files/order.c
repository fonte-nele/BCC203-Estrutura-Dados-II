/* funções para ordenação externa*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "order.h"

/* Distribui as strings nos 6 arquivos */

TpArquivo **distribuiStrings(char *nomeArquivo) {

	FILE *arquivo = fopen(nomeArquivo,"r");
	
	if(arquivo != NULL) 
	{
		TpArquivo **fitas  =  (TpArquivo**) malloc ( (NARQUIVOS + 1) *sizeof (TpArquivo*) );
				
		if(fitas)
		{
			criaArquivo(fitas,NARQUIVOS,1);
		}
		else
		{
			return NULL;
		}
		
		long contF = 1;

		long tamanho = calculaTamanho(arquivo);
		long limite = floor((tamanho * 0.5) / 100);

		if(tamanho > 0)
		{
			if (limite < MIN_TAMANHO) 
			{
				limite = MIN_TAMANHO;
			}
			while(1) {

				char *str = leStringsInteirasDeArquivo(arquivo, limite);

				if (str == NULL)
				{
					break;
				}

				long  contador = 1;

				TpPalavra **str1 = quebraEspaco(str,&contador);

				if(str1 != NULL)
				{
					TpHeap *heap = (TpHeap*) malloc (sizeof(TpHeap));

					if(!heap)
					{
						break;
					}
					heap->tamanho = contador;
					heap->flagAtual = 0;
					heap->palavra = str1;
					constroiHeap(heap);

					free(str);

					salvaBloco( heap, fitas[contF]->arquivo );
					freeHeap(heap);
				}
				contF++;

				if(contF > NARQUIVOS)
				{
					contF = 1;
				}
			}
		}
		fclose(arquivo);
		return fitas;
	}
	return NULL;

}

/* Faz 2f */

void doisVezesFitas(char *argv) {

	TpArquivo **fitas  = distribuiStrings(argv);
	
	if(fitas == NULL)
	{
		return;
	}
	int i;
	srand(time(NULL));
	float tempo;
	clock_t t_fim,t_ini;
	t_ini = clock(); // Inicia contagem... 
	for(i = 1; i <= NARQUIVOS; i++) {

		fseek(fitas[i]->arquivo,0,SEEK_SET);
	}
	TpHeap *A =  (TpHeap*) malloc ( sizeof (TpHeap) );
	
	if(A != NULL)
	{
		printf("\nINTERCALAÇÃO BALANCEADA POR SUBSTITUIÇÃO USANDO 2 VEZES NUMERO DE FITAS\n");
		TpArquivo **fita2  =  ( TpArquivo** ) malloc ( (NARQUIVOS + 1) * sizeof ( TpArquivo* ) );

		if(fita2)
		{
			srand(time(NULL));
			
			criaArquivo(fita2,NARQUIVOS,2);
			selecaoPorSubstituicao( A,fitas,fita2);
			
			t_fim = clock();//marca a diferença  de tempo...
			tempo = ((float)(t_fim-t_ini))/CLOCKS_PER_SEC;
			printf("\n\n\033[1;32mTempo de %f segundos\033[0m\n\n",tempo);
			
			freeHeap(A);
			for(i = 1; i <= NARQUIVOS; i++)
			{
				remove(fita2[i]->nome);
			}
			freeFitas(fita2);
		}
	}	
	freeFitas(fitas);
}

/* Faz f + 1 */

void fMaisUmaFita(char *argv) {

	TpArquivo **fitas = distribuiStrings(argv);
	int i ;
	if(fitas != NULL)
	{	
		TpArquivo *arquivo = (TpArquivo*) malloc (sizeof (TpArquivo));
		if(arquivo)
		{
			arquivo->nome = (char *) malloc(sizeof(char) * 2);
			strcpy(arquivo->nome, "0");
			arquivo->nome[1] = '\0';
			arquivo->arquivo = fopen(arquivo->nome,"w+");
				
			fitas[0] = arquivo;
			fitas[0]->ativo = 1;
			fitas[0]->nBlocos = 0;
		}
	}
	if(fitas == NULL)
	{
		return;
	}
	srand(time(NULL));
	float tempo;
	clock_t t_fim,t_ini;
	t_ini = clock(); // Inicia contagem... 
	for(i = 1; i <= NARQUIVOS; i++) {

		fseek(fitas[i]->arquivo,0,SEEK_SET);
	}
	TpHeap *A =  (TpHeap*) malloc ( sizeof (TpHeap) );
	
	if(A != NULL)
	{
		srand(time(NULL));
		
		printf("INTERCALAÇÃO BALANCEADA POR SUBSTITUIÇÃO USANDO F + 1 Fitas\n");
		
		selecaoPorSubstituicaoFMaisUmaFita(A,fitas);

		t_fim = clock();//marca a diferença  de tempo...
		tempo = ((float)(t_fim-t_ini))/CLOCKS_PER_SEC;
		printf("\n\n\033[1;32mTempo de %f segundos\033[0m\n\n",tempo);
		freeHeap(A);
		for(i = 0; i <= NARQUIVOS; i++) {
		
			remove(fitas[i]->nome);
			fclose(fitas[i]->arquivo);
			free(fitas[i]->nome);
			free(fitas[i]);
		}
		free(fitas);
		
	}

}

/* Pega um inteiro e transforma em string */

char* int_Para_String(int numero) {

	char* string = (char *) malloc (sizeof(char) * 8);

	if(string != NULL)
	{
		sprintf(string, "%d", numero);

		char *temp = (char*) realloc (string, ( strlen(string) + 1) * sizeof(char) );

		if(string)
		{
			string = temp;
			return string;
		}
	}
	return NULL;
}

/* Cria arquivos necessários para a ordenação(leitura e escrita) */

TpArquivo **criaArquivo(TpArquivo **arquivos,int nfitas, int nome) {
	

	if(arquivos)
	{
		if(nome == 1)
		{
			int i;
			for(i = 1; i <= nfitas; i++) {

				TpArquivo *arquivo = (TpArquivo*) malloc (sizeof (TpArquivo));
	
				if(arquivo != NULL)
				{
					arquivo->nome = int_Para_String(i);
					arquivo->arquivo = fopen(arquivo->nome,"w+");
						
					arquivos[i] = arquivo;
					arquivos[i]->ativo = 1;
					arquivos[i]->nBlocos = 0;
				}
				else 
				{
					free(arquivos);
					exit(1);
				}
			}
			return arquivos;
		}
		if(nome == 2)
		{
			int i;
			int nome = nfitas + 1 ;

			for(i = 1; i <= nfitas; i++) {

				TpArquivo *arquivo = (TpArquivo*) malloc (sizeof (TpArquivo));
	
				if(arquivo != NULL)
				{
					arquivo->nome = int_Para_String(nome);
					arquivo->arquivo = fopen(arquivo->nome,"w+");
					
					arquivos[i] = arquivo;
					arquivos[i]->ativo = 1;
					arquivos[i]->nBlocos = 0;
				}
				else 
				{
					free(arquivos);
					exit(1);
				}
				nome ++;
			}
			return arquivos;

		}
	}
	return NULL;
}

/* Calcula o tamanho de uma arquivo retornando ele */

long calculaTamanho(FILE *arquivo) {

	if(arquivo != NULL)
	{
		long tamanho;

		fseek(arquivo,0,SEEK_END);

		tamanho = ftell(arquivo);
		
		fseek(arquivo, 0, SEEK_SET);

		return tamanho;
	}
	else
	{
		printf("Arquivo inexistente\n\n");
		exit(1);
	}
	return -1;
}

/* Retorna string de um arquivo */

char *retornoString(FILE *arquivo) {
	
	if(arquivo != NULL)
	{
		char *str = (char*) malloc ( (101) * sizeof(char) );

		if(!str)
		{
			printf("ERRO AO ALOCAR MEMÓRIA\n");
			return NULL;
		}
		int i = 0;
		char ch;

		ch = fgetc(arquivo);

		while ( ch != EOF)
		{
			if( ( ch == EOF ) || ( ch == (char)CODIGO_DELETE ) ||  ( ( ch == ( char ) CODIGO_ESC ) || ( ch == '\n' ) ) )
			{
				break;
			}
			else
			{
				str[i] = ch;
				i++;
				ch = fgetc(arquivo);	
			}
		}
		if(i < 1)
		{	
			free(str);
			return NULL;
		}
		else
		{
			char *string = (char*) malloc ( ( i + 2 ) * sizeof(char));
		
			if(string != NULL)
			{
				int j ;
				i = i - 1 ;

				for (j = 0; j <= i; j++) {

					if(str[j])
					{
						string[j] = str[j];	
					}
				}
				string[j] = '\0';
				free(str);
				if(string) 
				{
					return string;
				}
			}
		}
	}
	return NULL;
}

/* Remove char da string */

void removeChar(char *str, char garbage) {

    char *src, *dst;
    
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

/*  Quebra string por espaço */

TpPalavra **quebraEspaco(char *str, long *contador) {

	if(str != NULL)
	{
		TpPalavra **aux = (TpPalavra**) malloc (sizeof (TpPalavra*) );
		removeChar(str,'\n');
		if(aux != NULL)
		{
			long cont = 1;
			const char *espaco = " ";
			char *token = strtok(str,espaco); 
	
			while (token != NULL) {

				TpPalavra **temp = (TpPalavra**) realloc (aux, ( cont + 1) *sizeof (TpPalavra*) );

				if(temp != NULL)
				{
					aux = temp;
                    			aux[cont] = (TpPalavra*) malloc (sizeof(TpPalavra));
					
				
					if(aux[cont] != NULL) 
					{
						aux[cont]->palavra = (char *) malloc ( ( strlen(token) + 1 ) * sizeof(char) );

						if (!aux[cont]->palavra)
						{
							free(aux);
							free(temp);
							return NULL;
						}

						aux[cont]->flag = 0;
						aux[cont]->narquivo = 0;
						strcpy(aux[cont]->palavra,token);
						aux[cont]->palavra[strlen(token)] = '\0';
						token = strtok(NULL, espaco);
						cont++;
					}
				}
				else
				{

					fprintf(stderr,"ERROR\n\n");
					return NULL;
				}
			
			}

			*contador = (cont - 1);
			return aux;
		}
	}
	return NULL;
}

/* Funções para reconstituição do heap */

long Parent(long i) {

	return floor(i/2);
}
long Left(long i) {

	return (2*i);
}
long Right(long i) {

	return (2*i) + 1;
}

/* Faz swap por ponteiro */

void trocaString(char **str1, char **str2) {
	
	if(*str1 != NULL && *str2 != NULL)
	{
		char *auxiliar = *str1;
		*str1  = *str2;
		*str2  = auxiliar;

	}
	else
	{
		exit(1);
	}	
}

/* Faz swap de dois TpPalavras */

void trocaArquivoFlag(TpPalavra *palavraI,TpPalavra *palavraII) {

	if(palavraI != NULL && palavraII != NULL)
	{
		int temp  = palavraI->flag;
		palavraI->flag = palavraII->flag;
		palavraII->flag = temp;
		
		int numero  = palavraI->narquivo;
		palavraI->narquivo = palavraII->narquivo;
		palavraII->narquivo = numero;
	}
}

/* lee as strings de um arquivo 'x' */

char* leStringsInteirasDeArquivo(FILE *arq, long limite_tamanho) {

    if(arq != NULL)
    {
	    char *string = (char *) malloc ( (limite_tamanho + 1) * sizeof(char) );

	    if (!string) {

	    	fprintf(stderr, "Erro ao alocar string!");
	    	return NULL;
	    }
	    else 
            {
		    long lido = fread (string, sizeof(char), (limite_tamanho) * sizeof(char), arq) ;

		    if(lido == 0) 
		    {
				free(string);
				return NULL;
		    }
		    if (!lido)
		    {
				free(string);
				return NULL;
		    }

		    string[lido] = '\0';
		    
		    if (string[lido - 1] == ' ') 
		    {
			return string;
		    } 
		    else 
		    {
			// armazena a posicao do ponteiro do arquivo 
			// antes de realizar leituras e modificacoes
			long current_read_bytes = ftell(arq);        
			char *prox = (char*) malloc (sizeof(char));
		
			if(!prox) 
			{
				free(string);
				return NULL;
			}
			/* Se nao conseguir ler um caractere para a frente
			pode ser que o arquivo terminou, entao retorna "string" */
			if (  fread(prox, sizeof(char), 1, arq)  != 1) 
			{
			    	free(prox);
				return string;
			}
		
			// Retorna o ponteiro do arquivo a  posicao anterior a leitura de 1 caractere
			fseek(arq, current_read_bytes, SEEK_SET);       	
			/* Se o caractere lido nao for um espaco, entao a string deve ser cortada
			ate o ultimo espaco anterior, e o ponteiro do arquivo tambem deve voltar ate o final
			da nova string*/
			if (prox[0] != ' ') {

				    int cur = lido - 1;

				    while ( ( string[cur] != ' ') && ( cur > 0 )) {

					cur--;
				    }
				    
				    // calculando a diferenca para voltar o ponteiro do arquivo
				    long diff;

				    if(lido > cur)
				    {
				   	diff = lido - cur;
				    }
				    if(lido <= cur)
				    {
					diff = cur - lido;
				    }
				    int r = (int)fseek(arq, current_read_bytes - diff, SEEK_SET);
				    
				    if (r != 0)
				    {
					fprintf(stderr, "Erro ao manipular ponteiro de arquivo com FSEEK\n");
					return NULL;
				    
				    }
				    else 
				    {
					    char *substr = (char *) malloc ( (cur + 2) * sizeof(char)  );

					    if(substr != NULL)
					    {
						    // Copia n(cur) caracteres da string "string" para a string "substr"
						    substr[cur] = '\0';
						    strncpy(substr, string, cur );

						    free(prox);
						    free(string);

						    return substr;
					    }
				    }
			}
			free(prox);
			return string;
		    }
	}
    }
    return NULL;
}

/* Compara strings seguindo as condições das flags caso seja necessário */

int comparaString(TpPalavra *str1,TpPalavra *str2,int flagAtual) {

	if( (str1 != NULL && str2 != NULL) && ( str1->palavra != NULL && str2->palavra ) )
	{
		
		if( str1->flag == str2->flag )
		{

			if(strcmp( str1->palavra,str2->palavra ) < 0) 
			{
				return 1;
			}
			if(strcmp( str1->palavra,str2->palavra ) == 0) 
			{
				return 2;
			}
			if(strcmp( str1->palavra,str2->palavra ) > 0) 
			{
				return 3;
			}
		}
		else if(  str1->flag != str2->flag  )
		{
			if(  str1->flag != flagAtual )
			{
				return 3;
			}
			else if(str2->flag != flagAtual)
			{
				return 1;
			}
			else if(strcmp( str1->palavra,str2->palavra ) == 0)
			{
				return 2;
			}
			
		}	
	}
	return 0;
}

/* Constroi um heap, chamando o 'minHeapify', onde monta a fila de prioridades */

void constroiHeap(TpHeap *heap) {

	if(heap != NULL)
	{
		long i;
		long limite = floor(heap->tamanho/2);
	
		for(i = limite; i >= 1; i--) {

			minHeapify(heap,i);
		}		
	}
}

/* Cria um heap */

void criaHeap(TpPalavra **str,long indice) {

	TpHeap *heap = (TpHeap *) malloc (sizeof (TpHeap));	

	if(heap != NULL && indice > 0) 
	{
		heap->tamanho = indice;
		heap->flagAtual = 0;
		heap->palavra = (TpPalavra**) malloc ( (indice + 1) * sizeof (TpPalavra*) );

		if(heap->palavra != NULL) 
		{
			long i;

			for(i = 1; i <= indice; i++) {

                		heap->palavra[i] = (TpPalavra*) malloc (sizeof(TpPalavra*));

				if(!heap->palavra[i])
				{
					free(heap->palavra);
					free(heap);
					exit(1);
				}
				heap->palavra[i]->palavra = (char*) malloc ( (strlen(str[i]->palavra) + 2) * sizeof (char) );
				heap->palavra[i]->flag = heap->flagAtual;

				if(heap->palavra[i]->palavra != NULL) 
				{
					strcpy(heap->palavra[i]->palavra,str[i]->palavra); // copia memoria 
					
				}
				else
				{
					free(heap->palavra[i]);
					free(heap);
					exit(1);
				}
			}
			constroiHeap(heap);
		}
	}
}

/* Faz uma fila prioridades, seguindo as propiedade do heap */

void minHeapify(TpHeap *A,long i) { /* Heap minimo para arquivos */
	
	if (A->tamanho <= 1)
		return;
	
	long l = Left(i);
	long r = Right(i);
	long menor;
	
	if( ( l <= A->tamanho) && ( (comparaString( A->palavra[l], A->palavra[i],A->flagAtual ) == 1 ) ) ) //  || (comparaString( A->palavra[l], A->palavra[i],A->flagAtual ) == 2 )
	{
		menor = l;	
	}
	else 
	{
		menor = i;
	}
	if( (r <= A->tamanho)  && ( (comparaString( A->palavra[r],A->palavra[menor],A->flagAtual ) == 1 ) ) )
	{
		menor = r;	
	}
	if(menor != i) 
	{
		trocaString(&A->palavra[i]->palavra,&A->palavra[menor]->palavra);
		trocaArquivoFlag(A->palavra[i],A->palavra[menor]);
		
		minHeapify(A,menor);
	}
}

/* Reconstitui a propiedade do heap */

void heapSort(TpHeap *heap)
{
	if(heap)
	{
		constroiHeap(heap);

		if(heap == NULL)
		{
			freeHeap(heap);
			return;
		}
		
		long i,m = heap->tamanho;

		for (i = heap->tamanho; i >= 2; i--)
		{
			trocaString(&heap->palavra[1]->palavra, &heap->palavra[i]->palavra);
			trocaArquivoFlag(heap->palavra[1],heap->palavra[i]);
			
			m = m - 1;

			minHeapify(heap,m);
		}
	}
}

/* Insere uma TpPalavra no heap, recontituindo sua propiedade */

void heapInsereChave(TpHeap *heap, int i,TpPalavra *chave) {

	if(heap && chave)
	{
		long tamanho = heap->tamanho;
		TpPalavra **temp = (TpPalavra**) realloc (heap->palavra,sizeof(TpPalavra*) * (tamanho + 1));
		
		if(temp)
		{
			heap->palavra = temp;
			
			heap->palavra[i] = (TpPalavra*) malloc (sizeof (TpPalavra));

			if(!heap->palavra[i])
			{
				freeHeap(heap);
				exit(1);
			}
			heap->palavra[i]->palavra = (char*) malloc ( (strlen(chave->palavra) + 1) * sizeof(char) );
		
			if(!heap->palavra[i]->palavra)
			{
				freeHeap(heap);
				exit(1);
			}
			strcpy(heap->palavra[i]->palavra, chave->palavra);
			heap->palavra[i]->flag = chave->flag;
			heap->palavra[i]->narquivo = chave->narquivo;
	
			while( i > 1 && ( comparaString(heap->palavra[Parent(i)],heap->palavra[i],heap->flagAtual )  == 1 || (comparaString( heap->palavra[Parent(i)], heap->palavra[i],heap->flagAtual ) == 2 ) ) )
			{
				trocaString(&heap->palavra[i]->palavra,&heap->palavra[Parent(i)]->palavra);
				trocaArquivoFlag(heap->palavra[i],heap->palavra[Parent(i)]);

				i = Parent(i);
			}
		}
	}	
}

/* Remove uma string na posição 1 e reconstitui a propiedade do heap */

TpPalavra *heapRemove(TpHeap *heap) {

	if(heap)
	{
		if(heap->tamanho >= 1)
		{
			TpPalavra *menor = heap->palavra[1];
		
			heap->palavra[1] = heap->palavra[heap->tamanho];
			heap->tamanho--;
			
			minHeapify(heap,1);

			return menor;
		}
	}
	return NULL;
}

/* Dá um free nas posições do heap e no mesmo */

void freeHeap(TpHeap *heap) {

	if(heap) 
	{
		long i;
		long tam = heap->tamanho;
		for(i = 1; i <= tam; i++) {
		
			if(heap->palavra[i]->palavra)
			{
				free(heap->palavra[i]->palavra);
				
				if(heap->palavra[i])
				{
					free(heap->palavra[i]);
				}
			}
			else
			{
				break;
			}
		}
		free(heap->palavra);
		free(heap);
	}
}

/* Limpa as posições das fitas,e a fita, fecha os arquivos */

void freeFitas(TpArquivo **arquivos) {
	
	if(arquivos)
	{
		
		int i;
		
		for(i = 1; i <= NARQUIVOS; i++) {

				fclose(arquivos[i]->arquivo);
		}
		for(i = 1; i <= NARQUIVOS; i++) {

			free(arquivos[i]->nome);
			free(arquivos[i]);
		}
		free(arquivos);
		
	}
}

/* Salva Bloco, retira sempre o menor do heap até esvaziar o mesmo */

void salvaBloco(TpHeap *heap, FILE *A) {

	if(heap && A) 
	{

		long i, tamanho = heap->tamanho;
	
		for( i = 1 ; i <= tamanho; i++ ) {
		
			TpPalavra *pal = heapRemove(heap);
			fprintf(A, "%s%c", pal->palavra,(char)CODIGO_DELETE );

			free(pal->palavra);
			free(pal);
		}
		fprintf(A,"%c",(char)CODIGO_ESC);
	}
}
/* Retorna a flag contrária */

int flagContrario(TpHeap *heap) {

	if(heap)
	{
		if(heap->flagAtual == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return -1;
}

/* Verifica qual flag esta atualmente e retorna 2 caso for igual, assim tem o controle para ver quando se deve salvar o bloco */

int verificaFlag(TpHeap *heap) {

	int contador = 1;

	if(!heap || !heap->palavra || !heap->tamanho )
	{
		return 0;
	}
	else
	{
		if( heap->palavra[1]->flag == heap->flagAtual )
		{
			contador = 2;
		}
	}
	return contador;
}
/* Verica se todos os arquivos já foram lidos até o fim, volta os arquivos na posição zero , chama a intercalação balanceada */

void retornoProximo(TpArquivo **arquivos,TpArquivo **fitas,TpHeap *heap1,TpHeap *heap2) {

	if(arquivos == NULL || fitas == NULL)
	{
		exit(1);
	}
	int i;
	if( retornoFimArquivos(arquivos) == NARQUIVOS )
	{
		for(i = 1; i <= NARQUIVOS; i++) 
		{
			arquivos[i]->ativo = 1;
		}
		TpHeap *heap = (TpHeap*) malloc (sizeof(TpHeap));
		TpHeap *hRemove = (TpHeap*) malloc (sizeof(TpHeap));
		
		if(heap != NULL && hRemove != NULL)
		{
			for(i = 1; i <= NARQUIVOS; i++) {
	
				fseek(fitas[i]->arquivo,0,SEEK_SET);
				arquivos[i]->arquivo = freopen(arquivos[i]->nome, "w+",arquivos[i]->arquivo);
				fitas[i]->ativo = 1;
				arquivos[i]->ativo = 1;
				arquivos[i]->nBlocos = 0;
			}
			heap->tamanho = 0;
			hRemove->tamanho = 0;
			heap->flagAtual = 0;
			hRemove->flagAtual = 0;
			
			intercalacaoBalanceada(fitas,arquivos,heap,hRemove);
			for(i = 1; i <= NARQUIVOS; i++) {

				arquivos[i]->arquivo = freopen(arquivos[i]->nome, "w+",arquivos[i]->arquivo);
				fitas[i]->arquivo = freopen(fitas[i]->nome, "w+",fitas[i]->arquivo);
				fitas[i]->ativo = 1;
				arquivos[i]->ativo = 1;
				arquivos[i]->nBlocos = 0;
				fitas[i]->nBlocos = 0;
			}
			freeHeap(heap);
			free(hRemove);
			return;
		}
	}

}
/* Retorna os numero de arquivos que foi lido até o final neste momento da chamada */

int retornoFimArquivos(TpArquivo **arquivos) {

	if(arquivos != NULL)
	{
		int i,cont = 0;
		
		for(i = 1; i <= NARQUIVOS; i++) {
		
			if( feof(arquivos[i]->arquivo) )
			{
				arquivos[i]->ativo = 0;
				cont++;
			}
		}
		return cont;
	}
	return -1;
}

/* Salva os o heap em um arquivo 'x' e verifica se algum esta vazio, se estiver já coloca o arquivo como inativo  retornando o numero de arquivos inativos */

int Salva(TpHeap *heap, TpArquivo **arquivos,TpArquivo **destino,int narquivo) {

	if(arquivos != NULL && destino != NULL)
	{
		heapSort(heap);
		salvaBloco(heap,destino[narquivo]->arquivo);
		destino[narquivo]->nBlocos++;
		int i,contador = 0;
		long tamanho = heap->tamanho;
		for(i = 1; i <= tamanho; i++) {

			free(heap->palavra[i]->palavra);
			free(heap->palavra[i]);
			heap->tamanho--;
		}
		for(i = 1; i <= NARQUIVOS; i++) {
	
			if( feof(arquivos[i]->arquivo)  )
			{
				arquivos[i]->ativo = 0;
				contador++;
			}
			else
			{
				arquivos[i]->ativo = 1;
			}
		}
		return contador;
	}
	return 0;
}

/* Função onde obtem o arquivo RESULTADO com as strings ordenadas, retira string por string dos arquivos, faz um heapSort, escrevendo sempre no arquivo a menor, ou seja a que esta na posição 1 */

void resultado(TpArquivo **arquivos,TpHeap *heap) {
	
	if(arquivos != NULL && heap != NULL)
	{
		
		FILE *saida = fopen("RESULTADO","w+");
		
		if(saida == NULL)
		{
			printf("ERRO AO ABRIR ARQUIVO\n\n");
			freeFitas(arquivos);
			exit(1);
		}
		if(heap != NULL && saida != NULL)
		{
			heapNovo(arquivos,heap);
			
			long auxiliar;
			int j,indice = heap->palavra[1]->narquivo;
			char *string = retornoString( arquivos[indice]->arquivo );
			
			while( string )
			{
				TpPalavra *palavra = heapRemove(heap);
				
				fprintf( saida, "%s ", palavra->palavra);
				
				TpPalavra *chave = (TpPalavra*) malloc ( sizeof(TpPalavra) );

				if(chave != NULL)
				{
					chave->palavra = (char*) malloc ( ( strlen(string) + 1) * sizeof(char) );
					if(chave->palavra)
					{
						strcpy(chave->palavra,string);
						chave->flag = heap->flagAtual;
						chave->narquivo = indice;
						heap->tamanho++;
						heapInsereChave(heap,heap->tamanho,chave);
						heapSort(heap);
						free(chave->palavra);
						free(chave);
					}
				}
				free(string);
				indice = palavra->narquivo;
				string = retornoString( arquivos[indice]->arquivo );
				
				if(!string)
				{
					arquivos[indice]->ativo = 0;
					auxiliar = heap->tamanho;
					for (j = 1; j <= auxiliar; j++) {
						indice = j;
				
						if( arquivos[indice]->ativo == 1 && feof(arquivos[indice]->arquivo) == 0 )
						{
							string = retornoString(arquivos[indice]->arquivo);
							
							if (!string)
							{
								arquivos[indice]->ativo = 0;
							}
							else
							{
								arquivos[indice]->ativo = 1;
								break;
							}
						}
					
				
					}
					if(j > heap->tamanho && !string )
					{
						for (j = 1; j <= NARQUIVOS; j++) 
						{
							indice = j;
						
							if( arquivos[indice]->ativo == 1 && feof(arquivos[indice]->arquivo) == 0 )
							{
								string = retornoString(arquivos[indice]->arquivo);
								if (!string)
								{
									arquivos[indice]->ativo = 0;
								}
								else
								{
									arquivos[indice]->ativo = 1;
									break;
								}
							}
						}
					}
				}
				if( retornoFimArquivos(arquivos) == ( (NARQUIVOS) - 1 ) )
				{
					for(j = 1; j <= heap->tamanho; j++) {
						
						fprintf( saida, "%s ", heap->palavra[j]->palavra);
					}
					for(j = 1 ; j <= NARQUIVOS;j++) {
						
						if(feof(arquivos[j]->arquivo) == 0)
						{
							indice = j;
						}
					}
					string = retornoString( arquivos[indice]->arquivo );
					
					while( string ) {
					
						fprintf( saida, "%s ", string);
						free(string);
						string = retornoString( arquivos[indice]->arquivo);
						if(!string)
						{
							break;
						}
					}
					
				}
				
				free(palavra->palavra);
				free(palavra);
			}
		}
	}
	else
	{
		return;
	}
}

/* 2 X Fitas :: faz a intercalação balanceada. Onde retira string dos arquivos. Deixa os blocos inativos e ativa novamente só quando todos forem lidos. Quando tiver um bloco cada arquivo ou nenhum(arquivo vazio) chama a função resultado onde vai obter um arquivo ordenado*/

void intercalacaoBalanceada(TpArquivo **A,TpArquivo **B,TpHeap *heap,TpHeap *hRemove) {
	
	if(A == NULL || B == NULL || heap == NULL || hRemove == NULL)
	{
		printf("ERRO\n");
		exit(1);
	}
	int i,j,contador = 0,k = 0;
	long auxiliar = 0;
	
	for(i = 1;i <= NARQUIVOS;i++) { 

		if(A[i]->nBlocos <= 1 || feof(A[i]->arquivo) ) 
		{
			k++;
		}
		auxiliar = auxiliar + A[i]->nBlocos;
	}
	if(k == NARQUIVOS)
	{
		resultado(A,heap);
		return;
	}
	k = 1;
	heapNovo(A,heap);
	hRemove->palavra = (TpPalavra**) malloc (sizeof (TpPalavra*) );

	if(hRemove->palavra == NULL)
	{
		free(hRemove);
		freeHeap(heap);
		freeFitas(A);
		freeFitas(B);
		exit(1);
	}
	hRemove->tamanho = 0;
	hRemove->flagAtual = 0;
	
	int indice = heap->palavra[1]->narquivo;
	char *string = retornoString( A[indice]->arquivo );
	
	if( string )
	{
		A[indice]->ativo = 1;
		
		while( string )
		{
			TpPalavra *palavra = heapRemove(heap);
			
			if(palavra->palavra == NULL)
			{
				break;
			}
			inserirPalavraHeap(palavra->palavra,hRemove,k);
			
			TpPalavra *chave = (TpPalavra*) malloc ( sizeof(TpPalavra) );

			if(chave != NULL)
			{
				chave->palavra = (char*) malloc ( ( strlen(string) + 1) * sizeof(char) );
				if(chave->palavra)
				{
					strcpy(chave->palavra,string);
					chave->flag = heap->flagAtual;
					chave->narquivo = indice;
					heap->tamanho++;
					long tamanho = heap->tamanho;
					heapInsereChave(heap,tamanho,chave);
					heapSort(heap);
				}
			}
			free(string);
			indice = palavra->narquivo;
			string = retornoString(A[indice]->arquivo);
			
			if( !string )
			{	
				A[indice]->ativo = 0;
				contador++;
				if(contador == NARQUIVOS) 
				{
					contador = Salva(hRemove,A,B,k);
					if(contador == NARQUIVOS)
					{
						break;
					}
					k++;
					if( k > NARQUIVOS)
					{
						k = 1;
					}
				}
				auxiliar = heap->tamanho;
				for (j = 1; j <= auxiliar; j++) 
				{
					
					indice = j;
				
					if( A[indice]->ativo == 1 && feof(A[indice]->arquivo) == 0 )
					{
						string = retornoString(A[indice]->arquivo);
						if (!string)
						{
							A[indice]->ativo = 0;
							contador++;
							if(contador == NARQUIVOS ) 
							{
								contador = Salva(hRemove,A,B,k);
								if(contador == NARQUIVOS )
								{
									break;
								}
								k++;
								if( k > NARQUIVOS)
								{
									k = 1;
								}
							}
						}
						else
						{
							A[indice]->ativo = 1;
							break;
						}
					}
					
				
				}
				if(!string )
				{
					for (j = 1; j <= NARQUIVOS; j++) 
					{
						indice = j;
						
						if( A[indice]->ativo == 1 && feof(A[indice]->arquivo) == 0 )
						{
							string = retornoString(A[indice]->arquivo);
							if (!string)
							{
								A[indice]->ativo = 0;
								contador++;
								if(contador == NARQUIVOS) 
								{
									contador = Salva(hRemove,A,B,k);
									if(contador == NARQUIVOS )
									{
										break;
									}
									k++;
									if( k > NARQUIVOS)
									{
										k = 1;
									}
								}
							}
							else
							{
								A[indice]->ativo = 1;
								break;
							}
						}
					}
				}
			}
			free(chave->palavra);
			free(chave);
		
			free(palavra->palavra);
			free(palavra);
		}
		if( retornoFimArquivos(A) == NARQUIVOS )
		{
			if(heap->tamanho >= 1 || hRemove->tamanho >= 1)
			{
				int tamanho = heap->tamanho;
				
				for(i = 1; i <= tamanho; i++) {
				
					TpPalavra *palavra = heapRemove(heap);
					inserirPalavraHeap(palavra->palavra,hRemove,k);
					free(palavra->palavra);
					free(palavra);
				}
				heap->tamanho = 0;
				free(heap->palavra);
				if(k < NARQUIVOS)
				{
					k++;
				}
				else
				{
					k = 1;
				}
				if(hRemove->tamanho > 0)
				{
					heapSort(hRemove);
					salvaBloco(hRemove,B[k]->arquivo);
					if (hRemove == NULL)
					{
						printf("FALHA\n\n");
						return;
					}
				}
			}
			free(hRemove->palavra);
			
			for(i = 1; i <= NARQUIVOS; i++) {

				fseek(B[i]->arquivo,0,SEEK_SET);
				A[i]->arquivo = freopen(A[i]->nome, "w+",A[i]->arquivo);
				A[i]->ativo = 1;
				B[i]->ativo = 1;
				A[i]->nBlocos = 0;
			}
			intercalacaoBalanceada(B,A,heap,hRemove);
		} 
		else 
		{
			printf("ERRO\n");
		}			
	}
}

/* Insere uma palavra no heap */

void inserirPalavraHeap(char *palavra,TpHeap *A,int narquivo) {

	if(palavra != NULL && A != NULL)
	{
		
		A->tamanho = A->tamanho + 1;
		long tamanho = A->tamanho;
		TpPalavra **temporario = (TpPalavra**) realloc ( A->palavra , ( tamanho + 1) * sizeof (TpPalavra*) );

		if(temporario != NULL)
		{
		 	A->palavra =  temporario;
		}	
		A->palavra[tamanho] = (TpPalavra*) malloc (sizeof (TpPalavra) );

		if( A->palavra[tamanho] != NULL)
		{ 
			A->palavra[tamanho]->palavra = (char*) malloc ( ( strlen(palavra) + 1 ) * sizeof(char) );						
			if(A->palavra[tamanho]->palavra)
			{
				strcpy(A->palavra[tamanho]->palavra,palavra);
				A->palavra[tamanho]->flag = A->flagAtual;
				A->palavra[tamanho]->narquivo = narquivo;
			}			
		}
	}
}
/* Insere string das fitas no heap */

void heapNovo(TpArquivo **arquivos,TpHeap *heap) {
	
	if(heap != NULL && arquivos != NULL)
	{
		heap->tamanho = 0;
		heap->flagAtual = 0;
		
		heap->palavra = (TpPalavra**) malloc (sizeof (TpPalavra*) );

		if( heap->palavra != NULL)
		{
			int i;
			long tamanho;
			
			for( i = 1; i <= NARQUIVOS; i++) {

				if(arquivos[i]->arquivo != NULL)
				{
					char *str = retornoString(arquivos[i]->arquivo);
					if(str)
					{
						tamanho = heap->tamanho + 1;
						heap->tamanho = tamanho;
						
						TpPalavra **temp = (TpPalavra**) realloc ( heap->palavra ,( tamanho + 1) * sizeof (TpPalavra*) );
	
						if(temp != NULL)
						{
							heap->palavra =  temp;
						}
						
						heap->palavra[tamanho] = (TpPalavra*) malloc ( sizeof(TpPalavra) );

						if( heap->palavra && arquivos[i]->arquivo != NULL && heap->palavra[tamanho] != NULL )
						{
							if( heap->tamanho <=  NARQUIVOS)
							{
								heap->palavra[tamanho]->palavra = (char*) malloc ( ( strlen(str) + 1 ) * sizeof(char) );	

								if(heap->palavra[tamanho]->palavra)
								{
									strcpy(heap->palavra[tamanho]->palavra,str);
									heap->palavra[tamanho]->flag = heap->flagAtual;
									heap->palavra[tamanho]->narquivo = i;
									
								}
							}
						}
					}
					else
					{
						arquivos[i]->ativo = 0;
					}
					free(str);
				}
			}	
			//printf("tamanho::%lu\n\n",heap->tamanho);
			heapSort(heap);
		}
	}
}
 
/* Faz a seleção por substituição */

void selecaoPorSubstituicao( TpHeap *heap,TpArquivo **arquivos,TpArquivo **fitas) {

	if(heap == NULL || arquivos == NULL || fitas == NULL)
	{
		free(heap);
		exit(1);
	}
	heap->flagAtual = 0;
	heap->tamanho = 0;
	heapNovo(arquivos,heap);
	
	TpHeap *A = (TpHeap*) malloc (sizeof(TpHeap));
	
	if(A != NULL) 
	{
		A->palavra = (TpPalavra**) malloc (sizeof (TpPalavra*) );
		
		if(A->palavra == NULL)
		{
			free(heap);
			freeFitas(arquivos);
			freeFitas(fitas);
			exit(1);
		}
		A->tamanho = 0;
		A->flagAtual = 0;
		
		int indice = heap->palavra[1]->narquivo;
		char *string = retornoString(arquivos[indice]->arquivo);
		
		if(!string) 
		{
			indice = heap->palavra[2]->narquivo;
			string = retornoString(arquivos[indice]->arquivo);
		}
		if(string)
		{	
			int k = 1;
			long i;
				
			while(string)
			{
				TpPalavra *palavra = substituiMenor(heap,string,indice);
				
				indice = palavra->narquivo;

				if(!palavra)
				{
					break;
				}
				inserirPalavraHeap(palavra->palavra,A,k);
				int troca =  verificaFlag(heap);
	
				if( troca == 1 && heap != NULL )
				{
					heapSort(A);
					
					salvaBloco(A,fitas[k]->arquivo);
					fitas[k]->nBlocos++;
					
					heap->flagAtual = flagContrario(heap);
					
					for(i = 1; i <= A->tamanho; i++) {
						
						free(A->palavra[i]->palavra);
						free(A->palavra[i]);
					}
					A->tamanho = 0;
					k++;
					if(k > NARQUIVOS)
					{
						k = 1;
					}
					
				}
				free(string);
				string = retornoString(arquivos[indice]->arquivo);
			
				if(!string)
				{
					int j;
					for(j = 1; j <= heap->tamanho; j++)
					{
						indice = j;
						if(string)
						{
							break;
						}
					}
					if(!string)
					{
						for(j = 1; j <= NARQUIVOS; j++) 
						{
							string = retornoString(arquivos[j]->arquivo);
					
							if (string)
							{
								indice = j;
								break;
							}
						}
					}
					if( retornoFimArquivos(arquivos) == NARQUIVOS )
					{
						if(heap->tamanho > 0 || A->tamanho > 0)
						{
							int tamanho = heap->tamanho;
			
							for(i = 1; i <= tamanho; i++) {
			
								TpPalavra *palavra = heapRemove(heap);
								inserirPalavraHeap(palavra->palavra,A,k);
								free(palavra->palavra);
								free(palavra);
							}
							if(A->tamanho > 0)
							{
								heapSort(A);
								salvaBloco(A,fitas[k]->arquivo);
								fitas[k]->nBlocos++;
							}
						}
						retornoProximo(arquivos,fitas,heap,A);
					}
				}
				free(palavra->palavra);
				free(palavra);
			}
			freeHeap(A);
		}
	}
}

/* Utilizada para verificar se a string que esta entrando é menor que a que esta saindo, se for menor marca com flag contraria */

TpPalavra *substituiMenor(TpHeap *heap, char *strI, int nArquivo) {

	if(heap)
	{

		TpPalavra *enter = (TpPalavra*) malloc ( sizeof(TpPalavra) );

		if(enter)
		{
			enter->palavra = (char*) malloc ( (strlen(strI) + 2) * sizeof(char));
			
			if( strcmp(strI,heap->palavra[1]->palavra) < 0)
			{
				strcpy(enter->palavra,strI);
				enter->flag = flagContrario(heap);;
				enter->narquivo = nArquivo;
			}
			else
			{
				strcpy(enter->palavra,strI);
				enter->flag = heap->flagAtual;
				enter->narquivo = nArquivo;
			}
			
			TpPalavra *m = heapRemove(heap);
			heap->tamanho++;
			long tamanho = heap->tamanho;
			heapInsereChave(heap,tamanho,enter);
			heapSort(heap);
			free(enter->palavra);
			free(enter);
			if(m != NULL)
			{
				return m;
			}
		}	
	}
	return NULL;
}
/* Redistribui os blocos nas fitas de 1 a 6 */

void redistribui( TpArquivo **arquivos ) {
	
	if(arquivos != NULL)
	{
		char *string = retornoString(arquivos[0]->arquivo);
		int k = 1;
		while(string) {
	
			fprintf(arquivos[k]->arquivo,"%s%c", string,(char)CODIGO_DELETE );
			free(string);
			string = retornoString(arquivos[0]->arquivo);
			if(!string)
			{
				fprintf(arquivos[k]->arquivo,"%c",(char)CODIGO_ESC);
				arquivos[k]->nBlocos++;
				k++;
				if(k > NARQUIVOS)
				{
					k = 1; 
				}
				
				if(!string) 
				{
					string = retornoString(arquivos[0]->arquivo);
					if( !string && feof(arquivos[0]->arquivo) )
					{
						break;
					}
		
				}
			}
				
			if(!string && feof(arquivos[0]->arquivo) == 0 ) 
			{
				string = retornoString(arquivos[0]->arquivo);
				if(!string && feof(arquivos[0]->arquivo) == 0 )
				{
					break;
				}
				else
				{
					free(string);
					string = retornoString(arquivos[0]->arquivo);
				}
		
			}
		
		}
		
		for(k = 1; k <= NARQUIVOS; k++) {
		
			fseek(arquivos[k]->arquivo,0,SEEK_SET);
			arquivos[k]->ativo = 1;
		}
		arquivos[0]->arquivo = freopen(arquivos[0]->nome, "w+",arquivos[0]->arquivo);
		arquivos[0]->nBlocos = 0;
		arquivos[0]->ativo = 1;
	}
}

/* Salva o heap no arquivo 0 verificando se algum foi lido totalmente e retorna o numero de arquivos que chegaram ao final */

int SalvaII(TpHeap *heap,TpArquivo **arquivos)  {

	if(arquivos != NULL && arquivos != NULL)
	{
		int i,contador = 0;
		heapSort(heap);
		salvaBloco(heap,arquivos[0]->arquivo);
		arquivos[0]->nBlocos++;
		long tamanho = heap->tamanho;
		for(i = 1; i <= tamanho; i++) {

			free(heap->palavra[i]->palavra);
			free(heap->palavra[i]);
			heap->tamanho--;
		}
		for(i = 1; i <= NARQUIVOS; i++) {

			if( feof(arquivos[i]->arquivo)  )
			{
				arquivos[i]->ativo = 0;
				contador++;
			}
			else
			{
				arquivos[i]->ativo = 1;
			}
		}
		return contador;
	}
	return 0;
}

/* Verifica se foi lido todos os arquivos, redistribui os blocos e chama a intercalação balanceada */ 

void retornoProximoII( TpArquivo **arquivos ) {

	if(arquivos == NULL)
	{
		exit(1);
	}
	int i;
	if( retornoFimArquivos(arquivos) == NARQUIVOS )
	{
		for(i = 0; i <= NARQUIVOS; i++) 
		{
			arquivos[i]->ativo = 1;
		}
		TpHeap *heap = (TpHeap*) malloc (sizeof(TpHeap));
		TpHeap *hRemove = (TpHeap*) malloc (sizeof(TpHeap));
		if(heap != NULL && hRemove != NULL)
		{
			fseek(arquivos[0]->arquivo,0,SEEK_SET);
			arquivos[0]->ativo = 1;
		
			for(i = 1; i <= NARQUIVOS; i++) {

				arquivos[i]->arquivo = freopen(arquivos[i]->nome, "w+",arquivos[i]->arquivo);
				arquivos[i]->ativo = 1;
				arquivos[i]->nBlocos = 0;
			
			}
			heap->tamanho = 0;
			hRemove->tamanho = 0;
			heap->flagAtual = 0;
			hRemove->flagAtual = 0;
		
			redistribui(arquivos);
			intercalacaoBalanceadaII(arquivos,heap,hRemove);
		
			for(i = 0; i <= NARQUIVOS; i++) {

				arquivos[i]->arquivo = freopen(arquivos[i]->nome, "w+",arquivos[i]->arquivo);
				arquivos[i]->ativo = 1;
				arquivos[i]->nBlocos = 0;
			}
			freeHeap(heap);
			free(hRemove);
			return;
		}
	}
}

/* Faz a intercação balanceada, jogando os blocos no arquivo 0  antes de chamar a recurção redistribui os blocos. Quando obtiver um bloco em cada arquivo ou tiver vazio chama função resultado */

void intercalacaoBalanceadaII(TpArquivo **arquivos, TpHeap* heap,TpHeap *hRemove) {

	if(arquivos == NULL || heap == NULL || hRemove == NULL)
	{
		printf("ERRO FATAL\n");
		exit(1);
	}
	int i,j,contador = retornoFimArquivos(arquivos),k = 0;
	long auxiliar = 0;
	
	for(i = 1;i <= NARQUIVOS;i++) { 
	
		if(arquivos[i]->nBlocos <= 1 || feof(arquivos[i]->arquivo) ) 
		{
			k++;
		}
		auxiliar = auxiliar + arquivos[i]->nBlocos;
	}
	if(k == NARQUIVOS)
	{
		resultado(arquivos,heap);
		return;
	}
	heapNovo(arquivos,heap);
	if(heap == NULL)
	{
		printf("heap esta nulo\n\n");
		exit(1);
	}
	hRemove->palavra = (TpPalavra**) malloc (sizeof (TpPalavra*) );

	if(hRemove->palavra == NULL)
	{
		printf("Erro ao Alocar Memória\n\n");
		free(hRemove);
		freeHeap(heap);
		freeFitas(arquivos);
		exit(1);
	}
	hRemove->tamanho = 0;
	hRemove->flagAtual = 0;
	
	int indice = heap->palavra[1]->narquivo;
	char *string = retornoString(arquivos[indice]->arquivo );
	
	if( string )
	{
		arquivos[indice]->ativo = 1;
		
		while( string )
		{
			TpPalavra *palavra = heapRemove(heap);
			
			if(palavra->palavra == NULL)
			{
				break;
			}
			inserirPalavraHeap(palavra->palavra,hRemove,0);
			
			TpPalavra *chave = (TpPalavra*) malloc ( sizeof(TpPalavra) );

			if(chave != NULL)
			{
				chave->palavra = (char*) malloc ( ( strlen(string) + 1) * sizeof(char) );
				if(chave->palavra)
				{
					strcpy(chave->palavra,string);
					chave->flag = heap->flagAtual;
					chave->narquivo = indice;
					heap->tamanho++;
					long tamanho = heap->tamanho;
					heapInsereChave(heap,tamanho,chave);
					heapSort(heap);
				}
			}
			free(string);
			indice = palavra->narquivo;
			string = retornoString(arquivos[indice]->arquivo);
			
			if( !string )
			{	
				arquivos[indice]->ativo = 0;
				contador++;
				if(contador == NARQUIVOS) 
				{
					contador = SalvaII(hRemove,arquivos);
					if(contador == NARQUIVOS)
					{
						break;
					}
				}
				auxiliar = heap->tamanho;
				for (j = 1; j <= auxiliar; j++) 
				{
					indice = j;
					if( arquivos[indice]->ativo == 1 && feof(arquivos[indice]->arquivo) == 0 )
					{
						string = retornoString(arquivos[indice]->arquivo);
						if (!string)
						{
							arquivos[indice]->ativo = 0;
							contador++;
							if(contador == NARQUIVOS ) 
							{
								contador = SalvaII(hRemove,arquivos);
								if(contador == NARQUIVOS )
								{
									break;
								}
							}
						}
						else
						{
							arquivos[indice]->ativo = 1;
							break;
						}
					}
					
				
				}
				if(!string)
				{
					for (j = 1; j <= NARQUIVOS; j++) 
					{
						indice = j;
						
						if( arquivos[indice]->ativo == 1 && feof(arquivos[indice]->arquivo) == 0 )
						{
							string = retornoString(arquivos[indice]->arquivo);
							if (!string)
							{
								arquivos[indice]->ativo = 0;
								contador++;
								if(contador == NARQUIVOS) 
								{
									contador = SalvaII(hRemove,arquivos);
									if(contador == NARQUIVOS )
									{
										break;
									}
								}
							}
							else
							{
								arquivos[indice]->ativo = 1;
								break;
							}
						}
					}
				}
			}
			free(chave->palavra);
			free(chave);
		
			free(palavra->palavra);
			free(palavra);
		}
		if( retornoFimArquivos(arquivos) == NARQUIVOS )
		{
		
			if(heap->tamanho >= 1 || hRemove->tamanho >= 1)
			{
				int tamanho = heap->tamanho;
				
				for(i = 1; i <= tamanho; i++) {
				
					TpPalavra *palavra = heapRemove(heap);
					inserirPalavraHeap(palavra->palavra,hRemove,0);
					free(palavra->palavra);
					free(palavra);
				}
				heap->tamanho = 0;
				free(heap->palavra);
				if(hRemove->tamanho >= 1)
				{
					heapSort(hRemove);
					salvaBloco(hRemove,arquivos[0]->arquivo);

					if (hRemove == NULL) {
					
						printf("FALHA\n\n");
					}

				}
			}
			free(hRemove->palavra);
			fseek(arquivos[0]->arquivo,0,SEEK_SET);
			for(i = 1; i <= NARQUIVOS; i++) {
			
				arquivos[i]->arquivo = freopen(arquivos[i]->nome, "w+",arquivos[i]->arquivo);
				arquivos[i]->ativo = 1;
				arquivos[i]->nBlocos = 0;
			}
			redistribui(arquivos);
			intercalacaoBalanceadaII(arquivos,heap,hRemove);
		} 
		else 
		{
			printf("ERRO\n");
			return;
		}			
	}
	return;
}

/* Faz seleção por substuição, removendo o primeiro da fila e quando muda flag insere as string em um bloco */

void selecaoPorSubstituicaoFMaisUmaFita( TpHeap *heap,TpArquivo **arquivos ) {

	if(heap == NULL || arquivos == NULL )
	{
		free(heap);
		exit(1);
	}
	heap->flagAtual = 0;
	heap->tamanho = 0;
	heapNovo(arquivos,heap);
	
	TpHeap *A = (TpHeap*) malloc (sizeof(TpHeap));
	
	if(A != NULL) 
	{
		A->palavra = (TpPalavra**) malloc (sizeof (TpPalavra*) );
		
		if(A->palavra == NULL)
		{
			free(heap);
			int i;
			for(i = 0; i <= NARQUIVOS; i++) {

				fclose(arquivos[i]->arquivo);
				free(arquivos[i]->nome);
				free(arquivos[i]);
			}
			exit(1);
		}
		A->tamanho = 0;
		A->flagAtual = 0;
		int k = 0;
		int indice = heap->palavra[1]->narquivo;
		char *string = retornoString(arquivos[indice]->arquivo);
		
		if(string)
		{	
			long i;
				
			while(string)
			{
				
				TpPalavra *palavra = substituiMenor(heap,string,indice);
				
				
				if(!palavra)
				{
					break;
				}
				inserirPalavraHeap(palavra->palavra,A,k);
				heapSort(A);
				int troca =  verificaFlag(heap);
	
				if( troca == 1 && heap != NULL )
				{
					salvaBloco(A,arquivos[k]->arquivo);
					arquivos[k]->nBlocos++;
					
					heap->flagAtual = flagContrario(heap);
					
					for(i = 1; i <= A->tamanho; i++) {
						
						free(A->palavra[i]->palavra);
						free(A->palavra[i]);
					}
					A->tamanho = 0;
				}
				free(string);
				indice = palavra->narquivo;
				string = retornoString(arquivos[indice]->arquivo);
			
				if(!string)
				{
					int j;
					for(j = 1; j <= heap->tamanho; j++)
					{
						indice = j;
						if(string)
						{
							break;
						}
					}
					if(!string)
					{
						for(j = 1; j <= NARQUIVOS; j++) 
						{
							string = retornoString(arquivos[j]->arquivo);
					
							if (string)
							{
								indice = j;
								break;
							}
						}
					}
					if( retornoFimArquivos(arquivos) == NARQUIVOS )
					{
						
						if(heap->tamanho > 0 || A->tamanho > 0)
						{
							long tamanho = heap->tamanho;
			
							for(i = 1; i <= tamanho; i++) {
			
								TpPalavra *palavra = heapRemove(heap);
								inserirPalavraHeap(palavra->palavra,A,k);
								free(palavra->palavra);
								free(palavra);
							}
							if(A->tamanho > 0)
							{
								heapSort(A);
								salvaBloco(A,arquivos[k]->arquivo);
								arquivos[k]->nBlocos++;
							}
						}
						retornoProximoII(arquivos);
					}
				}
				free(palavra->palavra);
				free(palavra);
			}
			freeHeap(A);
		}
	}
}
