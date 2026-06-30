#include "controlador.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ControladorDeTransito controlador;
    controlador.carregar();

    int opcao = 0;
    while (opcao != 8) {
        cout << "\n=== SISTEMA CONTROLADOR DE VIAGENS ===" << endl;
        cout << "1. Cadastrar Cidade" << endl;
        cout << "2. Cadastrar Trajeto" << endl;
        cout << "3. Cadastrar Transporte" << endl;
        cout << "4. Cadastrar Passageiro" << endl;
        cout << "5. Iniciar Viagem" << endl;
        cout << "6. Avancar Horas" << endl;
        cout << "7. Relatorios e Estado do Sistema" << endl;
        cout << "8. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (opcao == 1) {
            string nome;
            cout << "Nome da Cidade: ";
            cin >> nome;
            controlador.cadastrarCidade(nome);
        }
        else if (opcao == 2) {
            string orig, dest;
            char tipo;
            int dist;
            cout << "Cidade de Origem: ";
            cin >> orig;
            cout << "Cidade de Destino: ";
            cin >> dest;
            cout << "Tipo (A - Aquatico, T - Terestre): ";
            cin >> tipo;
            cout << "Distancia (Km): ";
            cin >> dist;
            controlador.cadastrarTrajeto(orig, dest, tipo, dist);
        }
        else if (opcao == 3) {
            string nome, local;
            char tipo;
            int cap, vel, distD, tempoD;
            cout << "Nome do Transporte: ";
            cin >> nome;
            cout << "Tipo (A - Aquatico, T - Terestre): ";
            cin >> tipo;
            cout << "Capacidade: ";
            cin >> cap;
            cout << "Velocidade (Km/h): ";
            cin >> vel;
            cout << "Distancia entre descansos (Km): ";
            cin >> distD;
            cout << "Tempo de descanso (h): ";
            cin >> tempoD;
            cout << "Cidade Local Atual: ";
            cin >> local;
            controlador.cadastrarTransporte(nome, tipo, cap, vel, distD, tempoD, local);
        }
        else if (opcao == 4) {
            string nome, local;
            cout << "Nome do Passageiro: ";
            cin >> nome;
            cout << "Cidade Local Atual: ";
            cin >> local;
            controlador.cadastrarPassageiro(nome, local);
        }
        else if (opcao == 5) {
            string trans, orig, dest, nomeP;
            int qtdP;
            vector<string> passs;
            cout << "Nome do Transporte: ";
            cin >> trans;
            cout << "Cidade de Origem: ";
            cin >> orig;
            cout << "Cidade de Destino: ";
            cin >> dest;
            cout << "Quantidade de passageiros: ";
            cin >> qtdP;
            for (int i = 0; i < qtdP; i++) {
                cout << "Nome do passageiro " << i + 1 << ": ";
                cin >> nomeP;
                passs.push_back(nomeP);
            }
            controlador.iniciarViagem(trans, passs, orig, dest);
        }
        else if (opcao == 6) {
            int horas;
            cout << "Quantidade de horas a avancar: ";
            cin >> horas;
            controlador.avancarHoras(horas);
        }
        else if (opcao == 7) {
            controlador.relatarEstado();
        }
        else if (opcao == 8) {
            controlador.salvar();
        }

        else{
            cout << "Opção inválida." << endl;
            break;
        }
    }

    return 0;
}