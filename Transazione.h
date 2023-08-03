#ifndef MAIN_CPP_TRANSAZIONE_H
#define MAIN_CPP_TRANSAZIONE_H

#include "ContoCorrente.h"


class Transazione {

protected:
    float importo;
    std::string data;
    std::string descrizione;
    std::string tipoTransazione;
    std::string mittente;
    std::string destinatario;

public:
    Transazione(const std::string &descrizione, float importo, const std::string &data="") :
                    descrizione(descrizione), importo(importo)
    {
        if ( data.empty() ) {
            this->data = creaData();
        }
        else {
            this->data = data;
        }
    }

    std::string toString() const;

    std::string creaData() const;

    virtual bool esegui(ContoCorrente* conto) = 0;

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