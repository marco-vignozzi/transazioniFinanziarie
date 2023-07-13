#ifndef MAIN_CPP_TRANSAZIONEINGRESSO_H
#define MAIN_CPP_TRANSAZIONEINGRESSO_H

#include "Transazione.h"


class TransazioneIngresso : public Transazione {
public:
    TransazioneIngresso(const std::string &descrizione, float importo, const std::string &mittente="") :
                    Transazione(descrizione, importo)
    {
        this -> mittente = mittente;
        tipoTransazione = "Ingresso";
    }

    void esegui(ContoCorrente *conto) {
        conto -> deposita(importo);
    }

};


#endif //MAIN_CPP_TRANSAZIONEINGRESSO_H
