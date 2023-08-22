#ifndef MAIN_CPP_CONTOCORRENTE_H
#define MAIN_CPP_CONTOCORRENTE_H


#include <fstream>
#include <utility>
#include "StoricoTransazioni.h"



class ContoCorrente {

private:
    std::string idUtente {"NULL"}; // togliere
    std::string id;
    float saldo;
    StoricoTransazioni storico;
    std::string percorsoFile;

public:
    ContoCorrente() {}

    ContoCorrente(const std::string &idUtente, std::string id, float saldoIniziale=0.0) :
                    idUtente(std::move(idUtente)), id(std::move(id)), saldo(saldoIniziale) {}

    bool invia(float importo, std::shared_ptr<ContoCorrente> destinatario, const std::string &descrizione="Invio");

    bool preleva(float importo, const std::string &descrizione="Prelievo", const std::string &destinatario="");

    bool deposita(float importo, const std::string &descrizione="Deposito", const std::string &mittente="");

    bool salvaDati() const;

    bool caricaDati();

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

    StoricoTransazioni &getStoricoTransazioni() {
        return storico;
    }

    const std::string &getPercorsoFile() const {
        return percorsoFile;
    }

    const std::string &getID() const {
        return id;
    }

    void setPercorsoFile(const std::string &percorsoFile) {
        this -> percorsoFile = percorsoFile;
    }
};


#endif // MAIN_CPP_CONTOCORRENTE_H