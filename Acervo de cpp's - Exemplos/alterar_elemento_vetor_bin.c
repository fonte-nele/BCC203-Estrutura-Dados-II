#include<stdio.h>
#include<stdlib.h>

int main()
{
	//Alterar o terceiro elemento de um vetor escrito em arquivo binario!!!
	float x [4] = { 5.6 , 6 , 9.8 , 4.2 };
	float nx [4] , tmp = 7.2;
	FILE *pfile ;
	pfile = fopen("num.bin" , "wb");
	fwrite(&x , sizeof (x),4,pfile);
	fclose(pfile);
	FILE *pfile2;
	pfile2 = fopen("num.bin" , "r+b");
	fseek(pfile2,sizeof(float)*2 , 0);
	fwrite(&tmp , sizeof (tmp),1,pfile2);
	rewind(pfile2);
	fread(&nx , sizeof(float),4,pfile2);
	for ( int i = 0; i < 4; i++)
	{
		printf("%.1f\n",nx[i]);
	}
	fclose(pfile2);
	return 0;
}