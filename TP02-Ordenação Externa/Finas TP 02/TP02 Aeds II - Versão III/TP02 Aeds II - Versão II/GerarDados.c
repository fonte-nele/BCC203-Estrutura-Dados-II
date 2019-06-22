#include "GerarDados.h"

int GerarArq(int tam, int sit)
{
    int i;
	char aux;
    Item reg;
    FILE *Arq, *Saida;
    Arq = fopen("PROVAO.txt","r");
    if(Arq == NULL)
    {
        return FALSE;
    }
    Saida = fopen ("teste.bin", "wb");
    if(Saida == NULL)
    {
        return FALSE;
    }
    /*Geracao arquivo binario com os dados do PROVAO.txt*/
    for(i=0; i<tam; i++)
    {
        fscanf(Arq,"%ld %f %s",&reg.mat,&reg.nota,reg.estado);
		aux = getc(Arq);
		
        fgets(reg.cidade,50,Arq);
		aux = getc(Arq);
		aux = getc(Arq);
		fscanf(Arq,"%[A-Z a-z]\n",reg.curso);

		fwrite(&reg, sizeof(Item), 1, Saida);
    }
	printf("Passou\n");
	/*
    switch(sit)
    {
        case 1:
        {
            for(i=0; i<tam; i++)
            {
                //Mudar!
                fscanf(Arq,"%ld %f %[A-Z a-z '-] %[A-Z a-z] %[A-Z a-z]\n",&reg.mat,&reg.nota,reg.estado,reg.cidade,reg.curso);
                fwrite(&reg, sizeof(Item), 1, Saida);
            }
            break;
        }
        case 2:
        {
            for(i=0; i<tam; i++)
            {
                //Mudar!
                fscanf(Arq,"%ld %f %[A-Z a-z '-] %[A-Z a-z] %[A-Z a-z]\n",&reg.mat,&reg.nota,reg.estado,reg.cidade,reg.curso);
                fwrite(&reg, sizeof(Item), 1, Saida);
            }
            break;
        }
        case 3:
        {   
            break;
        }
    }*/
    fclose(Saida);
    fclose(Arq);
    return TRUE;
}
