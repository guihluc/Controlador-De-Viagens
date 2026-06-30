#include "trajeto.h"
#include "cidade.h"

using namespace std;

Trajeto::Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia) : origem(origem), destino(destino), tipo(tipo), distancia(distancia) {
}

Cidade* Trajeto::getOrigem() {
    return origem;
}

Cidade* Trajeto::getDestino() {
    return destino;
}

char Trajeto::getTipo() {
    return tipo;
}

int Trajeto::getDistancia() {
    return distancia;
}