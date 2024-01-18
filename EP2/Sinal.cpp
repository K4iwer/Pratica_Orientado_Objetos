#include "Sinal.h"
#include "Grafico.h"
#include <iostream>
// precisa colocar stdexcept??

using namespace std;


Sinal :: Sinal (double* sequencia, int comprimento) {
    this -> comprimento = comprimento;    
    this -> sequencia = new double[comprimento];
    for(int i = 0; i < comprimento; i++) (this->sequencia[i]) = (sequencia[i]); 

    if (comprimento <= 0) {
        throw new invalid_argument("O comprimento precisa ser maior que zero!");
    }
}

Sinal :: Sinal(double constante, int comprimento) {
    //const double* sequencia[comprimento] = constante;
    this -> comprimento = comprimento;    
    this -> sequencia = new double[comprimento];  
    for(int i = 0; i < comprimento; i++) {
        (this->sequencia[i]) = constante;              // n entendi o enunciado lol 
    }

    if (comprimento <= 0) {
        throw new invalid_argument("O comprimento precisa ser maior que zero!");
    }
}

Sinal :: ~Sinal() {
    delete[] (this -> sequencia);
}


double* Sinal :: getSequencia() {
    return &(this -> sequencia)[0];
}


int Sinal :: getComprimento() {
    return (this -> comprimento);
}

void Sinal :: imprimir(string nomeDoSinal)
{
    Grafico* grafico1 = new Grafico(nomeDoSinal, (this -> sequencia), (this -> comprimento));
    grafico1->plot();
    grafico1->~Grafico();
    cout << endl;
}

void Sinal :: imprimir() {                                           // n ta imprimindo .0, mas se for .(algum_valor) ele vai   
    for (int i = 0; i < comprimento; i++) {
        cout << i << "- " << this-> sequencia[i] << endl;
    }    
    cout << "--" << endl;
}

void Sinal :: imprimir(int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        cout << i << "- " << this-> sequencia[i] << endl;
    }    
    cout << "--" << endl;    
}