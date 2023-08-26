#include "ContoCorrente.h"


// Questo metodo permette di salvare i dati di un conto corrente (saldo e storico transazioni) in un file ".txt".
// Ritorna "true" se l'operazione va a buon fine, "false" altrimenti.
bool ContoCorrente::salvaDati() const {
    std::ofstream file(percorsoFile);
    if ( file.is_open() ) {
        file << "Storico Transazioni Conto " << this->id << std::endl;
        file << storico.toString() << std::endl;
        file << "Saldo disponibile: " << FIXED_FLOAT(getSaldo()) << " €" << std::endl << std::endl;
        file.close();
        std::cout << "Storico transazioni salvato nel file: " << percorsoFile << std::endl;
        return true;
    }
    else {
        std::cout << "Impossibile aprire il file: " << percorsoFile << std::endl;
        return false;
    }
}

// Questo metodo permette di caricare i dati di un conto corrente (saldo e storico transazioni) da un file ".txt".
// Lo storico delle transazioni del conto che chiama questo metodo verrà sovrascritto, così come il saldo.
// Ritorna "true" se l'operazione va a buon fine, "false" altrimenti.
bool ContoCorrente::caricaDati() {
    //dichiaro variabili utili
    std::ifstream file(percorsoFile);
    size_t pos1;
    size_t pos2;
    std::string stringaCercata;

    //dichiaro variabili che servono a ricreare le transazioni
    std::string importoStr;
    std::string saldoStr;

    if ( file.is_open() ) {
        //svuoto il vettore delle transazioni
        this->storico.getTransazioni().clear();
        std::string linea;
        getline(file, linea);
        while ( getline(file, linea) ) {
            if ( !linea.empty() ) {
                if ( linea.find(" -") != std::string::npos ) {
                    std::shared_ptr<Transazione> transazione = std::make_shared<Transazione>();

                    pos1 = linea.find(" -");                 // cerco la fine della data
                    transazione->setData( linea.substr(0, pos1) );           // salvo la data


                    stringaCercata = "Importo: ";                     // cerco l'importo
                    pos1 = linea.find(stringaCercata) + stringaCercata.size();
                    pos2 = linea.find(" €");
                    importoStr = linea.substr(pos1, pos2 - pos1);       // salvo l'importo
                    transazione->setImporto( stof(importoStr) );

                    stringaCercata = "Descrizione: ";                         // cerco la descrizione
                    pos1 = linea.find(stringaCercata) + stringaCercata.size();
                    transazione->setDescrizione( linea.substr(pos1, linea.size() - pos1) );       // salvo la descrizione

                    stringaCercata = "ingresso - ";           // cerco se è una transazione in ingresso
                    if (linea.find(stringaCercata) != std::string::npos) {
                        pos1 = linea.find(stringaCercata) + stringaCercata.size();
                        if (linea[pos1] == 'M') {                 // vedo se c'è un mittente (altrimenti è un deposito)
                            stringaCercata = "Mittente: ";
                            pos1 += stringaCercata.size();
                            pos2 = linea.find(" -", pos1);
                            transazione->setControparte( linea.substr(pos1, pos2 - pos1) );     // salvo il mittente
                        }
                        transazione->setTipoTransazione( "ingresso" );
                    } else {
                        stringaCercata = "uscita - Destinatario: ";             // cerco se c'è il destinatario
                        if (linea.find(stringaCercata) != std::string::npos) {
                            pos1 = linea.find(stringaCercata) + stringaCercata.size();
                            pos2 = linea.find(" -", pos1);
                            transazione->setControparte( linea.substr(pos1, pos2 - pos1) );     // salvo il destinatario
                        }
                        transazione->setTipoTransazione( "uscita" );
                    }
                    this->storico.aggiungiTransazione(transazione);
                }
                else {
                    stringaCercata = ": ";
                    pos1 = linea.find(stringaCercata) + stringaCercata.size();
                    if ( pos1 != std::string::npos ) {
                        pos2 = linea.find(" €");
                        saldoStr = linea.substr(pos1, pos2 - pos1);
                        this->saldo = stof(saldoStr);
                    }
                }
            }
        }
        file.close();
        std::cout << "Storico transazioni caricato dal file: " << this->percorsoFile << std::endl;
        return true;
    }
    else {
        std::cout << "Impossibile aprire il file: " << this->percorsoFile << std::endl;
        return false;
    }
}

void ContoCorrente::aggiungiTransazione(std::shared_ptr<Transazione> &transazione) {
    if(transazione->getTipoTransazione() == "ingresso") {
        saldo += transazione->getImporto();
    }
    else {
        saldo -= transazione->getImporto();
    }
    storico.aggiungiTransazione(transazione);
}
