//  questao-02.cpp
//  Created by Reinaldo Silva Fortes on 02/07/16.

#include <iostream>
#include <iomanip>
using namespace std;

#define TAM_VETOR 100
typedef double tipoDado;
typedef tipoDado tipoVetor[TAM_VETOR];

// Prototipo das Funcoes
void ler(tipoVetor E);
int processar(tipoVetor E, tipoVetor P, tipoVetor V);
void imprimir(tipoVetor P, tipoVetor V, int tamanho);


// Programa Principal
int main() {
    tipoVetor E, P, V;
    ler(E);
    int tamanho = processar(E, P, V);
    imprimir(P, V, tamanho);
    return 0;
}

void ler(tipoVetor E) {
    for (int i = 0; i < TAM_VETOR; i++) {
        cin >> E[i];
    }
}

int processar(tipoVetor E, tipoVetor P, tipoVetor V) {
    int tamanho = 0;
    for (int i = TAM_VETOR - 2; i >= 0; i--) {
        if (E[i] > E[i+1]) {
            P[tamanho] = i;
            V[tamanho] = E[i];
            tamanho++;
        }
    }
    return tamanho;
}

void imprimir(tipoVetor P, tipoVetor V, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        cout << "[" << P[i] << "] " << fixed << setprecision(1) << V[i] << endl;
    }
}