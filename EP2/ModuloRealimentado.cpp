#include "ModuloRealimentado.h"
#include "Somador.h"
#include "ModuloEmSerie.h"
#include "Integrador.h"

ModuloRealimentado :: ModuloRealimentado() : Modulo()
{
  modSer = new ModuloEmSerie();
}

ModuloRealimentado :: ~ModuloRealimentado() {
  delete modSer;
}

Sinal* ModuloRealimentado :: processar(Sinal* sinalIN)
{
    Sinal* diferença = nullptr;
    Sinal* saida = nullptr;
    Sinal* saidaInvertida = nullptr;
    
    double* sequenciaSaidaInvertida = new double[sinalIN->getComprimento()]; 
    int vInicial = 0; 
                                                              
    sequenciaSaidaInvertida[0] = vInicial * (-1);
    diferença = new Sinal(sinalIN->getSequencia(), 1);

    saida = modSer->processar(diferença);

    delete diferença;
    
    for (int i = 1; i < sinalIN->getComprimento(); i++) {

        sequenciaSaidaInvertida[i] = saida->getSequencia()[i-1] * (-1);

        saidaInvertida = new Sinal(sequenciaSaidaInvertida , i+1);

        Somador* sum = new Somador();
        diferença = sum->processar(sinalIN, saidaInvertida);
        delete sum;
        delete saida;

        saida = modSer->processar(diferença);

        delete saidaInvertida;
        delete diferença;
    }

    delete sequenciaSaidaInvertida;    

    return saida;
}

void ModuloRealimentado :: adicionar(CircuitoSISO* circ) {
  modSer->adicionar(circ);
}

list<CircuitoSISO*>* ModuloRealimentado :: getCircuito() {
  return modSer->getCircuito();
}

/*Sinal* ModuloRealimentado :: processar(Sinal* sinalIN)
{
    double* sequenciaIN = sinalIN -> getSequencia();

    double* sequenciaVelocidade = new double[(sinalIN -> getComprimento())];
    Sinal* velocidade = new Sinal(sequenciaVelocidade, sinalIN -> getComprimento());
    sequenciaVelocidade = velocidade->getSequencia();

    sequenciaVelocidade[0] = sequenciaIN[0] * (this -> ganho);
    for(int i = 1; i < sinalIN->getComprimento(); i++)
    {
        sequenciaVelocidade[i] = sequenciaVelocidade[i - 1] +  (this -> ganho) * (sequenciaIN[i] - sequenciaVelocidade[i - 1]);
    }

    return velocidade;
}*/

/*Sinal* ModuloRealimentado :: concatenar(Sinal* sinalIN, double valor) //Não utilizada, pega um sinal qualquer e adiciona um elemento a mais
{                                                                       //na sequencia do sinal
    double* novaSequencia = new double[(sinalIN -> getComprimento()) + 1];
    double* auxSequencia = sinalIN -> getSequencia();

    for(int i = 0; i < (sinalIN -> getComprimento()); i++) novaSequencia[i] = auxSequencia[i];

    novaSequencia[sinalIN -> getComprimento()] = valor;

    return new Sinal(novaSequencia, (sinalIN -> getComprimento() + 1));
}*/
