#ifndef MAIN_CPP_TRANSAZIONEUSCITA_H
#define MAIN_CPP_TRANSAZIONEUSCITA_H

#include "Transazione.h"


class TransazioneUscita : public Transazione {
public:
    TransazioneUscita(const std::string &descrizione, float importo, const std::string &destinatario="",
                      const std::string &data="") : Transazione(descrizione, importo, data)
    {
        this -> destinatario = destinatario;
        tipoTransazione = "Uscita";
    }
    bool esegui(ContoCorrente *conto) override {
        return conto -> preleva(importo);
    }

};


#endif //MAIN_CPP_TRANSAZIONEUSCITA_H
