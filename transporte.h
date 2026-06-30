#ifndef TRANSPORTE_H
#define TRANSPORTE_H

#include <string>

class Cidade;

class Transporte {
private:
    std::string nome;
    char tipo;
    int capacidade;
    int velocidade;
    int distancia_entre_descansos;
    int tempo_de_descanso;
    int tempo_de_descanso_atual;
    Cidade* localAtual;

public:
    Transporte(std::string nome, char tipo, int capacidade, int velocidade, 
               int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual);

    std::string getNome();
    char getTipo();
    int getCapacidade();
    int getVelocidade();
    int getDistanciaEntreDescansos();
    int getTempoDescanso();
    int getTempoDescansoAtual();
    Cidade* getLocalAtual();
    void setLocalAtual(Cidade* local);
    void setTempoDescansoAtual(int tempo);
};

#endif