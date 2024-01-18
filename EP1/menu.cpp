#include <cmath>
#include "Amplificador.h"
#include "Somador.h"
#include "Derivador.h"
#include "Integrador.h"
#include "ModuloRealimentado.h"
#include "Grafico.h"

using namespace std;

Sinal* novoSinal() {
    cout << "Qual sinal voce gostaria de utilizar como entrada da sua simulacao?" << endl;
    cout << "1) 5+3*cos(n*pi/8)" << endl;
    cout << "2) constante" << endl;
    cout << "3) rampa" << endl;
    cout << "Escolha: ";

    double sequencia[60];
    int opcao = 0;

    cin >> opcao;
    cout << endl;

    if (opcao == 1) {

        for (int i = 0; i < 60; i++) { 
            sequencia[i] = 5+3*cos(i*M_PI/8);
        }
    }

    if (opcao == 2) {
        cout << "Qual o valor dessa constante?" << endl;
        cout << "C = ";

        double c = 0;

        cin >> c;
        cout << endl;

        for (int i = 0; i < 60; i++) {
            sequencia[i] = c;
        }
    }

    if (opcao == 3) {
        cout << "Qual a inclinacao dessa rampa?" << endl;
        cout << "a = ";

        double a = 0;

        cin >> a;
        cout << endl;

        for (int i = 0; i < 60; i++) {
            sequencia[i] = i*a;
        }
    }   

    Sinal* sinalNovo = new Sinal(sequencia, 60); 
    return sinalNovo;
} 

void novaOperacao(Sinal *sinalIN) {
    cout << "Qual operacao voce gostaria de fazer?" << endl;
    cout << "1) Amplificar" << endl;
    cout << "2) Somar" << endl;
    cout << "3) Derivar" << endl;
    cout << "4) Integrar" << endl;
    cout << "Escolha: ";

    Sinal *sinalOperado = nullptr;
    int escolha = 0;

    cin >> escolha;
    cout << endl;

    if (escolha == 1) {
        cout << "Qual o ganho dessa amplificacao?" << endl;
        cout << "g = ";

        double g = 0;
    
        cin >> g;
        cout << endl;

        Amplificador *amp = new Amplificador(g);

        sinalOperado = amp -> processar(sinalIN);

        delete amp;
    }

    if (escolha == 2) {
        cout << "Informe mais um sinal para ser somado" << endl;
        Sinal *segundoSinal = novoSinal();
        Somador *soma = new Somador();

        sinalOperado = soma -> processar(sinalIN, segundoSinal);

        delete segundoSinal;
        delete soma;
    }

    if (escolha == 3) {
        Derivador *der = new Derivador();

        sinalOperado = der -> processar(sinalIN);

        delete der;
    }

    if (escolha == 4) {
        Integrador *inte = new Integrador();

        sinalOperado = inte -> processar(sinalIN);

        delete inte;
    }

    cout << "O que voce quer fazer agora?" << endl;
    cout << "1) Realizar mais uma operacao no resultado" << endl;
    cout << "2) Imprimir o resultado para terminar" << endl;
    cout << "Escolha: ";

    cin >> escolha; 
    cout << endl;

    if (escolha == 1) {
        novaOperacao(sinalOperado);
    }

    if (escolha == 2) {
        Grafico *graf = new Grafico("Resultado Final", sinalOperado -> getSequencia(), sinalOperado -> getComprimento());

        graf -> plot();

        delete graf;
    }
}

void menu() {
    cout << "        Simulink em C++    " << endl;
    cout << "Qual simulacao voce gostaria de fazer?" << endl;
    cout << "1) Piloto Automatico" << endl;
    cout << "2) Sua propria sequencia de operacoes" << endl;
    cout << "Escolha: ";

    int opcao = 0;

    cin >> opcao;
    cout << endl;

    if (opcao == 1) {
        Sinal* sinalIN = novoSinal();

        cout << "Qual o ganho do acelerador?" << endl;
        cout << "g = ";

        double ganho = 0;

        cin >> ganho;
        cout << endl;

        ModuloRealimentado* modulo = new ModuloRealimentado(ganho);

        Sinal* sinalOUT = modulo -> processar(sinalIN);

        Grafico* grafico = new Grafico("Velocidade do Carro", sinalOUT -> getSequencia(), sinalOUT -> getComprimento());

        grafico -> plot();

        delete sinalIN;
        delete sinalOUT;
        delete modulo;
        delete grafico;
    }

    if (opcao == 2) {
        Sinal* sinalIN = novoSinal(); 

        novaOperacao(sinalIN);

        delete sinalIN;
    }
}