#include <gtest/gtest.h>
#include <fstream>
#include "../Utente.h"


class ContoCorrenteSuite : public ::testing::Test {

protected:
    void SetUp() override {
        marco = new Utente("Marco");
        giovanni = new Utente("Giovanni");
        std::shared_ptr<ContoCorrente> contoMarco( new ContoCorrente(marco->getID(), "uno", 10.0) );
        std::shared_ptr<ContoCorrente> contoGiovanni( new ContoCorrente(giovanni->getID(), "uno") );

        marco->aggiungiConto(contoMarco);
        giovanni->aggiungiConto(contoGiovanni);
    }

    // Questo metodo è utilizzato per confrontare il contenuto di 2 file.
    // Se è uguale ritorna "true", altrimenti "false".
    bool confrontaContenutoFile(const std::string &percorso1, const std::string &percorso2) const {
        std::ifstream file1(percorso1);
        std::ifstream file2(percorso2);
        std::ostringstream contenutoFile1;
        std::ostringstream contenutoFile2;

        if ( file1.is_open() ) {
            std::string linea;
            while ( std::getline(file1, linea) ) {
                contenutoFile1 << linea << std::endl;
            }
            file1.close();
        } else {
            std::cout << "Impossibile aprire il file: " << percorso1 << std::endl;
            return false;
        }
        if ( file2.is_open() ) {
            std::string linea;
            while ( std::getline(file2, linea) ) {
                contenutoFile2 << linea << std::endl;
            }
            file2.close();
        } else {
            std::cout << "Impossibile aprire il file: " << percorso2 << std::endl;
            return false;
        }
        if ( contenutoFile1.str() == contenutoFile2.str() ) {
            return true;
        }
        return false;
    }

    Utente* marco;
    Utente* giovanni;
};


TEST_F(ContoCorrenteSuite, InvioPositivo) {
    ASSERT_TRUE( marco -> getConto("uno")->invia(10, giovanni -> getConto("uno")) );

    EXPECT_EQ( marco -> getConto("uno")->getSaldo(), 0 );
    EXPECT_EQ( giovanni -> getConto("uno")->getSaldo(), 10 );
}

TEST_F(ContoCorrenteSuite, InvioNegativo) {
    ASSERT_FALSE( marco -> getConto("uno")->invia(-10, giovanni -> getConto("uno")) );

    EXPECT_EQ( marco -> getConto("uno")->getSaldo(), 10 );
    EXPECT_EQ( giovanni -> getConto("uno")->getSaldo(), 0 );
}

TEST_F(ContoCorrenteSuite, InvioNullo) {
    ASSERT_FALSE( marco -> getConto("uno")->invia(0, giovanni -> getConto("uno")) );

    EXPECT_EQ( marco -> getConto("uno")->getSaldo(), 10 );
    EXPECT_EQ( giovanni -> getConto("uno")->getSaldo(), 0 );
}

TEST_F(ContoCorrenteSuite, InvioFondiInsufficienti) {
    ASSERT_FALSE(marco -> getConto("uno")->invia(10.1, giovanni -> getConto("uno")));

    EXPECT_EQ( marco -> getConto("uno")->getSaldo(), 10 );
    EXPECT_EQ( giovanni -> getConto("uno")->getSaldo(), 0 );
}

TEST_F(ContoCorrenteSuite, NumeroTransazioniInvio) {
    ASSERT_EQ( giovanni -> getConto("uno")->getStoricoTransazioni().size(), 0);
    ASSERT_EQ( marco -> getConto("uno")->getStoricoTransazioni().size(), 0);

    ASSERT_TRUE(marco -> getConto("uno")->invia(1, giovanni -> getConto("uno")));
    ASSERT_TRUE(marco -> getConto("uno")->invia(1, giovanni -> getConto("uno")));
    ASSERT_FALSE(marco -> getConto("uno")->invia(0, giovanni -> getConto("uno")));
    ASSERT_FALSE(marco -> getConto("uno")->invia(-1, giovanni -> getConto("uno")));

    EXPECT_EQ( giovanni -> getConto("uno")->getStoricoTransazioni().size(), 2);
    EXPECT_EQ( marco -> getConto("uno")->getStoricoTransazioni().size(), 2);
}

TEST_F(ContoCorrenteSuite, NumeroTransazioniPrelievo) {
    ASSERT_EQ( marco -> getConto("uno")->getStoricoTransazioni().size(), 0);

    ASSERT_TRUE(marco -> getConto("uno")->preleva(1));
    ASSERT_TRUE(marco -> getConto("uno")->preleva(1));
    ASSERT_FALSE(marco -> getConto("uno")->preleva(0));
    ASSERT_FALSE(marco -> getConto("uno")->preleva(-1));

    EXPECT_EQ( marco -> getConto("uno")->getStoricoTransazioni().size(), 2);
}

TEST_F(ContoCorrenteSuite, NumeroTransazioniDeposito) {
    ASSERT_EQ( marco -> getConto("uno")->getStoricoTransazioni().size(), 0);

    ASSERT_TRUE(marco -> getConto("uno")->deposita(1));
    ASSERT_TRUE(marco -> getConto("uno")->deposita(1));
    ASSERT_FALSE(marco -> getConto("uno")->deposita(0));
    ASSERT_FALSE(marco -> getConto("uno")->deposita(-1));

    EXPECT_EQ( marco -> getConto("uno")->getStoricoTransazioni().size(), 2);
}


// Questo test verifica che il caricamento da file dei dati di un conto corrente funzioni correttamente.
// Per farlo carica i dati dal percorso file "test/docs/contoMarco.txt" nel conto dell'utente "marco" e
// li salva nel nuovo percorso "test/docs/nuovaCopiaContoMarco.txt", per poi controllare l'uguaglianza dei due file.
TEST_F(ContoCorrenteSuite, CaricaDatiContoVuoto) {
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().size(), 0);
    std::string percorsoFile = "../../test/docs/contoMarco1.txt";
    std::string nuovoPercorso = "../../test/docs/nuovaCopiaContoMarco.txt";

    marco->getConto("uno")->setPercorsoFile(percorsoFile);
    ASSERT_TRUE(marco->getConto("uno")->caricaDati());
    marco->getConto("uno")->setPercorsoFile(nuovoPercorso);
    ASSERT_TRUE(marco->getConto("uno")->salvaDati());

    EXPECT_TRUE(confrontaContenutoFile(percorsoFile, nuovoPercorso));
}

// in questo test ci si aspetta che i dati del conto vengano sovrascritti con quelli caricati da file.
TEST_F(ContoCorrenteSuite, CaricaDatiContoNonVuoto) {
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().size(), 0);
    ASSERT_TRUE(marco->getConto("uno")->deposita(10));
    ASSERT_EQ(marco->getConto("uno")->getStoricoTransazioni().size(), 1);
    std::string percorsoFile = "../../test/docs/contoMarco1.txt";
    std::string nuovoPercorso = "../../test/docs/nuovaCopiaContoMarco.txt";

    marco->getConto("uno")->setPercorsoFile(percorsoFile);
    ASSERT_TRUE(marco->getConto("uno")->caricaDati());
    marco->getConto("uno")->setPercorsoFile(nuovoPercorso);
    ASSERT_TRUE(marco->getConto("uno")->salvaDati());

    EXPECT_TRUE(confrontaContenutoFile(percorsoFile, nuovoPercorso));
}
