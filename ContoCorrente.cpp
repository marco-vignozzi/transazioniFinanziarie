#include "ContoCorrente.h"
#include "TransazioneIngresso.h"
#include "TransazioneUscita.h"

void ContoCorrente::invia(float importo, ContoCorrente* destinatario, const std::string& descrizione) {
    if ( verificaDisponibilità(importo) ) {
        Transazione *tOut = new TransazioneUscita(descrizione, importo);
        Transazione *tIn = new TransazioneIngresso(descrizione, importo);
        tOut -> esegui(this);
        tIn -> esegui(destinatario);
    }
    else {
        std::cout << "L' Utente " << idUtente << " non ha fondi sufficienti per completare l'operazione."
                  << std::endl;
    }
}

