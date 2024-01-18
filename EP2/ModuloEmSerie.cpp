#include "ModuloEmSerie.h"
#include <stdexcept>
#include <iostream>

ModuloEmSerie :: ModuloEmSerie() : Modulo() {};
ModuloEmSerie :: ~ModuloEmSerie(){};

Sinal* ModuloEmSerie :: processar(Sinal* sinalIN)
{
    if(this->listaCircuitos->empty()) throw new logic_error("A Lista esta vazia");

    Sinal* sinalOUT = new Sinal(sinalIN->getSequencia(), sinalIN->getComprimento());

    list<CircuitoSISO*>::iterator i = this->listaCircuitos->begin();
    
    while(i != this->listaCircuitos->end())
    {
        sinalOUT = (*i)->processar(sinalOUT);
        i++;
    }

    return sinalOUT;
}
