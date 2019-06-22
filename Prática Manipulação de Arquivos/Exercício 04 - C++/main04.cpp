/*
	Feito por: Felipe Fontenele de Ávila Magalhães
	Data: 21/04/2016
	Disciplina: BCC 203 - Estrutura de Dados II
	Prof.: Guilherme Tavares de Assis
*/
#include "exe04.h"

int main()
{
	cout<<endl<<endl;
	cout<<"                                       EXERCICIO 4                                              "<<endl;
	cout<<"   ============================================================================================ "<<endl;
	cout<<"  || Neste programa, trabalha-se o conceito de arquivo.txt. Neste codigo eh aberto o arquivo  ||"<<endl;
	cout<<"  || 'votos.txt' que antes foi gerado aleatoriamente os votos de 100 eleitores. O objetivo    ||"<<endl;
	cout<<"  || eh determinar qual foi o candidato(1,2,3,4 ou 5) que obteve mais votos e menos votos,    ||"<<endl;
	cout<<"  || seguido da quantidade de votos nulos.                                                    ||"<<endl;
	cout<<"  ||                                                                   Felipe Fontenele       ||"<<endl;
	cout<<"   ============================================================================================ "<<endl<<endl;
	
	//Gerar arquivo.txt com a votacao aleatoria!!!
	ofstream dados;
	dados.open("votos.txt");
	int v[100];
	gerar_dados(dados);
	dados.close();
	
	//Leitura arquivo.txt!!!
	ifstream entrada;
	entrada.open("votos.txt");
	leitura_votos(entrada,v);
	entrada.close();
	
	//Verificação de votos!!!
	cout<<endl;
	cout<<"CANDIDATO MAIS VOTADO:"<<endl;
	verificar_votos(v);
	
	return 0;
}