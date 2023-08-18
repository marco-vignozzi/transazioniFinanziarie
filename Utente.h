#ifndef MAIN_CPP_UTENTE_H
#define MAIN_CPP_UTENTE_H

#include "ContoCorrente.h"


class Utente {

private:
    std::string id;
    std::vector<std::shared_ptr<ContoCorrente>> contiCorrenti;

public:
    Utente(const std::string &id) : id(id) {}

    void aggiungiConto(std::shared_ptr<ContoCorrente> conto) {
        this -> contiCorrenti.push_back(conto);
    }

    std::vector<std::shared_ptr<ContoCorrente>> getConti() {
        return contiCorrenti;
    }

    std::shared_ptr<ContoCorrente> getConto(std::string idConto) {
        for(const auto &conto: contiCorrenti) {
            if ( conto->getID() == idConto ) {
                return conto;
            }
        }
        return nullptr;
    }

    std::string getID() const {
        return id;
    }

};


#endif //MAIN_CPP_UTENTE_H
