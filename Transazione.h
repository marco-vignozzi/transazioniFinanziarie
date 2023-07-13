#ifndef MAIN_CPP_TRANSAZIONE_H
#define MAIN_CPP_TRANSAZIONE_H

#include <iostream>
#include <utility>
#include "Data.h"
#include "ContoCorrente.h"


class Transazione {

protected:
    float importo;
    std::string data;
    std::string descrizione;
    std::string tipoTransazione;
    std::string mittente {""};
    std::string destinatario {""};

public:
    Transazione(const std::string &descrizione, float importo) : descrizione(descrizione), importo(importo)
    {
        data = (new Data()) -> toString();
    }

    std::string toString() const;

    virtual void esegui(ContoCorrente* conto) = 0;

    std::string getDescrizione() const {
        return descrizione;
    }

    float getImporto() const {
        return importo;
    }

    std::string getData() const {
        return data;
    }
};


#endif // MAIN_CPP_TRANSAZIONE_H