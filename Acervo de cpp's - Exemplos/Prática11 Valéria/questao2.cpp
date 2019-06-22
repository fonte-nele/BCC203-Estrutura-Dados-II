#include<iostream>
#define TAM 102
using namespace std;

void preencher_matriz(int,int[TAM][TAM]);
void imprimir_matriz(int,int[TAM][TAM]);

int main()
{
	int n,matriz[TAM][TAM];
	cin>>n;
	
	while(n%2 != 0 && (n>=5 && n<=101))
	{
		preencher_matriz(n,matriz);
		imprimir_matriz(n,matriz);
		
		cin>>n;
	}
	
	return 0;
}

void preencher_matriz(int n,int m[TAM][TAM])
{
	int i,j;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(i==j)
			{
				m[i][j]=2;
			}
			else
			{
				m[i][j]=0;
			}
		}
	}
	
	for(i=1,j=n;i<=n;i++,j--)
	{
		m[i][j]=3;
	}
	
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(i>(n/3) && i<=n-n/3 && j>(n/3) &&j<=n-n/3)
			{
				m[i][j]=1;
			}
			if(i==j && i==1+(n/2))
			{
				m[i][j]=4;
			}
		}
	}
}

void imprimir_matriz(int n,int m[TAM][TAM])
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cout<<m[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
}