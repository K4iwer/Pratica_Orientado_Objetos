#include "Sinal.h"
#include "CircuitoSISO.h"

#ifndef AMPLIFICADOR_H
#define AMPLIFICADOR_H

class Amplificador : public CircuitoSISO
{
private:
    double ganho;
public:
    Amplificador(double ganho);
    virtual ~Amplificador();
    Sinal* processar(Sinal* sinalIN);
    
    void setGanho(double ganho);
    double getGanho();
};

#endif