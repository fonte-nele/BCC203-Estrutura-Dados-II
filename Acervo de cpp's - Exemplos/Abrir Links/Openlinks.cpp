#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#define n 160
using namespace std;

int Menu()
{
	int op;
	cout<<"\nINSIRA A OPCAO DESEJADA.\n\n";
	cout<<"1-Abrir os links\n\n";
	cout<<"2-Adicionar mais links\n\n";
	cout<<"3-Sair\n\n";
	cin>>op;
	return op;
}


int main()
{
	int i, op; 
	fstream arqIn, arqOut;
	string links[n], url;
	arqIn.open("links.txt");
	arqOut.open("links2.txt");
	
	do{
		switch (op = Menu())
		{
			case 1:
                system("cls");
				for (i=0; i<n; i++)
				{
					getline (arqIn, links[i]);
				}
				for (i=0; i<1; i++)
				{
					ShellExecute(NULL, "open", links[i].c_str(), NULL, NULL, SW_MAXIMIZE);
					//Sleep(100);	
				}
				system("fechar2.bat");
				/*
				HWND H;
				H=FindWindow (NULL, links[0].c_str());
				PostMessage (H, WM_CLOSE, 0,0);
				DestroyWindow (H);
				
				Process p = Process.Start("Notepad.exe");
				p.CloseMainWindow();
				*/
				
				break;
			case 2:
				system("cls");
				for (i=0; i<n; i++)
				{
					getline (arqIn, links[i]);
				}
				cout<<"\nInsira os demais links a serem adicionados:\n\n";
				for (; i<n; i++)
				{
					getline (cin, links[i]);
				}
				for(i=0; i<n; i++)
				{
					
					arqOut<<links[i]<<endl;
				}
				break;
			case 3:
				system("cls");
				break;
			default:
				system("cls");
				cout<<"Opcao invalida. Tente novamente.";
		}
	}while (op != 3);
	
	arqIn.close();
	arqOut.close();
	return 0;
}