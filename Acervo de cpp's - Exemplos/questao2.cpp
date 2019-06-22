#include <iostream>
using namespace std;

int main()
{
	int i,j,inicial,passo,fim,op,num;
	cin>>num;
	
	for(i=0; i<num; i++)
	{
		cin>>inicial>>passo>>fim>>op;
		
		/*VERSAO FOR*/
		if(passo < 0)	//EH PRECISO ANALISAR SE O PASSO EH POSITIVO OU NEGATIVO SEPARADAMENTE!
		{
			if(op==1 || op==2)
			{
				//COMO O PASSO EH NEGATIVO ENTAO AS CONDICOES POSSIVEIS SAO > OU >=
				cout<<"loop infinito"<<endl;
			}
			else
			{
				if(op==3)
				{
					//CONDICAO >
					for(j=inicial; j>fim; j+=passo)
					{
						cout<<j<<",";
					}
					cout<<endl;
				}
				else
				{
					//CONDICAO >=
					for(j=inicial; j>=fim; j+=passo)
					{
						cout<<j<<",";
					}
					cout<<endl;
				}
			}
		}
		else
		{
			if(passo == 0)
			{
				if(inicial==fim)
				{
					//INICIO E FIM SAO IGUAIS, PORTANTO SE A CONDICAO FOR <= OU >= DEVERA IMPRIMIR AO MENOS UM ELEMENTO.
					if(op==2 || op==4)
						cout<<inicial<<","<<endl;
					else
						cout<<endl;
				}
				else
				{
					//SE O PASSO EH 0 E INICIO E FIM SAO DIFERENTES ENTAO ISSO FICARA EM UM LOOP INFINITO.
					cout<<"loop infinito"<<endl;
				}
			}
			else
			{
				if(op==3 || op==4)
				{
					//COMO O PASSO EH NEGATIVO ENTAO AS CONDICOES POSSIVEIS SAO < OU <=
					cout<<"loop infinito"<<endl;
				}
				else
				{
					if(op==1)
					{
						//CONDICAO <
						for(j=inicial; j<fim; j+=passo)
						{
							cout<<j<<",";
						}
						cout<<endl;
					}
					else
					{
						//CONDICAO <=
						for(j=inicial; j<=fim; j+=passo)
						{
							cout<<j<<",";
						}
						cout<<endl;
					}
				}	
			}
		}
		/*VERSAO WHILE - RACIOCINIO ANALOGO AO SUPERIOR POREM UTILIZANDO WHILE*/
		/*
		if(passo < 0)
		{
			if(op==1 || op==2)
			{
				cout<<"loop infinito"<<endl;
			}
			else
			{
				if(op==3)
				{
					j= inicial;
					while(j>fim)
					{
						cout<<j<<",";
						j+=passo;
					}
					cout<<endl;
				}
				else
				{
					j= inicial;
					while(j>=fim)
					{
						cout<<j<<",";
						j+=passo;
					}
					cout<<endl;
				}	
			}
		}
		else
		{
			if(passo == 0)
			{
				if(inicial==fim)
				{
					if(op==2 || op==4)
						cout<<inicial<<","<<endl;
					else
						cout<<endl;
				}
				else
				{
					cout<<"loop infinito"<<endl;
				}
			}
			else
			{
				if(op==3 || op==4)
				{
					cout<<"loop infinito"<<endl;
				}
				else
				{
					if(op==1)
					{
						j= inicial;
						while(j<fim)
						{
							cout<<j<<",";
							j+=passo;
						}
						cout<<endl;
					}
					else
					{
						j= inicial;
						while(j<=fim)
						{
							cout<<j<<",";
							j+=passo;
						}
						cout<<endl;
					}
				}	
			}
		}*/
	}
	return 0;
}