#include "Sinal.h"

#ifndef DERIVADOR_H
#define DERIVADOR_H

class Derivador
{
    private:

    public:
        Derivador();
        virtual ~Derivador();
        Sinal* processar(Sinal* sinalIN);
};

#endif