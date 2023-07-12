#include <iostream>
#include <gtest/gtest.h>
#include "../Utente.h"
#include "../Transazione.h"


TEST(Invio, SaldoFinale) {
    Utente* marco = new Utente("Marco");
    Utente* giovanni = new Utente("Giovanni");
    ContoCorrente* contoMarco = new ContoCorrente(marco -> getID(), 10.0);
    ContoCorrente* contoGiovanni = new ContoCorrente(giovanni -> getID());

    marco -> setContoCorrente(contoMarco);
    giovanni ->setContoCorrente(contoGiovanni);

    marco -> getContoCorrente().invia(4.0, contoGiovanni);

    EXPECT_EQ( giovanni -> getContoCorrente().getSaldo(), 4.0 );
    EXPECT_EQ( marco -> getContoCorrente().getSaldo(), 6.0 );
}

TEST(Invio, LunghezzaStoricoTransazioni) {
    Utente* marco = new Utente("Marco");
    Utente* giovanni = new Utente("Giovanni");
    ContoCorrente* contoMarco = new ContoCorrente(marco -> getID(), 10.0);
    ContoCorrente* contoGiovanni = new ContoCorrente(giovanni -> getID());

    marco -> setContoCorrente(contoMarco);
    giovanni ->setContoCorrente(contoGiovanni);

    marco -> getContoCorrente().invia(4.0, contoGiovanni);
    marco -> getContoCorrente().invia(2, contoGiovanni);

    EXPECT_EQ( giovanni -> getContoCorrente().getStoricoTransazioni().size(), 2);
    EXPECT_EQ( marco -> getContoCorrente().getStoricoTransazioni().size(), 2);
}