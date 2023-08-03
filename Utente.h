#ifndef MAIN_CPP_UTENTE_H
#define MAIN_CPP_UTENTE_H

#include "ContoCorrente.h"


class Utente {

private:
    std::string id;
    std::vector<std::shared_ptr<ContoCorrente>> contiCorrente;  // TODO: aggiungere possibilità di più conti

public:
    Utente(const std::string &id) : id(id) {}

    void addConto(std::shared_ptr<ContoCorrente> conto) {
        this -> contiCorrente.push_back(conto);
    }
// TODO: aggiungere possibilità di ricercare un conto per id
    std::vector<std::shared_ptr<ContoCorrente>> getConti(std::string idConto) {
        if ( idConto.empty() ) {
            return contiCorrente;
        }
    }

    std::string getID() const {
        return id;
    }

};


#endif //MAIN_CPP_UTENTE_H
