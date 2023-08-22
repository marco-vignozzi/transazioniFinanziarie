#include <gtest/gtest.h>
#include "../Utente.h"


TEST(TransazioneSuite, Modifica) {
    std::shared_ptr<Transazione> transazioneIngresso = std::make_shared<Transazione>("transazione in ingresso", 10, "ingresso", "Pino");
    std::shared_ptr<Transazione> transazioneUscita = std::make_shared<Transazione>("transazione in uscita", 2, "uscita", "Giorgia");
    std::string nuovaDescrizione = "nuova descrizione";
    std::string nuovaControparte = "Piero";

    transazioneIngresso->modifica("descrizione", nuovaDescrizione);
    ASSERT_EQ(transazioneIngresso->getDescrizione(), nuovaDescrizione);
    transazioneUscita->modifica("controparte", nuovaControparte);
    ASSERT_EQ(transazioneUscita->getControparte(), nuovaControparte);
}