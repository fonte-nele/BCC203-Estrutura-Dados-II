/* 
    Feito por:						matrícula:
        Felipe Fontenele de Ávila Magalhães		15.1.4331
        Gilmar Marques Serafim Júnior                   15.1.4314
        mateus Vitor Pereira Lana			15.1.4340
        Thiago Oliveira de Santana                      15.1.4313
 
    Data início: 13/06/2016			Término: ??????
    
    Disciplina: BCC 203 - Estrutura de Dados II
    Prof.: Guilherme Tavares de Assis
 */
#include "QuicksortExterno.h"

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
    while(tam<1 || tam>471705)
    {
        printf("\n  QUANTIDADE DE REGISTROS INVALIDA. FAVOR DIGITE UMA QUANTIDADE ENTRE 1 E 471705.\n\n");
        printf("  Digite: ");
        fflush(stdin);
        scanf("%d",&tam);
    }
    
    //Criacao arquivo para escrita e leitura!
    if(!GerarArq(tam,sit))
    {
        printf("\nArquivo nao pode ser aberto! FAVOR REINICIAR O PROGRAMA\n");
    }
    
    switch(metodo)
    {
        case 1:
        {
            /*Intercalacao balanceada 2f fitas, ordenacao interna "Estrutura de Dados I".*/
            /*Implementar*/
            
            break;
        }
        case 2:
        {
            /*Intercalacao Balanceada 2f fitas, tecnica selecao por substituicao.*/
            /*Implementar*/
            
            break;
        }
        case 3:
        {
            /*Intercalacao Balanceada f+1 fitas, tecnica selecao por substituicao.*/
            /*Implementar*/
            
            break;
        }
        case 4:
        {
            /*Quicksort Externo!*/
            /*Declaracao dos tipos utilizados pelo quicksort externo*/

            FILE *ArqLEs;   /* Gerencia o Ls e o Es */
            FILE *ArqLEi;   /* Gerencia o Li e o Ei */

            TipoItem reg;
            ArqLEi = fopen("teste.bin", "r+b");
            if(ArqLEi == NULL)
            {
                printf("Arquivo nao pode ser aberto\n");
                return 0;
            }
            ArqLEs = fopen("teste.bin", "r+b");
            if(ArqLEs == NULL) 
            {
                printf ("Arquivo nao pode ser aberto\n");
                return 0;
            }
            QuicksortExterno(&ArqLEi, &ArqLEs, 1, tam);
            fflush(ArqLEi);
            fclose(ArqLEs);
            fseek(ArqLEi,0, SEEK_SET);
            int cont=1;
            FILE* novo, *saida;
            novo = fopen("PROVAO_ORDENADO.txt","w");
            while(fread(&reg, sizeof(TipoItem), 1, ArqLEi))  
            {
                fprintf(novo,"%-8ld %.1f %s %s %s\n",reg.mat,reg.nota,reg.estado,reg.cidade,reg.curso);
                //fwrite(&reg, sizeof(Item), 1, Saida);
                //printf("Matricula %ld Registro %d Nota %.1f Estado %s Cidade %s Curso %s\n",reg.mat,cont,reg.nota,reg.estado,reg.cidade,reg.curso);
                cont++;
            }
            fclose(novo);
			fflush(ArqLEi);
            fseek(ArqLEi,0, SEEK_END);
			
			saida = fopen("PROVAO_DESORDENADO.txt","w");
			
			fseek(ArqLEi,-1*sizeof(TipoItem), SEEK_CUR);
			
			printf("Cheguei\n");
			int i=0;
			while(fread(&reg, sizeof(TipoItem), 1, ArqLEi))
			{
				fprintf(saida,"%-8ld %.1f %s %s %s\n",reg.mat,reg.nota,reg.estado,reg.cidade,reg.curso);
				fseek(ArqLEi,-2*sizeof(TipoItem), SEEK_CUR);
				i++;
				if(i== 471705)
				{
					break;
				}
			}
			printf("FUIII\n");
			
			/*
			TipoItem *v;
			v = (TipoItem*)malloc(471705*sizeof(TipoItem));
			char aux;
			int i,j;
			fscanf(novo,"\n");
			for(i=471705; i>=0; i--)
			{
				fscanf(novo,"%ld %f %s",&reg.mat,&reg.nota,reg.estado);
				aux = getc(novo);
				
				fgets(reg.cidade,50,novo);
				aux = getc(novo);
				//aux = getc(novo);
				fscanf(novo,"%[A-Z a-z]\n",reg.curso);

				v[i].mat = reg.mat;
				v[i].nota = reg.nota;
				for(j=0; j<3;j++)
				{
					v[i].estado[j] = reg.estado[j];
				}
				for(j=0; j<51;j++)
				{
					v[i].cidade[j] = reg.cidade[j];
				}
				for(j=0; j<31;j++)
				{
					v[i].curso[j] = reg.curso[j];
				}
				
				
				//fwrite(&reg, sizeof(Item), 1, Saida);
			}
			for(i=0; i<471705; i++)
			{
				fprintf(saida,"%-8ld %.1f %s %s %s\n",v[i].mat,v[i].nota,v[i].estado,v[i].cidade,v[i].curso);
			}
			free(v);
			*/
			fclose(ArqLEi);
            break;
        }
    }
    return 0;
}