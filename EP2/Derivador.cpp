#include "Derivador.h"
#include <iostream>

Derivador :: Derivador() : CircuitoSISO() {};

Derivador :: ~Derivador(){};

Sinal* Derivador :: processar(Sinal* sinalIN)
{
    double* sequenciaOUT = new double[(sinalIN -> getComprimento())]; // clona a sequencia de sinalIN

    double* aux = sinalIN->getSequencia();
    sequenciaOUT[0] = aux[0];
    for(int i = 1; i < (sinalIN -> getComprimento()); i++) sequenciaOUT[i] = aux[i] - aux[i - 1];

    return (new Sinal(sequenciaOUT, (sinalIN -> getComprimento()))); // retorna um novo sinal "derivado"
}
