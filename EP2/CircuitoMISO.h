#ifndef CIRCUITOMISO_H
#define CIRCUITOMISO_H

#include "Circuito.h"
#include "Sinal.h"

class CircuitoMISO : public Circuito {
public:
    CircuitoMISO();
    virtual ~CircuitoMISO();
    virtual Sinal* processar(Sinal* sinalIN1, Sinal* sinalIN2) = 0;
};

#endif