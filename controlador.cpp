#include "controlador.h"
#include "cidade.h"
#include "trajeto.h"
#include "transporte.h"
#include "passageiro.h"
#include "viagem.h"
#include <iostream>
#include <fstream>

using namespace std;

ControladorDeTransito::~ControladorDeTransito() {
    for (auto c : cidades) delete c;
    for (auto t : trajetos) delete t;
    for (auto tr : transportes) delete tr;
    for (auto p : passageiros) delete p;
    for (auto v : viagens) delete v;
}

void ControladorDeTransito::cadastrarCidade(string nome) {
    cidades.push_back(new Cidade(nome));
    cout << "Cidade '" << nome << "' cadastrada." << endl;
}

void ControladorDeTransito::cadastrarTrajeto(string nomeOrigem, string nomeDestino, char tipo, int distancia) {
    Cidade* orig = nullptr;
    Cidade* dest = nullptr;
    for (auto c : cidades) {
        if (c->getNome() == nomeOrigem) orig = c;
        if (c->getNome() == nomeDestino) dest = c;
    }
    if (orig && dest) {
        trajetos.push_back(new Trajeto(orig, dest, tipo, distancia));
        cout << "Trajeto cadastrado." << endl;
    } else {
        cout << "Uma ou ambas as cidades informadas não foram cadastradas." << endl;
    }
}

void ControladorDeTransito::cadastrarTransporte(string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, string localAtual) {
    Cidade* local = nullptr;
    for (auto c : cidades) {
        if (c->getNome() == localAtual) {
            local = c;
            break;
        }
    }
    if (local) {
        transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade, distancia_entre_descansos, tempo_de_descanso, local));
        cout << "Transporte '" << nome << "' cadastrado." << endl;
    } else {
        cout << "A cidade local atual '" << localAtual << "' não foi encontrada" << endl;
    }
}

void ControladorDeTransito::cadastrarPassageiro(string nome, string localAtual) {
    Cidade* local = nullptr;
    for (auto c : cidades) {
        if (c->getNome() == localAtual) {
            local = c;
            break;
        }
    }
    if (local) {
        passageiros.push_back(new Passageiro(nome, local));
        cout << "Passageiro '" << nome << "' cadastrado." << endl;
    } else {
        cout << "A cidade local '" << localAtual << "' não foi encontrada" << endl;
    }
}

void ControladorDeTransito::iniciarViagem(string nomeTransporte, vector<string> nomesPassageiros, string nomeOrigem, string nomeDestino) {
    Transporte* trans = nullptr;
    for (auto t : transportes) {
        if (t->getNome() == nomeTransporte) {
            trans = t;
            break;
        }
    }

    if(!trans){ 
        cout << "Transporte '" << nomeTransporte << "' não encontrado." << endl;
        return;
    }

    Cidade* orig = nullptr;
    Cidade* dest = nullptr;
    for (auto c : cidades) {
        if (c->getNome() == nomeOrigem) orig = c;
        if (c->getNome() == nomeDestino) dest = c;
    }

    if(!orig || !dest) {
        cout << "Cidade de origem ou destino não cadastrada." << endl;
        return;
    }

    vector<Cidade*> f;
    vector<Cidade*> vis;
    vector<Cidade*> p(cidades.size(), nullptr);

    f.push_back(orig);
    vis.push_back(orig);
    bool encontrou = false;

    while (!f.empty() && !encontrou) {
        Cidade* atual = f.front();
        f.erase(f.begin());

        if (atual == dest) {
            encontrou = true;
            break;
        }

        for (auto t : trajetos) {
            if (t->getOrigem() == atual && t->getTipo() == trans->getTipo()) {
                Cidade* viz = t->getDestino();
                bool visitado = false;
                for (auto v : vis) {
                    if (v == viz) {
                        visitado = true;
                        break;
                    }
                }
                if (!visitado) {
                    vis.push_back(viz);
                    f.push_back(viz);
                    
                    int idxVizinho = 0;
                    for (size_t i = 0; i < cidades.size(); i++) {
                        if (cidades[i] == viz) {
                            idxVizinho = i;
                            break;
                        }
                    }
                    p[idxVizinho] = atual;
                }
            }
        }
    }

    if (!encontrou) {
        cout << "Nao existe um trajeto ou conexao viavel entre essas cidades." << endl;
        return;
    }

    vector<Passageiro*> passs;
    for (const auto& nomeP : nomesPassageiros) {
        for (auto p : passageiros) {
            if (p->getNome() == nomeP) {
                passs.push_back(p);
            }
        }
    }

    if(passs.empty()){
        cout << "Nenhum passageiro válido encontrado." << endl;
        return;
    }

    vector<Cidade*> caminho;
    Cidade* atualCidade = dest;
    while (atualCidade != nullptr) {
        caminho.insert(caminho.begin(), atualCidade);
        if (atualCidade == orig) break;
        
        int idxAtual = 0;
        for (size_t i = 0; i < cidades.size(); i++) {
            if (cidades[i] == atualCidade) {
                idxAtual = i;
                break;
            }
        }
        atualCidade = p[idxAtual];
    }

    Viagem* ultimaViagem = nullptr;
    for (size_t i = 0; i < caminho.size() - 1; i++) {
        Cidade* o = caminho[i];
        Cidade* d = caminho[i+1];
        int dist = 0;
        
        for (auto t : trajetos) {
            if (t->getOrigem() == o && t->getDestino() == d) {
                dist = t->getDistancia();
                break;
            }
        }

        Viagem* novaViagem = new Viagem(trans, passs, o, d, dist);
        viagens.push_back(novaViagem);

        if (i == 0) {
            novaViagem->iniciarViagem();
        }

        if (ultimaViagem != nullptr) {
            ultimaViagem->setProxima(novaViagem);
        }
        ultimaViagem = novaViagem;
    }

    cout << "Viagem iniciada." << endl;
}

void ControladorDeTransito::avancarHoras(int horas) {
    vector<Viagem*> viagensAtuais = viagens;
    for (auto v : viagensAtuais) {
        v->avancarHoras(horas);
    }
    cout << "Tempo avançado em " << horas << " horas." << endl;
}

void ControladorDeTransito::relatarEstado() {
    cout << "--- RELATORIO DE VIAGENS ---" << endl;
    if(viagens.empty()){
        cout << "Nenhum viagem cadastrada." << endl;
    } else {
        for(auto v : viagens){
            v->relatarEstado();
        }
    }
    cout << "----------------------------" << endl;
}

void ControladorDeTransito::salvar() {
    ofstream fc("cidades.txt");
    for (auto c : cidades) {
        fc << c->getNome() << endl;
    }
    fc.close();

    ofstream ft("trajetos.txt");
    for (auto t : trajetos) {
        ft << t->getOrigem()->getNome() << ","
           << t->getDestino()->getNome() << ","
           << t->getTipo() << ","
           << t->getDistancia() << endl;
    }
    ft.close();

    ofstream ftr("transportes.txt");
    for (auto tr : transportes) {
        ftr << tr->getNome() << ","
            << tr->getTipo() << ","
            << tr->getCapacidade() << ","
            << tr->getVelocidade() << ","
            << tr->getDistanciaEntreDescansos() << ","
            << tr->getTempoDescanso() << ","
            << tr->getLocalAtual()->getNome() << endl;
    }
    ftr.close();

    ofstream fp("passageiros.txt");
    for (auto p : passageiros) {
        fp << p->getNome() << ","
           << p->getLocalAtual()->getNome() << endl;
    }
    fp.close();

    cout << "Dados salvos com sucesso." << endl;
}

void ControladorDeTransito::carregar() {
    ifstream fc("cidades.txt");
    if (fc.is_open()) {
        string nome;
        while (getline(fc, nome)) {
            if (!nome.empty()) {
                cidades.push_back(new Cidade(nome));
            }
        }
        fc.close();
    }

    ifstream ft("trajetos.txt");
    if (ft.is_open()) {
        string orig, dest, tipoStr, distStr;
        while (getline(ft, orig, ',') && getline(ft, dest, ',') && 
               getline(ft, tipoStr, ',') && getline(ft, distStr)) {
            Cidade* o = nullptr;
            Cidade* d = nullptr;
            for (auto c : cidades) {
                if (c->getNome() == orig) o = c;
                if (c->getNome() == dest) d = c;
            }
            if (o && d) {
                trajetos.push_back(new Trajeto(o, d, tipoStr[0], stoi(distStr)));
            }
        }
        ft.close();
    }

    ifstream ftr("transportes.txt");
    if (ftr.is_open()) {
        string nome, tipoStr, capStr, velStr, distDStr, tempoDStr, local;
        while (getline(ftr, nome, ',') && getline(ftr, tipoStr, ',') && 
               getline(ftr, capStr, ',') && getline(ftr, velStr, ',') && 
               getline(ftr, distDStr, ',') && getline(ftr, tempoDStr, ',') && 
               getline(ftr, local)) {
            Cidade* l = nullptr;
            for (auto c : cidades) {
                if (c->getNome() == local) {
                    l = c;
                    break;
                }
            }
            if (l) {
                transportes.push_back(new Transporte(nome, tipoStr[0], stoi(capStr), stoi(velStr), stoi(distDStr), stoi(tempoDStr), l));
            }
        }
        ftr.close();
    }

    ifstream fp("passageiros.txt");
    if (fp.is_open()) {
        string nome, local;
        while (getline(fp, nome, ',') && getline(fp, local)) {
            Cidade* l = nullptr;
            for (auto c : cidades) {
                if (c->getNome() == local) {
                    l = c;
                    break;
                }
            }
            if (l) {
                passageiros.push_back(new Passageiro(nome, l));
            }
        }
        fp.close();
    }

    cout << "Dados carregados com sucesso." << endl;
}