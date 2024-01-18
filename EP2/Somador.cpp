#include "Somador.h"

Somador :: Somador() : CircuitoMISO() {}

Somador :: ~Somador() {}

Sinal* Somador :: processar(Sinal* sinalIN1, Sinal* sinalIN2) {
    double* sequencia1 = sinalIN1 -> getSequencia();  
    double* sequencia2 = sinalIN2 -> getSequencia(); 
    int comprimentoFinal = sinalIN1 -> getComprimento();

    if (comprimentoFinal > sinalIN2 -> getComprimento()) {
        comprimentoFinal = sinalIN2 -> getComprimento();
    }

    double soma[comprimentoFinal];

    for (int i = 0; i < comprimentoFinal; i++) {
        soma[i] = sequencia1[i] + sequencia2[i];
    }

    Sinal* novoSinal = new Sinal(soma, comprimentoFinal);

    return novoSinal;
}
