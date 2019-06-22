#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	//Alterar o terceiro elemento de um vetor escrito em arquivo binario!!!
	float x [4] = { 5.6 , 6 , 9.8 , 4.2 };
	float nx [4] , tmp = 7.2;
	ofstream pfile ;
	pfile.open("num.bin" , ios :: binary);
	pfile.write((char*)x , sizeof ( float )* 4);
	pfile.close();
	fstream pfile2;
	pfile2.open("num.bin" , ios :: binary|ios::in|ios::out);
	pfile2.seekg(sizeof(float)*2 , ios::beg);
	pfile2.write((char*) &tmp , sizeof ( float ));
	pfile2.seekg(0 , ios :: beg );
	pfile2.read(( char*)nx , sizeof ( float )* 4);
	for ( int i = 0; i < 4; i++)
	{
		cout<<nx[i]<<" ";
	}
	pfile2.close();
	return 0;
}