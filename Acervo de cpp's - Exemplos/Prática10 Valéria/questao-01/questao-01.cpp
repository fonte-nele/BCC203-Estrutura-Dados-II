//  questao-01.cpp
//  Created by Reinaldo Silva Fortes on 02/07/16.

#include <iostream>
#include <iomanip>
using namespace std;

#define TAM_VETOR 100
typedef double tipoDado;
typedef tipoDado tipoVetor[TAM_VETOR];

// Prototipo das Funcoes
void ler(tipoVetor vetor);
void imprimir(tipoVetor vetor);


// Programa Principal
int main() {
    tipoVetor vetor;
    ler(vetor);
    imprimir(vetor);
    return 0;
}

void ler(tipoVetor vetor) {
    for (int i = 0; i < TAM_VETOR; i++) {
        cin >> vetor[i];
    }
}


void imprimir(tipoVetor vetor) {
    for (int i = 1; i < TAM_VETOR; i++) {
        if (vetor[i] < vetor[i-1]) {
            cout << "[" << i << "] " << fixed << setprecision(1) <<vetor[i] << endl;
        }
    }
}