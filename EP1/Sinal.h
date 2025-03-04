#ifndef SINAL_H
#define SINAL_H

#include <string>

using namespace std;

class Sinal {
private:
    int comprimento;
    double* sequencia;
public:
    Sinal(double* sequencia, int comprimento);
    virtual ~Sinal();
    double* getSequencia();
    int getComprimento();
    void imprimir(string nomeDoSinal);
};
#endif