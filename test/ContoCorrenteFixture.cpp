#include <gtest/gtest.h>
#include <fstream>
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
    ASSERT_TRUE(marco -> getContoCorrente().invia(10, &(giovanni -> getContoCorrente())));

    EXPECT_EQ( marco -> getContoCorrente().getSaldo(), 0 );
    EXPECT_EQ( giovanni -> getContoCorrente().getSaldo(), 10 );
}

TEST_F(ContoCorrenteSuite, InvioNegativo) {
    ASSERT_FALSE(marco -> getContoCorrente().invia(-10, &(giovanni -> getContoCorrente())));

    EXPECT_EQ( marco -> getContoCorrente().getSaldo(), 10 );
    EXPECT_EQ( giovanni -> getContoCorrente().getSaldo(), 0 );
}

TEST_F(ContoCorrenteSuite, InvioNullo) {
    ASSERT_FALSE(marco -> getContoCorrente().invia(0, &(giovanni -> getContoCorrente())));

    EXPECT_EQ( marco -> getContoCorrente().getSaldo(), 10 );
    EXPECT_EQ( giovanni -> getContoCorrente().getSaldo(), 0 );
}

TEST_F(ContoCorrenteSuite, InvioFondiInsufficienti) {
    ASSERT_FALSE(marco -> getContoCorrente().invia(10.1, &(giovanni -> getContoCorrente())));

    EXPECT_EQ( marco -> getContoCorrente().getSaldo(), 10 );
    EXPECT_EQ( giovanni -> getContoCorrente().getSaldo(), 0 );
}

TEST_F(ContoCorrenteSuite, NumeroTransazioniInvio) {
    ASSERT_EQ( giovanni -> getContoCorrente().getStoricoTransazioni().size(), 0);
    ASSERT_EQ( marco -> getContoCorrente().getStoricoTransazioni().size(), 0);

    ASSERT_TRUE(marco -> getContoCorrente().invia(1, &(giovanni -> getContoCorrente())));
    ASSERT_TRUE(marco -> getContoCorrente().invia(1, &(giovanni -> getContoCorrente())));
    ASSERT_FALSE(marco -> getContoCorrente().invia(0, &(giovanni -> getContoCorrente())));
    ASSERT_FALSE(marco -> getContoCorrente().invia(-1, &(giovanni -> getContoCorrente())));

    EXPECT_EQ( giovanni -> getContoCorrente().getStoricoTransazioni().size(), 2);
    EXPECT_EQ( marco -> getContoCorrente().getStoricoTransazioni().size(), 2);
}

TEST_F(ContoCorrenteSuite, NumeroTransazioniPrelievo) {
    ASSERT_EQ( marco -> getContoCorrente().getStoricoTransazioni().size(), 0);

    ASSERT_TRUE(marco -> getContoCorrente().preleva(1));
    ASSERT_TRUE(marco -> getContoCorrente().preleva(1));
    ASSERT_FALSE(marco -> getContoCorrente().preleva(0));
    ASSERT_FALSE(marco -> getContoCorrente().preleva(-1));

    EXPECT_EQ( marco -> getContoCorrente().getStoricoTransazioni().size(), 2);
}

TEST_F(ContoCorrenteSuite, NumeroTransazioniDeposito) {
    ASSERT_EQ( marco -> getContoCorrente().getStoricoTransazioni().size(), 0);

    ASSERT_TRUE(marco -> getContoCorrente().deposita(1));
    ASSERT_TRUE(marco -> getContoCorrente().deposita(1));
    ASSERT_FALSE(marco -> getContoCorrente().deposita(0));
    ASSERT_FALSE(marco -> getContoCorrente().deposita(-1));

    EXPECT_EQ( marco -> getContoCorrente().getStoricoTransazioni().size(), 2);
}

TEST_F(ContoCorrenteSuite, CopiaContoCorrente) {
    ASSERT_EQ( marco -> getContoCorrente().getStoricoTransazioni().size(), 0);
    ASSERT_EQ( marco -> getContoCorrente().getSaldo(), 10 );
    ASSERT_EQ( giovanni -> getContoCorrente().getStoricoTransazioni().size(), 0);
    ASSERT_EQ( giovanni -> getContoCorrente().getSaldo(), 0 );

    ASSERT_TRUE(marco -> getContoCorrente().preleva(1));
    giovanni -> setContoCorrente(&(marco -> getContoCorrente()));

    EXPECT_EQ( giovanni -> getContoCorrente().getStoricoTransazioni().size(), 1);
    EXPECT_EQ( giovanni -> getContoCorrente().getSaldo(), 9 );
}

// Questo test verifica che il caricamento da file dei dati di un conto funzioni correttamente.
// Per farlo carica i dati dal percorso file "test/docs/contoMarco.txt" nel conto dell'utente "marco" e
// li salva nel nuovo percorso "test/docs/nuovaCopiaContoMarco.txt", per poi testare l'uguaglianza dei due file.

TEST_F(ContoCorrenteSuite, CaricaDatiConto) {
    ASSERT_EQ(marco->getContoCorrente().getStoricoTransazioni().size(), 0);
    std::string percorsoFile = "../../test/docs/contoMarco.txt";
    std::string nuovoPercorso = "../../test/docs/nuovaCopiaContoMarco.txt";

    marco->getContoCorrente().setPercorsoFile(percorsoFile);
    ASSERT_TRUE(marco->getContoCorrente().caricaDati());
    marco->getContoCorrente().setPercorsoFile(nuovoPercorso);
    ASSERT_TRUE(marco->getContoCorrente().salvaDati());

    std::ifstream fileVecchio(percorsoFile);
    std::ifstream fileNuovo(nuovoPercorso);
    std::ostringstream contenutoFileVecchio;
    std::ostringstream contenutoFileNuovo;

    if ( fileVecchio.is_open() ) {
        std::string linea;
        while ( std::getline(fileVecchio, linea) ) {
            contenutoFileVecchio << linea << std::endl;
        }
        fileVecchio.close();
    } else {
        std::cout << "Impossibile aprire il file: " << percorsoFile << std::endl;
    }
    if ( fileNuovo.is_open() ) {
        std::string linea;
        while ( std::getline(fileNuovo, linea) ) {
            contenutoFileNuovo << linea << std::endl;
        }
        fileNuovo.close();
    } else {
        std::cout << "Impossibile aprire il file: " << nuovoPercorso << std::endl;
    }
    EXPECT_EQ(contenutoFileNuovo.str(), contenutoFileVecchio.str());
}
