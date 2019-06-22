#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "validation.h"
#include "merge.h"
#include "quicksort.h"

int main(int argc, char *argv[])
{
  int result;
  tArguments arguments;

  //Realiza validação dos argumentos
  result = validateArguments(argc, &argv, &arguments);

  if (result > 0)
  {
    puts("Erro na validacao dos argumentos");
  }
  else
  {
    /*Identifica qual dos arquivos de entrada será utilizado*/
    identifyProperInputFile(arguments.situation);

    if (arguments.method != 4)
      /*Chama função responsável pelos métodos de intercalação*/
      result = merge(arguments.method, arguments.quantity);
    else
      /*Chama função responsável pelo método quicksort externo*/
      result = externalQuickSort(arguments.quantity);
  }

  return result;
}

