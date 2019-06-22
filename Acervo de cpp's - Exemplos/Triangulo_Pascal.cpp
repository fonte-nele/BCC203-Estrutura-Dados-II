#include <iostream>
using namespace std;


void preencher(int n, int **T)
{
	int i,j;

	T[0][0] = 1;
	for(i=1; i<n; i++)
	{
		T[i][0] = 1;
		T[i][i] = 1;
		for(j=1; j<i; j++) 
		{
			T[i][j] = T[i-1][j] + T[i-1][j-1];
		}
	}
}

void imprimir(int n, int **T) 
{
	int i,j;
	
	cout<<"linha "<<n-1<<": ";
	for(i=0; i<n; i++) 
	{
		for(j=0; j<=i; j++)
		{
			if(i==n-1)
			{
			cout<<T[i][j]<<" ";
			}
		}
	}
}

int main() 
{
	int n,i,**T;

	cout<<"Qual eh o numero de linhas a serem impressas?"<<endl;
	cin>>n;
	
	if(n <= 0) 
	{
		return 0;
	}
	n += 1;

	//Alocação Dinamica!
	T = new int*[n];
	if(T == NULL)
	{
		cout<<"Erro ao alocar matriz\n\n";
		return 0;
	}
	for(i=0; i<n; i++)
	{
		T[i] = new int[i];
		if(T[i] == NULL)
		{
			cout<<"Erro ao alocar matriz\n\n";
			return 0;
		}
	}

	preencher(n,T);
	imprimir(n,T);
	
	//Liberando memoria!
	for(i=0; i<n; i++)
	{
		delete []T[i];
	}
	delete []T;
	return 0;
}