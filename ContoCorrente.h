#ifndef MAIN_CPP_CONTOCORRENTE_H
#define MAIN_CPP_CONTOCORRENTE_H


#include <fstream>
#include <utility>
#include "StoricoTransazioni.h"



class ContoCorrente {

private:
    std::string id;
    float saldo;
    StoricoTransazioni storico;
    std::string percorsoFile;

public:
    ContoCorrente() {}

    ContoCorrente(std::string id, float saldoIniziale=0.0) :
                    id(std::move(id)), saldo(saldoIniziale) {}

    bool salvaDati() const;

    bool caricaDati();

    void aggiungiTransazione(std::shared_ptr<Transazione> &transazione);

    bool verificaDisponibilità(float importo) const {
        if(importo <= saldo) { return true; }
        else { return false; }
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