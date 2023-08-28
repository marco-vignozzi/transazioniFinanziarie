#include "Utente.h"


int main() {

    Utente marco = *new Utente("Marco");
    Utente giovanni = *new Utente("Giovanni");
    Utente gemma = *new Utente("Gemma");
    std::shared_ptr<ContoCorrente> contoMarco1 = std::make_shared<ContoCorrente>("uno", 10.0);
    std::shared_ptr<ContoCorrente> contoMarco2 = std::make_shared<ContoCorrente>("due", 500.0);
    std::shared_ptr<ContoCorrente> contoGiovanni = std::make_shared<ContoCorrente>("uno");
    std::shared_ptr<ContoCorrente> contoGemma = std::make_shared<ContoCorrente>("uno", 20.3);


    marco.aggiungiConto(contoMarco1);
    marco.aggiungiConto(contoMarco2);
    giovanni.aggiungiConto(contoGiovanni);
    gemma.aggiungiConto(contoGemma);
    marco.getConto("uno")->setPercorsoFile("../test/docs/contoMarco1.txt");
    marco.getConto("due")->setPercorsoFile("../test/docs/contoMarco2.txt");
    giovanni.getConto("uno")->setPercorsoFile("../docs/contoGiovanni.txt");
    gemma.getConto("uno")->setPercorsoFile("../docs/contoGemma.txt");

    marco.invia("uno", giovanni, "uno", 5.0);
    marco.invia("uno", gemma, "uno", 5.0);
    giovanni.invia("uno", marco, "uno", 4);
    marco.deposita("uno", 14.8);
    marco.preleva("uno", 3);
    gemma.preleva("uno", 20.1);
    gemma.invia("uno", giovanni, "uno", 3.8);

    marco.preleva("due", 100);
    marco.deposita("due", 10);
    marco.invia("due", marco, "uno", 30, "scambio");
    marco.invia("due", marco,"uno", 50,"scambio");
    StoricoTransazioni transazioniCercate = marco.getConto("due")->getStoricoTransazioni().cercaTransazioni("scambio", "descrizione");

    std::cout << "Transazioni prima dell'eliminazione" << std::endl;
    std::cout << marco.getConto("due")->getStoricoTransazioni().toString() << std::endl;
    marco.getConto("due")->getStoricoTransazioni().eliminaTransazioni(transazioniCercate.getTransazioni());
    std::cout << "Transazioni eliminate" << std::endl;
    std::cout << transazioniCercate.toString() << std::endl;
    std::cout << "Transazioni rimaste" << std::endl;
    std::cout << marco.getConto("due")->getStoricoTransazioni().toString() << std::endl;


    marco.getConto("uno")->salvaDati();
    marco.getConto("due")->salvaDati();
    giovanni.getConto("uno")->salvaDati();
    gemma.getConto("uno")->salvaDati();
}

