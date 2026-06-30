#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

#include <string>

class Cidade;
class Passageiro{
private:
    std::string nome;
    Cidade* localAtual;

public:
    Passageiro(std::string nome, Cidade* localAtual);
    std::string getNome();
    Cidade* getLocalAtual();
    void setLocalAtual(Cidade* local);
};
#endif