#include "Modulo.h"
#include <iostream>

using namespace std;

Modulo :: Modulo() : CircuitoSISO() {
    listaCircuitos = new list<CircuitoSISO*>();
}

Modulo :: ~Modulo() {
    delete listaCircuitos;
}

void Modulo :: adicionar(CircuitoSISO* circ) {
    listaCircuitos->push_back(circ);
}

list<CircuitoSISO*>* Modulo :: getCircuito() {
    return listaCircuitos;
}

void Modulo :: imprimir() {                                          //vc deveria ser abstrato em circuito siso??
    list<CircuitoSISO*>::iterator i = listaCircuitos->begin();

    cout << "Modulo com ID " << ID << " e:" << endl;

    while (i != listaCircuitos->end()) {
        (*i)->imprimir();
        i++;
    }

    cout << "--" << endl;
}