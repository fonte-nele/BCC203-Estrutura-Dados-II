#include <iostream> 
#include <string>
using namespace std;


struct cliente // estrutura para tratar dos dados dos clientes 
{
	long int id; // identidade do cliente: CPF
	string nome; // nome do cliente
	string endereco; // endereco do cliente
	string email; // e-mail do cliente
	long int telefone; // telefone do cliente
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
    deslocamentos desloc[100];  //Indica que uma viagem pode ter no maximo 100 deslocamentos
	long int idcliente[100]; //sequencia de clientes, indicando que pode haver no maximo 100 clientes
    double custot;
    int quantc;
    int quantd;
};

struct inscricao // cadastro nas viagens 
{
	long int id; // identidade da viagem
	long int idc; // identidade do cliente
};

int menuPrincipal(); // funcao para gerenciar os sub-menus
int menu1(); // funcao menu 1 modulo cliente
int menu2(); // funcao menu 2 modulo destino
int menu3(); // funcao menu 3 modulo viagem 

// funcoes modulo cliente 
void insercao(cliente vetor[], int* contador); // cadastro de um novo cliente
void remocao(long int id, cliente vetor[], int* contador); // excluir um cliente 
void alteracao(long int id, cliente vetor[], int contador); // alteracao de dados de um cliente
void consulta(long int id, cliente vetor[], int contador); // consultar dados de um cliente
void listagem(cliente vetor[], int contador); //lista os dados de todos os clientes

// funcoes modulo destino
void insercaod(destino vetor2[], int* contador2);  // cadastro de um novo destino
void remocaod(long int id, destino vetor2[], int* contador2); // excluir um destino 
void alteracaod(long int id, destino vetor2[], int contador2); // alteracao de dados de um destino
void consultad(long int id, destino vetor2[], int contador2); // consultar dador de um destino
void listagemd(destino vetor2[], int contador2); // lista os dados de todos os destinos

// funcoes modulo viagem
void insercaov(cliente vetor[], destino vetor2[], viagem vetor3[], int contador, int contador2, int *contador3); //cadastro de uma nova viagem
void remocaov(long int id, viagem vetor3[], int* contador3); // excluir uma viagem
void alteracaov(long int id, cliente vetor[], destino vetor2[], viagem vetor3[], int contador, int contador2, int contador3); // alteracao dos dados de uma viagem
void consultav(long int id, viagem vetor3[], int contador3); // consultar dados de uma viagem
void inscricaov(inscricao insc, viagem vetor3[], int contador3, cliente vetor[], int contador);
void desistenciav(inscricao insc, viagem vetor3[], int contador3, cliente vetor[], int contador);
void listagemv(viagem vetor3[], int contador3, int dia_inicial, int dia_final, int mes_inicial, int mes_final); // lista os dados de um intervalo de viagens
void relatoriov(viagem vetor3[], int contador3);
bool verificarData(viagem vetor3[], int contador3, int pos);
bool verificarDisp(viagem vetor3[], int contador3, long int id);

int main()
{
	long int id;
	int n, op, opcao, contador = 0, contador2 = 0, contador3 = 0; // n = tamanho do vetor, opcao = numero da escolha feita no menu
	cout << "Digite ‚ o tamanho do vetor: ";
	cin >> n;
    cliente vetor[n];
	destino vetor2[n];
    viagem vetor3[n];
    inscricao insc;
    
    cout << endl << "\t\tBEM-VINDO A AGENCIA DE VIAGENS FONTE\n\t\tFAZENDO DO CEU O MELHOR LUGAR DA TERRA" << endl;
    
    do
    {
        op = menuPrincipal();
        switch(op)
        {
            case 1:
            {
                cout << endl << "\tMODULO CLIENTE" << endl;
                do
                {	
                    opcao = menu1();
                    switch(opcao)
                    {
                        case 1:
                        {
                            insercao(vetor, &contador);
                            break;
                        }
                        case 2:
                        {
                            cout << endl << "Informe o id do cliente que deseja excluir: ";
                            cin >> id; // id que o cliente quer excluir  
                            if(contador > 0)
                            {
                                remocao(id, vetor, &contador);
                            }
                            else
                            {
                                cout << "Cliente inexistente." << endl;
                            }
                            break;
                        }
                        case 3:
                        {
                            cout << endl << "Informe o id do cliente que deseja alterar os dados cadastrados: ";
                            cin >> id;
                            alteracao(id, vetor, contador);
                            break;
                        }
                        case 4:
                        {
                            cout << endl << "Informe o id do cliente que deseja consultar: ";
                            cin >> id; // id que o cliente quer consultar
                            consulta(id, vetor, contador);
                            break;
                        }
                        case 5:
                        {
                            listagem(vetor, contador);
                            break;
                        }
                        case 6:
                        {
                            cout << endl << "Menu Cliente finalizado com sucesso!" << endl;
                            break;
                        }
                        default:
                        {
                            cout << endl << "Opcao invalida. Tente novamente" << endl;
                            break;
                        }
                    }
                }while(opcao != 6);
                break;
            }
            case 2:
            {
                cout << endl << "\tMODULO DESTINO" << endl;
                do
                {
                    opcao = menu2();
                    switch(opcao)
                    {
                        case 1:
                        {
                            insercaod(vetor2, &contador2);
                            break;
                        }
                        case 2:
                        {
                            cout << endl << "Informe o id do destino que deseja excluir: ";
                            cin >> id; // id do destino que quer excluir  
                            if(contador2 > 0)
                            {
                                 remocaod(id, vetor2, &contador2);
                            }
                            else
                            {
                                cout << "Destino inexistente." << endl;
                            }
                            break;
                        }
                        case 3:
                        {
                            cout << endl << "Informe o id do destino que deseja alterar os dados cadastrados: ";
                            cin >> id;
                            alteracaod(id, vetor2, contador2);
                            break;
                        }
                        case 4:
                        {
                            cout << endl << "Informe o id do destino que deseja consultar: ";
                            cin >> id; // id do destino quer consultar
                            consultad(id, vetor2, contador2);
                            break;
                        }
                        case 5:
                        {
                            listagemd(vetor2, contador2);
                            break;
                        }
                        case 6:
                        {
                            cout << endl << "Menu Destino finalizado com sucesso!" << endl;
                            break; 
                        }
                        default:
                        {
                            cout << endl << "Opcao invalida. Tente novamente" << endl;
                            break;
                        }
                    }
                }while(opcao != 6);
                break;
            }
            case 3:
            {
                int dia_inicial,mes_inicial,dia_final,mes_final;
                cout << endl << "\tMODULO VIAGEM" << endl;
                do
                {
                    opcao = menu3();
                    switch(opcao)
                    {
                        case 1:
                        {
                            insercaov(vetor, vetor2, vetor3, contador, contador2, &contador3);
                            break;
                        }
                        case 2:
                        {
                            cout << endl << "Informe o id da viagem que deseja excluir: ";
                            cin >> id; // id da viagem que quer excluir  
                            if(contador3 > 0)
                            {
                                remocaov(id, vetor3, &contador3);
                            }
                            else
                            {
                                cout << "Viagem inexistente." << endl;
                            }
                            break;
                        }
                        case 3:
                        {
                            cout << endl << "Informe o id da viagem que deseja alterar os dados cadastrados: ";
                            cin >> id;
                            alteracaov(id, vetor, vetor2, vetor3, contador, contador2, contador3);
                            break;
                        }
                        case 4:
                        {
                            cout << endl << "Informe o id da viagem que deseja consultar: ";
                            cin >> id; // id da viagem que quer consultar
                            consultav(id, vetor3, contador3);
                            break;
                        }
                        case 5:
                        {
                            cout << endl << "Informe o id da viagem que deseja fazer a inscricao de um cliente: ";
                            cin >> insc.id;
                            inscricaov(insc,vetor3,contador3,vetor,contador);
                            break;
                        }
                        case 6:
                        {
                            cout << endl << "Informe o id da viagem que deseja fazer a remocao de um cliente: ";
                            cin >> insc.id;
                            desistenciav(insc,vetor3,contador3,vetor,contador);
                            break;
                        }
                        case 7:
                        {
                            cout << endl << "Informe o dia inicial e o mes inicial para listar as viagens: ";
                            cin >> dia_inicial >> mes_inicial;
                            cout << endl << "Informe o dia final e o mes final para listar as viagens: ";
                            cin >> dia_final >> mes_final;
                            listagemv(vetor3, contador3, dia_inicial, dia_final, mes_inicial, mes_final);
                            
                            break;
                        }
                        case 8:
                        {
                            relatoriov(vetor3, contador3);
                            break;
                        }
                        case 9:
                        {
                            cout << endl << "Menu Viagem finalizado com sucesso!" << endl;
                            break; 
                        }
                        default:
                        {
                            cout << endl << "Opcao invalida. Tente novamente" << endl;
                            break;
                        }
                    }
                }while(opcao != 9);
                
                break;
            }
            case 4:
            {
                cout << endl << "Programa finalizado com sucesso!" << endl;
                break;
            }
            default:
            {
                cout << endl << "Opcao invalida. Tente novamente" << endl;
                break;   
            }
        }
    }while(op != 4);
	
    cout << endl << "\tAGRADECEMOS A UTILIZACAO DA APLICACAO. VOLTE SEMPRE!!!" << endl;

	return 0;
}

int menuPrincipal()
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
    cout <<" || 5 - Listar dados de todos os clientes.                   ||" << endl;
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
	cout << endl << "Informe o id do cliente que deseja cadastrar (ate 8 digitos): ";
	cin >> id;
	for(int i = 0; i < (*contador); i++)
	{
		if(id == vetor[i].id)
		{
			cout << endl<< "Cliente existente." << endl;
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

void remocao(long int id, cliente vetor[], int* contador) // excluir um cliente
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
void insercaod(destino vetor2[], int *contador2)
{
	int flag = 0;
	long int id; // recebendo o id de um novo destino
	cout << endl << "Informe o id do destino que deseja cadastrar (ate 4 digitos): ";
	cin >> id;
	for(int i = 0; i < (*contador2); i++)
	{
		if(id == vetor2[i].id)
		{
			cout << endl << "Destino existente." << endl;
			flag = 1;
		}
	}
	if(flag == 0)
	{	
		vetor2[(*contador2)].id = id;
		cout << "Informe o nome da cidade que deseja cadastrar: ";
		cin.ignore();
		getline(cin,vetor2[(*contador2)].localidade);
		cout << "Informe o pais que pertence a cidade que deseja cadastrar: ";
		getline(cin,vetor2[(*contador2)].pais);
		cout << "Informe o numero de locais que deseja visitar: ";
		cin >> vetor2[(*contador2)].num;
		cout << "Informe o custo do destino: ";
		cin >> vetor2[(*contador2)].custo;
		cout << endl << "Destino inserido." << endl;
        (*contador2)++;
	}	
}

void remocaod(long int id, destino vetor2[], int* contador2)
{
	for(int i = 0; i < (*contador2); i++) // excluindo um destino e redimencionando 
	{
		if(id == vetor2[i].id)
		{
			for(int j = i; j < (*contador2); j++)
			{
				vetor2[j] = vetor2[j + 1];
			}
			cout << endl << "Destino excluido." << endl;
			(*contador2)--;
            return; // depois de excluido nao precisa verificar o restante do vetor
		}
	}
	cout << endl << "Destino inexistente." << endl;
}

void alteracaod(long int id, destino vetor2[], int contador2) 
{
	for(int i = 0; i < contador2; i++) 
	{
		if(id == vetor2[i].id) // verificando se o id fornecido é igual a algum id ja existente no vetor(lista de destinos)
		{
            cout << "Informe a nova localidade: ";
            cin.ignore();
            getline(cin,vetor2[i].localidade);
            cout << "Informe o novo pais: ";
            cin.ignore();
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

void consultad(long int id, destino vetor2[], int contador2)
{
	for(int i = 0; i < contador2; i++) 
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

void listagemd(destino vetor2[], int contador2)
{
    int flag = 0;
	for(int i = 0; i < contador2; i++)
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
void insercaov(cliente vetor[], destino vetor2[], viagem vetor3[], int contador, int contador2, int *contador3)
{
    long int idaux;
    vetor3[(*contador3)].custot = 0;
	int flag = 0;
	long int id; // recebendo o id de uma nova viagem 
	cout << endl << "Informe o id da viagem que deseja cadastrar (ate 3 digitos): ";
	cin >> id;
	for(int i = 0; i < (*contador3); i++)
	{
		if(id == vetor3[i].id)
		{
			cout << "Viagem existente." << endl;
			return; //Indica que nao precisa percorrer o resto da funcao!
		}
	}
    
    vetor3[(*contador3)].id = id;
    
    cout << "Informe o id do destino final da viagem: ";
    cin >> id;
    idaux = id;
    for(int i = 0; i < contador2; i++)
    {
        if(id == vetor2[i].id)
        {
            vetor3[(*contador3)].custot += vetor2[i].custo;
            vetor3[(*contador3)].custot += 5;
            
            vetor3[(*contador3)].quantd = vetor2[i].num + 1;
            
            
            for(int j=0; j < vetor2[i].num; j++)
            {
                cout << "Informe o dia da viagem do deslocamento " << j+1 << " : ";
                cin >> vetor3[(*contador3)].desloc[j].dia;
                cout << "Informe o mes da viagem do deslocamento " << j+1 << " : ";
                cin >> vetor3[(*contador3)].desloc[j].mes;
                while(!verificarData(vetor3,*contador3,j))
                {
                    cout << endl << "Data inexistente. " << endl;
                    cout << endl << "Tente novamente." << endl;
					cout << "Informe o dia da viagem: ";
					cin >> vetor3[(*contador3)].desloc[j].dia;
					cout << "Informe o mes da viagem: ";
					cin >> vetor3[(*contador3)].desloc[j].mes;
                }
                
                cout << "Informe o id do destino do deslocamento " << j+1 << " : ";
                cin >> id;
                
                for(int k=0; k < contador2; k++)
                {
                    if(id == vetor2[k].id)
                    {
                        flag = 1;
                        vetor3[(*contador3)].custot += vetor2[k].custo;
                        vetor3[(*contador3)].custot += 5;
                        vetor3[(*contador3)].desloc[j].iddestino = id;
                    }
                }
                if(flag ==0)
                {
                    cout << "Percurso invalido." << endl;
                    return;
                }
                flag = 0;
            }
            cout << "Informe o dia da viagem do deslocamento final: ";
            cin >> vetor3[(*contador3)].desloc[vetor2[i].num].dia;
            cout << "Informe o mes da viagem do deslocamento final: ";
            cin >> vetor3[(*contador3)].desloc[vetor2[i].num].mes;
            while(!verificarData(vetor3,*contador3,vetor2[i].num))
            {
                cout << endl << "Data inexistente. " << endl;
                cout << endl << "Tente novamente." << endl;
                cout << "Informe o dia da viagem do deslocamento final: ";
                cin >> vetor3[(*contador3)].desloc[vetor2[i].num].dia;
                cout << "Informe o mes da viagem do deslocamento final: ";
                cin >> vetor3[(*contador3)].desloc[vetor2[i].num].mes;
            }
            vetor3[(*contador3)].desloc[vetor2[i].num].iddestino = idaux;
             
            cout << "Informe a quantidade de clientes ja confirmados para essa viagem: ";
            cin >> vetor3[(*contador3)].quantc;  
            
            for(int j=0; j < vetor3[(*contador3)].quantc;  j++)
            {
                cout << "Informe o id do cliente : ";
                cin >> id;
                
                for(int k=0; k < contador; k++)
                {
                    if(id == vetor[k].id)
                    {
                        if(!verificarDisp(vetor3,*contador3,id))
                        {
                            cout << endl << "Cliente indisponivel." << endl;
                            return;
                        }
                        flag = 1;
                        vetor3[(*contador3)].idcliente[j] = id;
                        break;
                    }
                }
                if(flag == 0)
                {
                    cout << endl << "Cliente inexistente. " << endl;
                    return ;
                }    
            }
            
            cout << endl << "Viagem inserida." << endl;
            (*contador3)++;
            return; //Assim que encontrar o destino valido faz as operacoes relevantes e sai da funcao!
        }
    }
    
    cout << endl << "Destino inexistente " << endl;
}

bool verificarData(viagem vetor3[], int contador3, int pos)
{
    if(vetor3[contador3].desloc[pos].dia <= 0 || vetor3[contador3].desloc[pos].dia >30)
    {
        cout << "Dia inexistente. Favor fornecer um numero entre o intervalo 1 a 30: " <<endl;
        return false;
    }
    if(vetor3[contador3].desloc[pos].mes <= 0 || vetor3[contador3].desloc[pos].mes >12)
    {
        cout << "Mes inexistente. Favor fornecer um numero entre o intervalo 1 a 12: " <<endl;
        return false;
    }
    
    if(pos > 0)
    {
        if(vetor3[contador3].desloc[pos].mes > vetor3[contador3].desloc[pos-1].mes)
        {
            return true;
        }
        else
        {
            if(vetor3[contador3].desloc[pos].mes < vetor3[contador3].desloc[pos-1].mes)
            {
                return false;
            }
            else
            {
                if(vetor3[contador3].desloc[pos].dia > vetor3[contador3].desloc[pos-1].dia)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }  
    }
    else
    {
        return true;
    }
}

bool verificarDisp(viagem vetor3[], int contador3 , long int id)
{
    int quantd = vetor3[contador3].quantd;
    for(int i=0; i < contador3; i++)
    {
        for(int j=0; j < vetor3[i].quantc; j++)
        {
            if(id == vetor3[i].idcliente[j])
            {
                for(int k=0; k < vetor3[i].quantd && k < vetor3[contador3].quantd; k++)
                {
                    if(vetor3[contador3].desloc[0].mes == vetor3[i].desloc[k].mes)
                    {
                        if(vetor3[contador3].desloc[0].dia == vetor3[i].desloc[k].dia)
                        {
                            return false;
                        }
                    }
                    if(vetor3[contador3].desloc[quantd-1].mes == vetor3[i].desloc[k].mes)
                    {
                        if(vetor3[contador3].desloc[quantd-1].dia == vetor3[i].desloc[k].dia)
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void remocaov(long int id, viagem vetor3[], int* contador3)
{
    for(int i = 0; i < (*contador3); i++) // excluindo uma viagem e redimencionando 
	{
		if(id == vetor3[i].id)
		{
			for(int j = i; j < (*contador3); j++)
			{
				vetor3[j] = vetor3[j + 1];
			}
			cout << endl << "Viagem excluida." << endl;
			(*contador3)--;
            return; // depois de excluido nao precisa verificar o restante do vetor
		}
	}
	cout << endl << "Viagem inexistente." << endl;
}

void alteracaov(long int id, cliente vetor[], destino vetor2[], viagem vetor3[], int contador, int contador2, int contador3)
{
    long int idaux;
    int flag = 0,flag2 = 0;
    for(int i = 0; i < contador3; i++) 
	{
		if(id == vetor3[i].id) // verificando se o id fornecido é igual a algum id ja existente no vetor(lista de viagens)
		{
            cout << "Informe o id do destino final da viagem que deseja alterar: ";
            cin >> id;
            idaux = id;
            
            for(int j=0; j < contador2; j++)
            {
                if(id == vetor2[j].id)
                {
                    flag2 = 1;
                    vetor3[i].custot += vetor2[j].custo;
                    vetor3[i].custot += 5;
                    
                    vetor3[i].quantd = vetor2[j].num + 1;
                    
                    for(int k=0; k < vetor2[j].num; k++)
                    {
                        cout << "Informe o dia da viagem do deslocamento " << k+1 << " : ";
                        cin >> vetor3[i].desloc[k].dia;
                        cout << "Informe o mes da viagem do deslocamento " << k+1 << " : ";
                        cin >> vetor3[i].desloc[k].mes;
                        while(verificarData(vetor3,contador3,k))
                        {
                            cout << endl << "Data inexistente. " << endl;
                            cout << endl << "Tente novamente." << endl;
                            cout << "Informe o dia da viagem: ";
                            cin >> vetor3[i].desloc[k].dia;
                            cout << "Informe o mes da viagem: ";
                            cin >> vetor3[i].desloc[k].mes;
                        }
                        
                        cout << "Informe o id do destino do deslocamento " << k+1 << " : ";
                        cin >> id;
                        
                        for(int l=0; l < contador2; l++)
                        {
                            if(id == vetor2[l].id)
                            {
                                flag = 1;
                                vetor3[i].custot += vetor2[k].custo;
                                vetor3[i].custot += 5;
                                vetor3[i].desloc[k].iddestino = id;
                            }
                        }
                        if(flag ==0)
                        {
                            cout << "Percurso invalido." << endl;
                            return;
                        }
                        flag = 0;
                    }
                    cout << "Informe o dia da viagem do deslocamento final: ";
                    cin >> vetor3[i].desloc[vetor2[i].num].dia;
                    cout << "Informe o mes da viagem do deslocamento final: ";
                    cin >> vetor3[i].desloc[vetor2[i].num].mes;
                    while(!verificarData(vetor3,contador3,vetor2[i].num))
                    {
                        cout << endl << "Data inexistente. " << endl;
                        cout << endl << "Tente novamente." << endl;
                        cout << "Informe o dia da viagem do deslocamento final: ";
                        cin >> vetor3[i].desloc[vetor2[i].num].dia;
                        cout << "Informe o mes da viagem do deslocamento final: ";
                        cin >> vetor3[i].desloc[vetor2[i].num].mes;
                    }
                    vetor3[i].desloc[vetor2[i].num].iddestino = idaux;
                    
                    cout << "Informe a quantidade de clientes ja confirmados para essa viagem: ";
                    cin >> vetor3[i].quantc;
                   
                    for(int l=0; l < vetor3[i].quantc;  l++)
                    {
                        cout << "Informe o id do cliente : ";
                        cin >> id;
                        
                        for(int k=0; k < contador; k++)
                        {
                            if(id == vetor[k].id)
                            {
                                if(!verificarDisp(vetor3,contador3,id))
                                {
                                    cout << endl << "Cliente indisponivel." << endl;
                                    return;
                                }
                                flag = 1;
                                vetor3[i].idcliente[l] = id;
                                break;
                            }
                        }
                        if(flag == 0)
                        {
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
                cout << endl << "Destino inexistente." << endl;
                return;
            }
        }
    }
	cout << endl << "Viagem inexistente " << endl;    
}

void consultav(long int id, viagem vetor3[], int contador3)
{
    for(int i = 0; i < contador3; i++) 
	{
		if(id == vetor3[i].id) // verificando se o id fornecido é igual a algum id ja existente no vetor(lista de destinos)
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
            
            return; // depois de encontrado nao precisa verificar o restante do vetor
		}
	}
	cout << endl << "Viagem inexistente " << endl;  
}

void inscricaov(inscricao insc, viagem vetor3[], int contador3, cliente vetor[], int contador)
{
    int flag=0;
    for(int i=0; i < contador3; i++)
    {
        if(insc.id == vetor3[i].id)
        {
            cout << "Informe o id do cliente que deseja inscrever na viagem:  ";
            cin >> insc.idc;
            
            for(int j=0; j < contador; j++)
            {
                if(insc.idc == vetor[j].id)
                {
                    flag = 1;
                    break;
                }
            }
            if(flag == 0)
            {
                cout << endl << "Cliente inexistente." <<endl;
                return;
            }
            
            for(int j=0; j < vetor3[i].quantc; j++)
            {
                if(insc.idc == vetor3[i].idcliente[j])
                {
                    cout << endl << "Cliente ja inscrito." << endl;
                    return;
                }
            }
            
            vetor3[i].idcliente[vetor3[i].quantc] = insc.idc;
            vetor3[i].quantc += 1;
            
            cout << endl << "Cliente inscrito." << endl;
            return;
        }
    }
    cout << endl << "Viagem inexistente." << endl;
}

void desistenciav(inscricao insc, viagem vetor3[], int contador3, cliente vetor[], int contador)
{
    int flag=0;
    for(int i=0; i < contador3; i++)
    {
        if(insc.id == vetor3[i].id)
        {
            cout << "Informe o id do cliente que deseja remover da viagem:  ";
            cin >> insc.idc;
            
            for(int j=0; j < contador; j++)
            {
                if(insc.idc == vetor[j].id)
                {
                    flag = 1;
                    break;
                }
            }
            if(flag == 0)
            {
                cout << endl << "Cliente inexistente." <<endl;
                return;
            }
            
            for(int j=0; j < vetor3[i].quantc; j++)
            {
                if(insc.idc == vetor3[i].idcliente[j])
                {
                    for(int k=j; k < vetor3[i].quantc; k++)
                    {
                        vetor3[i].idcliente[k] = vetor3[i].idcliente[k+1];
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

void listagemv(viagem vetor3[], int contador3, int dia_inicial, int dia_final, int mes_inicial, int mes_final)
{
	int flag = 0;
    
    
    for(int i = 0; i < contador3; i++)
	{
        flag = 0;
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
            cout << "Dados da viagem " << i+ 1 << endl;
            
            cout << "Sequencia de deslocamentos: " << endl << endl;
            for(int j = 0; j < vetor3[i].quantd; j++)
            {
                cout << "Deslocamento " << j+1 << " :\nDia : " << vetor3[i].desloc[j].dia << " Mes: " << vetor3[i].desloc[j].mes << " ID Destino: " << vetor3[i].desloc[j].iddestino << endl;
            }
            
            cout << "Sequencia de clientes: " << endl << endl;
            for(int j = 0; j < vetor3[i].quantc; j++)
            {
                cout << "Id do cliente " << j+1 << " :" << vetor3[i].idcliente[j] << endl ;
            }
            cout << "Custo total da viagem: R$" << vetor3[i].custot << endl;	
        }
    }
    if(flag == 0)
    {
        cout << endl << "Nenhuma viagem cadastrada." << endl;
    }    
}

void relatoriov(viagem vetor3[], int contador3)
{
    double soma=0, menor, maior, medio, nummedio;
    int numtotal=0, flag = 0;
    
    menor = vetor3[0].custot;
    maior = vetor3[0].custot;
    for(int i=0; i < contador3; i++)
    {
        flag = 1;
        numtotal += vetor3[i].quantc;
        soma += vetor3[i].custot;
        
        if(menor > vetor3[i].custot)
        {
            menor = vetor3[i].custot;
        }
        if(maior < vetor3[i].custot)
        {
            maior = vetor3[i].custot;
        }
    }
    if(flag == 0)
    {
        cout << endl << "Nenhuma viagem cadastrada." << endl;
        return;
    }
    medio = soma/contador3;
    nummedio = (numtotal * 1.0)/contador3;
    
    cout << endl << "Numero total de viagens: "<< contador3 << endl;
    cout << "Menor valor de viagem: " << menor << endl;
    cout << "Maior valor de viagem: " << maior << endl;
    cout << "Valor medio das viagens: " << medio << endl;
    cout << "Numero total de clientes: " << numtotal << endl;
    cout << "Numero medio de clientes: " << nummedio << endl;
    cout << endl;
}