#include "GerarDados.h"

int GerarArq(int tam, int sit)
{
    int i;
    Item R;
    FILE *Arq, *Saida;
    Arq = fopen("PROVAO.txt","r");
    if(Arq == NULL)
    {
        return FALSE;
    }
    Saida = fopen ("provao.bin", "wb");
    if(Saida == NULL)
    {
        return FALSE;
    } 
    switch(sit)
    {
        case 1:
        {
            for(i=0; i<tam; i++)
            {
                //Mudar!
                fscanf(Arq,"%ld %f %[A-Z a-z '-] %[A-Z a-z] %[A-Z a-z]\n",&R.Mat,&R.Nota,R.Estado,R.Cidade,R.Curso);
                fwrite(&R, sizeof(Item), 1, Saida);
            }
            break;
        }
        case 2:
        {
            for(i=0; i<tam; i++)
            {
                //Mudar!
                fscanf(Arq,"%ld %f %[A-Z a-z '-] %[A-Z a-z] %[A-Z a-z]\n",&R.Mat,&R.Nota,R.Estado,R.Cidade,R.Curso);
                fwrite(&R, sizeof(Item), 1, Saida);
            }
            break;
        }
        case 3:
        {
            for(i=0; i<tam; i++)
            {
                //Deixar dessa forma!
                fscanf(Arq,"%ld %f %[A-Z a-z '-] %[A-Z a-z] %[A-Z a-z]\n",&R.Mat,&R.Nota,R.Estado,R.Cidade,R.Curso);
                fwrite(&R, sizeof(Item), 1, Saida);
            }
            break;
        }
    }
    fclose(Saida);
    fclose(Arq);
    return TRUE;
}
