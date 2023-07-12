#include <gtest/gtest.h>
#include "../Utente.h"


class ContoCorrenteSuite : public ::testing::Test {

protected:
    void SetUp() override {
        marco = new Utente("Marco");
        giovanni = new Utente("Giovanni");
        ContoCorrente *contoMarco = new ContoCorrente(marco->getID(), 10.0);
        ContoCorrente *contoGiovanni = new ContoCorrente(giovanni->getID());

        marco->setContoCorrente(contoMarco);
        giovanni->setContoCorrente(contoGiovanni);
    }

    Utente* marco;
    Utente* giovanni;
};


TEST_F(ContoCorrenteSuite, InvioPositivo) {
    marco -> getContoCorrente().invia(10, &(giovanni -> getContoCorrente()));

    EXPECT_EQ( marco -> getContoCorrente().getSaldo(), 0 );
    EXPECT_EQ( giovanni -> getContoCorrente().getSaldo(), 10 );
}

TEST_F(ContoCorrenteSuite, InvioNegativo) {
    marco -> getContoCorrente().invia(-10, &(giovanni -> getContoCorrente()));

    EXPECT_EQ( marco -> getContoCorrente().getSaldo(), 10 );
    EXPECT_EQ( giovanni -> getContoCorrente().getSaldo(), 0 );
}

TEST_F(ContoCorrenteSuite, InvioNullo) {
    marco -> getContoCorrente().invia(0, &(giovanni -> getContoCorrente()));

    EXPECT_EQ( marco -> getContoCorrente().getSaldo(), 10 );
    EXPECT_EQ( giovanni -> getContoCorrente().getSaldo(), 0 );
}

TEST_F(ContoCorrenteSuite, InvioFondiInsufficienti) {
    marco -> getContoCorrente().invia(10.1, &(giovanni -> getContoCorrente()));

    EXPECT_EQ( marco -> getContoCorrente().getSaldo(), 10 );
    EXPECT_EQ( giovanni -> getContoCorrente().getSaldo(), 0 );
}

TEST_F(ContoCorrenteSuite, NumeroTransazioniInvio) {
    ASSERT_EQ( giovanni -> getContoCorrente().getStoricoTransazioni().size(), 0);
    ASSERT_EQ( marco -> getContoCorrente().getStoricoTransazioni().size(), 0);

    marco -> getContoCorrente().invia(1, &(giovanni -> getContoCorrente()));
    marco -> getContoCorrente().invia(1, &(giovanni -> getContoCorrente()));
    marco -> getContoCorrente().invia(0, &(giovanni -> getContoCorrente()));
    marco -> getContoCorrente().invia(-1, &(giovanni -> getContoCorrente()));

    EXPECT_EQ( giovanni -> getContoCorrente().getStoricoTransazioni().size(), 2);
    EXPECT_EQ( marco -> getContoCorrente().getStoricoTransazioni().size(), 2);
}

TEST_F(ContoCorrenteSuite, NumeroTransazioniPrelievo) {
    ASSERT_EQ( marco -> getContoCorrente().getStoricoTransazioni().size(), 0);

    marco -> getContoCorrente().preleva(1);
    marco -> getContoCorrente().preleva(1);
    marco -> getContoCorrente().preleva(0);
    marco -> getContoCorrente().preleva(-1);

    EXPECT_EQ( marco -> getContoCorrente().getStoricoTransazioni().size(), 2);
}

TEST_F(ContoCorrenteSuite, NumeroTransazioniDeposito) {
    ASSERT_EQ( marco -> getContoCorrente().getStoricoTransazioni().size(), 0);

    marco -> getContoCorrente().deposita(1);
    marco -> getContoCorrente().deposita(1);
    marco -> getContoCorrente().deposita(0);
    marco -> getContoCorrente().deposita(-1);

    EXPECT_EQ( marco -> getContoCorrente().getStoricoTransazioni().size(), 2);
}

TEST_F(ContoCorrenteSuite, CopiaContoCorrente) {
    ASSERT_EQ( marco -> getContoCorrente().getStoricoTransazioni().size(), 0);
    ASSERT_EQ( marco -> getContoCorrente().getSaldo(), 10 );
    ASSERT_EQ( giovanni -> getContoCorrente().getStoricoTransazioni().size(), 0);
    ASSERT_EQ( giovanni -> getContoCorrente().getSaldo(), 0 );

    marco -> getContoCorrente().preleva(1);
    giovanni -> setContoCorrente(&(marco -> getContoCorrente()));


    EXPECT_EQ( giovanni -> getContoCorrente().getStoricoTransazioni().size(), 1);
    EXPECT_EQ( giovanni -> getContoCorrente().getSaldo(), 9 );
}