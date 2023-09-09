#ifndef MAIN_CPP_TRANSAZIONE_H
#define MAIN_CPP_TRANSAZIONE_H

// macro per stampare i float con 2 cifre decimali
#define FIXED_FLOAT(x) std::fixed << std::setprecision(2) << x


#include <utility>

#include "Data.h"



class Transazione {

private:
    float importo;
    Data data;
    std::string descrizione;
    std::string tipoTransazione;
    std::string controparte;

public:
    Transazione() {}

    Transazione(std::string descrizione, float importo, std::string tipo, std::string controparte="",
                const std::string &data="") :
                    descrizione(std::move(descrizione)), importo(importo), tipoTransazione(std::move(tipo)), controparte(std::move(controparte)) {

        for (char &c: tipoTransazione) {
            c = std::tolower(c);
        }
        if ( data.empty() ) {
            this->data = *(new Data());
        }
        else {
            this->data = *(new Data(data));
        }
    }

    std::string toString() const;

    void modifica(const std::string &campo, const std::string &nuovaStringa);

    bool operator==(const Transazione& other) const;

    float getImporto() const {
        return importo;
    }

    const Data &getData() const {
        return data;
    }

    const std::string &getTipoTransazione() const {
        return tipoTransazione;
    }

    const std::string &getControparte() const {
        return controparte;
    }

    const std::string &getDescrizione() const {
        return descrizione;
    }

    void setImporto(float importo) {
        Transazione::importo = importo;
    }

    void setData(const std::string &data) {
        Transazione::data = *(new Data(data));
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