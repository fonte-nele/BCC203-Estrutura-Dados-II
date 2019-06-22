#include <iostream>
#include <iomanip>
#include <cmath>
#define TAM 11
using namespace std;

typedef struct
{
	int idade;
	int altura;
	float peso;
	float gordura;
}TPaciente;

int main()
{
	int i,j,n,soma=0,media1=0,cont1=0,cont2=0,cont3=0;
	float media2=1,media3=0;
	TPaciente m[TAM][TAM];

	cin>>n;
	while(n<5 || n>100)
	{
		cin>>n;
	}
	
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			cin>>m[i][j].idade;
			cin>>m[i][j].altura;
			cin>>m[i][j].peso;
			cin>>m[i][j].gordura;
		}
	}
	
	
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(i > j &&  j < (n-1)-i)
			{
				soma += m[i][j].idade;
			}
			if(i < j && j < (n-1)-i)
			{
				media1 += m[i][j].altura;
				cont1++;
			}
			if(i < j && j > (n-1)-i)
			{
				media2 *= m[i][j].peso;
				cont2++;
			}
			if(i > j && j > (n-1)-i)
			{
				media3 += (1.0/m[i][j].gordura);
				cont3++;
			}
		}
	}
	
	cout<<"Calculo da regiao A: "<<soma<<endl;
	cout<<"Calculo da regiao B: "<<fixed<<setprecision(5)<<media1/(cont1*1.0)<<endl;
	cout<<"Calculo da regiao C: "<<fixed<<setprecision(5)<<pow(media2,(1.0/cont2))<<endl;
	cout<<"Calculo da regiao D: "<<fixed<<setprecision(5)<<media3/(cont3*1.0)<<endl;
	
	
	return 0;
}