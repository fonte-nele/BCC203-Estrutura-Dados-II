#include "gerar_dados.h"

void gerar_arq(FILE *arq,int tam,int sit)
{
	//Salvando dados em .txt para simples conferencia!
	FILE *arq2;
	arq2 = fopen("saida_dados.txt","w");
	Dados dados;
    long i,r,temp;
	char temp2[8];
	
	switch(sit)
	{
		case 1:
		{
			fprintf(arq2,"ARQUIVO ORDENADO ASCENDENTEMENTE!\n\n");
			for(i=1; i<=tam; i++)
			{
				dados.dado2[0]='\0';
				dados.chave = i;
				dados.dado1 = i;
				//Conversao do long para char!
				sprintf(temp2,"%ld",dados.dado1);
				num_extenso(temp2,dados.dado2);
				
				fprintf(arq2,"Chave: %-7d Dado 1: %-7ld Dado 2: %s\n",dados.chave,dados.dado1,dados.dado2);
				fwrite(&dados,sizeof(dados),1,arq);
			}
			break;
		}
		case 2:
		{
			fprintf(arq2,"ARQUIVO ORDENADO DESCENDENTEMENTE!\n\n");
			for(i=tam; i>0; i--)
			{
				dados.dado2[0]='\0';
				dados.chave = i;
				dados.dado1 = i;
				//Conversao do long para char!
				sprintf(temp2,"%ld",dados.dado1);
				num_extenso(temp2,dados.dado2);

				fprintf(arq2,"Chave: %-7d Dado 1: %-7ld Dado 2: %s\n",dados.chave,dados.dado1,dados.dado2);
				fwrite(&dados,sizeof(dados),1,arq);			
			}
			break;
		}
		case 3:
		{
			fprintf(arq2,"ARQUIVO DESORDENADO ALEATORIAMENTE!\n\n");
			long *v;
			int aux;
			v = (long*)malloc(tam*sizeof(long));
			for(i=1; i<=tam; i++)
			{
				//Preencher o vetor com as chaves ordenadas!!
				v[i] = i;
			}
			srand(time(NULL));
			for(i=1; i<=tam; i++)
			{
				//Necessario pois rand() é limitado ate 32767! Suponha o caso do tam=1000000 é necessario fazer a mult. de dois rand de 1000!
				aux = tam/2;
				r = ((rand()%aux)+1 * (rand()%aux)+1);
				temp = v[i];
				v[i] = v[r];
				v[r] = temp;
			}
			for(i=1; i<=tam; i++)
			{
				dados.dado2[0]='\0';
				dados.chave = v[i];
				dados.dado1 = v[i];
				//Conversao do long para char!
				sprintf(temp2,"%ld",dados.dado1);
				num_extenso(temp2,dados.dado2);
				
				fprintf(arq2,"Chave: %-7d Dado 1: %-7ld Dado 2: %s\n",dados.chave,dados.dado1,dados.dado2);
				fwrite(&dados,sizeof(dados),1,arq);
			}
			free(v);
			break;
		}
	}	
}

void num_extenso(char *numero,char *retorno)
{
	int cont=0,pos;
	cont = strlen(numero);
	inverter_char_numero(numero,cont);
	
	if(numero[0]=='0' && cont<=1)
	{
        strcat(retorno,"Zero");
	}
	
    for(pos=cont;pos>=0;pos--)
	{
		switch(pos)
		{      
            case 0:
				um_digito(numero,retorno,&cont,&pos);
				break;
            case 1:
				dois_digitos(numero,retorno,&cont,&pos);
				break;
            case 2:
				tres_digitos(numero,retorno,&cont,&pos);
				break;
            case 3:
				quatro_digitos(numero,retorno,&cont,&pos);
				break;
            case 4:
				cinco_digitos(numero,retorno,&cont,&pos);
				break;
            case 5:
				seis_digitos(numero,retorno,&cont,&pos);
				break;
            case 6:
				sete_digitos(numero,retorno,&cont,&pos);
				break;
		}
    }
}

void inverter_char_numero(char *valor, int cont)
{
	char aux;
	int i,j;
	j = cont;
	for(i=0; i<cont/2; i++)
	{
		j--; 
		aux = valor[i];
		valor[i]=valor[j];
		valor[j]=aux;
	}
}

void um_digito(char *valor,char *num_string,int *cont,int *pos)
{
    switch(valor[(*pos)])
	{
        case '1':
			if((*cont)>=2)
				strcat(num_string," e ");
			strcat(num_string,"um");
			break;
        case '2':
			if((*cont)>=2)
				strcat(num_string," e ");
			strcat(num_string,"dois");
			break;
        case '3':
			if((*cont)>=2)
				strcat(num_string," e ");
			strcat(num_string,"tres");
			break;
        case '4':
			if((*cont)>=2)
				strcat(num_string," e ");
			strcat(num_string,"quatro");
			break;
        case '5':
			if((*cont)>=2)
				strcat(num_string," e ");
			strcat(num_string,"cinco");
			break;
        case '6':
			if((*cont)>=2)
				strcat(num_string," e ");
			strcat(num_string,"seis");
			break;
        case '7':
			if((*cont)>=2)
				strcat(num_string," e ");
			strcat(num_string,"sete");
			break;
        case '8':
			if((*cont)>=2)
				strcat(num_string," e ");
			strcat(num_string,"oito");
			break;
		case '9':
			if((*cont)>=2)
				strcat(num_string," e ");
			strcat(num_string,"nove");
			break;
    }
}

void dois_digitos(char *valor,char *num_string,int *cont,int *pos)
{
    if(valor[(*pos)]=='1')
	{
        switch(valor[(*pos)-1])
		{
            case '0':
				(*pos)--;
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"dez");
				break;
            case '1':
				(*pos)--;
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"onze");
				break;
            case '2':
				(*pos)--;
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"doze");
				break;
            case '3':
				(*pos)--;
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"treze");
				break;
            case '4':
				(*pos)--;
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"quatorze");
				break;
            case '5':
				(*pos)--;
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"quinze");
				break;
            case '6':
				(*pos)--;
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"dezesseis");
				break;
            case '7':
				(*pos)--;
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"dezessete");
				break;
            case '8':
				(*pos)--;
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"dezoito");
				break;
            case '9':
				(*pos)--;
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"dezenove");
				break;
        }
    }
    else
	{ 
        switch(valor[(*pos)])
		{
            case '2':
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"vinte");
				break;
            case '3':
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"trinta");
				break;
            case '4':
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"quarenta");
				break;
			case '5':
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"cinquenta");
				break;
			case '6':
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"sessenta");
				break;
            case '7':
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"setenta");
				break;
			case '8':
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"oitenta");
				break;
            case '9':
				if((*cont)>=3)
					strcat(num_string," e ");
				strcat(num_string,"noventa");
				break;
        }          
    }
}

void tres_digitos(char *valor,char *num_string,int *cont,int *pos)
{
    switch(valor[(*pos)])
	{
		case '1':
			if(valor[(*pos)-1]=='0'&&valor[(*pos)-2]=='0')
			{
				if((*cont)>=4)
					strcat(num_string," e ");
				strcat(num_string,"cem"); 
			}
			else
			{
				if((*cont)>=4)
					strcat(num_string," e ");
				strcat(num_string,"cento");
			}
			break;
		case '2':
			if((*cont)>=4)
				strcat(num_string," e ");
			strcat(num_string,"duzentos");
			break;
        case '3':
			if((*cont)>=4)
				strcat(num_string," e ");
			strcat(num_string,"trezentos");
			break;
        case '4':
			if((*cont)>=4)
				strcat(num_string," e ");
			strcat(num_string,"quatrocentos");
			break;
        case '5':
			if((*cont)>=4)
				strcat(num_string," e ");
			strcat(num_string,"quinhentos");
			break;
        case '6':
			if((*cont)>=4)
				strcat(num_string," e ");
			strcat(num_string,"seiscentos");
			break;
        case '7':
			if((*cont)>=4)
				strcat(num_string," e ");
			strcat(num_string,"setecentos");
			break;
        case '8':
			if((*cont)>=4)
				strcat(num_string," e ");
			strcat(num_string,"oitocentos");
			break;
		case '9':
			if((*cont)>=4)
				strcat(num_string," e ");
			strcat(num_string,"novecentos");
			break;
    }          
}

void quatro_digitos(char *valor,char *num_string,int *cont,int *pos)
{
    switch(valor[(*pos)])
	{
        case '1':
			if((*cont)>=5)
				strcat(num_string," e ");
			strcat(num_string,"um mil");
			break;
        case '2':
			if((*cont)>=5)
				strcat(num_string," e ");
			strcat(num_string,"dois mil");
			break;
        case '3':
			if((*cont)>=5)
				strcat(num_string," e ");
			strcat(num_string,"tres mil");
			break;
        case '4':
			if((*cont)>=5)
				strcat(num_string," e ");
			strcat(num_string,"quatro mil");
			break;
        case '5':
			if((*cont)>=5)
				strcat(num_string," e ");
			strcat(num_string,"cinco mil");
			break;
        case '6':
			if((*cont)>=5)
				strcat(num_string," e ");
			strcat(num_string,"seis mil");
			break;
        case '7':
			if((*cont)>=5)
				strcat(num_string," e ");
			strcat(num_string,"sete mil");
			break;
        case '8':
			if((*cont)>=5)
				strcat(num_string," e ");
			strcat(num_string,"oito mil");
			break;
        case '9':
			if((*cont)>=5)
				strcat(num_string," e ");
			strcat(num_string,"nove mil");
			break;
    }
}                         
  
void cinco_digitos(char *valor,char *num_string,int *cont,int *pos)
{
    if(valor[(*pos)-1]=='0'&& valor[(*pos)]=='1')
	{
        switch(valor[(*pos)])
		{
			case '1':
				if((*cont)>=6)
						strcat(num_string," e ");
				strcat(num_string,"dez mil");
			break;
        }
    }
    else
	{
		if(valor[(*pos)]=='1')
		{          
			switch(valor[(*pos)-1])
			{
				case '1':
					(*pos)--;
					if((*cont)>=6)
						strcat(num_string," e ");
					strcat(num_string,"onze mil");
					break;
				case '2':
					(*pos)--;
					if((*cont)>=6)
						strcat(num_string," e ");
					strcat(num_string,"doze mil");
					break;
				case '3':
					(*pos)--;
					if((*cont)>=6)
						strcat(num_string," e ");
					strcat(num_string,"treze mil");
					break;
				case '4':
					(*pos)--;
					if((*cont)>=6)
						strcat(num_string," e ");
					strcat(num_string,"quatorze mil");
					break;
				case '5':
					(*pos)--;
					if((*cont)>=6)
						strcat(num_string," e ");
					strcat(num_string,"quinze mil");
					break;
				case '6':
					(*pos)--;
					if((*cont)>=6)
						strcat(num_string," e ");
					strcat(num_string,"dezesseis mil");
					break;
				case '7':
					(*pos)--;
					if((*cont)>=6)
						strcat(num_string," e ");
					strcat(num_string,"dezessete mil");
					break;
				case '8':
					(*pos)--;
					if((*cont)>=6)
						strcat(num_string," e ");
					strcat(num_string,"dezoito mil");
					break;
				case '9':
					(*pos)--;
					if((*cont)>=6)
						strcat(num_string," e ");
					strcat(num_string,"dezenove mil");
					break;
			}          
		}
        else
		{ 
            switch(valor[(*pos)])
			{
				case '2':
					if((*cont)>5)
						strcat(num_string," e ");
					strcat(num_string,"vinte");
					if((valor[(*pos)-1])=='0')
						strcat(num_string," mil");
					break;
				case '3':
					if((*cont)>5)
						strcat(num_string," e ");
					strcat(num_string,"trinta");
					if((valor[(*pos)-1])=='0')
						strcat(num_string," mil");
					break;
                case '4':
					if((*cont)>5)
						strcat(num_string," e ");
					strcat(num_string,"quarenta");
					if((valor[(*pos)-1])=='0')
						strcat(num_string," mil");
					break;
                case '5':
					if((*cont)>5)
						strcat(num_string," e ");
					strcat(num_string,"cinquenta");
					if((valor[(*pos)-1])=='0')
						strcat(num_string," mil");
					break;
                case '6':
					if((*cont)>5)
						strcat(num_string," e ");
					strcat(num_string,"sessenta");
					if((valor[(*pos)-1])=='0')
						strcat(num_string," mil");
					break;
                case '7':
					if((*cont)>5)
						strcat(num_string," e ");
					strcat(num_string,"setenta");
					if((valor[(*pos)-1])=='0')
						strcat(num_string," mil");
					break;
                case '8':
					if((*cont)>5)
						strcat(num_string," e ");
					strcat(num_string,"oitenta");
					if((valor[(*pos)-1])=='0')
						strcat(num_string," mil");
					break;
                case '9':
					if((*cont)>5)
						strcat(num_string," e ");
					strcat(num_string,"noventa");
					if((valor[(*pos)-1])=='0')
						strcat(num_string," mil");
					break;
            }          
        }
	}
}         

void seis_digitos(char *valor,char *num_string,int *cont,int *pos)
{
    switch(valor[(*pos)])
	{
        case '1':
			if(valor[(*pos)-1]=='0'&&valor[(*pos)-2]=='0')
				strcat(num_string,"cem mil");
			else 
				strcat(num_string,"cento");
			break;
        case '2':
			if((*cont)>6)
				strcat(num_string," e ");
			strcat(num_string,"duzentos");
			if(valor[(*pos)-1]=='0'&&valor[(*pos)-2]=='0')
				strcat(num_string," mil");
			break;
        case '3':
			if((*cont)>6)
				strcat(num_string," e ");
			strcat(num_string,"trezentos");
			if(valor[(*pos)-1]=='0'&&valor[(*pos)-2]=='0')
				strcat(num_string," mil");
			break;
        case '4':
			if((*cont)>6)
				strcat(num_string," e ");
			strcat(num_string,"quatrocentos");
			if(valor[(*pos)-1]=='0'&&valor[(*pos)-2]=='0')
				strcat(num_string," mil");
			break;
        case '5':
			if((*cont)>6)
				strcat(num_string," e ");
			strcat(num_string,"quinhentos");
			if(valor[(*pos)-1]=='0'&&valor[(*pos)-2]=='0')
				strcat(num_string," mil");
			break;
        case '6':
			if((*cont)>6)
				strcat(num_string," e ");
			strcat(num_string,"seiscentos");
			if(valor[(*pos)-1]=='0'&&valor[(*pos)-2]=='0')
				strcat(num_string," mil");
			break;
        case '7':
			if((*cont)>6)
				strcat(num_string," e ");
			strcat(num_string,"setecentos");
			if(valor[(*pos)-1]=='0'&&valor[(*pos)-2]=='0')
				strcat(num_string," mil");
			break;
        case '8':
			if((*cont)>6)
				strcat(num_string," e ");
			strcat(num_string,"oitocentos");
			if(valor[(*pos)-1]=='0'&&valor[(*pos)-2]=='0')
				strcat(num_string," mil");
			break;
        case '9':
			if((*cont)>6)
				strcat(num_string," e ");
			strcat(num_string,"novecentos");
			if(valor[(*pos)-1]=='0'&&valor[(*pos)-2]=='0')
				strcat(num_string," mil");
			break;
    }
}

void sete_digitos(char *valor,char *num_string,int *cont,int *pos)
{
    if((*cont)>=7)
	{
        switch(valor[(*pos)])
		{
			case '1':
				strcat(num_string,"um milhao");
				break;
		}          
	}
}