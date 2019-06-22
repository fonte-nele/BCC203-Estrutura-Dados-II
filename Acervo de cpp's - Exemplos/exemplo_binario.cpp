#include<iostream>
#include<fstream>
using namespace std;

typedef struct
{
	float x,y;
}Ponto;

int main()
{
	int i,n;
	Ponto p;
	
	//Escrita arquivo binario!!!
	ofstream fp;
	fp.open("dados.txt",ios::binary);
	if(fp.fail())
	{
		cout<<"Erro na abertura do arquivo"<<endl;
		exit(1);
	}
	cout<<"Quantas coordenadas deseja gravar?"<<endl;
	cin>>n;
	for(i=0; i<n; i++)
	{
		cin>>p.x>>p.y;
		fp.write((char*)&p, sizeof(Ponto));
	}
	fp.close();
	
	//Leitura arquivo binario!!!
	ifstream nfp;
	nfp.open("dados.txt",ios::binary);
	if(nfp.fail())
	{
		cout<<"Erro na abertura do arquivo"<<endl;
		exit(1);
	}
	while(nfp.read((char*)&p, sizeof(Ponto)))
	{
		cout<<"Ponto x: "<<p.x<<" Ponto y: "<<p.y<<endl;
	}
	nfp.close();
	return 0;
}