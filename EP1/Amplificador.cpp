#include "Amplificador.h"


Amplificador :: Amplificador(double ganho)
{
    this -> ganho = ganho;
}

Amplificador :: ~Amplificador() {}

void Amplificador :: setGanho(double ganho)
{
    this -> ganho = ganho;
}

double Amplificador :: getGanho()
{
    return (this -> ganho);
}

Sinal* Amplificador :: processar(Sinal* sinalIN)
{
    double* sequenciaOut = new double[sinalIN -> getComprimento()];
    
    double* aux = sinalIN -> getSequencia();

    for(int i = 0; i < sinalIN -> getComprimento(); i++) sequenciaOut[i] = (this -> ganho) * aux[i];

    return (new Sinal(&sequenciaOut[0], (sinalIN -> getComprimento()))); // cria e retorna um novo sinal modificado
}
