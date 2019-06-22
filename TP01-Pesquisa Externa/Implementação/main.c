/*
	Feito por:									Matrícula:
		Felipe Fontenele de Ávila Magalhães			15.1.4331
		Mateus Vitor Pereira Lana					15.1.4340
	Data início código: 02/05/2016				Término: ??????
	Disciplina: BCC 203 - Estrutura de Dados II
	Prof.: Guilherme Tavares de Assis
*/
#include "gerar_dados.h"
#include "acesso_sequencial_indexado.h"
#include "arvore_binaria.h"
#include "arvore_b.h"
#include "arvore_b_estrela.h"

int main(int argc,char *argv[])
{
	if(argc<5 || argc>6)
	{
		printf("\nFormato de entrada via linha de comando invalido!\n");
		return 0;
	}
	
    //Criacao do arquivo para escrita e leitura!!!
    FILE *arq;
    if((arq = fopen("numeros.bin", "w+b")) == NULL)
    {
        printf("\nERRO NA CRIACAO DO ARQUIVO 'NUMEROS.BIN'!!!\n");
        return 0;
    }
	clock_t inicio,fim,total;
	double tempo,tempo2;
	long comp_criacao=0,comp_pesq=0, trans_criacao=0, trans_pesq=0;
	int sit,tam,op,chave_digitada,status=0;
	op = atoi(argv[1]);
	tam = atoi(argv[2]);
	sit = atoi(argv[3]);
	chave_digitada = atoi(argv[4]);
	
	while(op<1 || op>4)
	{
		printf("\n  METODO DE PESQUISA INVALIDO. FAVOR ESCOLHER UMA OPCAO DO MENU ABAIXO...\n\n");
		printf("   ============================================MENU============================================ \n");
		printf("  ||                                                                                          ||\n");
		printf("  || 1 - Acesso Sequencial Indexado.                                                          ||\n");
		printf("  || 2 - Arvore Binaria de Pesquisa Adequado a Memoria Externa.                               ||\n");
		printf("  || 3 - Arvore B.                                                                            ||\n");
		printf("  || 4 - Arvore B*.                                                                           ||\n");
		printf("  ||                                                                                          ||\n");
		printf("   ============================================================================================ \n\n");
		printf("  Escolha: ");
		fflush(stdin);
		scanf("%d",&op);
	}
	while(sit<1 || sit>3)
	{
		printf("\n  SITUACAO DE ORDEM DO ARQUIVO INVALIDA. FAVOR ESCOLHER UMA OPCAO DO MENU ABAIXO...\n\n");
		printf("   ============================================MENU============================================ \n");
		printf("  ||                                                                                          ||\n");
		printf("  || 1 - Arquivo Ordenado Ascendentemente.                                                    ||\n");
		printf("  || 2 - Arquivo Ordenado Descendentemente.                                                   ||\n");
		printf("  || 3 - Arquivo Desordenado Aleatoriamente.                                                  ||\n");
		printf("  ||                                                                                          ||\n");
		printf("   ============================================================================================ \n\n");
		printf("  Escolha: ");
		fflush(stdin);
		scanf("%d",&sit);
	}
	while(tam<1 || tam>1000000)
	{
		printf("\n  QUANTIDADE DE REGISTROS INVALIDA. FAVOR DIGITE UMA QUANTIDADE ENTRE 1 E 1000000.\n\n");
		printf("  Digite: ");
		fflush(stdin);
		scanf("%d",&tam);
	}
	while(chave_digitada == 0)
	{
		printf("\n  CHAVE DIGITADA INVALIDA. FAVOR DIGITE UM NUMERO.\n\n");
		printf("  Digite: ");
		fflush(stdin);
		scanf("%d",&chave_digitada);
	}
	
	printf("\nCRIANDO ARQUIVO 'NUMEROS.BIN' ....");
	gerar_arq(arq,tam,sit);
    rewind(arq);
	
	switch(op)
	{
		case 1:
		{
			//Acesso Sequencial Indexado!!!
			//Etapa Criacao!
			inicio = clock();
			printf("\n\nMETODO DE PESQUISA: ACESSO SEQUENCIAL INDEXADO!\n");
			if(sit!=1)
			{
				printf("\nSITUACAO DE ORDEM DO ARQUIVO NAO SE APLICA A ESTE METODO!\n");
				break;
			}
			Indice *tabela;
			tabela = (Indice*)malloc((tam/NUM_ITENS_PAG+1)*sizeof(Indice));
			Item item;
			int pos = 0;
			//Criando tabela de indices!
			while(fread(&item,sizeof(item),1, arq) == 1)
			{
				trans_criacao++;
				fseek(arq,(NUM_ITENS_PAG-1)*sizeof(item),SEEK_CUR);
				tabela[pos].chave_indice = item.chave_item;
				pos++;
			}
			fclose(arq);
			fim = clock();
			total = fim - inicio;
			tempo = ((double)total)/CLOCKS_PER_SEC;
			
			//Etapa Pesquisa!
			inicio = clock();
			item.chave_item = chave_digitada;
			if(pesquisa(tabela,pos,&item,arq,&comp_pesq,&trans_pesq))
			{
				status = 1;
			}			
			fim = clock();
			total = fim - inicio;
			tempo2 = ((double)total)/CLOCKS_PER_SEC;
			free(tabela);
			
			if(status == 1)
			{
				printf("\n\n    =========================================RESULTADOS=========================================");
				printf("\n   ||                                                                                           ||");
				printf("\n   ||  Chave Encontrada com Sucesso: %-8d                                                   ||",item.chave_item);
				printf("\n   ||                                                                                           ||");				
				printf("\n   ||  Registro:                                                                                ||");
				printf("\n   ||  Dado 1: %-7ld                                                                          ||",item.dado1);
				printf("\n   ||  Dado 2: %-80s ||",item.dado2);
				printf("\n   ||  Tempo de execucao (etapa criacao) acesso sequencial indexado: %.3f segundos.            ||",tempo);
				printf("\n   ||  Tempo de execucao (etapa pesquisa) acesso sequencial indexado: %.3f segundos.           ||",tempo2);
				printf("\n   ||  Numero de transferencias arquivo (etapa criacao): %-8ld                               ||",trans_criacao);
				printf("\n   ||  Numero de transferencias arquivo (etapa pesquisa): %-8ld                              ||",trans_pesq);
				printf("\n   ||  Numero de comparacoes entre as chaves de pesquisa: %-8ld                              ||",comp_pesq);
				printf("\n   ||                                                                                           ||");				
				printf("\n    ============================================================================================\n\n");

			}
			else
			{
				printf("\n\n    =========================================RESULTADOS=========================================");
				printf("\n   ||                                                                                           ||");
				printf("\n   ||  Chave nao existe no arquivo: %-8d                                                    ||",item.chave_item);
				printf("\n   ||                                                                                           ||");
				printf("\n   ||  Tempo de execucao (etapa criacao) acesso sequencial indexado: %.3f segundos.            ||",tempo);
				printf("\n   ||  Tempo de execucao (etapa pesquisa) acesso sequencial indexado: %.3f segundos.           ||",tempo2);
				printf("\n   ||  Numero de transferencias arquivo (etapa criacao): %-8ld                               ||",trans_criacao);
				printf("\n   ||  Numero de transferencias arquivo (etapa pesquisa): %-8ld                              ||",trans_pesq);
				printf("\n   ||  Numero de comparacoes entre as chaves de pesquisa: %-8ld                              ||",comp_pesq);
				printf("\n   ||                                                                                           ||");				
				printf("\n    ============================================================================================\n\n");		
			}
			break;
		}
		case 2:
		{
			//Arvore Binaria de Pesquisa Adequada a memoria Externa!!!
			//Etapa Criacao!
			inicio = clock();
			printf("\n\nMETODO DE PESQUISA: ARVORE BINARIA DE PESQUISA!\n");
			Dados_arv_bin dados;
			TBinaria registro;
			trans_criacao++;
			fread(&dados,sizeof(Dados_arv_bin),1, arq);
			registro.no = dados;	//No raiz!
			registro.esq = -1;  	//No esquerdo!
			registro.dir = -1; 		//No direito!
			FILE *arvore;
			if((arvore = fopen("arvore.bin", "w+b")) == NULL)
			{
				printf("\nERRO NA CRIACAO DO ARQUIVO 'ARVORE.BIN'!!!\n");
				return 0;
			}
			int cont = 1;
			fwrite(&registro, sizeof(TBinaria), 1, arvore); //Salvando no raiz
			while(fread(&dados,sizeof(dados),1, arq) == 1)
			{
				trans_criacao++;
				if(inserir_arv_binaria(arvore,registro,dados,cont,sit,&trans_criacao,&comp_criacao));
				cont++;
			}
			fim = clock();
			total = fim - inicio;
			tempo = ((double)total)/CLOCKS_PER_SEC;
			
			//Etapa Pesquisa!
			inicio = clock();
			dados.chave = chave_digitada;
			rewind(arvore);
			if(pesquisar_arv_binaria(arvore,registro,&dados,&trans_pesq,&comp_pesq))
			{
				status = 1;
			}
			fclose(arvore);
			fclose(arq);
			fim = clock();
			total = fim - inicio;
			tempo2 = ((double)total)/CLOCKS_PER_SEC;
			
			if(status == 1)
			{
				printf("\n\n    =========================================RESULTADOS=========================================");
				printf("\n   ||                                                                                           ||");
				printf("\n   ||  Chave Encontrada com Sucesso: %-8d                                                   ||",dados.chave);
				printf("\n   ||                                                                                           ||");				
				printf("\n   ||  Registro:                                                                                ||");
				printf("\n   ||  Dado 1: %-7ld                                                                          ||",dados.dado1);
				printf("\n   ||  Dado 2: %-80s ||",dados.dado2);
				printf("\n   ||  Tempo de execucao (etapa criacao) arvore binaria: %.3f segundos.                        ||",tempo);
				printf("\n   ||  Tempo de execucao (etapa pesquisa) arvore binaria: %.3f segundos.                       ||",tempo2);
				printf("\n   ||  Numero de transferencias arquivo (etapa criacao): %-8ld                               ||",trans_criacao);
				printf("\n   ||  Numero de transferencias arquivo (etapa pesquisa): %-8ld                              ||",trans_pesq);
				printf("\n   ||  Numero de comparacoes entre as chaves de pesquisa (etapa criacao): %-8ld              ||",comp_criacao);
				printf("\n   ||  Numero de comparacoes entre as chaves de pesquisa (etapa pesquisa): %-8ld             ||",comp_pesq);
				printf("\n   ||                                                                                           ||");				
				printf("\n    ============================================================================================\n\n");

			}
			else
			{
				printf("\n\n    =========================================RESULTADOS=========================================");
				printf("\n   ||                                                                                           ||");
				printf("\n   ||  Chave nao existe no arquivo: %-8d                                                    ||",dados.chave);
				printf("\n   ||                                                                                           ||");
				printf("\n   ||  Tempo de execucao (etapa criacao) arvore binaria: %.3f segundos.                        ||",tempo);
				printf("\n   ||  Tempo de execucao (etapa pesquisa) arvore binaria: %.3f segundos.                       ||",tempo2);
				printf("\n   ||  Numero de transferencias arquivo (etapa criacao): %-8ld                               ||",trans_criacao);
				printf("\n   ||  Numero de transferencias arquivo (etapa pesquisa): %-8ld                              ||",trans_pesq);
				printf("\n   ||  Numero de comparacoes entre as chaves de pesquisa (etapa criacao): %-8ld              ||",comp_criacao);
				printf("\n   ||  Numero de comparacoes entre as chaves de pesquisa (etapa pesquisa): %-8ld             ||",comp_pesq);
				printf("\n   ||                                                                                           ||");				
				printf("\n    ============================================================================================\n\n");		
			}
			break;
		}
		case 3:
		{
			//ARVORE B!!!
			//Etapa Criacao!
			inicio = clock();
			printf("\n\nMETODO DE PESQUISA: ARVORE B!\n");
			Registro reg;
			Apont apont;
			inicializar(&apont);
			while(fread(&reg,sizeof(reg),1, arq) == 1)
			{
				trans_criacao++;
				inserir(reg,&apont,&comp_criacao);
			}
			fclose(arq);
			fim = clock();
			total = fim - inicio;
			tempo = ((double)total)/CLOCKS_PER_SEC;
			
			//Etapa Pesquisa!
			inicio = clock();
			reg.chave = chave_digitada;
			if(pesquisar(&reg,apont,&comp_pesq))
			{
				status = 1;
			}
			fim = clock();
			total = fim - inicio;
			tempo2 = ((double)total)/CLOCKS_PER_SEC;
			
			
			if(status == 1)
			{
				printf("\n\n    =========================================RESULTADOS=========================================");
				printf("\n   ||                                                                                           ||");
				printf("\n   ||  Chave Encontrada com Sucesso: %-8d                                                   ||",reg.chave);
				printf("\n   ||                                                                                           ||");				
				printf("\n   ||  Registro:                                                                                ||");
				printf("\n   ||  Dado 1: %-7ld                                                                          ||",reg.dado1);
				printf("\n   ||  Dado 2: %-80s ||",reg.dado2);
				printf("\n   ||  Tempo de execucao (etapa criacao) arvore B: %.3f segundos.                              ||",tempo);
				printf("\n   ||  Tempo de execucao (etapa pesquisa) arvore B: %.3f segundos.                             ||",tempo2);
				printf("\n   ||  Numero de transferencias arquivo (etapa criacao): %-8ld                               ||",trans_criacao);
				printf("\n   ||  Numero de comparacoes entre as chaves de pesquisa (etapa criacao): %-8ld              ||",comp_criacao);
				printf("\n   ||  Numero de comparacoes entre as chaves de pesquisa (etapa pesquisa): %-8ld             ||",comp_pesq);
				printf("\n   ||                                                                                           ||");				
				printf("\n    ============================================================================================\n\n");

			}
			else
			{
				printf("\n\n    =========================================RESULTADOS=========================================");
				printf("\n   ||                                                                                           ||");
				printf("\n   ||  Chave nao existe no arquivo: %-8d                                                    ||",reg.chave);
				printf("\n   ||                                                                                           ||");
				printf("\n   ||  Tempo de execucao (etapa criacao) arvore B: %.3f segundos.                              ||",tempo);
				printf("\n   ||  Tempo de execucao (etapa pesquisa) arvore B: %.3f segundos.                             ||",tempo2);
				printf("\n   ||  Numero de transferencias arquivo (etapa criacao): %-8ld                               ||",trans_criacao);
				printf("\n   ||  Numero de comparacoes entre as chaves de pesquisa (etapa criacao): %-8ld              ||",comp_criacao);
				printf("\n   ||  Numero de comparacoes entre as chaves de pesquisa (etapa pesquisa): %-8ld             ||",comp_pesq);
				printf("\n   ||                                                                                           ||");				
				printf("\n    ============================================================================================\n\n");		
			}
			
			/*
			//Perguntar Guilherme!!!
			printf("\n   Caminhamento Arvore B\n\n");
			caminhamento(apont);
			*/
			break;
		}
		case 4:
		{
			//Arvore B*!!!
			//Etapa Criacao!
			inicio = clock();
			printf("\n\nMETODO DE PESQUISA: ARVORE B*!\n");
			Reg reg2;
			ApontEstrela apont2;
			inicializarEstrela(&apont2);
			while(fread(&reg2,sizeof(reg2),1, arq) == 1)
			{
				//printf("Chave: %d\n",reg2.chave);
				trans_criacao++;
				insere(reg2,&apont2,&comp_criacao);
			}
			fim = clock();
			total = fim - inicio;
			tempo = ((double)total)/CLOCKS_PER_SEC;
			
			printf("\n Pesquisa B Estrela.\n\n");
			//Etapa Pesquisa!
			inicio = clock();
			reg2.chave = chave_digitada;
			//printf("Aqui");
			if(pesquisar_estrela(&reg2,&apont2,&comp_pesq))
			{
				status = 1;
			}
			fim = clock();
			total = fim - inicio;
			tempo2 = ((double)total)/CLOCKS_PER_SEC;
			fclose(arq);
			
			if(status == 1)
			{
				printf("\n\n    =========================================RESULTADOS=========================================");
				printf("\n   ||                                                                                           ||");
				printf("\n   ||  Chave Encontrada com Sucesso: %-8d                                                   ||",reg2.chave);
				printf("\n   ||                                                                                           ||");				
				printf("\n   ||  Registro:                                                                                ||");
				printf("\n   ||  Dado 1: %-7ld                                                                          ||",reg2.dado1);
				printf("\n   ||  Dado 2: %-80s ||",reg2.dado2);
				printf("\n   ||  Tempo de execucao (etapa criacao) arvore B*: %.3f segundos.                             ||",tempo);
				printf("\n   ||  Tempo de execucao (etapa pesquisa) arvore B*: %.3f segundos.                            ||",tempo2);
				printf("\n   ||  Numero de transferencias arquivo (etapa criacao): %-8ld                               ||",trans_criacao);
				printf("\n   ||  Numero de comparacoes entre as chaves de pesquisa (etapa criacao): %-8ld              ||",comp_criacao);
				printf("\n   ||  Numero de comparacoes entre as chaves de pesquisa (etapa pesquisa): %-8ld             ||",comp_pesq);
				printf("\n   ||                                                                                           ||");				
				printf("\n    ============================================================================================\n\n");

			}
			else
			{
				printf("\n\n    =========================================RESULTADOS=========================================");
				printf("\n   ||                                                                                           ||");
				printf("\n   ||  Chave nao existe no arquivo: %-8d                                                    ||",reg2.chave);
				printf("\n   ||                                                                                           ||");
				printf("\n   ||  Tempo de execucao (etapa criacao) arvore B*: %.3f segundos.                             ||",tempo);
				printf("\n   ||  Tempo de execucao (etapa pesquisa) arvore B*: %.3f segundos.                            ||",tempo2);
				printf("\n   ||  Numero de transferencias arquivo (etapa criacao): %-8ld                               ||",trans_criacao);
				printf("\n   ||  Numero de comparacoes entre as chaves de pesquisa (etapa criacao): %-8ld              ||",comp_criacao);
				printf("\n   ||  Numero de comparacoes entre as chaves de pesquisa (etapa pesquisa): %-8ld             ||",comp_pesq);
				printf("\n   ||                                                                                           ||");				
				printf("\n    ============================================================================================\n\n");
			}
			break;
		}
	}
    return 0;
}