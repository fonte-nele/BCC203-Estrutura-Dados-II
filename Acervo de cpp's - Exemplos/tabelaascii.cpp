/*#include <iostream>

using namespace std;

int main(void)
{
    for (char i = 32; i <= 126; i++)
    {
        cout << i << "[" << (int) i << "]" << endl;
    }

    return 0;
}*/

#include <stdio.h>

int main(void)
{
    int i;

    for (i = 32; i <= 126; i++)
    {
        printf("%c [%d]\n", i, i);
    }
	

    return 0;
}