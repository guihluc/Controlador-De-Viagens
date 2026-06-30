#include "cidade.h"
#include <string>
using namespace std;

Cidade::Cidade(string nome) : nome(nome){
}
string Cidade::getNome(){
    return nome;
}