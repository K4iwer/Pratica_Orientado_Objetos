#ifndef MODULOEMPARALELO_H
#define MODULOEMPARALELO_H

#include "Modulo.h"
#include <list>

class ModuloEmParalelo : public Modulo {
protected:

public:
    ModuloEmParalelo();
    virtual ~ModuloEmParalelo();
    Sinal* processar(Sinal* sinalIN);
};

#endif