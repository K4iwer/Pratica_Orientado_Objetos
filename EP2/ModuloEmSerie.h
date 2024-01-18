#include "Modulo.h"

#ifndef MODULOEMSERIE_H
#define MODULOEMSERIE_H
class ModuloEmSerie : public Modulo
{
    private:

    public:
        ModuloEmSerie();
        virtual ~ModuloEmSerie();
        Sinal* processar(Sinal* sinalIN);

};
#endif