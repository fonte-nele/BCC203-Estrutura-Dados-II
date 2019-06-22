#include "exe04.h"

void gerar_dados(ofstream &file)
{
	int i, temp;
	srand((unsigned)time(NULL));
	for(i=0; i<100; i++)
	{
		//Gerar numeros aleatorios de 1 a 6 - 6 para indicar votos nulos!!!
		temp = rand ()%6 + 1;
		if(i != 99)
		{
			file<<temp<<endl;
		}
		else
		{
			file<<temp;
		}
	}
}

void leitura_votos(ifstream &file, int *v)
{
	int i=0;
	while(!file.eof())
	{
		file>>v[i];
		i++;
	}
}

void verificar_votos(int *v)
{
	int i, cont1=0, cont2=0, cont3=0, cont4=0, cont5=0, cont6=0;
	for(i=0; i<100; i++)
	{
		if(v[i]==1)
		{
			cont1++;
		}
		else
		{
			if(v[i]==2)
			{
				cont2++;
			}
			else
			{
				if(v[i]==3)
				{
					cont3++;
				}
				else
				{
					if(v[i]==4)
					{
						cont4++;
					}
					else
					{
						if(v[i]==5)
						{
							cont5++;
						}
						else
						{
							cont6++;
						}
					}
				}
			}
		}
	}
	
	if(cont1>cont2 && cont1>cont3 && cont1>cont4 && cont1>cont5)
	{
		cout<<"Codigo: 1 Quantidades votos: "<<cont1<<endl;
	}
	else
	{
		if(cont2>cont1 && cont2>cont3 && cont2>cont4 && cont2>cont5)
		{
			cout<<"Codigo: 2 Quantidades votos: "<<cont2<<endl;
		}
		else
		{
			if(cont3>cont1 && cont3>cont2 && cont3>cont4 && cont3>cont5)
			{
				cout<<"Codigo: 3 Quantidades votos: "<<cont3<<endl;
			}
			else
			{
				if(cont4>cont1 && cont4>cont2 && cont4>cont3 && cont4>cont5)
				{
					cout<<"Codigo: 4 Quantidades votos: "<<cont4<<endl;
				}
				else
				{
					cout<<"Codigo: 5 Quantidades votos: "<<cont5<<endl;
				}
			}
		}
	}
	
	cout<<endl;
	cout<<"CANDIDATO MENOS VOTADO:"<<endl;
	if(cont1<cont2 && cont1<cont3 && cont1<cont4 && cont1<cont5)
	{
		cout<<"Codigo: 1 Quantidades votos: "<<cont1<<endl;
	}
	else
	{
		if(cont2<cont1 && cont2<cont3 && cont2<cont4 && cont2<cont5)
		{
			cout<<"Codigo: 2 Quantidades votos: "<<cont2<<endl;
		}
		else
		{
			if(cont3<cont1 && cont3<cont2 && cont3<cont4 && cont3<cont5)
			{
				cout<<"Codigo: 3 Quantidades votos: "<<cont3<<endl;
			}
			else
			{
				if(cont4<cont1 && cont4<cont2 && cont4<cont3 && cont4<cont5)
				{
					cout<<"Codigo: 4 Quantidades votos: "<<cont4<<endl;
				}
				else
				{
					cout<<"Codigo: 5 Quantidades votos: "<<cont5<<endl;
				}
			}
		}
	}
	
	cout<<endl;
	cout<<"Quantidade de votos nulos: "<<cont6<<endl;
}
