#include <fstream>
#include "ContoCorrente.h"
#include "TransazioneIngresso.h"
#include "TransazioneUscita.h"


bool ContoCorrente::invia(float importo, ContoCorrente *destinatario, const std::string &descrizione) {
    if ( importo <= 0 ) {
       std::cout << "Impossibile inviare quantità negative o nulle di denaro." << std::endl;
        return false;
    }
    if ( preleva(importo, descrizione, destinatario -> getIDUtente()) ) {
        destinatario -> deposita(importo, descrizione, getIDUtente());
        return true;
    }
    else {
        return false;
    }
}

void ContoCorrente::deposita(float importo, const std::string &descrizione, const std::string &mittente) {
    if ( importo <= 0 ) {
        std::cout << "Impossibile depositare quantità negative o nulle di denaro." << std::endl;
        return;
    }
    Transazione *transazione = new TransazioneIngresso(descrizione, importo, mittente);
    saldo += importo;
    aggiungiTransazione(transazione);
}

bool ContoCorrente::preleva(float importo, const std::string &descrizione, const std::string &destinatario) {
    if ( importo <= 0 ) {
        std::cout << "Impossibile prelevare quantità negative o nulle di denaro." << std::endl;
        return false;
    }
    if ( verificaDisponibilità(importo) ) {
        Transazione *transazione = new TransazioneUscita(descrizione, importo, destinatario);
        saldo -= importo;
        aggiungiTransazione(transazione);
        return true;
    }
    else {
        std::cout << "L'utente " << idUtente << " non ha fondi sufficienti per completare l'operazione."
                  << std::endl;
        return false;
    }
}

std::string ContoCorrente::getStoricoToString() const {
    std::ostringstream oss;
    for(const auto &transazione : storicoTransazioni) {
        oss << transazione->toString();
    }
    return oss.str();
}

void ContoCorrente::salvaStoricoTransazioni() const {
    std::ofstream file(percorsoFile, std::ios::app);
    if ( file.is_open()) {
        file << getStoricoToString();
        file.close();
        std::cout << "Storico transazioni salvato nel file: " << percorsoFile << std::endl;
    } else {
        std::cout << "Impossibile aprire il file: " << percorsoFile << std::endl;
    }
}

ContoCorrente::~ContoCorrente() {
    for(auto transazione: storicoTransazioni){
        delete transazione;
    }
}
