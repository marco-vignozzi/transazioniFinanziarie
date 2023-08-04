#include "Utente.h"


int main() {
    Utente *marco = new Utente("Marco");
    Utente *giovanni = new Utente("Giovanni");
    Utente *gemma = new Utente("Gemma");
    std::shared_ptr<ContoCorrente> contoMarco1( new ContoCorrente(marco->getID(), "uno", 10.0) );
    std::shared_ptr<ContoCorrente> contoMarco2( new ContoCorrente(marco->getID(), "due", 500.0) );
    std::shared_ptr<ContoCorrente> contoGiovanni( new ContoCorrente(giovanni->getID(), "uno") );
    std::shared_ptr<ContoCorrente> contoGemma( new ContoCorrente(gemma->getID(), "uno", 20.3) );

    marco->aggiungiConto(contoMarco1);
    giovanni->aggiungiConto(contoGiovanni);
    gemma->aggiungiConto(contoGemma);
    marco->getConto("uno")->setPercorsoFile("../test/docs/contoMarco1.txt");
    giovanni->getConto("uno")->setPercorsoFile("../docs/contoGiovanni.txt");
    gemma->getConto("uno")->setPercorsoFile("../docs/contoGemma.txt");

//    marco->getContoCorrente().caricaDati();
//    giovanni->getContoCorrente().caricaDati();

//    std::cout << marco -> getContoCorrente().getStoricoToString() << std::endl;

    marco->getConto("uno")->invia(5.0, giovanni->getConto("uno"));
    marco->getConto("uno")->invia(5.0, gemma->getConto("uno"));
    giovanni->getConto("uno")->invia(4, marco->getConto("uno"));
    marco->getConto("uno")->deposita(14.8);
    marco->getConto("uno")->preleva(3);
    gemma->getConto("uno")->preleva(20.1);
    gemma->getConto("uno")->invia(3.8, giovanni->getConto("uno"));

    //std::cout << "Soldi di marco: " << marco->getContoCorrente().getSaldo() << std::endl;
    //std::cout << "Soldi di giovanni: " << giovanni->getContoCorrente().getSaldo() << std::endl;
    //std::cout << "Soldi di gemma: " << sergio->getContoCorrente().getSaldo() << std::endl;

    marco->getConto("uno")->salvaDati();
    giovanni->getConto("uno")->salvaDati();
    gemma->getConto("uno")->salvaDati();
}

