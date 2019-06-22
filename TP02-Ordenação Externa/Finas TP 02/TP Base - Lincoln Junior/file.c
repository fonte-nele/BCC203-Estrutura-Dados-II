#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

/*
Função: readStudent
  - Responsável por realizar a leitura de uma linha do arquivo de entrada e
    preencher a variavel que armazena as informações do estudante, recebida via
    passagem por referência.

Parâmetros:
  - file: Arquivo de entrada
  - student: Variável que representa um estudante

Retorno:
  - 0, caso a leitura ocorra com sucesso
  - 1, caso ocorra algum erro na leitura
*/

short readStudent(FILE **file, tStudent *student)
{
  char str[86], *newString;
  short stateBeg, cityBeg, cityEnd, courseBeg, courseEnd;
  int result;

  /*Variáveis que indicam posição de início de cada um dos campos dos registros
  contidos no arquivo de entrada.*/
  stateBeg = 0;
  cityBeg = 3;
  cityEnd = cityBeg + 49;
  courseBeg = 54;
  courseEnd = courseBeg + 29;

  /*Em sistemas Linux, que representam o caractere "final de linha", pela
  sequencia de escape '\n', cada linha do arquivo de entrada possui 100
  caracteres.*/
  result = fscanf(*file, "%d %f ", &(student->id), &(student->grade));

  if (result == 2)
  {
    /*Leitura dos 2 campos iniciais (matrícula e nota) realizada com sucesso*/
    fgets(str, 86, *file);

    newString = strtok (str, " ");

    strcpy(student->city, "");
    strcpy(student->course, "");

    while (newString != NULL)
    {
      if (newString >= str + cityBeg && newString <= str + cityEnd)
      {
        strcat(student->city, newString);
        strcat(student->city, " ");
      }
      else if (newString >= str + courseBeg && newString <= str + courseEnd)
      {
        strcat(student->course, newString);
        strcat(student->course, " ");
      }
      else if (newString == str + stateBeg)
        strcpy(student->state, newString);

      newString = strtok (NULL, " ");
    }

    /*Remove o espaço em branco no final de uma cadeia de caracteres*/
    student->city[strlen(student->city) - 1] = '\0';
    student->course[strlen(student->course) - 1] = '\0';

    return 0;
  }
  else
    return 1;
}

/*
Função: identifyProperInputFile
  - Identifica e define arquivo que será utilizado como entrada. O arquivo
    adequado é escolhido com base no valor do parâmetro de entrada. Uma vez
    identificado, tal arquivo é copiado para o mesmo diretório, mas com outro
    nome, "PROVAO.txt", que é o nome de arquivo utilizado durante o processo
    de leitura dos dados de entrada.

  - Observação: Essa função é dependente de Sistemas Operacionais baseados em
    Linux, pois faz uso do comando "cp". A função assume que os arquivos
    "PROVAO-ASC.txt", "PROVAO-DESC.txt" e "PROVAO-RANDOM.txt" existem e estejam
    localizados no mesmo diretório que o executável do programa e, por isso, não
    verifica se a cópia foi realizada com sucesso.

Parâmetros:
  - situation: Número inteiro que indica situação do arquivo de entrada
               (1 - ordenado ascendentemente, 2 - ordenado descendentemente,
               3 - desordenado aleatoriamente).

Retorno:
  - Nenhum
*/

void identifyProperInputFile(short situation)
{
  switch(situation)
  {
    case 1:
      /*Renomeia arquivo "PROVAO-ASC.txt", que está ordenado ascendentemente, de
      acordo com as notas, para "PROVAO.txt".*/
      system("cp ./PROVAO-ASC.txt ./PROVAO.txt");

      break;
    case 2:
      /*Renomeia arquivo "PROVAO-DESC.txt", que está ordenado descendentemente,
      de acordo com as notas, para "PROVAO.txt".*/
      system("cp ./PROVAO-DESC.txt ./PROVAO.txt");

      break;
    case 3:
      /*Renomeia arquivo "PROVAO-RANDOM.txt", que está desordenado
      aleatoriamente, de acordo com as notas, para "PROVAO.txt".*/
      system("cp ./PROVAO-RANDOM.txt ./PROVAO.txt");
  }
}

short writeStudent(FILE *file, tStudent student)
{
  if (file != NULL)
  {
    fprintf(file, "%08d %05.1f %s %-50s %-30s\n", student.id,
            student.grade, student.state, student.city, student.course);

    return ferror(file);
  }
  else
  {
    return 1;
  }
}
