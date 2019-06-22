#include <iostream>
//#include <stdlib.h>
#include <time.h>
using namespace std;

//use this first function to seed the random number generator,
//call this before any of the other functions
void initrand()
{
    srand((unsigned)(time(0)));
}

// Programa Principal
int main() {
    initrand();
    for (int i = 0; i < 100; i++) {
        cout << rand() % 200 - 100 << endl;
    }
    return 0;
}
