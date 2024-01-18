#ifndef SOMADOR_H
#define SOMADOR_H

#include "Sinal.h"
#include "CircuitoMISO.h"

class Somador: public CircuitoMISO {
    private:

    public:
    Somador();
    virtual ~Somador();
    Sinal* processar(Sinal* sinalIN1, Sinal* sinalIN2);
};

#endif