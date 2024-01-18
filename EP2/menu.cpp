#include <cmath>
#include <iostream>
#include <string>
#include <stdexcept>

#include "PersistenciaDeModulo.h"
#include "Modulo.h"
#include "ModuloEmSerie.h"
#include "ModuloEmParalelo.h"
#include "ModuloRealimentado.h"

#include "Sinal.h"


#include "Amplificador.h"
#include "Integrador.h"
#include "Derivador.h"



using namespace std;
#define sinalSize 60

void menu() {
    cout << "        Simulink em C++    " << endl;
    cout << "Qual simulacao voce gostaria de fazer?" << endl;
    cout << "1) Circuito advindo de arquivo" << endl;
    cout << "2) Sua propria sequencia de operacoes" << endl;
    cout << "Escolha: ";
    int escolha;
    cin >> escolha;
    cout << endl;

    int escolhaSinal;
    cout << "Qual sinal voce gostaria de utilizar como entrada da sua simulacao?" << endl;
    cout << "1) 5 + 3*cos(n*pi/8)" << endl;
    cout << "2) constante" << endl;
    cout << "3) rampa" << endl;
    cout << "Escolha: ";
    cin >> escolhaSinal;
    cout << endl;

    Sinal* sinalIN;
    if(escolhaSinal == 3)
    {
        cout << "Qual a inclinacao dessa rampa?" << endl;
        cout << "a = ";
        double inclinacao;
        cin >> inclinacao;
        cout << endl;

        double sequenciaSaida[sinalSize];

        for(int i = 0; i < sinalSize; i ++)
        {
            sequenciaSaida[i] = i*inclinacao;
        }

        sinalIN = new Sinal(&sequenciaSaida[0], sinalSize);
    }else if(escolhaSinal == 2)
    {
        cout << "Qual o valor dessa constante?" << endl;
        cout << "C = ";
        double c;
        cin >> c;
        cout << endl;

        sinalIN = new Sinal(c, sinalSize);
    }else
    {
        double sequenciaSaida[sinalSize];

        for(int i = 0; i < sinalSize; i++) sequenciaSaida[i] = 5 + 3*cos(i * M_PI/8);

        sinalIN = new Sinal(&sequenciaSaida[0], sinalSize);
    }


    Modulo* modRun;
    if(escolha == 1)
    {

        cout << "Qual o nome do arquivo a ser lido?" << endl << "Nome: ";
        string nomeDeArquivo;
        cin >> nomeDeArquivo;
        cout << endl;

        PersistenciaDeModulo* p1 = new PersistenciaDeModulo(nomeDeArquivo);

        try {
            modRun = p1->lerDeArquivo();         
        } catch (invalid_argument *e) {
            cout << e->what() << endl;
            delete e;
        } catch (logic_error *e) {
            cout << e->what() << endl;
            delete e;
        }

        
    }else
    {
        cout << "Qual estrutura de operações voce deseja ter como base?" << endl;
        cout << "1) Operacoes em serie nao realimentadas" << endl;
        cout <<  "2) Operacoes em paralelo nao realimentadas" << endl;
        cout << "3) Operacoes em serie realimentadas" << endl;
        cout << "Escolha: ";
        cin >> escolha;
        cout << endl;
        
        switch (escolha)
        {
        case 1:
            modRun = new ModuloEmSerie();
            break;
        
        case 2:
            modRun = new ModuloEmParalelo();
            break;

        case 3:
            modRun = new ModuloRealimentado();
            break;
        default:
            modRun = new ModuloEmSerie();
            break;
        }

        escolha = 1;
        while(escolha == 1)
        {
            cout << "Qual operacao voce gostaria de fazer?" << endl;
            cout << "1) Amplificar" << endl;
            cout << "2) Derivar" << endl;
            cout << "3) Integrar" << endl;
            cout << "Escolha: ";
            cin >> escolha;
            cout << endl;

            if(escolha == 1)
            {
                cout << "Qual o ganho dessa amplificacao:" << endl << "g = ";
                double g;
                cin >> g;
                cout << endl;

                modRun->adicionar(new Amplificador(g));
            }else if(escolha == 2)
            {
                modRun->adicionar(new Derivador());
            }else
            {
                modRun->adicionar(new Integrador());
            }

            cout << "O que voce quer fazer agora?" << endl;
            cout << "1) Realizar mais uma operacao no resultado" << endl;
            cout << "2) Imprimir o resultado" << endl;
            cout << "Escolha: ";
            cin >> escolha;
            cout << endl;

        }
    }

    modRun->imprimir();

    Sinal* sinalOUT = modRun->processar(sinalIN);                        // aqui se vê o processar el está indo para o q retorna nullptr, isso n é um problema?
    double* sequencia = sinalOUT->getSequencia();
    for(int i = 0; i < sinalOUT->getComprimento(); i++)
    {
        if(i < sinalOUT->getComprimento() -1) cout << ",";
        cout << sequencia[i] << " ";
    }
    cout << endl;
    sinalOUT->imprimir("Resultado final"); // não é esse nome
    cout << "Voce gostaria de salvar o circuito em um outro arquivo?" << endl;
    cout << "1) Sim" << endl;
    cout << "2) Nao" << endl;
    cout << "Escolha: ";
    cin >> escolha;
    cout << endl;

    if(escolha == 1)
    {
        string nomeDeArquivo;
        cout << "Qual o nome do arquivo a ser escrito?" << endl << "Nome: ";
        cin >> nomeDeArquivo;
        cout << endl;

        PersistenciaDeModulo* p1 = new PersistenciaDeModulo(nomeDeArquivo);
        p1->salvarEmArquivo(modRun);
    }
}