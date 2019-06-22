/*
	Feito por: Felipe Fontenele de Ávila Magalhães
	Data: 21/04/2016
	Disciplina: BCC 203 - Estrutura de Dados II
	Prof.: Guilherme Tavares de Assis
*/
#include<stdio.h>
#include<stdlib.h>

int main()
{
	printf("\n\n");
	printf("                                       EXERCICIO 1                                              \n");
	printf("   ============================================================================================ \n");
	printf("  || Neste programa, trabalha-se o conceito de arquivos .txt.Inicialmente eh aberto um arquivo||\n");
	printf("  || que consta as notas de alunos de uma classe, o objetivo eh determinar a situacao do aluno||\n");
	printf("  || querendo saber se o mesmo esta aprovado ou nao, para isso eh feito uma media das notas   ||\n");
	printf("  || presentes no arquivo. A situacao do aluno e os seus dados sao salvos em outro arquivo.txt||\n");
	printf("  || chamado 'conceitos.txt'.                                                                 ||\n");
	printf("   ============================================================================================ \n\n");
	
	FILE *entrada;
	FILE *saida;
	char matricula[5];
	char nome[31];
	float nota1, nota2, nota3,media;
	int faltas;
	if((entrada = fopen("alunos.txt", "r")) == NULL)
	{
		puts("Arquivo nao pode ser aberto...");
		exit(1);
	}
	if((saida = fopen("conceitos.txt", "w")) == NULL)
	{
		puts("Erro na criacao do arquivo!!!");
		exit(1);
	}
	while(fscanf(entrada,"%s %[A-Z a-z] %f %f %f %d '\n'",matricula,nome,&nota1,&nota2,&nota3,&faltas) != EOF)
	{
		printf("%s %20s %.1f %.1f %.1f %d\n",matricula,nome,nota1,nota2,nota3,faltas);
		if(faltas<=18)
		{
			media = (nota1+nota2+nota3)/3;
			if(media>=8.5)
			{
				fprintf(saida,"%s %s %c\n",matricula,nome,'A');
			}
			else
			{
				if(media>=7.0)
				{
					fprintf(saida,"%s %s %c\n",matricula,nome,'B');
				}
				else
				{
					if(media>=6.0)
					{
						fprintf(saida,"%s %s %c\n",matricula,nome,'C');
					}
					else
					{
						fprintf(saida,"%s %s %c\n",matricula,nome,'R');
					}
				}
			}
		}
		else
		{
			fprintf(saida,"%s %s %c\n",matricula,nome,'F');
		}
	}
	fclose(entrada);
	fclose(saida);
	return 0;
}