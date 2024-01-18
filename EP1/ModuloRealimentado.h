#ifndef MODULOREALIMENTADO_H
#define MODULOREALIMENTADO_H

#include "Sinal.h"

class ModuloRealimentado
{
    private:
        double ganho;
        Sinal* concatenar(Sinal* sinalIn, double valor);

    public:
        ModuloRealimentado(double ganho);
        virtual ~ModuloRealimentado();
        Sinal* processar(Sinal* sinalIN);
};

#endif