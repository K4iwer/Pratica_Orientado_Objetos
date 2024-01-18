#include "Modulo.h"
#include <iostream>

using namespace std;

Modulo :: Modulo() : CircuitoSISO() {
    listaCircuitos = new list<CircuitoSISO*>();
}

Modulo :: ~Modulo() {
    delete listaCircuitos;             // tem q deletar o conteudo tbm ou so a lista????
}

void Modulo :: adicionar(CircuitoSISO* circ) {
    listaCircuitos->push_back(circ);
}

list<CircuitoSISO*>* Modulo :: getCircuito() {
    return listaCircuitos;
}

void Modulo :: imprimir() {                               //deveria ser abstrato na classe circuito?? (no ep fala pra redefinir)
    list<CircuitoSISO*>::iterator i = listaCircuitos->begin();            // precisa fazer outro sistema de ID?

    cout << "Modulo com ID " << ID << " e:" << endl;

    while (i != listaCircuitos->end()) {
        (*i)->imprimir();
        i++;
    }

    cout << "--" << endl;
}