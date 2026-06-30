#ifndef VIAGEM_H
#define VIAGEM_H

#include <vector>

class Transporte;
class Passageiro;
class Cidade;

class Viagem {
private:
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino;
    Viagem* proxima;
    int horasEmTransito;
    bool emAndamento;
    int distanciaTotal;
    int dp;
    int q;

public:
    Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int distanciaTotal);

    void iniciarViagem();
    void avancarHoras(int horas);
    void relatarEstado();
    bool isEmAndamento();
    
    Viagem* getProxima();
    void setProxima(Viagem* prox);
};

#endif