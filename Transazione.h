#ifndef MAIN_CPP_TRANSAZIONE_H
#define MAIN_CPP_TRANSAZIONE_H

#include "ContoCorrente.h"


class Transazione {

protected:
    float importo;
    std::string data;
    std::string descrizione;
    std::string tipoTransazione;
    std::string controparte;

public:
    Transazione() {}

    Transazione(const std::string &descrizione, float importo, const std::string &tipo, const std::string &controparte="",
                const std::string &data="") :
                    descrizione(descrizione), importo(importo), tipoTransazione(tipo), controparte(controparte)
    {
        for (char &c: tipoTransazione) {
            c = std::tolower(c);
        }
        if ( data.empty() ) {
            this->data = creaData();
        }
        else {
            this->data = data;
        }
    }

    std::string toString() const;

    std::string creaData() const;

    std::string getDescrizione() const {
        return descrizione;
    }

    float getImporto() const {
        return importo;
    }

    std::string getData() const {
        return data;
    }

    void setImporto(float importo) {
        Transazione::importo = importo;
    }

    void setData(const std::string &data) {
        Transazione::data = data;
    }

    void setDescrizione(const std::string &descrizione) {
        Transazione::descrizione = descrizione;
    }

    void setTipoTransazione(const std::string &tipoTransazione) {
        Transazione::tipoTransazione = tipoTransazione;
    }

    void setControparte(const std::string &controparte) {
        Transazione::controparte = controparte;
    }

};


#endif // MAIN_CPP_TRANSAZIONE_H