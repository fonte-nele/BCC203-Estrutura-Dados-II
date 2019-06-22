/* 
    Feito por:													Matrícula:
        Felipe Fontenele de Ávila Magalhães		15.1.4331
        Gilmar Marques Serafim Júnior				15.1.4314
        Mateus Vitor Pereira Lana						15.1.4340
        Thiago Oliveira de Santana                     15.1.4313
 
    Data início: 13/06/2016			Término: 19/07/2016
    
    Disciplina: BCC 203 - Estrutura de Dados II
    Prof.: Guilherme Tavares de Assis
 */
#include "GerarDados.h"
#include "QuicksortExterno.h"
#include "Interc_Balanceada.h"
#include "Interc_Balanceada_Sub.h"

int main(int argc, char *argv[])
{
    if(argc<4 || argc>5)
    {
        printf("\nFormato de entrada via linha de comando invalido!\n");
        printf("Formato esperado: <executavel> <metodo> <quantidade> <situacao> [-P](opcional)\n\n");
        return 0;
    }
    int metodo, tam, sit;
    metodo = atoi(argv[1]);
    tam = atoi(argv[2]);
    sit = atoi(argv[3]);
    
    while(metodo<1 || metodo>4)
    {
        printf("\n  METODO DE ORDENACAO INVALIDO. FAVOR ESCOLHER UMA OPCAO DO MENU ABAIXO...\n\n");
        printf("   ============================================MENU============================================ \n");
        printf("  ||                                                                                          ||\n");
        printf("  || 1 - Intercalacao Balanceada 2f fitas, metodo ordenacao interna 'Estrutura de Dados I'.   ||\n");
        printf("  || 2 - Intercalacao Balanceada 2f fitas, tecnica selecao por substituicao.                  ||\n");
        printf("  || 3 - Intercalacao Balanceada f+1 fitas, tecnica selecao por substituicao.                 ||\n");
        printf("  || 4 - Quicksort Externo.                                                                   ||\n");
        printf("  ||                                                                                          ||\n");
        printf("   ============================================================================================ \n\n");
        printf("  Escolha: ");
        fflush(stdin);
        scanf("%d",&metodo);
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
    while(tam != 100 && tam != 1000 && tam != 10000 && tam != 100000 && tam != 471705)
    {
        printf("\n  QUANTIDADE DE REGISTROS INVALIDA. FAVOR DIGITE UMA QUANTIDADE VALIDA, QUE SAO: 100, 1000, 10000, 100000 E 471705.\n\n");
        printf("  Digite: ");
        fflush(stdin);
        scanf("%d",&tam);
    }
    
	clock_t inicio, fim, total;
	double tempo_total;
	
    //Criacao arquivo para escrita e leitura!
    if(!GerarArq(tam,sit))
    {
        printf("\nArquivo binario nao pode ser gerado! FAVOR REINICIAR O PROGRAMA\n");
    }
    
    switch(metodo)
    {
        case 1:
        {
            /*Intercalacao balanceada 2f fitas, ordenacao interna "Estrutura de Dados I".*/
            inicio = clock();
			
            Analise desempenho;
            desempenho.Num_transf_read=0;
            desempenho.Num_transf_write=0;
            desempenho.Num_comparacoes=0;
            
			printf("\nExecutando metodo Intercalacao Balanceada 2f fitas !!!\n");
			
            //Criacao das firas!
			FILE *arq,*fitas[20];
			arq = fopen("provao.bin","rb");
			if(arq == NULL) 
			{
				printf("Arquivo nao pode ser aberto\n");
				return 0;
			}
			int i,j=0,cont=0,tamanho;
			char temp2[2];
			
			for(i=0; i<20; i++)
			{
				char temp[11] = "Fita_";
				sprintf(temp2,"%d",i+1);
				strcat(temp,temp2);		
				strcat(temp,".bin");
				
				fitas[i] = fopen(temp,"w+b");
				if(fitas[i] == NULL) 
				{
					printf("Arquivo nao pode ser aberto\n");
					return 0;
				}
			}
			tamanho = tam%10;
			if(tamanho != 0)
			{
				tamanho=1;
			}
			tamanho += (tam/10);
			
			for(i=0; i<tamanho; i++)
			{
				construir_blocos(arq,fitas,cont,j,&desempenho);
					
				cont++;
				j++;
				if(cont==10)
				{
					cont=0;
				}
			}
			
			for(i=0; i<10; i++)
			{
				rewind(fitas[i]);
			}
			
			intercalar_blocos(fitas,tamanho,&desempenho);
			FILE *saida;
            saida = fopen("SAIDA.txt","w");
            
			TipoReg reg;
			rewind(fitas[11]);
			i=0;
			while(fread(&reg,sizeof(TipoReg),1,fitas[11]))
			{
                fprintf(saida,"%-8ld %.1f %s %s %s\n",reg.mat,reg.nota,reg.estado,reg.cidade,reg.curso);
				i++;
			}
			
			fclose(arq);
			fclose(*fitas);
            fclose(saida);
			fim=clock();
			total = fim - inicio;
			tempo_total = ((double)total)/CLOCKS_PER_SEC;
            
            printf("\n\n    =========================================RESULTADOS=========================================");
			printf("\n   ||                                                                                          ||");
			printf("\n   ||  Metodo de ordenacao : Intercalacao Balanceada 2f fitas                                  ||");
			printf("\n   ||  Comparacoes entre valores do campo de ordenacao dos registros: %-7ld                  ||",desempenho.Num_comparacoes);
			printf("\n   ||  Transferencias(leitura) de registros da memoria externa para memoria interna: %-7ld   ||",desempenho.Num_transf_read);
			printf("\n   ||  Transferencias(escrita) de registros da memoria externa para memoria interna: %-7ld   ||",desempenho.Num_transf_write);
			printf("\n   ||  Tempo de execucao do Intercalacao Balanceada 2f fitas: %.3f segundos.                  ||",tempo_total);
			printf("\n   ||                                                                                          ||");				
			printf("\n    ============================================================================================\n\n");	
            printf("OBS.: OS DADOS GERADOS NA ORDENACAO ESTAO SALVOS EM OUTRO ARQUIVO DENOMINADO SAIDA.TXT\n\n");
            
            break;
        }
        case 2:
        {
            /*Intercalacao Balanceada 2f fitas, tecnica selecao por substituicao.*/
            inicio = clock();
			
			printf("\nExecutando metodo Intercalacao Balanceada 2f fitas!!!\n");
			
            Analise desempenho;
            desempenho.Num_transf_read=0;
            desempenho.Num_transf_write=0;
            desempenho.Num_comparacoes=0;
            
			FILE *arq,*fitas[20];
			arq = fopen("provao.bin","rb");
			if(arq == NULL) 
			{
				printf("Arquivo nao pode ser aberto\n");
				return 0;
			}
			int i,j=0,cont=0,tamanho;
			char temp2[2];
			
			for(i=0; i<20; i++)
			{
				char temp[11] = "Fita_";
				sprintf(temp2,"%d",i+1);
				strcat(temp,temp2);		
				strcat(temp,".bin");
				
				fitas[i] = fopen(temp,"w+b");
				if(fitas[i] == NULL) 
				{
					printf("Arquivo nao pode ser aberto\n");
					return 0;
				}
			}
			tamanho = tam%10;
			if(tamanho != 0)
			{
				tamanho=1;
			}
			tamanho += (tam/10);
			
			for(i=0; i<tamanho; i++)
			{
				construir_blocos_sub(arq,fitas,cont,j);
					
				cont++;
				j++;
				if(cont==10)
				{
					cont=0;
				}
				
			}
			
			for(i=0; i<10; i++)
			{
				rewind(fitas[i]);
			}
			
			//intercalar_blocos_sub(fitas,tamanho,&desempenho);
			
			fim=clock();
			total = fim - inicio;
			tempo_total = ((double)total)/CLOCKS_PER_SEC;

            
            printf("\n\n    =========================================RESULTADOS=========================================");
			printf("\n   ||                                                                                          ||");
			printf("\n   ||  Metodo de ordenacao : Intercalacao Balanceada 2f fitas                                   ||");
			printf("\n   ||  Comparacoes entre valores do campo de ordenacao dos registros: %-7ld                  ||",desempenho.Num_comparacoes);
			printf("\n   ||  Transferencias(leitura) de registros da memoria externa para memoria interna: %-7ld   ||",desempenho.Num_transf_read);
			printf("\n   ||  Transferencias(escrita) de registros da memoria externa para memoria interna: %-7ld   ||",desempenho.Num_transf_write);
			printf("\n   ||  Tempo de execucao do Intercalacao Balanceada 2f fitas: %.3f segundos.                                 ||",tempo_total);
			printf("\n   ||                                                                                          ||");				
			printf("\n    ============================================================================================\n\n");	
            printf("OBS.: OS DADOS GERADOS NA ORDENACAO ESTAO SALVOS EM OUTRO ARQUIVO DENOMINADO SAIDA.TXT\n\n");
            
            break;
        }
        case 3:
        {
            /*Intercalacao Balanceada f+1 fitas, tecnica selecao por substituicao.*/
            inicio = clock();
			
            Analise desempenho;
            desempenho.Num_transf_read=0;
            desempenho.Num_transf_write=0;
            desempenho.Num_comparacoes=0;
            
			printf("\nExecutando metodo Intercalacao Balanceada f+1 fitas!!!\n");
			
			//Criacao das firas!
			FILE *arq,*fitas[11];
			arq = fopen("provao.bin","rb");
			if(arq == NULL) 
			{
				printf("Arquivo nao pode ser aberto\n");
				return 0;
			}
			int i,j=0,cont=0,tamanho;
			char temp2[2];
			
			for(i=0; i<11; i++)
			{
				char temp[11] = "Fita_";
				sprintf(temp2,"%d",i+1);
				strcat(temp,temp2);		
				strcat(temp,".bin");
				
				fitas[i] = fopen(temp,"w+b");
				if(fitas[i] == NULL) 
				{
					printf("Arquivo nao pode ser aberto\n");
					return 0;
				}
			}
			tamanho = tam%10;
			if(tamanho != 0)
			{
				tamanho=1;
			}
			tamanho += (tam/10);
			
			for(i=0; i<tamanho; i++)
			{
				construir_blocos(arq,fitas,cont,j,&desempenho);
					
				cont++;
				j++;
				if(cont==10)
				{
					cont=0;
				}
			}
			
			for(i=0; i<10; i++)
			{
				rewind(fitas[i]);
			}
			
			intercalar_blocos(fitas,tamanho,&desempenho);
			FILE *saida;
            saida = fopen("SAIDA.txt","w");
            
			TipoReg reg;
			rewind(fitas[11]);
			i=0;
			while(fread(&reg,sizeof(TipoReg),1,fitas[11]))
			{
				printf("Matricula: %ld Nota: %.1f\n",reg.mat,reg.nota);
                fprintf(saida,"%-8ld %.1f %s %s %s\n",reg.mat,reg.nota,reg.estado,reg.cidade,reg.curso);
				i++;
			}
			
			fclose(arq);
			fclose(*fitas);
            fclose(saida);

			fim=clock();
			total = fim - inicio;
			tempo_total = ((double)total)/CLOCKS_PER_SEC;
            
            printf("\n\n    =========================================RESULTADOS=========================================");
			printf("\n   ||                                                                                          ||");
			printf("\n   ||  Metodo de ordenacao : Intercalacao Balanceada f+1 fitas                                   ||");
			printf("\n   ||  Comparacoes entre valores do campo de ordenacao dos registros: %-7ld                  ||",desempenho.Num_comparacoes);
			printf("\n   ||  Transferencias(leitura) de registros da memoria externa para memoria interna: %-7ld   ||",desempenho.Num_transf_read);
			printf("\n   ||  Transferencias(escrita) de registros da memoria externa para memoria interna: %-7ld   ||",desempenho.Num_transf_write);
			printf("\n   ||  Tempo de execucao do Intercalacao Balanceada: %.3f segundos.                                 ||",tempo_total);
			printf("\n   ||                                                                                          ||");				
			printf("\n    ============================================================================================\n\n");		
            printf("OBS.: OS DADOS GERADOS NA ORDENACAO ESTAO SALVOS EM OUTRO ARQUIVO DENOMINADO SAIDA.TXT\n\n");            
            break;
        }
        case 4:
        {			
			/*Quicksort Externo!*/
            /*Declaracao dos tipos utilizados pelo quicksort externo*/
			inicio = clock();
			
            TAnalise desempenho;
            desempenho.Num_transf_read=0;
            desempenho.Num_transf_write=0;
            desempenho.Num_comparacoes=0;
            
            FILE *ArqLEs;   /* Gerencia o Ls e o Es */
            FILE *ArqLEi;   /* Gerencia o Li e o Ei */
            TipoItem reg;
			
			printf("\nExecutando metodo QuickSort Externo!!!\n");
			
            ArqLEi = fopen("provao.bin", "r+b");
            if(ArqLEi == NULL)
            {
                printf("Arquivo nao pode ser aberto\n");
                return 0;
            }
            ArqLEs = fopen("provao.bin", "r+b");
            if(ArqLEs == NULL) 
            {
                printf ("Arquivo nao pode ser aberto\n");
                return 0;
            }
			
            QuicksortExterno(&ArqLEi, &ArqLEs, 1, tam,&desempenho);
            fflush(ArqLEi);
            fclose(ArqLEs);
            rewind(ArqLEi);
			
            FILE *saida;
            saida = fopen("SAIDA.txt","w");
			TipoItem *v;
			v = (TipoItem*)malloc(tam*sizeof(TipoItem));
			int cont=0,i=0;
			
			fseek(ArqLEi,0,SEEK_SET);
			
            while(fread(&reg, sizeof(TipoItem), 1, ArqLEi))  
            {
                v[i] = reg;				
				i++;
				cont ++;
				if(cont == tam)
				{
					break;
				}
            }
			fclose(ArqLEi);
			
			for(i=tam-1; i>=0; i--) 
            {
                fprintf(saida,"%-8ld %.1f %s %s %s\n",v[i].mat,v[i].nota,v[i].estado,v[i].cidade,v[i].curso);
            }
			free(v);
			fclose(saida);
			
			fim=clock();
			total = fim - inicio;
			tempo_total = ((double)total)/CLOCKS_PER_SEC;
            
            printf("\n\n    =========================================RESULTADOS=========================================");
			printf("\n   ||                                                                                          ||");
			printf("\n   ||  Metodo de ordenacao : Quicksort Externo                                                 ||");
			printf("\n   ||  Comparacoes entre valores do campo de ordenacao dos registros: %-7ld                  ||",desempenho.Num_comparacoes);
			printf("\n   ||  Transferencias(leitura) de registros da memoria externa para memoria interna: %-7ld   ||",desempenho.Num_transf_read);
			printf("\n   ||  Transferencias(escrita) de registros da memoria externa para memoria interna: %-7ld   ||",desempenho.Num_transf_write);
			printf("\n   ||  Tempo de execucao do Quicksort Externo: %.3f segundos.                                 ||",tempo_total);
			printf("\n   ||                                                                                          ||");				
			printf("\n    ============================================================================================\n\n");			
            printf("OBS.: OS DADOS GERADOS NA ORDENACAO ESTAO SALVOS EM OUTRO ARQUIVO DENOMINADO SAIDA.TXT\n\n");
			break;
        }
    }
    return 0;
}