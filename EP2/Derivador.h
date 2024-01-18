#include "Sinal.h"
#include "CircuitoSISO.h"

#ifndef DERIVADOR_H
#define DERIVADOR_H

class Derivador : public CircuitoSISO
{
    private:

    public:
        Derivador();
        virtual ~Derivador();
        Sinal* processar(Sinal* sinalIN);
};

#endif