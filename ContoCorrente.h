#ifndef MAIN_CPP_CONTOCORRENTE_H
#define MAIN_CPP_CONTOCORRENTE_H

#include <utility>
#include <vector>
#include <iostream>

class Transazione;

class ContoCorrente {

private:
    std::string idUtente;
    float saldo;
    std::vector<Transazione*> storicoTransazioni;

public:
    ContoCorrente(std::string  idUtente, float saldoIniziale=0.0) :
                    idUtente(std::move(idUtente)), saldo(saldoIniziale) {}

    void invia(float importo, ContoCorrente* destinatario, const std::string& descrizione="");

    void aggiungiTransazione(Transazione* transazione) {
        storicoTransazioni.push_back(transazione);
    }

    void preleva(float importo) {
        saldo -= importo;
    }

    void deposita(float importo) {
        saldo += importo;
    }

    bool verificaDisponibilità(float importo) const {
        if(importo <= saldo) { return true; }
        else { return false; }
    }

    const std::string& getIDUtente() const {
        return idUtente;
    }

    float getSaldo() const {
        return saldo;
    }
};

#endif // MAIN_CPP_CONTOCORRENTE_H