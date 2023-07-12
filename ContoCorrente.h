#ifndef MAIN_CPP_CONTOCORRENTE_H
#define MAIN_CPP_CONTOCORRENTE_H

#include <utility>
#include <vector>
#include <iostream>

class Transazione;


class ContoCorrente {

private:
    std::string idUtente {"NULL"};
    float saldo;
    std::vector<Transazione*> storicoTransazioni;

public:
    ContoCorrente() {}

    ContoCorrente(std::string  idUtente, float saldoIniziale=0.0) :
                    idUtente(std::move(idUtente)), saldo(saldoIniziale) {}

    bool invia(float importo, ContoCorrente *destinatario, const std::string &descrizione="Invio");

    bool preleva(float importo, const std::string &descrizione="Prelievo");

    void deposita(float importo, const std::string &descrizione="Deposito");

    void aggiungiTransazione(Transazione *transazione) {
        storicoTransazioni.push_back(transazione);
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

    std::vector<Transazione*> getStoricoTransazioni() const {
        return storicoTransazioni;
    }

};


#endif // MAIN_CPP_CONTOCORRENTE_H