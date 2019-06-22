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

//generates a psuedo-random float between 0.0 and 0.999...
float randfloat()
{
    return rand()/(float(RAND_MAX)+1);
}

//generates a psuedo-random float between min and max
float randfloat(float min, float max)
{
    if (min>max)
    {
        return randfloat()*(min-max)+max;    
    }
    else
    {
        return randfloat()*(max-min)+min;
    }    
}


// Programa Principal
int main() {
    initrand();
    for (int i = 0; i < 100; i++) {
        cout << randfloat(-100, 100) << endl;
    }
    return 0;
}
