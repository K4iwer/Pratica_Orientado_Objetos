#ifndef CIRCUITO_H
#define CIRCUITO_H

class Circuito {
protected:
    int ID;
    static int ultimoID; 
public:
    Circuito();
    virtual ~Circuito() = 0;
    int getID();
    void imprimir();
    static int getUltimoID();
    
};

#endif