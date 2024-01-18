#ifndef MODULOREALIMENTADO_H
#define MODULOREALIMENTADO_H

#include "Sinal.h"
#include "Modulo.h"
#include "ModuloEmSerie.h"
class ModuloRealimentado : public Modulo
{
    protected:
        ModuloEmSerie* modSer;
        void adicionar(CircuitoSISO* circ);
        list<CircuitoSISO*>* getCircuito();
        //double ganho;
        //Sinal* concatenar(Sinal* sinalIn, double valor);

    public:
        ModuloRealimentado();
        virtual ~ModuloRealimentado();
        Sinal* processar(Sinal* sinalIN);
};

#endif