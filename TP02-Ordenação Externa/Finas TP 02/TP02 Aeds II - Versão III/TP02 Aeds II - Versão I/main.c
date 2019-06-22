/* 
    Feito por:						Matrícula:
        Felipe Fontenele de Ávila Magalhães		15.1.4331
        Gilmar Marques Serafim Júnior                   15.1.4314
        Mateus Vitor Pereira Lana			15.1.4340
        Thiago Oliveira de Santana                      15.1.4313
 
    Data início: 13/06/2016			Término: ??????
    
    Disciplina: BCC 203 - Estrutura de Dados II
    Prof.: Guilherme Tavares de Assis
 */
#include "GerarDados.h"
#include "QuicksortExterno.h"

int main(int argc, char *argv[])
{
    if(argc<4 || argc>5)
    {
        printf("\nFormato de entrada via linha de comando invalido!\n");
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
        printf("  || 1 - Intercalacao Balanceada 2f fitas, metodo ordenacao interna ""Estrutura de Dados I"". ||\n");
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
    while(tam<1 || tam>471705)
    {
        printf("\n  QUANTIDADE DE REGISTROS INVALIDA. FAVOR DIGITE UMA QUANTIDADE ENTRE 1 E 471705.\n\n");
        printf("  Digite: ");
        fflush(stdin);
        scanf("%d",&tam);
    }
    
    //Criacao arquivo para escrita e leitura!
    GerarArq(tam,sit);
    
	FILE *ArqLi,*ArqEi,*ArqLEs;
    ArqLi = fopen("provao.bin", "r+b");
    if(ArqLi == NULL)
    {
        printf("Arquivo nao pode ser aberto\n");
        return 0;
    }
    ArqEi = fopen("provao.bin", "r+b");
    if(ArqEi == NULL) 
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
    TipoRegistro R;
    QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, 1, tam);
    fflush(ArqLi);
    fclose(ArqEi);
    fclose(ArqLEs);
    fseek(ArqLi,0, SEEK_SET);
    int cont=0;
    while(fread(&R, sizeof(TipoRegistro), 1, ArqLi))  
    {
        printf("Cont: %d Matricula: %-8ld Nota: %.1f\n",cont,R.Mat,R.Nota);
				
        cont++;
    }
    fclose(ArqLi);
    return 0;
}