#include "ModuloRealimentado.h"


ModuloRealimentado :: ModuloRealimentado(double ganho)
{
    this -> ganho = ganho;
}

Sinal* ModuloRealimentado :: processar(Sinal* sinalIN)
{
    double* sequenciaIN = sinalIN -> getSequencia();

    double* sequenciaVelocidade = new double[(sinalIN -> getComprimento())];
    Sinal* velocidade = new Sinal(sequenciaVelocidade, sinalIN -> getComprimento());
    sequenciaVelocidade = velocidade->getSequencia();

    sequenciaVelocidade[0] = sequenciaIN[0] * (this -> ganho);
    for(int i = 1; i < sinalIN->getComprimento(); i++)
    {
        sequenciaVelocidade[i] = sequenciaVelocidade[i - 1] +  (this -> ganho) * (sequenciaIN[i] - sequenciaVelocidade[i - 1]);
    }

    return velocidade;
}

/*Sinal* ModuloRealimentado :: concatenar(Sinal* sinalIN, double valor) //Não utilizada, pega um sinal qualquer e adiciona um elemento a mais
{                                                                       //na sequencia do sinal
    double* novaSequencia = new double[(sinalIN -> getComprimento()) + 1];
    double* auxSequencia = sinalIN -> getSequencia();

    for(int i = 0; i < (sinalIN -> getComprimento()); i++) novaSequencia[i] = auxSequencia[i];

    novaSequencia[sinalIN -> getComprimento()] = valor;

    return new Sinal(novaSequencia, (sinalIN -> getComprimento() + 1));
}*/

ModuloRealimentado :: ~ModuloRealimentado(){}
