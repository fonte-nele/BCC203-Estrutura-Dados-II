#include <iostream>
#include <string>
using namespace std;
void leitura(int[9][9]);
string verificar(int[9][9]);

int main() 
{
	int n, cont = 1;
	int matriz[9][9];
	

	cin >> n;
	while(n>0) 
	{
		string saida;
		leitura(matriz);
		saida = verificar(matriz);
		
		cout<<"Instancia "<<cont<<endl;
		cout<<saida<<endl<<endl;
		cont++;
		n--;
	}
	
	return 0;
}

void leitura(int matriz[9][9])
{
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			cin>>matriz[i][j];
		}
	}
}

string verificar(int matriz[9][9])
{
	int somaLinha[9], somaColuna[9], somaMatriz[3][3];
	int i, j, n, soma = 285;
	string s;
	
	for (i = 0; i < 9; i++)
	{
		somaLinha[i] = somaColuna[i] = somaMatriz[i/3][i%3] = 0;
	}
		
	for (i=0; i<9; i++) 
	{
		for (j=0; j<9; j++) 
		{
			n = matriz[i][j];
			n *= n;
			somaLinha[i] += n;
			somaColuna[j] += n;
			somaMatriz[i/3][j/3] += n;
			cout<<"Soma Matriz: "<<somaMatriz[i/3][j/3]<<endl;

			if (i==8 && somaColuna[j] != soma)
			{
				break;
			}
		}

		if (somaLinha[i] != soma)
		{
			break;
		}
	}

	for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++)
		{
			if (somaMatriz[i][j] != soma)
			{
				s = "NAO";
				return s;
			}
		}
	}
	
	s  = "SIM";

	return s;
}