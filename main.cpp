#include <iostream>
#include "Utente.h"


int main() {
    Utente *marco = new Utente("Marco");
    Utente *giovanni = new Utente("Giovanni");
    Utente *gemma = new Utente("Gemma");
    ContoCorrente *contoMarco = new ContoCorrente(marco->getID(), 10.0);
    ContoCorrente *contoGiovanni = new ContoCorrente(giovanni->getID());
    ContoCorrente *contoGemma = new ContoCorrente(gemma->getID(), 20.3);

    marco->setContoCorrente(contoMarco);
    giovanni->setContoCorrente(contoGiovanni);
    gemma->setContoCorrente(contoGemma);
    marco->getContoCorrente().setPercorsoFile("../test/docs/contoMarco.txt");
    giovanni->getContoCorrente().setPercorsoFile("../docs/contoGiovanni.txt");
    gemma->getContoCorrente().setPercorsoFile("../docs/contoGemma.txt");

//    marco->getContoCorrente().caricaDati();
//    giovanni->getContoCorrente().caricaDati();

//    std::cout << marco -> getContoCorrente().getStoricoToString() << std::endl;

    marco->getContoCorrente().invia(5.0, &(giovanni->getContoCorrente()));
    marco->getContoCorrente().invia(5.0, &(gemma->getContoCorrente()));
    giovanni->getContoCorrente().invia(4, &(marco->getContoCorrente()));
    marco->getContoCorrente().deposita(14.8);
    marco->getContoCorrente().preleva(3);
    gemma->getContoCorrente().preleva(20.1);
    gemma->getContoCorrente().invia(3.8, &(giovanni->getContoCorrente()));

    //std::cout << "Soldi di marco: " << marco->getContoCorrente().getSaldo() << std::endl;
    //std::cout << "Soldi di giovanni: " << giovanni->getContoCorrente().getSaldo() << std::endl;
    //std::cout << "Soldi di gemma: " << sergio->getContoCorrente().getSaldo() << std::endl;

    marco->getContoCorrente().salvaDati();
    giovanni->getContoCorrente().salvaDati();
    gemma->getContoCorrente().salvaDati();
}

