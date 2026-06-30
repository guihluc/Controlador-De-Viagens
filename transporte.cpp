#include "transporte.h"
#include "cidade.h"
#include <string>

using namespace std;

Transporte::Transporte(string nome, char tipo, int capacidad, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, Cidade* localAtual) : nome(nome), tipo(tipo), capacidade(capacidad), velocidade(velocidade), distancia_entre_descansos(distancia_entre_descansos), tempo_de_descanso(tempo_de_descanso), tempo_de_descanso_atual(0), localAtual(localAtual) {
}

string Transporte::getNome() {
    return nome;
}

char Transporte::getTipo() {
    return tipo;
}

int Transporte::getCapacidade() {
    return capacidade;
}

int Transporte::getVelocidade() {
    return velocidade;
}

int Transporte::getDistanciaEntreDescansos() {
    return distancia_entre_descansos;
}

int Transporte::getTempoDescanso() {
    return tempo_de_descanso;
}

int Transporte::getTempoDescansoAtual() {
    return tempo_de_descanso_atual;
}

Cidade* Transporte::getLocalAtual() {
    return localAtual;
}

void Transporte::setLocalAtual(Cidade* local) {
    localAtual = local;
}

void Transporte::setTempoDescansoAtual(int tempo) {
    tempo_de_descanso_atual = tempo;
}