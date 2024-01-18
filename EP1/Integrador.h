#ifndef INTEGRADOR_H
#define INTEGRADOR_H

#include "Sinal.h"

class Integrador {
private:


public:
    Integrador();
    virtual ~Integrador();
    Sinal* processar(Sinal* sinalIN);
};


#endif