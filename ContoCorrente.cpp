#include "ContoCorrente.h"
#include "TransazioneIngresso.h"
#include "TransazioneUscita.h"


bool ContoCorrente::invia(float importo, ContoCorrente *destinatario, const std::string &descrizione) {
    if ( preleva(importo, descrizione) ) {
        destinatario -> deposita(importo, descrizione);
        return true;
    }
    else {
        return false;
    }
}

void ContoCorrente::deposita(float importo, const std::string &descrizione) {
    Transazione *transazione = new TransazioneIngresso(descrizione, importo);
    saldo += importo;
    aggiungiTransazione(transazione);
}

bool ContoCorrente::preleva(float importo, const std::string &descrizione) {
    if ( verificaDisponibilità(importo) ) {
        Transazione *transazione = new TransazioneUscita(descrizione, importo);
        saldo -= importo;
        aggiungiTransazione(transazione);
        return true;
    }
    else {
        std::cout << "L' Utente " << idUtente << " non ha fondi sufficienti per completare l'operazione."
                  << std::endl;
        return false;
    }
}

