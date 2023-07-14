#include <iostream>
#include "Utente.h"


int main() {
    Utente *marco = new Utente("Marco");
    Utente *giovanni = new Utente("Giovanni");
    Utente *sergio = new Utente("Sergio");
    ContoCorrente *contoMarco = new ContoCorrente(marco->getID(), 10.0);
    ContoCorrente *contoGiovanni = new ContoCorrente(giovanni->getID());
    ContoCorrente *contoSergio = new ContoCorrente(sergio->getID(), 20.3);

    marco->setContoCorrente(contoMarco);
    giovanni->setContoCorrente(contoGiovanni);
    sergio->setContoCorrente(contoSergio);
    marco->getContoCorrente().setPercorsoFile("../test/docs/contoMarco.txt");
    giovanni->getContoCorrente().setPercorsoFile("../test/docs/contoGiovanni.txt");
    sergio->getContoCorrente().setPercorsoFile("../test/docs/contoSergio.txt");

    //marco->getContoCorrente().caricaStoricoTransazioni();
    //giovanni->getContoCorrente().caricaStoricoTransazioni();

    //std::cout << marco -> getContoCorrente().getStoricoToString() << std::endl;

    marco->getContoCorrente().invia(5.0, &(giovanni->getContoCorrente()));
    marco->getContoCorrente().invia(5.0, &(sergio->getContoCorrente()));
    giovanni->getContoCorrente().invia(4, &(marco->getContoCorrente()));
    marco->getContoCorrente().deposita(14.8);
    marco->getContoCorrente().preleva(3);
    sergio->getContoCorrente().preleva(20.1);
    sergio->getContoCorrente().invia(3.8, &(giovanni->getContoCorrente()));

    //std::cout << "Soldi di marco: " << marco->getContoCorrente().getSaldo() << std::endl;
    //std::cout << "Soldi di giovanni: " << giovanni->getContoCorrente().getSaldo() << std::endl;
    //std::cout << "Soldi di sergio: " << sergio->getContoCorrente().getSaldo() << std::endl;

    marco->getContoCorrente().salvaStoricoTransazioni();
    giovanni->getContoCorrente().salvaStoricoTransazioni();
    sergio->getContoCorrente().salvaStoricoTransazioni();
}

