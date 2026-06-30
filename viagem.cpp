#include "viagem.h"
#include "transporte.h"
#include "passageiro.h"
#include "cidade.h"
#include <iostream>

using namespace std;

Viagem::Viagem(Transporte* transporte, vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int distanciaTotal)
    : transporte(transporte), passageiros(passageiros), origem(origem), destino(destino),
      proxima(nullptr), horasEmTransito(0), emAndamento(false), distanciaTotal(distanciaTotal), 
      dp(0), q(0) {
}

void Viagem::iniciarViagem() {
    emAndamento = true;
    horasEmTransito = 0;
    dp = 0;
    q = 0;
}

bool Viagem::isEmAndamento() {
    return emAndamento;
}

Viagem* Viagem::getProxima() {
    return proxima;
}

void Viagem::setProxima(Viagem* prox) {
    proxima = prox;
}

void Viagem::avancarHoras(int horas) {
    if (!emAndamento) return;

    for (int i = 0; i < horas; i++) {
        if (!emAndamento) break;

        if (transporte->getTempoDescansoAtual() > 0) {
            transporte->setTempoDescansoAtual(transporte->getTempoDescansoAtual() - 1);
            horasEmTransito++;
            
            if (transporte->getTempoDescansoAtual() == 0 && dp >= distanciaTotal) {
                emAndamento = false;
                transporte->setLocalAtual(destino);
                for (auto p_ass : passageiros) {
                    p_ass->setLocalAtual(destino);
                }
                if (proxima != nullptr) {
                    proxima->iniciarViagem();
                }
                break;
            }
            continue;
        }

        horasEmTransito++;
        int vel = transporte->getVelocidade();
        dp += vel;
        q += vel;

        if (dp >= distanciaTotal) {
            dp = distanciaTotal;
        }

        if (q >= transporte->getDistanciaEntreDescansos()) {
            transporte->setTempoDescansoAtual(transporte->getTempoDescanso());
            q = 0;
            continue;
        }

        if (dp >= distanciaTotal) {
            emAndamento = false;
            transporte->setLocalAtual(destino);
            for (auto p_ass : passageiros) {
                p_ass->setLocalAtual(destino);
            }
            
            if (proxima != nullptr) {
                proxima->iniciarViagem();
            }
        }
    }
}

void Viagem::relatarEstado() {
    cout << "Origem: " << origem->getNome() << " | Destino: " << destino->getNome() << " | Progresso: " << dp << "/" << distanciaTotal << " Km"<< " | Transporte: " << transporte->getNome() << " | Horas em transito: " << horasEmTransito;
         
   if (!emAndamento && dp >= distanciaTotal && distanciaTotal > 0) {
        cout << " | Status: Finalizada" << endl;
    } else if (!emAndamento && dp == 0) {
        cout << " | Status: Agendada" << endl; // Faltava essa distinção!
    } else if (transporte->getTempoDescansoAtual() > 0) {
        cout << " | Status: Descansando (" << transporte->getTempoDescansoAtual() << "h restantes)" << endl;
    } else {
        cout << " | Status: Em movimento" << endl;
    }
}