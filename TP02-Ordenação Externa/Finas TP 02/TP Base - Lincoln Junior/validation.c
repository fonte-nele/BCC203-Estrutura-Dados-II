#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "validation.h"

/*
Função: validaargumentos
    - Verifica se argumentos recebidos, via linha de comando, são válidos.

Parâmetros:
    - argc: Quantidade de argumentos recebidos
    - argv: Lista de argumentos recebidos
    - arguments: Variável que armazena os argumentos convertidos para o tipo int

Retorno:
    - valor verdadeiro: Caso algum argumento seja inválido
    - valor falso: caso Todos os argumentos estejam corretos
*/

int validateArguments(int argc, char ***argv, tArguments *arguments)
{
  if (argc != 4 && argc != 5)
  {
    //Erro na quantidade de argumentos

	return 501;
  }

  //Converte primeiro argumento para o tipo int
  arguments->method = atoi((*argv)[1]);

  if (arguments->method < 1 || arguments->method > 4)
  {
    //Metodo esta fora do intervalo especificado
 
	return 502;
  }

  //Converte segundo argumento para o tipo int
  arguments->quantity = atoi((*argv)[2]);
/*
  if (arguments->quantity != 100 &&
      arguments->quantity != 2000 &&
      arguments->quantity != 20000 &&
      arguments->quantity != 200000 &&
      arguments->quantity != 471705)
  {
	
    //Quantidade de registros incorreta
    return 503;
  }
*/
  //Converte terceiro argumento para o tipo int
  arguments->situation = atoi((*argv)[3]);

  if (arguments->situation < 1 || arguments->situation > 3)
  {
    return 504;
  }

  //Verifica se o argumento "-P" foi informado
  if (argc == 5)
  {
    if (strcmp((*argv)[4], "-P") == 0)
      arguments->showData = 1;
    else      
      return 505;
  }

  return 0;
}
