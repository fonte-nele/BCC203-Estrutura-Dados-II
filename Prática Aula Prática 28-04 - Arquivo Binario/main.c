/*
	Feito por: Felipe Fontenele de Ávila Magalhães
	Data: 28/04/2016
	Disciplina: BCC 203 - Estrutura de Dados II
	Prof.: Guilherme Tavares de Assis
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    char mat[6];
    char nome[31];
    float nota[3];
    int faltas;
}Aluno;

int main()
{
    //Exercicio 1!!!
	printf("\n\n                                       EXERCICIO 1                                           \n");
	printf("   ============================================================================================= \n");
	printf("  ||   Nessa parte do programa, trabalha-se o conceito de arquivos .txt e .bin.Inicialmente eh ||\n");
	printf("  || aberto um arquivo.txt que consta notas de alunos de uma certa classe e faz-se a conversao ||\n");
	printf("  || para um arquivo .bin.                                                                     ||\n");
	printf("   ============================================================================================= \n\n");
	
    FILE *entrada, *saida;
    Aluno aluno;
    
    if((entrada = fopen("alunos.txt", "r")) == NULL)
	{
		printf("Arquivo nao pode ser aberto(texto)...\n");
		return 0;
	}
    if((saida = fopen("alunos.bin", "wb")) == NULL)
    {
        printf("Arquivo nao pode ser criado(binario)...\n");
        return 0;
    }
    printf("Impressao dos dados presentes no arquivo .txt somente para simples conferencia!\n\n");
    while(fscanf(entrada,"%s %[A-Z a-z] %f %f %f %d '\n'",aluno.mat,aluno.nome,&aluno.nota[0],&aluno.nota[1],&aluno.nota[2],&aluno.faltas) != EOF)
	{
		printf("%s %-18s %.1f %.1f %.1f %d\n",aluno.mat,aluno.nome,aluno.nota[0],aluno.nota[1],aluno.nota[2],aluno.faltas);
		fwrite(&aluno,sizeof(aluno),1,saida);
	}
    fclose(entrada);
    fclose(saida);
    
    //Exercicio 2!!!
	printf("\n\n                                       EXERCICIO 2                                          \n");
	printf("   ============================================================================================ \n");
	printf("  ||    Ja nessa parte do programa, eh aberto um arquivo .bin para leitura dos seus dados     ||\n");
	printf("  || determinando a situacao do aluno,se o mesmo esta aprovado ou nao, para isso eh feito uma ||\n");
	printf("  || media das notas presentes no arquivo. A situacao do aluno e os seus dados sao salvos em  ||\n");
	printf("  || um arquivo.txt chamados 'conceitos.txt'                                                  ||\n");
	printf("   ============================================================================================ \n\n");
	
    FILE *arq,*saida2;
    if((arq = fopen("alunos.bin", "rb")) == NULL)
    {
        printf("Arquivo nao pode ser lido(binario)...\n");
        return 0;
    }
    if((saida2 = fopen("conceitos.txt", "w")) == NULL)
    {
        printf("Arquivo nao pode ser criado(conceitos.txt)...\n");
        return 0;
    }
    Aluno aluno2;
    float media;
    printf("Impressao dos dados presentes no arquivo .bin somente para simples conferencia!\n\n");
    while(fread(&aluno2,sizeof(aluno2),1,arq) == 1)
    {
        printf("%s %-18s %.1f %.1f %.1f %d\n",aluno2.mat,aluno2.nome,aluno2.nota[0],aluno2.nota[1],aluno2.nota[2],aluno2.faltas);
        
        if(aluno2.faltas<=18)
		{
			media = (aluno2.nota[0]+aluno2.nota[1]+aluno2.nota[2])/3;
			if(media>=8.5)
			{
				fprintf(saida2,"%s %s %c\n",aluno2.mat,aluno2.nome,'A');
			}
			else
			{
				if(media>=7.0)
				{
					fprintf(saida2,"%s %s %c\n",aluno2.mat,aluno2.nome,'B');
				}
				else
				{
					if(media>=6.0)
					{
						fprintf(saida2,"%s %s %c\n",aluno2.mat,aluno2.nome,'C');
					}
					else
					{
						fprintf(saida2,"%s %s %c\n",aluno2.mat,aluno2.nome,'R');
					}
				}
			}
		}
		else
		{
			fprintf(saida2,"%s %s %c\n",aluno2.mat,aluno2.nome,'F');
		}
        
    }
    fclose(arq);
    fclose(saida2);
    
    //Exercicio 3!!!
	printf("\n\n                                       EXERCICIO 3                                          \n");
	printf("   ============================================================================================ \n");
	printf("  ||    Ja nessa parte, eh aberto um arquivo .bin para leitura dos seus dados. O usuario vai  ||\n");
	printf("  || informar um numero de matricula, e mediante esse numero ha uma pesquisa no arquivo .bin  ||\n");
	printf("  || para a exclusao do registro que possua esse numero. Para isso foi necessario criar um    ||\n");
	printf("  || arquivo .bin temporario para fazer a manipulacao do problema, removendo fisicamente.     ||\n");
	printf("   ============================================================================================ \n\n");
    
    FILE *arq_bin,*arq_bin2;
    Aluno aluno3;
    if((arq_bin = fopen("alunos.bin", "rb")) == NULL)
    {
        printf("Arquivo nao pode ser lido(binario 3)...\n");
        return 0;
    }
    if((arq_bin2 = fopen("temp.bin", "wb")) == NULL)
    {
        printf("Arquivo nao pode ser criado(binario 4)....\n");
        return 0;
    }
    int temp,temp2,cont=0;
    printf("\nDigite o numero da matricula que deseja retirar do arquivo binario(remocao fisica):\n");
    scanf("%d",&temp);
    printf("\nImpressao dos dados contidos no arquivo .bin apos a alteracao!\n");
    while(fread(&aluno3,sizeof(aluno3),1,arq_bin) == 1)
    {
        temp2 = atoi(aluno3.mat);
        if(temp2 != temp)
        {
            printf("%s %-18s %.1f %.1f %.1f %d\n",aluno3.mat,aluno3.nome,aluno3.nota[0],aluno3.nota[1],aluno3.nota[2],aluno3.faltas);
            fwrite(&aluno3,sizeof(aluno3),1,arq_bin2);
        }
        else
        {
            cont++;
        }
    }
    if(cont==0)
    {
        printf("\nNao houve alteracao no arquivo .bin pois a matricula digitada nao existe nos registros!\n");
    }
    fclose(arq_bin);
    fclose(arq_bin2);
    remove("alunos.bin");
    rename("temp.bin","alunos.bin");
    
    //Exercicio 4!!!
    printf("\n\n                                       EXERCICIO 4                                          \n");
	printf("   ============================================================================================ \n");
	printf("  ||    E por ultimo, eh aberto um arquivo .bin para leitura dos seus dados. O usuario vai    ||\n");
	printf("  || informar um numero de matricula, e mediante esse numero ha uma pesquisa no arquivo .bin  ||\n");
	printf("  || para a exclusao do registro que possua esse numero(remocao logica).                      ||\n");
	printf("   ============================================================================================ \n\n");
    
    FILE *arquivo;
    Aluno alu;
    if((arquivo = fopen("alunos.bin", "rb")) == NULL)
    {
        printf("Arquivo nao pode ser lido(binario 4)...\n");
        return 0;
    }
    int mat2,mat_atual,cont2=0;
    printf("\nDigite a matricula cujo registro deseja excluir(remocao logica):\n");
    scanf("%d",&mat2);
    printf("\nImpressao dos dados contidos no arquivo .bin apos alteracao dos dados!\n");
    
    while(fread(&alu,sizeof(alu),1,arquivo)==1)
    {
        mat_atual = atoi(alu.mat);
        if(mat_atual == mat2)
        {
            alu.mat[0] = '0';
            alu.mat[1] = '0';
            alu.mat[2] = '0';
            alu.mat[3] = '0';
            alu.mat[4] = '0';
            alu.mat[5] = '0';
            alu.mat[6] = '0';
            cont2++;
        }
        if(atoi(alu.mat)>0)
        {
            printf("%s %-18s %.1f %.1f %.1f %d\n",alu.mat,alu.nome,alu.nota[0],alu.nota[1],alu.nota[2],alu.faltas);
        }
    }
    if(cont2==0)
    {
        printf("\nNao houve alteracao no arquivo .bin pois a matricula digitada nao existe nos registros!\n");
    }
    fclose(arquivo);
    return 0;
}