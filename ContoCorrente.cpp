#include "ContoCorrente.h"
#include "TransazioneIngresso.h"
#include "TransazioneUscita.h"


bool ContoCorrente::invia(float importo, ContoCorrente *destinatario, const std::string &descrizione) {
    if ( importo <= 0 ) {
       std::cout << "Impossibile inviare quantità negative o nulle di denaro." << std::endl;
        return false;
    }
    if ( preleva(importo, descrizione) ) {
        destinatario -> deposita(importo, descrizione);
        return true;
    }
    else {
        return false;
    }
}

void ContoCorrente::deposita(float importo, const std::string &descrizione) {
    if ( importo <= 0 ) {
        std::cout << "Impossibile depositare quantità negative o nulle di denaro." << std::endl;
        return;
    }
    Transazione *transazione = new TransazioneIngresso(descrizione, importo);
    saldo += importo;
    aggiungiTransazione(transazione);
}

bool ContoCorrente::preleva(float importo, const std::string &descrizione) {
    if ( importo <= 0 ) {
        std::cout << "Impossibile prelevare quantità negative o nulle di denaro." << std::endl;
        return false;
    }
    if ( verificaDisponibilità(importo) ) {
        Transazione *transazione = new TransazioneUscita(descrizione, importo);
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

