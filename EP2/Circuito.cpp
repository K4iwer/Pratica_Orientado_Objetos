#include "Circuito.h"
#include <iostream>

using namespace std;

int Circuito :: ultimoID = 0;

Circuito :: Circuito() {
    ultimoID ++;
    ID = ultimoID;
}

Circuito :: ~Circuito() {}

int Circuito :: getID() {
    return ID;
}

void Circuito :: imprimir() {
    cout << "Circuito com ID " << ID << endl;
}

int Circuito :: getUltimoID() {
    return ultimoID;
}