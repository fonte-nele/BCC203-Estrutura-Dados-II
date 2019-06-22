#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
    
    if(argc!= 2)
    {
        printf("\nFORMATO INVALIDO!!!\n");
        return 0;
    }
    int temp;
    temp = atoi(argv[1]);
    printf("%i\n",2*temp);
    
    return 0;
}