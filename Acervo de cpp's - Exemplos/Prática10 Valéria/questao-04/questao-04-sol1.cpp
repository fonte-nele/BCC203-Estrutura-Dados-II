//  questao-04-sol1.cpp
//  Created by Reinaldo Silva Fortes on 02/07/16.
//
//  Solucao para questao-04 utilizando variaveis para gerenciar o tamanho dos vetores.

#include <iostream>
using namespace std;

typedef unsigned long tipoDado;
typedef tipoDado tipoVetor[200];

// Prototipo das Funcoes
int gerar(tipoVetor vetorEntrada, int tamanhoEntrada, tipoVetor vetorSaida);
void imprimir(tipoVetor vetorEntrada, int tamanhoEntrada);


// Programa Principal
int main() {
    int linha;
    cin >> linha;
    while (linha >= 0 && linha <= 200) {
        tipoVetor vetorLinha;
        vetorLinha[0] = 1;
        int tamVetorLinha = 1;
        for (int l = 0; l < linha; l++) {
            tamVetorLinha = gerar(vetorLinha, tamVetorLinha, vetorLinha);
        }
        imprimir(vetorLinha, tamVetorLinha);
        cin >> linha;
    }
    return 0;
}

int gerar(tipoVetor vetorEntrada, int tamanhoEntrada, tipoVetor vetorSaida) {
    tipoVetor novoVetor;
    novoVetor[0] = 1;
    for (int i = 1; i < tamanhoEntrada; i++) {
        novoVetor[i] = vetorEntrada[i-1] + vetorEntrada[i];
    }
    novoVetor[tamanhoEntrada] = 1;
    // Copiando os dados do novoVetor para o vetorSaida (nao basta fazer atribuicao)
    for (int i = 0; i <= tamanhoEntrada; i++) {
        vetorSaida[i] = novoVetor[i];
    }
    return tamanhoEntrada + 1;
}


void imprimir(tipoVetor vetorEntrada, int tamanhoEntrada) {
    cout << "linha " << (tamanhoEntrada-1) << ": ";
    for (int i = 0; i < tamanhoEntrada; i++) {
        cout << vetorEntrada[i] << " ";
    }
    cout << endl;
}