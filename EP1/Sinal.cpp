#include "Sinal.h"
#include "Grafico.h"
#include <iostream>

using namespace std;


Sinal :: Sinal (double* sequencia, int comprimento) {
    this -> comprimento = comprimento;    
    this -> sequencia = new double[comprimento];
    for(int i = 0; i < comprimento; i++) (this->sequencia[i]) = (sequencia[i]); 
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
    cout << endl;
    Grafico* grafico1 = new Grafico(nomeDoSinal, (this -> sequencia), (this -> comprimento));
    grafico1->plot();
    grafico1->~Grafico();
    cout << endl;
}
