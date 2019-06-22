#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;

struct cliente // estrutura para tratar dos dados dos clientes 
{
	long int id; // identidade do cliente: CPF
	string nome; // nome do cliente
	string endereco; // endereco do cliente ???
	string email; // e-mail do cliente ???
	long int telefone; // telefone do cliente ???
};

struct destino // estrutura para tratar os destinos 
{
	long int id; // codigo de cada destino, identificacao de cada destino por um numero
	string localidade; // nome da cidade de destino 
	string pais; // pais de destino 
	int num; // numero de locais a serem visitados 
	double custo; // custo de cada viajem, destino
};

struct deslocamentos // sequencia de deslocamentos que a pessoa fara ate seu destino final
{
	int mes; // mes da viagem representado por numeros ex: 5- Maio
	int dia; // dia da viagem 
	long int iddestino;
};

struct viagem
{
	int id; // numero sequencial para cada viagem, codigo de viagem 
	deslocamentos desloc[100];   //Indica que uma viagem pode ter no maximo 100 deslocamentos 
	long int idcliente[100]; //sequencia de clientes, indicando que pode haver no maximo 100 clientes
	double custot; // custo total da viagem, soma de todos os destinos
	int quantc; //quantidade de clientes que ira viajar 
    int quantd; //quantidade de deslocamentos da viagem
};

struct inscricao // cadastro nas viagens 
{
	long int idv; // identidade da viagem
	long int idc; // identidade do cliente
};

int menuprincipal(); // funcao menu principal que direciona para todos os outros modulos

int menu1(); // funcao menu 1 modulo cliente

int menu2(); // funcao menu 2 modulo destino

int menu3(); // funcao menu 3 modulo viagem 

// funcoes modulo cliente 
void insercao(cliente vetor[], int *contador); // cadastro de um novo cliente
void remocao(long int id, cliente vetor[], int *contador); // excluir um cliente 
void alteracao(long int id, cliente vetor[], int contador); // alteracao de dados de um cliente
void consulta(long int id, cliente vetor[], int contador); // consultar dados de um cliente
void listagem(cliente vetor[], int contador); //lista os dados de todos os clientes

// funcoes modulo destino
void insercaod(destino vetor2[], int *cont);  // cadastro de um novo destino
void remocaod(long int id, destino vetor2[], int *cont); // excluir um destino 
void alteracaod(long int id, destino vetor2[], int cont); // alteracao de dados de um destino
void consultad(long int id, destino vetor2[], int cont); // consultar dador de um destino
void listagemd(destino vetor2[], int cont); // lista os dados de todos os destinos

// funcoes modulo viagem
void insercaov(cliente vetor[], destino vetor2[], viagem vetor3[], int *contar, int contador, int cont); //cadastro de uma nova viagem
void remocaov(long int id, viagem vetor3[], int *contar); // excluir uma viagem
void alteracaov(long int id, cliente vetor[], destino vetor2[], viagem vetor3[], int contar, int contador, int cont); // alteracao dos dados de uma viagem
void consultav(long int id, viagem vetor3[], int contar); // consultar dados de uma viagem
bool verificarData(viagem vetor3[], int contar, int pos); // verificar se as datas dos destinos sao seguidas uma da outra, dias com uma sequencia logica  
bool verificarDisp(viagem vetor3[], int contar, long int idc); //funcao para saber se o cliente esta cadastrado em viagens na mesma data

void inscricaov(inscricao insc, cliente vetor[], viagem vetor3[], int contador, int contar); // funcao para inscrever um cliente em uma viagem
void desistenciav(inscricao insc, cliente vetor[], viagem vetor3[], int contador, int contar); // funcao para remover um cliente de uma viagem
void listagemv(viagem vetor3[], int contar, int dia_inicial, int dia_final, int mes_inicial, int mes_final);  //lista de dados de viagens por data
void relatoriov(viagem vetor3[], int contar); // relaorio sumarizado de viagens

int main()
{
	ifstream arqclientes, arqdestinos, arqviagens;
	arqclientes.open("clientes.txt",ios_base::in);
	//arqdestinos.open("destinos.txt");
	//arqviagens.open("viagens.txt");

	long int id;
	int c = 0, opc, opcao, contador = 0, cont = 0, contar = 0, dia_inicial, dia_final, mes_inicial, mes_final; // n = tamanho do vetor, opcao = numero da escolha feita no menu
	cliente vetor[500]; // idcliente = estrutura com todos os dados que o cliente quer alterar
	destino vetor2[500], iddestino; 
	viagem vetor3[500];
	inscricao insc; // estrutura incricao com os dados do destino e do cliente; 
	cout<<"ADF"<<endl;
    
    char aux[20];
    string line;
    while(!arqclientes.eof())
    {
        getline(arqclientes,line);
        for(int j=0; j<line.size(); j++)
        {
            aux[j] = line[j];
        }
        vetor[contador].id = atol(aux);
        
        getline(arqclientes,line);
        vetor[contador].nome = line;
        
        getline(arqclientes,line);
        vetor[contador].endereco = line;
        
        getline(arqclientes,line);
        vetor[contador].email = line;
        
        getline(arqclientes,line);
        for(int j=0; j<line.size(); j++)
        {
            aux[j] = line[j];
        }
        vetor[contador].telefone = atol(aux);
        
        cout << " id: " << vetor[contador].id << endl;
		cout << " nome: " << vetor[contador].nome << endl;
		cout << " endereco: " << vetor[contador].endereco << endl;
		cout << " email: " <<vetor[contador].email << endl;
		cout << " telefone: " << vetor[contador].telefone << endl;
        
        contador++;
    }/*
    while(arqclientes >> vetor[contador].id >> vetor[contador].nome >> vetor[contador].endereco >> vetor[contador].email >> vetor[contador].telefone)
	{

        cout << "Parte 1 "<<endl;
		cout << " id: " << vetor[contador].id << endl;
		cout << " nome: " << vetor[contador].nome << endl;
		cout << " endereco: " << vetor[contador].endereco << endl;
		cout << " email: " <<vetor[contador].email << endl;
		cout << " telefone: " << vetor[contador].telefone << endl;
		contador++;
	}*/
    cout << "efe" <<endl;
    arqclientes.close();
	//arqdestinos.close();
	//arqviagens.close();
    
    ofstream arqclientes2, arqdestinos2, arqviagens2;
	arqclientes2.open("clientes.txt",ios_base::out);
	//arqdestinos2.open("destinos.txt");
	//arqviagens2.open("viagens.txt");
    
    cout << endl << "\t\tBEM-VINDO A AGENCIA DE VIAGENS FONTE\n\t\tFAZENDO DO CEU O MELHOR LUGAR DA TERRA" << endl;
   
	opc = menuprincipal();   
	while(opc != 4)
	{
		switch(opc)
		{
			case 1:
			{
                cout << endl << "\tMODULO CLIENTE" << endl;
				opcao = menu1();
				while(opcao != 6)
				{	
					switch(opcao)
					{
						case 1:
						{
							insercao(vetor,	&contador);
							break;
						}
						case 2:
						{
							cout << "Informe o id do cliente que deseja excluir: ";
							cin >> id; // id que o cliente quer excluir  
							if(contador > 0)
			                {
			                    remocao(id, vetor, &contador); // tudo o que for feito no contador dentro da funcao vai alterar no main
							}
			                else
			                {
			                    cout << "Cliente inexistente." << endl;
			                }
			                break;
						}
						case 3:
						{
							cout << "Informe o id do cliente que deseja alterar os dados cadastrados: ";
							cin >> id;
							alteracao(id, vetor, contador);
							break;
						}
						case 4:
						{
							cout << "Informe o id do cliente que deseja consultar: ";
							cin >> id; // id que o cliente quer consultar
							consulta(id, vetor, contador);
							break;
						}
						case 5:
						{
							listagem(vetor, contador);
							break;
						}
						default:
						{
							cout << "Opcao invalida. Tente novamente" << endl;
							break;
						}
					}
					opcao = menu1();
				}
                cout << endl << "Menu Cliente finalizado com sucesso!" << endl;
				break;
			}
			case 2:
			{
                cout << endl << "\tMODULO DESTINO" << endl;
				opcao = menu2();
				while(opcao != 6)
				{
					switch(opcao)
					{
						case 1:
						{
							insercaod(vetor2, &cont);
							break;
						}
						case 2:
						{
							cout << "Informe o id do destino que deseja excluir: ";
							cin >> id; // id do destino que quer excluir 
							if(cont > 0)
			                {
			                    remocaod(id, vetor2, &cont);
							}
			                else
			                {
			                    cout << "Destino inexistente." << endl;
			                }
							break;
						}
						case 3:
						{
							cout << "Informe o id do destino que deseja alterar os dados cadastrados: ";
							cin >> id;
							alteracaod(id, vetor2, cont);
							break;
						}
						case 4:
						{
							cout << "Informe o id do destino que deseja consultar: ";
							cin >> id; // id do destino quer consultar
							consultad(id, vetor2, cont);
							break;
						}
						case 5:
						{
							listagemd(vetor2, cont);
							break;
						}
						default:
						{
							cout << "Opcao invalida. Tente novamente" << endl;
							break;
						}
					}
					opcao = menu2();
				}
                cout << endl << "Menu Destino finalizado com sucesso!" << endl;
				break;
			}
			case 3:
			{
                cout << endl << "\tMODULO VIAGEM" << endl;
				opcao = menu3();
				while(opcao != 9)
				{
					switch(opcao)
					{
						case 1:
						{
							insercaov(vetor, vetor2, vetor3, &contar, contador, cont);
							break;
						}
						case 2:
						{
							cout << "Informe o id da viagem que deseja excluir: ";
							cin >> id; // id da viagem que quer excluir 
							if(contar > 0)
			                {
			                    remocaov(id, vetor3, &contar);
							}
			                else
			                {
			                    cout << "Viagem inexistente." << endl;
			                }
							break;
						}
						case 3:
						{
							cout << "Informe o id da viagem que deseja alterar os dados cadastrados: ";
							cin >> id;
							alteracaov(id, vetor, vetor2, vetor3, contar, contador, cont);
							break;
						}
						case 4:
						{
							cout << "Informe o id da viagem que deseja consultar: ";
							cin >> id; // id da viagem que deseja consultar
							consultav(id, vetor3, contar);
							break;
						}
						case 5:
						{
							cout << "Informe o id da viagem que deseja fazer a inscricao de um cliente: ";
							cin >> insc.idv;
							inscricaov(insc, vetor, vetor3, contador, contar);					
							break;
						}
						case 6:
						{
							cout << "Informe o id da  viagem que deseja fazer a remocao um cliente: ";
							cin >> insc.idv;
							desistenciav(insc, vetor, vetor3, contador, contar);
							break;
						}
						case 7:
						{
							cout << "Informe o dia e o mes inicial que deseja consultar: ";
							cin >> dia_inicial;
							cin >> dia_final;
							cout << "Informe o dia e o mes inicial que deseja consultar: ";
							cin >> mes_inicial;
							cin >> mes_final;
							listagemv(vetor3, contar, dia_inicial, dia_final, mes_inicial, mes_final);
							break;
						}
						case 8:
						{
							relatoriov(vetor3, contar);
							break;
						}						
						default:
						{
							cout << "Opcao invalida. Tente novamente" << endl;
						break;
						}
					}
					opcao = menu3();
				}
                cout << endl << "Menu Viagem finalizado com sucesso!" << endl;
				break;
			}
			default:
			{
				cout << "Opcao invalida. Tente novamente" << endl;
				break;
			}
		}
		opc = menuprincipal();
	}
    
    c = 0;
    while(arqclientes2 << vetor[c].id << endl << vetor[c].nome << endl << vetor[c].endereco << endl << vetor[c].email << endl << vetor[c].telefone << endl)
	{
		cout << "Parte 2 " << endl;
        cout << " id: " << vetor[c].id << endl;
		cout << " nome: " << vetor[c].nome << endl;
		cout << " endereco: " << vetor[c].endereco << endl;
		cout << " email: " <<vetor[c].email << endl;
		cout << " telefone: " << vetor[c].telefone << endl;
		if(c == (contador-1))
        {
            break;
        }
        c++;
	}
    cout << endl << "Programa finalizado com sucesso." << endl;
	arqclientes2.close();
	//arqdestinos2.close();
	//arqviagens2.close();
    
    
    cout << endl << "\tAGRADECEMOS A UTILIZACAO DA APLICACAO. VOLTE SEMPRE!!!" << endl;

  	return 0;
}

int menuprincipal()
{
    int escolha;
    cout << endl;
	cout <<"  =======================MENU PRINCIPAL=======================" << endl;
	cout <<" ||                                                          ||" << endl;
    cout <<" ||                                                          ||" << endl;
	cout <<" || 1 - Menu Cliente.                                        ||" << endl;
	cout <<" || 2 - Menu Destino.                                        ||" << endl;
    cout <<" || 3 - Menu Viagem.                                         ||" << endl;
	cout <<" || 4 - Sair da aplicacao.                                   ||" << endl;
	cout <<" ||                                                          ||" << endl;
	cout <<"  =======================MENU PRINCIPAL=======================" << endl;
    cout << endl;
	cout << "  Escolha: ";  
	cin >> escolha;
    cin.ignore();
    return escolha;
}

int menu1() // menu cliente
{
    int escolha;
    cout << endl;
	cout <<"  ========================MENU CLIENTE========================" << endl;
	cout <<" ||                                                          ||" << endl;
    cout <<" ||                                                          ||" << endl;
	cout <<" || 1 - Cadastro de novo cliente.                            ||" << endl;
	cout <<" || 2 - Exclusao de um cliente.                              ||" << endl;
    cout <<" || 3 - Alteracao dos dados de um cliente.                   ||" << endl;
    cout <<" || 4 - Consulta dados de um cliente.                	     ||" << endl;
    cout <<" || 5 - Lista dados de todos os clientes.                    ||" << endl;
	cout <<" || 6 - Sair.                                                ||" << endl;
	cout <<" ||                                                          ||" << endl;
	cout <<"  ========================MENU CLIENTE========================" << endl;
    cout << endl;
	cout << "  Escolha: ";  
	cin >> escolha;
    cin.ignore();
    return escolha;
}

int menu2() // menu destino
{
    int escolha;
    cout << endl;
	cout <<"  ========================MENU DESTINO========================" << endl;
	cout <<" ||                                                          ||" << endl;
    cout <<" ||                                                          ||" << endl;
	cout <<" || 1 - Cadastro de um novo destino.                         ||" << endl;
	cout <<" || 2 - Exclusao de um destino.                              ||" << endl;
    cout <<" || 3 - Alteracao dos dados de um destino.                   ||" << endl;
    cout <<" || 4 - Consultar dados de um destino.                	     ||" << endl;
    cout <<" || 5 - Listar dados de todos os destinos.                   ||" << endl;
	cout <<" || 6 - Sair.                                                ||" << endl;
	cout <<" ||                                                          ||" << endl;
	cout <<"  ========================MENU DESTINO========================" << endl;
    cout << endl;
	cout << "  Escolha: ";  
	cin >> escolha;
    cin.ignore();
    return escolha;
}

int menu3() // menu viagem
{
    int escolha;
    cout << endl;
	cout <<"  ======================== MENU VIAGEM========================" << endl;
	cout <<" ||                                                          ||" << endl;
    cout <<" ||                                                          ||" << endl;
	cout <<" || 1 - Cadastro de uma nova viagem.                         ||" << endl;
	cout <<" || 2 - Exclusao de uma viagem.                              ||" << endl;
    cout <<" || 3 - Alteracao dos dados de uma viagem.                   ||" << endl;
    cout <<" || 4 - Consultar dados de uma viagem.                	     ||" << endl;
    cout <<" || 5 - Inscricao de um cliente em uma viagem.               ||" << endl;
    cout <<" || 6 - Desistencia de um cliente em uma viagem.             ||" << endl;
    cout <<" || 7 - Listar dados de viagens por data.             	     ||" << endl;
    cout <<" || 8 - Relatorio sumarizado de viagens.                     ||" << endl;
	cout <<" || 9 - Sair.                                                ||" << endl;
	cout <<" ||                                                          ||" << endl;
	cout <<"  ======================== MENU VIAGEM========================" << endl;
    cout << endl;
	cout << "  Escolha: ";  
	cin >> escolha;
    cin.ignore();
    return escolha;  
}

// funcoes modulo cliente
void insercao(cliente vetor[], int *contador) // cadastro de um novo cliente   contador = vai inserir o dado em cada posicao do vetor, como o i 
{
	int flag = 0;
	long int id; // recebendo o id de um novo cliente
	cout << endl << "Informe o id do cliente que deseja cadastrar (ate 5 digitos): ";
	cin >> id;
	for(int i = 0; i < (*contador); i++)
	{
		if(id == vetor[i].id)
		{
			cout << endl << "Cliente existente." << endl;
			flag = 1;
		}
	}
	if(flag == 0)
	{	
		vetor[(*contador)].id = id;
		cout << "Informe o nome do cliente que deseja cadastrar: ";
		cin.ignore();
		getline(cin,vetor[(*contador)].nome);
		cout << "Informe o endereco do cliente que deseja cadastrar: ";		
		getline(cin,vetor[(*contador)].endereco);
		cout << "Informe o email de contato do cliente que deseja cadastrar: ";
		getline(cin,vetor[(*contador)].email);
		cout << "Informe o telefone de contato do cliente que deseja cadastrar: ";
		cin >> vetor[(*contador)].telefone;
		cout << endl << "Cliente inserido." << endl;
        (*contador)++;
	}
}

void remocao(long int id, cliente vetor[], int *contador) // excluir um cliente
{
	for(int i = 0; i < (*contador); i++) // excluindo um cliente e redimencionando 
	{
		if(id == vetor[i].id) // comparando o id que a pessoa digitou para ser excluido com os ids ja existem
		{
			for(int j = i; j < (*contador); j++)
			{
				vetor[j] = vetor[j + 1];
			}
			cout << endl << "Cliente excluido." << endl;
			(*contador)--;
            return; // depois de excluido nao precisa verificar o restante do vetor
		}
	}
	cout << endl << "Cliente inexistente." << endl;
}

void alteracao(long int id, cliente vetor[], int contador) // alteracao de dados de um cliente
{
	for(int i = 0; i < contador; i++) 
	{
		if(id == vetor[i].id) // verificando se o id fornecido é igual a algum id ja existente no vetor(lista de clientes)
		{
            cout << "Informe o novo nome: ";
            cin.ignore();
            getline(cin,vetor[i].nome);
            cout << "Informe o novo endereco: ";
			getline(cin,vetor[i].endereco);
			cout << "Informe o novo email: ";
			getline(cin,vetor[i].email);
			cout << "Informe o novo telefone: ";
			cin >> vetor[i].telefone;
			cout << endl << "Cliente alterado." << endl;
			return; // depois de alterado nao precisa verificar o restante do vetor
		}
	}
	cout << endl << "Cliente inexistente " << endl;
} 

void consulta(long int id, cliente vetor[], int contador) // consultar dados de um cliente
{
	for(int i = 0; i < contador; i++) 
	{
		if(id == vetor[i].id) // verificando se o id fornecido é igual a algum id ja existente no vetor(lista de clientes)
		{
			cout << "Nome: " << vetor[i].nome << endl;
			cout << "Endereco: " << vetor[i].endereco << endl;
			cout << "Email: " << vetor[i].email << endl;
			cout << "Telefone: " << vetor[i].telefone << endl;
			return; // depois de alterado nao precisa verificar o restante do vetor
		}
	}
	cout << endl << "Cliente inexistente " << endl;
}

void listagem(cliente vetor[], int contador) // lista os dados de todos os clientes
{
    int flag = 0;
	for(int i = 0; i < contador; i++)
	{
        cout << endl;
		cout << "Dados do cliente " << i+ 1 << endl;
		cout << "Nome: " << vetor[i].nome << endl;
		cout << "Endereco: " << vetor[i].endereco << endl;
		cout << "Email: " << vetor[i].email << endl;
		cout << "Telefone: " << vetor[i].telefone << endl << endl;
        flag = 1;
	}
    if(flag == 0)
    {
        cout << endl << "Nenhum cliente cadastrado." << endl;
    }
}

// funcoes modulo destino
void insercaod(destino vetor2[], int *cont)
{
	int flag = 0;
	long int id; // recebendo o id de um novo destino
	cout << endl << "Informe o id do destino que deseja cadastrar (ate 3 digitos): ";
	cin >> id;
	for(int i = 0; i < (*cont); i++)
	{
		if(id == vetor2[i].id)
		{
			cout << endl << "Destino existente." << endl;
			flag = 1;
		}
	}
	if(flag == 0)
	{	
		vetor2[(*cont)].id = id;
		cout << "Informe o nome da cidade que deseja cadastrar: ";
		cin.ignore();
		getline(cin,vetor2[(*cont)].localidade);
		cout << "Informe o pais que pertence a cidade que deseja cadastrar: ";
		getline(cin,vetor2[(*cont)].pais);
		cout << "Informe o numero de locais que deseja visitar: ";
		cin >> vetor2[(*cont)].num;
		cout << "Informe o custo do destino: ";
		cin >> vetor2[(*cont)].custo;
		cout << endl << "Destino inserido." << endl;
        (*cont)++;
	}	
}

void remocaod(long int id, destino vetor2[], int *cont)
{
	for(int i = 0; i < (*cont); i++) // excluindo um destino e redimencionando 
	{
		if(id == vetor2[i].id)
		{
			for(int j = i; j < (*cont); j++)
			{
				vetor2[j] = vetor2[j + 1];
			}
			cout << endl << "Destino excluido." << endl;
			(*cont)--;
            return; // depois de excluido nao precisa verificar o restante do vetor
		}
	}
	cout << endl << "Destino inexistente." << endl;
}

void alteracaod(long int id, destino vetor2[], int cont) 
{
	for(int i = 0; i < cont; i++) 
	{
		if(id == vetor2[i].id) // verificando se o id fornecido é igual a algum id ja existente no vetor(lista de destinos)
		{
			cout << "Informe a nova cidade (localidade): ";
			cin.ignore();
            getline(cin,vetor2[i].localidade);
			cout << "Informe o novo pais: ";
			getline(cin,vetor2[i].pais);
			cout << "Informe o novo numero de locais a visitar: ";
			cin >> vetor2[i].num;
			cout << "Informe o custo do novo destino: ";
			cin >> vetor2[i].custo;
			cout << endl << "Destino alterado." << endl;
			return; // depois de alterado nao precisa verificar o restante do vetor
		}
	}
	cout << endl << "Destino inexistente " << endl;
} 

void consultad(long int id, destino vetor2[], int cont)
{
	for(int i = 0; i < cont; i++) 
	{
		if(id == vetor2[i].id) // verificando se o id fornecido é igual a algum id ja existente no vetor(lista de destinos)
		{
			cout << "Localidade: " << vetor2[i].localidade << endl;
			cout << "Pais: " << vetor2[i].pais << endl;
			cout << "Numero de locais a visitar: " << vetor2[i].num << endl;
			cout << "Custo: " << vetor2[i].custo << endl;
			return; // depois de alterado nao precisa verificar o restante do vetor
		}
	}
	cout << endl << "Destino inexistente " << endl;
}

void listagemd(destino vetor2[], int cont)
{
	int flag = 0;
	for(int i = 0; i < cont; i++)
	{
		cout << "Dados do destino " << i+ 1 << endl;
		cout << "Localidade: " << vetor2[i].localidade << endl;
		cout << "Pais: " << vetor2[i].pais << endl;
		cout << "Numero de locais a visitar: " << vetor2[i].num << endl;
		cout << "Custo: " << vetor2[i].custo << endl << endl;
		flag = 1;
	}
	if(flag == 0)
    {
        cout << endl << "Nenhum destino cadastrado." << endl;
    }
}

// funcoes modulo viagem
void insercaov(cliente vetor[], destino vetor2[], viagem vetor3[], int *contar, int contador, int cont) // inserindo uma nova viagem 
{
	vetor3[(*contar)].custot = 0;
	int flag = 0; 
	long int id, idc, idaux; // recebendo o id de uma nova viagem, idc = id do cliente 
	cout << endl << "Informe o id da viagem que deseja cadastrar (ate 2 digitos): ";
	cin >> id;
	for(int i = 0; i < (*contar); i++) // percorendo o vetor para saber se ja existe viagem com esse id cadastrado
	{
		if(id == vetor3[i].id)
		{
			cout << endl << "Viagem existente." << endl;
			return; //Indica que ja existe uma viagem com o mesmo ID
		}
	}
    vetor3[(*contar)].id = id;
    
    cout << "Informe o id do destino final da viagem: "; // cidade final que o cliente deseja chegar 
	cin >> id;
    idaux = id; // So para nao perder o destino final!
    
	for(int i = 0; i < cont; i++)
	{
		if(id == vetor2[i].id) // Verifica se o destino pretendido existe dentro do vetor de destino
		{
			vetor3[(*contar)].custot += vetor2[i].custo; //Somando o custo de cada deslocamento
			vetor3[(*contar)].custot += 5; // 5,00 taxa de deslocamento pre definida
			
            vetor3[(*contar)].quantd = vetor2[i].num+1;
            
			for(int j = 0; j < vetor2[i].num; j++) //Inserindo os deslocamentos intermediarios!
			{
				cout << "Informe o dia da viagem do deslocamento " << j+1 << " : ";
				cin >> vetor3[(*contar)].desloc[j].dia;
				cout << "Informe o mes da viagem do deslocamento " << j+1 << " : ";
				cin >> vetor3[(*contar)].desloc[j].mes;
				while(!verificarData(vetor3,*contar,j)) // considerando todos os meses com 30 dias e verifica se o intervalo de datas é válido
				{
                    //Vai pedir a data até que seja válido as condições
					cout << endl << "Data inexistente. " << endl;
                    cout << endl << "Tente novamente." << endl;
					cout << "Informe o dia da viagem: ";
					cin >> vetor3[(*contar)].desloc[j].dia;
					cout << "Informe o mes da viagem: ";
					cin >> vetor3[(*contar)].desloc[j].mes;
				}
				cout << "Informe o id do destino intermediario " << j+1 << " : "; //id das cidades que o cliente passara antes de chegar na cidade final
				cin >> id;
				
                for(int l = 0; l < cont; l++)
				{
					if(id == vetor2[l].id)//Verifica se as cidades intermediarias existem
					{
                        flag = 1;
                        vetor3[(*contar)].custot += vetor2[l].custo; // Soma-se o custo dessa cidade ao custo total!
                        vetor3[(*contar)].custot += 5;
                        vetor3[(*contar)].desloc[j].iddestino = id;
					}
				}
                if(flag == 0)
                {
                    // Se a cidade que queira passar, nao exista dentro do vetor de destinos, entao o percurso é invalido
                    cout << endl << "Percurso invalido. " << endl;
                    return;
                }
                flag = 0;
			}
            //Informando data para o destino final
            cout << "Informe o dia da viagem do deslocamento final: ";
            cin >> vetor3[(*contar)].desloc[vetor2[i].num].dia;
            cout << "Informe o mes da viagem do deslocamento final: ";
            cin >> vetor3[(*contar)].desloc[vetor2[i].num].mes;
            while(!verificarData(vetor3,*contar,vetor2[i].num))
            {
                cout << endl << "Data inexistente. " << endl;
                cout << endl << "Tente novamente." << endl;
                cout << "Informe o dia da viagem do deslocamento final: ";
                cin >> vetor3[(*contar)].desloc[vetor2[i].num].dia;
                cout << "Informe o mes da viagem do deslocamento final: ";
                cin >> vetor3[(*contar)].desloc[vetor2[i].num].mes;
            }
            vetor3[(*contar)].desloc[vetor2[i].num].iddestino = idaux; //Salva o destino final no vetor de deslocamentos, sendo o ultimo desloc
            
            
			cout << "Informe a quantidade de clientes ja confirmados para essa viagem: ";
			cin >> vetor3[(*contar)].quantc;
            for(int j = 0; j < vetor3[(*contar)].quantc; j++)
			{
				cout << "Informe o id do cliente: ";
				cin >> idc; // id do cliente que deseja cadastrar na viagem 
				
                for(int k=0; k < contador; k++)
				{
					if(idc == vetor[k].id) //Verifica se o cliente desejado existe no vetor de clientes
					{
						if(!verificarDisp(vetor3, *contar, idc)) //Funcao que verifica se o cliente não está cadastrado em outra viagem, podendo haver datas iguais, sendo invalido! 
                        {
                        	cout << endl << "Cliente indisponivel. " << endl;
							return;
						}
                        // Se o cliente não for indisponivel o mesmo pode ser salvo no vetor de viagens
						flag = 1;
                        vetor3[(*contar)].idcliente[j] = idc;
                        break;
					}
				}
                if(flag == 0)
                {
                    //Se o cliente digitado não existir dentro do vetor de clientes!
                    cout << endl << "Cliente inexistente. " << endl;
                    return ;
                }
			}
	
            cout << endl << "Viagem inserida. " << endl;
            (*contar)++;
            return;  //Assim que encontrar o destino valido faz as operacoes relevantes e sai da funcao!
		}
	}
	cout << endl << "Destino inexistente " << endl;
}

bool verificarData(viagem vetor3[], int contar, int pos) // Verifica se a data é valida
{
    if(vetor3[contar].desloc[pos].dia < 1 || vetor3[contar].desloc[pos].dia >30) //Intervalo 1 a 30 dias
    {
        cout << "Dia inexistente. Favor fornecer um numero entre o intervalo 1 a 30: " <<endl;
        return false;
    }
    if(vetor3[contar].desloc[pos].mes < 1 || vetor3[contar].desloc[pos].mes >12) //Intervalo 1 a 12 meses
    {
        cout << "Mes inexistente. Favor fornecer um numero entre o intervalo 1 a 12: " <<endl;
        return false;
    }
    
    if(pos > 0) // Se existe mais de um deslocamento já salvo no vetor!
    {
        // Compara o mes que deseja inserir com o anterior
        if(vetor3[contar].desloc[pos].mes > vetor3[contar].desloc[pos-1].mes) 
        {
            //Se o mes a ser adicionado for maior que o anterior, é valido!
            return true;
        }
        else
        {
            if(vetor3[contar].desloc[pos].mes < vetor3[contar].desloc[pos-1].mes)
            {
                //Se o mes a ser adicionado for menor que o anterior, é falso 
                return false;
            }
            else
            {
                //Senao, os meses sao iguais, e é preciso analisar os dias
                if(vetor3[contar].desloc[pos].dia > vetor3[contar].desloc[pos-1].dia)
                {
                    //Se o dia a ser adicionado for maior que o anterior, entao é valido!
                    return true;
                }
                else
                {
                    //Senão, o dia a ser adicionado é menor ou igual, sendo invalido!
                    return false;
                }
            }
        }  
    }
    else
    {
        //Se não existir mais de um deslocamento salvo no vetor, o mesmo pode ser salvo no vetor
        return true;
    }
}

bool verificarDisp(viagem vetor3[], int contar , long int id)  // bool é uma funcao que retorna verdadeiro ou falso
{
    int quantd = vetor3[contar].quantd;
    for(int i=0; i < contar; i++) //Analisa todas as viagens cadastradas
    {
        for(int j=0; j < vetor3[i].quantc; j++)//Analisa todos os clientes de uma viagem
        {
            if(id == vetor3[i].idcliente[j])//Verifica se o cliente existe dentro de cada viagem
            {
                //Se encontrar o cliente dentro de uma viagem, analisa as datas para verificar se o cliente é disponível
                for(int k=0; k < vetor3[i].quantd && k < vetor3[contar].quantd; k++)
                {
                    if(vetor3[contar].desloc[0].mes == vetor3[i].desloc[k].mes) // Analisa se o cliente possui o deslocamento inicial, igual aos deslocamentos da viagem
                    {
                        //Se existir, verifica se a dia inicial do deslocamento é menor ou igual aos deslocamentos disponiveis
                        if(vetor3[contar].desloc[0].dia <= vetor3[i].desloc[k].dia)
                        {
                            return false;
                        }
                    }
                    if(vetor3[contar].desloc[quantd-1].mes == vetor3[i].desloc[k].mes) //Analisa o mes do deslocamento final com os deslocamentos salvos no vetor
                    {
                        //Analisa o dia do deslocamento final em comparacao ao deslocamentos salvos
                        if(vetor3[contar].desloc[quantd-1].dia >= vetor3[i].desloc[k].dia)
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }
    //Se nao entrar em nenhumas das condicoes que retornam false, a data é valida
    return true;
}

void remocaov(long int id, viagem vetor3[], int *contar) // excluir uma viagem
{
	for(int i = 0; i < (*contar); i++) // excluindo uma viagem e redimencionando 
	{
		if(id == vetor3[i].id) // comparando o id que a pessoa digitou para ser excluido com os ids ja existem
		{
			for(int j = i; j < (*contar); j++)
			{
				vetor3[j] = vetor3[j + 1];
			}
			cout << endl << "Viagem excluida." << endl;
            (*contar)--;
			return; // depois de excluido nao precisa verificar o restante do vetor
		}
	}
	cout << endl << "Viagem inexistente." << endl;
}

void alteracaov(long int id, cliente vetor[], destino vetor2[], viagem vetor3[], int contar, int contador, int cont) // alteracao dos dados de uma viagem
{
	int flag = 0, flag2 = 0;
	long int idaux, idc; // recebendo o novo id do destino final da viagem, idc = id do cliente  
	for(int i = 0; i < contar; i++) // percorendo o vetor para saber se existe esse id cadastrado para ser alterado
	{
		if(id == vetor3[i].id)
		{
			cout << "Informe o novo id do destino final da viagem que deseja alterar: ";
            cin >> idaux; //Guarda o id do destino final da viagem 
            
            for(int j=0; j < cont; j++)
            {
                if(idaux == vetor2[j].id) //Verifica se o id final existe no vetor de destinos
                {
                    flag2 = 1;
                    vetor3[i].custot += vetor2[j].custo; //Soma o custo dessa cidade.
                    vetor3[i].custot += 5; //Taxa pre-definida
                    
                    vetor3[i].quantd = vetor2[j].num + 1;
                    
                    for(int k=0; k < vetor2[j].num; k++) //Insercao dos deslocamentos intermediarios
                    {
                        cout << "Informe o novo dia da viagem do deslocamento " << k+1 << " : ";
                        cin >> vetor3[i].desloc[k].dia;
                        cout << "Informe o novo mes da viagem do deslocamento " << k+1 << " : ";
                        cin >> vetor3[i].desloc[k].mes;
                        while(verificarData(vetor3,contar,k)) //Verificando se a data e valida
                        {
                            cout << endl << "Data inexistente. " << endl;
                            cout << endl << "Tente novamente." << endl;
                            cout << "Informe o novo dia da viagem: ";
                            cin >> vetor3[i].desloc[k].dia;
                            cout << "Informe o novo mes da viagem: ";
                            cin >> vetor3[i].desloc[k].mes;
                        }
                        
                        //Destinos intermediarios
                        cout << "Informe o novo id do destino do deslocamento " << k+1 << " : ";
                        cin >> id;
                        
                        for(int l=0; l < cont; l++)
                        {
                            if(id == vetor2[l].id) //Verifica se ele existe
                            {
                                flag = 1;
                                vetor3[i].custot += vetor2[k].custo;
                                vetor3[i].custot += 5;
                                vetor3[i].desloc[k].iddestino = id;
                            }
                        }
                        if(flag ==0)
                        {
                            //Se o destino não existir dentro do vetor, o percurso é invalido
                            cout << endl << "Percurso invalido." << endl;
                            return;
                        }
                        flag = 0;
                    }
                    //Pedindo a data do deslocamento final
                    cout << "Informe o novo dia da viagem do deslocamento final: ";
                    cin >> vetor3[i].desloc[vetor2[i].num].dia;
                    cout << "Informe o novo mes da viagem do deslocamento final: ";
                    cin >> vetor3[i].desloc[vetor2[i].num].mes;
                    while(!verificarData(vetor3,contar,vetor2[i].num))
                    {
                        cout << endl << "Data inexistente. " << endl;
                        cout << endl << "Tente novamente." << endl;
                        cout << "Informe o novo dia da viagem do deslocamento final: ";
                        cin >> vetor3[i].desloc[vetor2[i].num].dia;
                        cout << "Informe o novo mes da viagem do deslocamento final: ";
                        cin >> vetor3[i].desloc[vetor2[i].num].mes;
                    }
                    vetor3[i].desloc[vetor2[i].num].iddestino = idaux;
                    
                    //A nova quantidade de clientes da viagem!
                    cout << "Informe a nova quantidade de clientes ja confirmados para essa viagem: ";
                    cin >> vetor3[i].quantc;
                   
                    for(int l=0; l < vetor3[i].quantc;  l++)
                    {
                        cout << "Informe o novo id do cliente : ";
                        cin >> idc; //Novos ids de clientes
                        
                        for(int k=0; k < contador; k++)
                        {
                            if(idc == vetor[k].id) // Verifica se o cliente existe!
                            {
                                if(!verificarDisp(vetor3,contar,idc)) // Verifica a disponibilidade do cliente
                                {
                                    cout << endl << "Cliente indisponivel." << endl;
                                    return;
                                }
                                flag = 1;
                                vetor3[i].idcliente[l] = idc;
                                break;
                            }
                        }
                        if(flag == 0)
                        {
                            //Se o cliente não existe
                            cout << endl << "Cliente inexistente. " << endl;
                            return ;
                        }
                    }
                    
                    cout << endl << "Viagem alterada." << endl;
                    return; // depois de alterada nao precisa verificar o restante do vetor
                }
            }
            if(flag2 == 0)
            {
                //Caso o destino final digitado seja invalido
                cout << endl << "Destino inexistente." << endl;
                return;
            }
        }
    }
    //Id da viagem não existe dentro do vetor de viagens
	cout << endl << "Viagem inexistente " << endl;    
}

void consultav(long int id, viagem vetor3[], int contar) // consultar dados de uma viagem
{
    for(int i = 0; i < contar; i++) 
	{
		if(id == vetor3[i].id) // verificando se o id fornecido é igual a algum id ja existente no vetor(lista de viagens)
		{
			cout << endl << "Dados da viagem " << endl;
            cout << endl << "Sequencia de deslocamentos: " << endl;
            for(int j = 0; j < vetor3[i].quantd; j++)
			{
				cout << "Deslocamento " << j+1 << " :\nDia : " << vetor3[i].desloc[j].dia << " Mes: " << vetor3[i].desloc[j].mes << " ID Destino: " << vetor3[i].desloc[j].iddestino << endl;
			}
			cout << "Sequencia de clientes: " << endl;
			for(int j = 0; j < vetor3[i].quantc; j++)
			{
				cout << "Id do cliente " << j+1 << " :" << vetor3[i].idcliente[j] << endl ;
			}
			cout << "Custo total da viagem: " << vetor3[i].custot << endl;	
			return; // depois de alterado nao precisa verificar o restante do vetor
		}
	}
	cout << endl << "Viagem inexistente " << endl;
}

void inscricaov(inscricao insc, cliente vetor[], viagem vetor3[], int contador, int contar)
{
	int flag = 0;
	for(int i = 0; i < contar; i++)
	{
		if(insc.idv == vetor3[i].id)
		{
			cout << "Informe o id do cliente que deseja cadastrar na viagem: ";
			cin >> insc.idc;
			for(int j = 0; j < contador; j++)
			{
				if(insc.idc == vetor[j].id)
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0)
			{
				cout << endl << "Cliente inexistente." << endl;
				return;
			}
			for(int k = 0; k < vetor3[i].quantc; k++)
			{
				if(insc.idc == vetor3[i].idcliente[k])
				{
					cout << endl << "Cliente ja inscrito." << endl;
                    return;
				}
			}
			
            vetor3[i].idcliente[vetor3[i].quantc] = insc.idc; // colocando dentro do vetor de clientes inscritos o novo cliente que foi inscrito
            vetor3[i].quantc += 1;
            cout << endl << "Cliente inscrito." << endl;
            return;
		}
	}
	cout << endl << "Viagem inexistente." << endl;
}

void desistenciav(inscricao insc, cliente vetor[], viagem vetor3[], int contador, int contar)
{
	int flag = 0;
	for(int i = 0; i < contar; i++)
	{
		if(insc.idv == vetor3[i].id)
		{
			cout << "Informe o id do cliente que deseja cadastrar na viagem: ";
			cin >> insc.idc;
			for(int j = 0; j < contador; j++)
			{
				if(insc.idc == vetor[j].id)
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0)
			{
				cout << endl << "Cliente inexistente." << endl;
				return;
			}
			for(int k = 0; k < vetor3[i].quantc; k++)
			{
				if(insc.idc == vetor3[i].idcliente[k])  
				{
					for(int l=k; l < vetor3[i].quantc; l++)
					{
						vetor3[i].idcliente[l] = vetor3[i].idcliente[l+1];
					}
					vetor3[i].quantc -= 1;
                    cout << endl << "Cliente removido." << endl;
					return; 
				}
			}
            cout << endl << "Cliente nao inscrito." << endl;
            return;
		}
	}
	cout << endl << "Viagem inexistente." << endl;
}

void listagemv(viagem vetor3[], int contar, int dia_inicial, int dia_final, int mes_inicial, int mes_final)
{
	int flag = 0;
	for(int i = 0; i < contar; i++)
	{
		flag = 0;
        //Verifica o intervalo de datas pretendido, primeiro analisa os meses
		if(mes_inicial < vetor3[i].desloc[0].mes &&  mes_final > vetor3[i].desloc[vetor3[i].quantd-1].mes)
        {
            flag = 1;
        }
        if(mes_inicial == vetor3[i].desloc[0].mes &&  mes_final == vetor3[i].desloc[vetor3[i].quantd-1].mes)
        {
            if(dia_inicial <= vetor3[i].desloc[0].dia && dia_final >= vetor3[i].desloc[vetor3[i].quantd-1].dia)
            {
                flag = 1;
            }
            else
            {
                flag = 0;
            }
        }
		if(flag == 1)
		{
			cout << "Dados da viagem " << i + 1 << ": " << endl;
			for(int j = 0; j < vetor3[i].quantd; j++)
			{
				cout << "Dia da viagem: " << vetor3[i].desloc[j].dia << endl;
				cout << "Mes da viagem: " << vetor3[i].desloc[j].mes << endl;
				cout << "Id do destino: " << vetor3[i].desloc[j].iddestino << endl;
			}
			cout << "Sequencia de clientes: " << endl;
			for(int j = 0; j < vetor3[i].quantc; j++)
			{
				cout << "Id do cliente " << j + 1 << " : " << vetor3[i].idcliente[j] << endl;
			}
			cout << "Custo total da viagem: " << vetor3[i].custot << endl;
		}
	}
	if(flag == 0)
	{
		cout << endl << "Nenhuma viagem cadastrada." << endl;
	}
}

void relatoriov(viagem vetor3[], int contar)
{
	int flag = 0, qtotalc; // quantidade total de clientes
	double custotv = 0, vmedio, mediac, menorv, maiorv; // custo total das viagens , valor medio de viagens, media de clientes, menor valor de viagem, maior valor de viagem
	menorv = vetor3[0].custot;
	maiorv = vetor3[0].custot;
	for(int i = 0; i < contar; i++)
	{
		flag = 1;
		if(menorv > vetor3[i].custot)
		{
			menorv = vetor3[i].custot;
		}
		if(maiorv < vetor3[i].custot)
		{
			maiorv = vetor3[i].custot;
		}
		custotv = custotv + vetor3[i].custot;
		qtotalc = qtotalc + vetor3[i].quantc;
	}
    if(flag == 0)
    {
        cout << endl << "Nenhuma viagem cadastrada." << endl;
        return;
    }
	vmedio = custotv / contar;
	mediac = (qtotalc*1.0) / contar;
	cout << endl;
    cout << "Numero total de viagens: " << contar << endl;
    cout << "Menor valor de viagem: " << menorv << endl;
    cout << "Maior valor de viagem: " << maiorv << endl;
    cout << "Valor medio das viagens: " << vmedio << endl;
    cout << "Numero total de clientes: " << qtotalc << endl;
    cout << "Numero medio de clientes: " << mediac << endl << endl;
}
