#ifndef MAIN_CPP_UTENTE_H
#define MAIN_CPP_UTENTE_H

#include <iostream>
#include "ContoCorrente.h"


class Utente {

private:
    std::string id;
    ContoCorrente *conto;

public:
    Utente(const std::string &id) : id(id) {
        conto = new ContoCorrente();
    }

    void setContoCorrente(ContoCorrente *conto) {
        this -> conto = conto;
    }

    ContoCorrente &getContoCorrente() {
        return *conto;
    }

    std::string getID() const {
        return id;
    }

};


#endif //MAIN_CPP_UTENTE_H
