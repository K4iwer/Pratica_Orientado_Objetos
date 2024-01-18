#include "ModuloEmParalelo.h"
#include "Somador.h"
#include <stdexcept>
#include <iostream>

ModuloEmParalelo :: ModuloEmParalelo() : Modulo() {} 
                                                            
ModuloEmParalelo :: ~ModuloEmParalelo() {}

Sinal* ModuloEmParalelo :: processar(Sinal* sinalIN) {
    if (listaCircuitos->empty()) {
        throw new logic_error("A Lista esta vazia");
    }

    list<CircuitoSISO*>::iterator i = listaCircuitos->begin();
    Somador* sum = new Somador();
    
    double* sequentiaInitializer = new double[sinalIN->getComprimento()];
    for(int i = 0 ; i < (sinalIN->getComprimento()); i++) sequentiaInitializer[i] = 0;
    
    Sinal* soma = new Sinal(sequentiaInitializer, sinalIN->getComprimento());
    
    delete sequentiaInitializer;

    Sinal** sinais = new Sinal*[(this->listaCircuitos->size())];

    for(int j = 0; (i != this->listaCircuitos->end()); j++)
    {
        sinais[j] = (*i)->processar(sinalIN);
        soma = sum->processar(soma, sinais[j]);
        i++;
    }

    delete[] sinais;
    delete sum;

    return soma;
} 
