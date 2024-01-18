#ifndef MODULO_H
#define MODULO_H

#include "CircuitoSISO.h"
#include <list>

class Modulo : public CircuitoSISO {
protected:
    list<CircuitoSISO*>* listaCircuitos;    
public:
    Modulo();
    virtual ~Modulo();
    virtual void adicionar(CircuitoSISO* circ);
    virtual list<CircuitoSISO*>* getCircuito();
    void imprimir();
};

#endif