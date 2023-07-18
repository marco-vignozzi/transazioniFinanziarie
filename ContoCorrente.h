#ifndef MAIN_CPP_CONTOCORRENTE_H
#define MAIN_CPP_CONTOCORRENTE_H

// macro per stampare i float con 2 cifre decimali
#define FIXED_FLOAT(x) std::fixed << std::setprecision(2) << x

#include <utility>
#include <vector>
#include <iostream>
#include <sstream>


class Transazione;


class ContoCorrente {

private:
    std::string idUtente {"NULL"};
    float saldo;
    std::vector<Transazione*> storicoTransazioni;
    std::string percorsoFile;

public:
    ContoCorrente() {}

    ContoCorrente(std::string  idUtente, float saldoIniziale=0.0) :
                    idUtente(std::move(idUtente)), saldo(saldoIniziale) {}

    ~ContoCorrente();

    bool invia(float importo, ContoCorrente *destinatario, const std::string &descrizione="Invio");

    bool preleva(float importo, const std::string &descrizione="Prelievo", const std::string &destinatario="");

    bool deposita(float importo, const std::string &descrizione="Deposito", const std::string &mittente="");

    std::string getStoricoToString() const;

    bool salvaDati() const;

    bool caricaDati();

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

    const std::string& getPercorsoFile() const {
        return percorsoFile;
    }

    void setPercorsoFile(const std::string &percorsoFile) {
        this -> percorsoFile = percorsoFile;
    }
};


#endif // MAIN_CPP_CONTOCORRENTE_H