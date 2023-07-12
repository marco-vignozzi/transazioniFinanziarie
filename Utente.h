#ifndef MAIN_CPP_UTENTE_H
#define MAIN_CPP_UTENTE_H

#include <iostream>
#include "ContoCorrente.h"

class Utente {
private:
    std::string id;
    ContoCorrente conto;
public:
    Utente(ContoCorrente& conto, std::string id) : conto(conto), id(id) {}

    std::string getID() const {
        return id;
    }
};


#endif //MAIN_CPP_UTENTE_H
