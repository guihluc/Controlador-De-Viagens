#include "passageiro.h"
#include "cidade.h"
#include <string>

using namespace std;

Passageiro::Passageiro(string nome, Cidade* localAtual) : nome(nome), localAtual(localAtual){
}

string Passageiro::getNome(){
    return nome;
}

Cidade* Passageiro::getLocalAtual(){
    return localAtual;
}

void Passageiro::setLocalAtual(Cidade* local){
    localAtual = local;
}
