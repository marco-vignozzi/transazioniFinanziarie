#include "StoricoTransazioni.h"


std::string StoricoTransazioni::toString() const {
    std::ostringstream oss;
    for(const auto &transazione : transazioni) {
        oss << transazione->toString();
    }
    return oss.str();
}


StoricoTransazioni &StoricoTransazioni::cercaTransazioni(float importoMax, float importoMin) const {
    StoricoTransazioni &nuovoStorico = *new StoricoTransazioni();
    for( const auto &transazione : transazioni ) {
        if (transazione->getImporto() <= importoMax && transazione->getImporto() >= importoMin) {
            nuovoStorico.aggiungiTransazione(transazione);
        }
    }
    return nuovoStorico;
}

StoricoTransazioni &StoricoTransazioni::cercaTransazioni(Data dataMax, Data dataMin) const {
    StoricoTransazioni &nuovoStorico = *new StoricoTransazioni();
    for( const auto &transazione : transazioni ) {
        if ( transazione->getData() < *(new Data(dataMax)) &&
             transazione->getData() > *(new Data(dataMin)) ) {
            nuovoStorico.aggiungiTransazione(transazione);
        }
    }
    return nuovoStorico;
}

StoricoTransazioni &StoricoTransazioni::cercaTransazioni(const std::string &parolaCercata, const std::string &tipoRicerca) const {
    if(tipoRicerca == "tipo") {
        return ricercaTipoTrans(parolaCercata);
    }
    else if(tipoRicerca == "controparte") {
        return ricercaControparte(parolaCercata);
    }
    else if(tipoRicerca == "descrizione") {
        return ricercaDescrizione(parolaCercata);
    }
    else {
        std::cout << "Tipo di ricerca non disponibile." << std::endl;
        std::cout << "Tipi di ricerca possibili: 'tipo', 'controparte' e 'descrizione'." << std::endl;
        return *new StoricoTransazioni();
    }
}

StoricoTransazioni &StoricoTransazioni::ricercaTipoTrans(const std::string &tipoTrans) const {
    StoricoTransazioni &nuovoStorico = *new StoricoTransazioni();
    for( const auto &transazione : transazioni) {
        if ( transazione->getTipoTransazione() == tipoTrans )
            nuovoStorico.aggiungiTransazione(transazione);
    }
    return nuovoStorico;
}

StoricoTransazioni &StoricoTransazioni::ricercaControparte(const std::string &controparte) const {
    StoricoTransazioni &nuovoStorico = *new StoricoTransazioni();
    for( const auto &transazione : transazioni ) {
        if ( transazione->getControparte() == controparte ) {
            nuovoStorico.aggiungiTransazione(transazione);
        }
    }
    return nuovoStorico;
}

StoricoTransazioni &StoricoTransazioni::ricercaDescrizione(const std::string &descrizione) const {
    StoricoTransazioni &nuovoStorico = *new StoricoTransazioni();
    for( const auto &transazione : transazioni ) {
        if ( transazione->getDescrizione().find(descrizione) != std::string::npos ) {
            nuovoStorico.aggiungiTransazione(transazione);
        }
    }
    return nuovoStorico;
}

bool StoricoTransazioni::eliminaTransazione(std::shared_ptr<Transazione> transazione) {
    for( auto it = transazioni.begin(); it != transazioni.end(); ++it ) {
        if (**it == *transazione) {
            transazioni.erase(it);
            return true;
        }
    }
    return false;
}

void StoricoTransazioni::eliminaTransazioni(std::vector<std::shared_ptr<Transazione>> transazioni) {
    for( auto it = transazioni.begin(); it != transazioni.end(); ++it ) {
        eliminaTransazione(*it);
        }
}
