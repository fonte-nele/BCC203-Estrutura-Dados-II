//  questao-01.cpp
//  Created by Reinaldo Silva Fortes on 02/07/16.

#include <iostream>
using namespace std;

#define TAM_VETOR 100
#define TAM_VETOR_PI 5
typedef int tipoDado;
typedef tipoDado tipoVetor[TAM_VETOR];
typedef tipoDado tipoVetorPI[TAM_VETOR_PI];

// Prototipo das Funcoes
void ler(tipoVetor E);
void processar(tipoVetor E);
void imprimir(tipoVetorPI PI, int tamanho);


// Programa Principal
int main() {
    tipoVetor E;
    ler(E);
    processar(E);
    return 0;
}

void ler(tipoVetor E) {
    for (int i = 0; i < TAM_VETOR; i++) {
        cin >> E[i];
    }
}

void processar(tipoVetor E) {
    tipoVetorPI P, I;
    int tamanhoP = 0, tamanhoI = 0;
    for (int i = 0; i < TAM_VETOR; i++) {
        if (E[i]%2 == 0) {
            P[tamanhoP++] = E[i];
            if (tamanhoP == TAM_VETOR_PI) {
                imprimir(P, tamanhoP);
                tamanhoP = 0;
            }
        } else {
            I[tamanhoI++] = E[i];
            if (tamanhoI == TAM_VETOR_PI) {
                imprimir(I, tamanhoI);
                tamanhoI = 0;
            }
        }
    }
    imprimir(I, tamanhoI);
    imprimir(P, tamanhoP);
}

void imprimir(tipoVetorPI PI, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        cout << (PI[i]%2==0 ? "par[" : "impar[") << i << "] = " << PI[i] << endl;
    }
}