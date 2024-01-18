#ifndef SOMADOR_H
#define SOMADOR_H

#include "Sinal.h"

class Somador {
    private:

    public:
    Somador();
    virtual ~Somador();
    Sinal* processar(Sinal* sinalIN1, Sinal* sinalIN2);
};

#endif