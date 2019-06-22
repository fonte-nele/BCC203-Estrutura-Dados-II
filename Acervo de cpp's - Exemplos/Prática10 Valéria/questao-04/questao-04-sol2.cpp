//  questao-04-sol1.cpp
//  Created by Reinaldo Silva Fortes on 02/07/16.
//
//  Solucao para questao-04 utilizando a posicao 0 para gerenciar o tamanho dos vetores.

#include <iostream>
using namespace std;

typedef unsigned long tipoDado;
typedef tipoDado tipoVetor[201];// podem ser armazenados 200 valores, na posicao 0 armazena-se o tamanho "real" do vetor (quantidade de valores armazenados)

// Prototipo das Funcoes
void gerar(tipoVetor vetorEntrada, tipoVetor vetorSaida);
void imprimir(tipoVetor vetorEntrada);


// Programa Principal
int main() {
    int linha;
    cin >> linha;
    while (linha >= 0 && linha <= 200) {
        tipoVetor vetorLinha;
        vetorLinha[0] = 1; // tamanho
        vetorLinha[1] = 1; // primeiro valor
        for (int l = 0; l < linha; l++) {
            gerar(vetorLinha, vetorLinha);
        }
        imprimir(vetorLinha);
        cin >> linha;
    }
    return 0;
}

void gerar(tipoVetor vetorEntrada, tipoVetor vetorSaida) {
    tipoVetor novoVetor;
    novoVetor[0] = vetorEntrada[0] + 1;
    novoVetor[1] = 1;
    for (int i = 2; i <= vetorEntrada[0]; i++) {
        novoVetor[i] = vetorEntrada[i-1] + vetorEntrada[i];
    }
    novoVetor[novoVetor[0]] = 1; // ultimo valor
    // Copiando os dados do novoVetor para o vetorSaida (nao basta fazer atribuicao
    for (int i = 0; i <= novoVetor[0]; i++) {
        vetorSaida[i] = novoVetor[i];
    }
}


void imprimir(tipoVetor vetorEntrada) {
    cout << "linha " << (vetorEntrada[0]-1) << ": ";
    for (int i = 1; i <= vetorEntrada[0]; i++) {
        cout << vetorEntrada[i] << " ";
    }
    cout << endl;
}