#ifndef MAIN_CPP_TRANSAZIONEINGRESSO_H
#define MAIN_CPP_TRANSAZIONEINGRESSO_H

#include "Transazione.h"


class TransazioneIngresso : public Transazione {
public:
    TransazioneIngresso(const std::string& descrizione, float importo) : Transazione(descrizione, importo) {}

    void esegui(ContoCorrente* conto) {
        conto -> deposita(importo);
        conto -> aggiungiTransazione(this);
    }

};


#endif //MAIN_CPP_TRANSAZIONEINGRESSO_H
