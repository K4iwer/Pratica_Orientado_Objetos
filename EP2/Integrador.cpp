#include "Integrador.h"

#include <iostream>
Integrador :: Integrador() : CircuitoSISO() {}

Integrador :: ~Integrador() {}

Sinal* Integrador :: processar(Sinal* sinalIN) {
    double valor = 0;
    double* copiaVetor = sinalIN-> getSequencia();

    for (int i = 0; i < sinalIN -> getComprimento(); i++) {
        copiaVetor[i] = copiaVetor[i] + valor;
        valor = copiaVetor[i];
    }

    return (new Sinal(copiaVetor, sinalIN -> getComprimento()));
}