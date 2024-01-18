#include "Piloto.h"
#include "Amplificador.h"
#include "Integrador.h"

Piloto :: Piloto(double ganho) :
ganho (ganho) {
    this-> ganho = ganho;
}

Piloto :: ~Piloto() {

}

Sinal* Piloto :: processar(Sinal* sinalIN) {
    Sinal* novoSinal = new Sinal(sinalIN -> getSequencia(), sinalIN -> getComprimento());
    Amplificador* amp = new Amplificador(ganho);
    Integrador* integ = new Integrador();

    novoSinal = amp -> processar(novoSinal);
    novoSinal = integ -> processar(novoSinal);

    delete amp;
    delete integ;

    return novoSinal;
}


