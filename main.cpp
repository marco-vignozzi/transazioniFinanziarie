#include <iostream>
#include "Utente.h"


int main() {
    Utente *marco = new Utente("Marco");
    Utente *giovanni = new Utente("Giovanni");
    ContoCorrente *contoMarco = new ContoCorrente(marco->getID(), 10.0);
    ContoCorrente *contoGiovanni = new ContoCorrente(giovanni->getID());

    marco->setContoCorrente(contoMarco);
    giovanni->setContoCorrente(contoGiovanni);

    marco->getContoCorrente().setPercorsoFile("../contoMarco.txt");
    giovanni->getContoCorrente().setPercorsoFile("../contoGiovanni.txt");

    marco->getContoCorrente().caricaStoricoTransazioni();
    giovanni->getContoCorrente().caricaStoricoTransazioni();

    std::cout << marco -> getContoCorrente().getStoricoToString() << std::endl;
}
    /*
    marco -> getContoCorrente().invia(5.0, contoGiovanni);
    contoMarco->invia(5.0, contoGiovanni);
    contoGiovanni->invia(4, contoMarco);

    std::cout << "Soldi di marco: " << marco->getContoCorrente().getSaldo() << std::endl;
    std::cout << "Soldi di giovanni: " << giovanni->getContoCorrente().getSaldo() << std::endl;

    marco -> getContoCorrente().salvaStoricoTransazioni();
    giovanni -> getContoCorrente().salvaStoricoTransazioni();

    std::string ano = "ano";
    std::cout << ano.size() << std::endl;
}
*/