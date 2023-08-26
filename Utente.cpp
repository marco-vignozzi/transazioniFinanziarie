#include "Utente.h"

std::shared_ptr<ContoCorrente> Utente::getConto(const std::string &idConto) {
    for( auto &conto : contiCorrenti) {
        if ( conto->getID() == idConto ) {
            return conto;
        }
    }
    return std::make_shared<ContoCorrente>();
}

bool Utente::invia(const std::string &idConto, Utente &destinatario, const std::string &idContoDest, float importo, const std::string &descrizione) {
    if ( importo <= 0 ) {
        std::cout << "Impossibile inviare quantità negative o nulle di denaro." << std::endl;
        return false;
    }
    if ( preleva(idConto, importo, destinatario.getID(), descrizione) ) {
        destinatario.deposita(idContoDest, importo, destinatario.getID(), descrizione);
        return true;
    }
    return false;
}

bool Utente::preleva(const std::string &idConto, float importo, const std::string &idDestinatario, const std::string &descrizione) {
    if ( importo <= 0 ) {
        std::cout << "Impossibile prelevare quantità negative o nulle di denaro." << std::endl;
        return false;
    }
    if ( this->getConto(idConto)->verificaDisponibilità(importo) ) {
        std::shared_ptr<Transazione> transazione = std::make_shared<Transazione>(descrizione, importo, "uscita", idDestinatario);
        this->getConto(idConto)->aggiungiTransazione(transazione);
        return true;
    }
    else {
        std::cout << "L'utente " << id << " non ha fondi sufficienti per completare l'operazione."
                  << std::endl;
        return false;
    }
}

bool Utente::deposita(const std::string &idConto, float importo, const std::string &idMittente, const std::string &descrizione) {
    if ( importo <= 0 ) {
        std::cout << "Impossibile depositare quantità negative o nulle di denaro." << std::endl;
        return false;
    }
    std::shared_ptr<Transazione> transazione = std::make_shared<Transazione>(descrizione, importo, "ingresso", idMittente);
    this->getConto(idConto)->aggiungiTransazione(transazione);
    return true;
}
