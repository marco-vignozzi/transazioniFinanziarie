#ifndef MAIN_CPP_TRANSAZIONEINGRESSO_H
#define MAIN_CPP_TRANSAZIONEINGRESSO_H

#include "Transazione.h"


class TransazioneIngresso : public Transazione {
public:
    TransazioneIngresso(const std::string &descrizione, float importo,const std::string &mittente="",
                        const std::string &data="") : Transazione(descrizione, importo, data)
    {
        this -> mittente = mittente;
        tipoTransazione = "Ingresso";
    }

    bool esegui(ContoCorrente *conto) override {
        return conto -> deposita(this->importo, this->descrizione, this->mittente);
    }

};


#endif //MAIN_CPP_TRANSAZIONEINGRESSO_H
