#ifndef MAIN_CPP_UTENTE_H
#define MAIN_CPP_UTENTE_H

#include "ContoCorrente.h"


class Utente {

private:
    std::string id;
    std::vector<std::shared_ptr<ContoCorrente>> contiCorrente;

public:
    Utente() {}
    Utente(const std::string &id) : id(id) {}

    bool invia(const std::string &idConto, Utente &destinatario, const std::string &idContoDest, float importo, const std::string &descrizione= "Invio");

    bool preleva(const std::string &idConto, float importo, const std::string &idDestinatario="", const std::string &descrizione="Prelievo");

    bool deposita(const std::string &idConto, float importo, const std::string &idMittente="", const std::string &descrizione="Deposito");

    bool aggiungiConto(const std::string &idConto, float saldoIniziale=0);

    bool aggiungiConto(std::shared_ptr<ContoCorrente> conto);

    bool eliminaConto(const std::string &idConto);

    std::shared_ptr<ContoCorrente> getConto(const std::string &idConto);

    std::vector<std::shared_ptr<ContoCorrente>> getConti() {
        return contiCorrente;
    }

    std::string getID() const {
        return id;
    }

};


#endif //MAIN_CPP_UTENTE_H
