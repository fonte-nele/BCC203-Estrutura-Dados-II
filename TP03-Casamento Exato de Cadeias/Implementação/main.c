/*
    Feito por:													Matrícula:
        Felipe Fontenele de Ávila Magalhães							15.1.4331
        Gilmar Marques Serafim Júnior								15.1.4314
        Mateus Vitor Pereira Lana									15.1.4340
        Thiago Oliveira de Santana                    				15.1.4313
 
    Data início: 21/07/2016			Término: 26/07/2016

    Disciplina: BCC 203 - Estrutura de Dados II
    Prof.: Guilherme Tavares de Assis


*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Cadeia.h"
#include "ForcaBruta.h"
#include "BM.h"
#include "BMHS.h"
#include "ShiftAnd.h"

int main(int argc, char* argv[]){
    if(argc<4 || argc>5){
        printf("\nFormato de entrada via linha de comando invalido!\n");
        printf("Formato esperado: <executavel> <metodo> <texto> <padrao> [-P](opcional)\n\n");
        return 0;
    }
    
    clock_t inicio, fim, total;
	double tempo;
    int op;
    char nome[20];
    long comp=0, desloc=0;
    op = atoi(argv[1]);
    strcpy(nome,argv[2]);
    
    while(op<1 || op>4){
		printf("\n  METODO DE CASAMENTO EXATO DE CADEIAS INVALIDO. FAVOR ESCOLHER UMA OPCAO DO MENU ABAIXO...\n\n");
		printf("   ============================================MENU============================================ \n");
		printf("  ||                                                                                          ||\n");
		printf("  || 1 - Forca Bruta.                                                                         ||\n");
		printf("  || 2 - Boyer-Moore(BM) com a heuristica ocorrencia.                                         ||\n");
		printf("  || 3 - Boyer-Moore-Horspool-Sunday(BHMS).                                                   ||\n");
		printf("  || 4 - Shift-And Exato.                                                                     ||\n");
		printf("  ||                                                                                          ||\n");
		printf("   ============================================================================================ \n\n");
		printf("  Escolha: ");
		fflush(stdin);
		scanf("%d",&op);
	}
	while(strcmp(nome ,"texto_pequeno") != 0 && strcmp(nome,"texto_medio") != 0 && strcmp(nome,"texto_grande") != 0){
		printf("\n  NOME DO ARQUIVO INVALIDO. FAVOR DIGITAR UM NOME REFERENTE AS OPCOES ABAIXO...\n\n");
		printf("   ============================================MENU============================================ \n");
		printf("  ||                                                                                          ||\n");
		printf("  || - texto_pequeno                                                                          ||\n");
		printf("  || - texto_medio                                                                            ||\n");
		printf("  || - texto_grande                                                                           ||\n");
		printf("  ||                                                                                          ||\n");
		printf("   ============================================================================================ \n\n");
		printf("  Escolha: ");
		fflush(stdin);
		scanf("%s",nome);
	}
    
    strcat(nome,".txt");
    TipoTexto tipoTexto;
    
    tipoTexto = lerTexto(nome);
    
    //padrão a ser pesquisado
    TipoPadrao tipoPadrao = malloc(sizeof(argv[3]));
    strcpy(tipoPadrao, argv[3]);

    //avalia qual método vai ser usado
    switch(op){
        case 1:{ //força bruta
            inicio = clock();
            printf("\nMetodo Forca Bruta:\n");
            if(!ForcaBruta(tipoTexto, strlen(tipoTexto), tipoPadrao, strlen(tipoPadrao),&comp,&desloc)){
                printf("\nPadrao nao encontrado\n");
            }
            
            fim = clock();
            total = fim - inicio;
            tempo = ((double)total)/CLOCKS_PER_SEC;
            if(argv[4] != NULL)
            {
                if(strcmp(argv[4],"[-P]") ==0 || strcmp(argv[4],"[-p]")==0)
                {
                    printf("\n\n    =========================================RESULTADOS=========================================");
                    printf("\n   ||                                                                                          ||");
                    printf("\n   ||  Metodo de casamento exato de cadeias: Forca Bruta                                       ||");
                    printf("\n   ||  Comparacoes entre os caracteres do texto e do padrao: %-7ld                           ||",comp);
                    printf("\n   ||  Deslocamentos realizados na varredura de todo o texto: %-7ld                          ||",desloc);
                    printf("\n   ||  Tempo de execucao do Forca Bruta: %.3f segundos.                                       ||",tempo);
                    printf("\n   ||                                                                                          ||");				
                    printf("\n    ============================================================================================\n\n");			
                }
            }
            break;
        }
        case 2: {//boyer-moore
            inicio = clock();
            printf("\nMetodo Boyer-Moore com a heuristica ocorrencia:\n");
            if(!BM(tipoTexto, strlen(tipoTexto), tipoPadrao, strlen(tipoPadrao),&comp,&desloc)){
                printf("\nPadrao nao encontrado\n");
            }
            
            fim = clock();
            total = fim - inicio;
            tempo = ((double)total)/CLOCKS_PER_SEC;
            if(argv[4] != NULL)
            {
                if(strcmp(argv[4],"[-P]") ==0 || strcmp(argv[4],"[-p]")==0)
                {
                    printf("\n\n    =========================================RESULTADOS=========================================");
                    printf("\n   ||                                                                                          ||");
                    printf("\n   ||  Metodo de casamento exato de cadeias: Boyer-Moore                                       ||");
                    printf("\n   ||  Comparacoes entre os caracteres do texto e do padrao: %-7ld                           ||",comp);
                    printf("\n   ||  Deslocamentos realizados na varredura de todo o texto: %-7ld                          ||",desloc);
                    printf("\n   ||  Tempo de execucao do Boyer-Moore: %.3f segundos.                                       ||",tempo);
                    printf("\n   ||                                                                                          ||");				
                    printf("\n    ============================================================================================\n\n");			
                }
            }
            break;
        }
        case 3:{ //boyer-moore-horspool-sunday
            inicio = clock();
            printf("\nMetodo Boyer-Moore-Horspool-Sunday(BMHS):\n");
            if(!BMHS(tipoTexto, strlen(tipoTexto), tipoPadrao, strlen(tipoPadrao),&comp,&desloc)){
                printf("\nPadrao nao encontrado\n");
            }
            
            fim = clock();
            total = fim - inicio;
            tempo = ((double)total)/CLOCKS_PER_SEC;
            if(argv[4] != NULL)
            {
                if(strcmp(argv[4],"[-P]") ==0 || strcmp(argv[4],"[-p]")==0)
                {
                    printf("\n\n    =========================================RESULTADOS=========================================");
                    printf("\n   ||                                                                                          ||");
                    printf("\n   ||  Metodo de casamento exato de cadeias: Boyer-Moore-Horspool-Sunday                       ||");
                    printf("\n   ||  Comparacoes entre os caracteres do texto e do padrao: %-7ld                           ||",comp);
                    printf("\n   ||  Deslocamentos realizados na varredura de todo o texto: %-7ld                          ||",desloc);
                    printf("\n   ||  Tempo de execucao do Boyer-Moore-Horspool-Sunday: %.3f segundos.                       ||",tempo);
                    printf("\n   ||                                                                                          ||");				
                    printf("\n    ============================================================================================\n\n");			
                }
            }
            break;
        }
        case 4:{ //shift-and exato
            inicio = clock();
            printf("\nMetodo Shift-And Exato:\n");
            if(!ShiftAnd(tipoTexto, strlen(tipoTexto), tipoPadrao, strlen(tipoPadrao),&comp,&desloc)){
                printf("\nPadrao nao encontrado\n");
            }
            
            fim = clock();
            total = fim - inicio;
            tempo = ((double)total)/CLOCKS_PER_SEC;
            if(argv[4] != NULL)
            {
                if(strcmp(argv[4],"[-P]") ==0 || strcmp(argv[4],"[-p]")==0)
                {
                    printf("\n\n    =========================================RESULTADOS=========================================");
                    printf("\n   ||                                                                                          ||");
                    printf("\n   ||  Metodo de casamento exato de cadeias: Shift-And Exato                                   ||");
                    printf("\n   ||  Comparacoes entre os caracteres do texto e do padrao: %-7ld                           ||",comp);
                    printf("\n   ||  Deslocamentos realizados na varredura de todo o texto: %-7ld                          ||",desloc);
                    printf("\n   ||  Tempo de execucao do Shift-And Exato: %.3f segundos.                                   ||",tempo);
                    printf("\n   ||                                                                                          ||");				
                    printf("\n    ============================================================================================\n\n");			
                }
            }
            break;
        }
    }
    
    free(tipoTexto);
    free(tipoPadrao);
    return 0;
}
