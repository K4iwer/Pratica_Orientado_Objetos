#ifndef INTEGRADOR_H
#define INTEGRADOR_H

#include "Sinal.h"
#include "CircuitoSISO.h"

class Integrador : public CircuitoSISO{
protected:

public:
    Integrador();
    virtual ~Integrador();
    Sinal* processar(Sinal* sinalIN);
};


#endif