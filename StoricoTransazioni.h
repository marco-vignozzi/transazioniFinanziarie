#ifndef README_MD_STORICOTRANSAZIONI_H
#define README_MD_STORICOTRANSAZIONI_H

#include <memory>
#include <vector>
#include "Transazione.h"

class StoricoTransazioni {
private:
    std::vector<std::shared_ptr<Transazione>> transazioni;

public:
    StoricoTransazioni() {}

    std::string toString() const;

    StoricoTransazioni &cercaTransazioni(float importoMax, float importoMin=0.0) const;

    StoricoTransazioni &cercaTransazioni(Data dataMax, Data dataMin=*(new Data("1900-01-01 00:00:00"))) const;

    StoricoTransazioni &cercaTransazioni(std::string parolaCercata, std::string tipoRicerca="tipo") const;

    StoricoTransazioni &ricercaTipoTrans(std::string tipoTrans) const;

    StoricoTransazioni &ricercaControparte(std::string controparte) const;

    StoricoTransazioni &ricercaDescrizione(std::string descrizione) const;

    bool eliminaTransazione(std::shared_ptr<Transazione> transazione);

    void eliminaTransazioni(std::vector<std::shared_ptr<Transazione>> transazioni);

    void aggiungiTransazione(std::shared_ptr<Transazione> transazione) {
        transazioni.push_back(transazione);
    }

    std::vector<std::shared_ptr<Transazione>> &getTransazioni() {
        return transazioni;
    }
};


#endif //README_MD_STORICOTRANSAZIONI_H
