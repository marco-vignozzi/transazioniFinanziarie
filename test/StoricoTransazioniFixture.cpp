#include <gtest/gtest.h>
#include "../Utente.h"


class StoricoTransazioniSuite : public ::testing::Test {

protected:
    void SetUp() override {
        Utente* marco = new Utente("Marco");
        std::shared_ptr<ContoCorrente> contoMarco(new ContoCorrente("uno", 10.0));

        marco->aggiungiConto(contoMarco);

        marco->getConto("uno")->setPercorsoFile("../../test/docs/storico1.txt");
        marco->getConto("uno")->caricaDati();
    }

    Data dataVecchia = *new Data("2020-8-22 15:18:00");
    Data dataMedia = *new Data("2022-2-22 15:18:00");
    Data dataNuova = *new Data("2023-8-22 15:17:43");

    Utente* marco;
};


TEST_F(StoricoTransazioniSuite, RicercaData) {
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni(dataVecchia).getTransazioni().size(), 2);
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni(dataMedia).getTransazioni().size(), 4);
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni(dataMedia, dataVecchia).getTransazioni().size(), 2);
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni(dataNuova, dataMedia).getTransazioni().size(), 2);
}

TEST_F(StoricoTransazioniSuite, RicercaTipoTransazione) {
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni("uscita").getTransazioni().size(), 3);
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni("ingresso").getTransazioni().size(), 4);
}

TEST_F(StoricoTransazioniSuite, RicercaControparte) {
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni("Giovanni", "controparte").getTransazioni().size(), 1);
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni("", "controparte").getTransazioni().size(), 2);
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni("Laura", "controparte").getTransazioni().size(), 0);
}

TEST_F(StoricoTransazioniSuite, RicercaDescrizione) {
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni("Invio", "descrizione").getTransazioni().size(), 3);
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni("Deposito", "descrizione").getTransazioni().size(), 1);
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni("", "descrizione").getTransazioni().size(), 7);
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni("Questa descrizione non c'è", "descrizione").getTransazioni().size(), 0);
}

TEST_F(StoricoTransazioniSuite, RicercaImporto) {
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni(50).getTransazioni().size(), 7);
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni(0).getTransazioni().size(), 0);
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni(10, 5).getTransazioni().size(), 2);
}

TEST_F(StoricoTransazioniSuite, RicercaInnestata) {
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni(dataMedia).cercaTransazioni(5).cercaTransazioni("Marco", "controparte").getTransazioni().size(), 1);
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni(dataMedia).cercaTransazioni(5).cercaTransazioni("Invio", "descrizione").getTransazioni().size(), 3);
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni(dataMedia).cercaTransazioni(5).cercaTransazioni("uscita", "tipo").getTransazioni().size(), 2);
}

TEST_F(StoricoTransazioniSuite, Eliminazione) {
    StoricoTransazioni transDaEliminare = marco->getConto("uno")->getStoricoTransazioni().cercaTransazioni("uscita");
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().getTransazioni().size(), 7);
    marco->getConto("uno")->getStoricoTransazioni().eliminaTransazioni(transDaEliminare.getTransazioni());
    // verifico che abbia eliminato tutte le transazioni in uscita
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().getTransazioni().size(), 4);
    marco->getConto("uno")->getStoricoTransazioni().eliminaTransazioni(marco->getConto("uno")->getStoricoTransazioni().getTransazioni());
    // verifico che abbia eliminato anche tutte le transazioni in ingresso
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().getTransazioni().size(), 0);
}

