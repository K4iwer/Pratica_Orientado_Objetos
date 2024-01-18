#include "PersistenciaDeModulo.h"
#include "ModuloEmParalelo.h"
#include "ModuloEmSerie.h"
#include "ModuloRealimentado.h"
#include "Amplificador.h"
#include "Integrador.h"
#include "Derivador.h"

#include <fstream>
#include <stdexcept>                                // na verdade n precisa, coloquei por precaucao

PersistenciaDeModulo :: PersistenciaDeModulo(string nomeDoArquivo) : Modulo() {
    this->nomeArquivo = nomeDoArquivo;
    ifstream input;
    input.open(nomeDoArquivo);

    input.close();
}

PersistenciaDeModulo :: ~PersistenciaDeModulo() {}

void auxiliarSalvarEmArquivo(ofstream& output, Modulo* mod) {
    string tipo;
    double ganho;
    
    if (dynamic_cast<ModuloEmParalelo*> (mod)) {
        tipo = "P";                                    
        output << tipo << endl;
    }

    else if (dynamic_cast<ModuloEmSerie*> (mod)) {
        tipo = "S";                                              
        output << tipo << endl;
    }

    else if (dynamic_cast<ModuloRealimentado*> (mod)) {
        mod = dynamic_cast<ModuloRealimentado*> (mod);
        tipo = "R";                                                
        output << tipo << endl;
    }

    list<CircuitoSISO*>* copiaLista = mod->getCircuito();
    list<CircuitoSISO*>::iterator i = copiaLista->begin(); 

    while (i != copiaLista->end()) {

        bool eAmplificador = false; 

        if (dynamic_cast<Integrador*> (*i)) {
            tipo = "I"; 
            output << tipo;  
            output << endl;                                  
        }

        else if (dynamic_cast<Derivador*> (*i)) {
            tipo = "D";  
            output << tipo;  
            output << endl;                                       
        }

        else if (dynamic_cast<Amplificador*> (*i)) {
            Amplificador* amp = dynamic_cast<Amplificador*> (*i);
            ganho = amp->getGanho();
            tipo = "A";                                        
            eAmplificador = true;
            output << tipo;
        }

        else if (dynamic_cast<ModuloEmParalelo*> (*i)) {
            ModuloEmParalelo* modAux = dynamic_cast<ModuloEmParalelo*> (*i);
            auxiliarSalvarEmArquivo(output, modAux); 
            delete modAux; 
        }

        else if (dynamic_cast<ModuloEmSerie*> (*i)) {
            ModuloEmSerie* modAux = dynamic_cast<ModuloEmSerie*> (*i);
            auxiliarSalvarEmArquivo(output, modAux); 
            delete modAux;
        }

        else if (dynamic_cast<ModuloRealimentado*> (*i)) {
            ModuloRealimentado* modAux = dynamic_cast<ModuloRealimentado*> (*i);
            auxiliarSalvarEmArquivo(output, modAux);  
            delete modAux;
        }

        if (eAmplificador) {
            output << " " << ganho;
            eAmplificador = false;
            output << endl;
        }

        i++;
    }

    //delete *i;           //preciso te deletar??

    output << "f" << endl;
}

void PersistenciaDeModulo :: salvarEmArquivo(Modulo* mod) {
    ofstream output;
    output.open(nomeArquivo, ios_base::app);

    auxiliarSalvarEmArquivo(output, mod);

    output.close();
}

Modulo* auxiliarLerArquivo(ifstream& input, Modulo* mod) {  
    string tipoDoCirc;                                          
    
    input >> tipoDoCirc;
    while (input && tipoDoCirc != "f" && tipoDoCirc != "") {                        
        if (tipoDoCirc != "S" && tipoDoCirc != "P" && tipoDoCirc != "R" && tipoDoCirc != "A" && tipoDoCirc != "D" && tipoDoCirc != "I") {
            throw new logic_error("Formatacao invalida");
        }

        else if (tipoDoCirc == "S") {
            ModuloEmSerie* modSer = new ModuloEmSerie();
            modSer = (ModuloEmSerie*)auxiliarLerArquivo(input, modSer);
            mod->adicionar(modSer);
        }

        else if (tipoDoCirc == "P") {
            ModuloEmParalelo* modPar = new ModuloEmParalelo();
            modPar = (ModuloEmParalelo*)auxiliarLerArquivo(input, modPar);
            mod->adicionar(modPar);
        }

        else if (tipoDoCirc == "R") {
            ModuloRealimentado* modRea = new ModuloRealimentado();       
            modRea = (ModuloRealimentado*)auxiliarLerArquivo(input, modRea);       
            mod->adicionar(modRea);
        }

        else if (tipoDoCirc == "A") {
            double ganho;
            input >> ganho;
            Amplificador* amp = new Amplificador(ganho);
            mod->adicionar(amp);  
        }

        else if (tipoDoCirc == "I") {
            Integrador* inte = new Integrador();
            mod->adicionar(inte);
        }

        else if (tipoDoCirc == "D") {
            Derivador* der = new Derivador();
            mod->adicionar(der);
        }

        input >> tipoDoCirc;
    }

    return mod;
}

Modulo* PersistenciaDeModulo :: lerDeArquivo() {     
    Modulo* modOut;   
    ifstream input;                                                     
    input.open(nomeArquivo);

    if (input.fail()) {
        throw new invalid_argument("Arquivo nao encontrado");
    }

    string cirType;
    input >> cirType;

    if (!(cirType == "S" || cirType == "R" || cirType == "P")) {
        throw new logic_error("Formatacao invalida");
    }else if(cirType == "S")
    {
        modOut = new ModuloEmSerie();
    }else if(cirType == "R")
    {
        modOut = new ModuloRealimentado();
    }else {
        modOut = new ModuloEmParalelo();
    }

    modOut = auxiliarLerArquivo(input, modOut);

    input >> cirType;
    if (!input.eof()) {
        throw new logic_error("Formatacao incorreta do arquivo");
    };

    input.close();

   return modOut;
}

Sinal* PersistenciaDeModulo :: processar(Sinal* sinalIN){                // vc e necessario?
    return nullptr;
}


/*                        //metodo tentando fazer por comparação de processar q n deu certo


void auxiliarLerArquivo(ifstream& input, Modulo* mod) {           //talvez a passagem de parametro esteja errada  // colocando pra analizar o f logo no comeco ficaria melhor
    string tipoDoCirc;                                            //se n funcionar assim fazer uma outra funcao apenas para os sinais
    
    input >> tipoDoCirc;
    cout << tipoDoCirc << endl;

    while (input && tipoDoCirc != "f") {                          // tá certo o operador "e"?

        cout << "bruh" << endl;           //teste

        if (tipoDoCirc == "S") {
            ModuloEmSerie* modSer;
            cout << "abracadabra" << endl;             //teste
            auxiliarLerArquivo(input, modSer);
            cout << "abracadabra" << endl;             //teste
            //mod->adicionar(modSer);
            //delete modSer;                             //talvez isso tbm esteja causando problemas
        }

        else if (tipoDoCirc == "P") {
            ModuloEmParalelo* modPar;
            auxiliarLerArquivo(input, modPar);
            //mod->adicionar(modPar);
            delete modPar;
        }

        /*else if (tipoDoCirc == "R") {
            ModuloRealimentado* modRea;       
            auxiliarLerArquivo(input, modRea);
            mod->adicionar(modRea);                                // checar depois pq quando eu fiz ele ainda n tava pronto  
            delete modRea;
        }*/
/*
        else if (tipoDoCirc == "A") {
            double ganho;
            input >> ganho;
            //mod->adicionar(new Amplificador(ganho));  
        }

        else if (tipoDoCirc == "I") {
            cout << "xazam" << endl;             //teste
            Integrador* inte = new Integrador();
            //mod->adicionar(inte);
            cout << "xazam" << endl;             //teste
            //delete inte;
        }

        else if (tipoDoCirc == "D") {
            cout << "blam" << endl;             //teste
            Derivador* der = new Derivador;
            mod->adicionar(der);
        }

        input >> tipoDoCirc;
        cout << tipoDoCirc << endl;
    }
}



Modulo* PersistenciaDeModulo :: lerDeArquivo() {
    Modulo* modOut; 
    ifstream input;
    input.open(nomeArquivo);

    if (input.fail()) {
        throw new invalid_argument("Arquivo nao encontrado");
    }

    auxiliarLerArquivo(input, modOut);

    //if (!input.eof()) {
    //    throw new logic_error("Formatacao incorreta do arquivo");                             //essa posicao pode estar errada
    //}

    input.close();

    return modOut;
} */

/*
void auxiliarLerArquivo(ifstream& input, Modulo* mod) {           //talvez a passagem de parametro esteja errada  // colocando pra analizar o f logo no comeco ficaria melhor
    string tipoDoCirc;                                            //se n funcionar assim fazer uma outra funcao apenas para os sinais
    
    input >> tipoDoCirc;
    cout << tipoDoCirc << endl;

    while (input && tipoDoCirc != "f") {                          // tá certo o operador "e"?

        cout << "bruh" << endl;           //teste

        if (tipoDoCirc == "S") {
            ModuloEmSerie* modSer = new ModuloEmSerie();
            cout << "abracadabra" << endl;             //teste
            auxiliarLerArquivo(input, modSer);
            cout << "abracadabra" << endl;             //teste
            mod->adicionar(modSer);
            //delete modSer;                             //Se eu deletar aqui eu tiro do mod oficial né?
        }

        else if (tipoDoCirc == "P") {
            ModuloEmParalelo* modPar = new ModuloEmParalelo();
            auxiliarLerArquivo(input, modPar);
            mod->adicionar(modPar);
            //delete modPar;
        }

        else if (tipoDoCirc == "R") {
            ModuloRealimentado* modRea;       
            auxiliarLerArquivo(input, modRea);
            mod->adicionar(modRea);                                // checar depois pq quando eu fiz ele ainda n tava pronto  
            delete modRea;
        }

        else if (tipoDoCirc == "A") {
            double ganho;
            input >> ganho;
            Amplificador* amp = new Amplificador(ganho);
            mod->adicionar(amp);
        }

        else if (tipoDoCirc == "I") {
            cout << "xazam" << endl;             //teste
            Integrador* inte = new Integrador();
            mod->adicionar(inte);
            cout << "xazam" << endl;             //teste
        }

        else if (tipoDoCirc == "D") {
            cout << "blam" << endl;             //teste
            Derivador* der = new Derivador();
            mod->adicionar(der);
        }

        input >> tipoDoCirc;
        cout << tipoDoCirc << endl;
    }
}



Modulo* PersistenciaDeModulo :: lerDeArquivo() {                 //ainda n tá defendendo de formatações erradas
    ifstream input;
    input.open(nomeArquivo);

    string tipoDoCirc;
    
    input >> tipoDoCirc;
    cout << tipoDoCirc << endl;

    if (input.fail()) {
        throw new invalid_argument("Arquivo nao encontrado");
    }

    while (input && tipoDoCirc != "f") {

        cout << "bruh" << endl;           //teste

        if (tipoDoCirc == "S") {
            Modulo* modSer = new Modulo();
            modSer->adicionar(new Derivador());
            cout << "abracadabra" << endl;             //teste
            auxiliarLerArquivo(input, modSer);
            cout << "abracadabra" << endl;             //teste
            input.close();
            return modSer;
        }

        else if (tipoDoCirc == "P") {
            ModuloEmParalelo* modPar;
            auxiliarLerArquivo(input, modPar);
            input.close();
            return modPar;
            //delete modPar;
        }

        else if (tipoDoCirc == "R") {
            ModuloRealimentado* modRea;       
            auxiliarLerArquivo(input, modRea);
            return modRea;
            mod->adicionar(modRea);                                // checar depois pq quando eu fiz ele ainda n tava pronto  
            delete modRea;
        }

        cout << tipoDoCirc << endl;
    }

    if (!input.eof()) {
        throw new logic_error("Formatacao incorreta do arquivo");                             //essa posicao pode estar errada
    }

    input.close();
    return nullptr;
}*/






/*          salvar em arquivo versão q n consegui fazer

void auxiliarSalvarEmArquivo(ofstream& output, Modulo* mod) {
    string tipo;
    Sinal* sinalAux = new Sinal(1, 60);
    Derivador* derComparativo = new Derivador();
    Amplificador* ampComparativo = new Amplificador(0);
    Integrador* intComparativo = new Integrador();
    ModuloEmParalelo* modParComparativo = new ModuloEmParalelo();
    ModuloEmSerie* modSerComparativo = new ModuloEmSerie();
    //ModuloRealimentado* modReaComparativo = new ModuloRealimentado();
    Sinal* sinalProcessado;

    list<CircuitoSISO*>* copiaLista = mod->getCircuito();
    list<CircuitoSISO*>::iterator i = copiaLista->begin();      // precisa fazer uma copia mesmo?
    
    cout << "bruh" << endl;                                       //teste

    while (i != copiaLista->end()) {
        Sinal* sinalTeste = new Sinal(1, 60);

        cout << "bruh" << endl;   

        sinalProcessado = (*i)->processar(sinalTeste);      //aqui deu erro      //processar de derivador tava dando primeiro valor com 2 ao inves de 1??

        sinalTeste = sinalAux;

        cout << "bruh" << endl;   
        double ganho = (sinalProcessado->getSequencia())[1];     // como o sinal possui sequencia com constantes 1, o valor de qualquer casa e' o valor de ganho
        ampComparativo->setGanho(ganho);
        bool eAmplificador = false;

        cout << "bobrinha" << endl;   

        if (dynamic_cast<Integrador*> (*i)) {
            tipo = "A";                                                //se n der certo tentar isso
            cout << "LESGOOOOOOOOOOO" << endl;
        }

        

        //if (sinalProcessado == modParComparativo->processar(sinalTeste)) {
        //    cout << "maionese" << endl;   
        //    tipo = "P";
        //    auxiliarSalvarEmArquivo(output, mod);
        //}

        cout << "bobrinha" << endl; 

        //if (sinalProcessado == modSerComparativo->processar(sinalTeste)) {
        //    tipo = "S";
        //    auxiliarSalvarEmArquivo(output, mod);
        //}

        //else if (sinalProcessado == modReaComparativo->processar(sinalTeste)) {
        //    tipo = "R";
        //    auxiliarSalvarEmArquivo(output, mod);
        //}

        sinalTeste = sinalAux;
        sinalTeste = intComparativo->processar(sinalTeste);
        double* seq = sinalTeste->getSequencia();
        double* br = sinalProcessado->getSequencia();

         if (seq == br) {
            tipo = "D";
            cout << "THE ONE PIECEEEEEEE" << endl;
        }

        sinalTeste->imprimir();

        cout << "IS REEEAAAAAALLLLL" << endl;

         if ((ganho == ((ampComparativo->processar(sinalTeste))->getSequencia())[3])) {                   // ta analizando com o três, pq se for um amplificador ele precisa ser igual para todos, mas tem uma chance de isso dar errado caso os valores sejam iguais
            tipo = "A";
            ganho = (sinalProcessado->getSequencia())[1];
            eAmplificador = true;
        }

         if (sinalProcessado == intComparativo->processar(sinalTeste)) {
            tipo = "I";
            cout << "THE ONE PIECEEEEEEE" << endl;
        }

        //if (dynamic_cast<Amplificador*> (*i)) {
        //    type = "A";                                                //se n der certo tentar isso
        //}

        output << tipo;

        if (eAmplificador) {
            output << ganho;
            eAmplificador = false;
        }

        output << endl;

        i++;
        delete sinalTeste;

    }

    delete derComparativo;
    delete ampComparativo;
    delete intComparativo;
    delete modParComparativo;
    delete modSerComparativo;
    //delete modReaComparativo;
    delete sinalProcessado;
}

void PersistenciaDeModulo :: salvarEmArquivo(Modulo* mod) {      //precisa apagar o q estava anteriormente no arquivo??
    ofstream output;
    output.open(nomeArquivo, ios_base::app);

    auxiliarSalvarEmArquivo(output, mod);

    output.close();
}




*/
