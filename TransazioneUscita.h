#ifndef MAIN_CPP_TRANSAZIONEUSCITA_H
#define MAIN_CPP_TRANSAZIONEUSCITA_H

#include "Transazione.h"


class TransazioneUscita : public Transazione {
public:
    TransazioneUscita(const std::string &descrizione, float importo) : Transazione(descrizione, importo) {}

    void esegui(ContoCorrente *conto) {
        conto -> preleva(importo);
    }

};


#endif //MAIN_CPP_TRANSAZIONEUSCITA_H
