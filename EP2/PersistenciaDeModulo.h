#ifndef PERSISTENCIADEMODULO_H
#define PERSISTENCIADEMODULO_H

#include "Modulo.h"
#include <string>            // na verdade n precisa, mas melhor deixar ai por precaucao

class PersistenciaDeModulo : public Modulo {
protected:
    string nomeArquivo;
    Sinal* processar(Sinal* sinalIN);
public:
    PersistenciaDeModulo(string nomeDoArquivo);
    virtual ~PersistenciaDeModulo();
    void salvarEmArquivo(Modulo* mod);
    Modulo* lerDeArquivo();
};

#endif