#include <fstream>
#include "ContoCorrente.h"
#include "TransazioneIngresso.h"
#include "TransazioneUscita.h"


// Questo metodo esegue lo scambio di fondi tra due conti. Lo scambio è effettuato eseguendo un prelievo (se possibile)
// dal conto chiamante seguito da un deposito sul conto "destinatario", passato come parametro.
// Vengono create ed eseguite due transizioni, in ingresso per il destinatario e in uscita per il chiamante.
// Ritorna "true" se l'operazione va a buon fine, "false" altrimenti.
bool ContoCorrente::invia(float importo, ContoCorrente *destinatario, const std::string &descrizione) {
    if ( importo <= 0 ) {
       std::cout << "Impossibile inviare quantità negative o nulle di denaro." << std::endl;
        return false;
    }
    Transazione *transMittente = new TransazioneUscita(descrizione, importo, destinatario->getIDUtente());
    Transazione *transDestinatario = new TransazioneIngresso(descrizione, importo, getIDUtente());
    if ( transMittente->esegui(this) ) {
        transDestinatario->esegui(destinatario);
        return true;
    }
    return false;
}

// Questo metodo aggiunge fondi al conto corrente e salva la relativa transazione in ingresso.
// Ritorna "true" se l'operazione va a buon fine, "false" altrimenti.
bool ContoCorrente::deposita(float importo, const std::string &descrizione, const std::string &mittente) {
    if ( importo <= 0 ) {
        std::cout << "Impossibile depositare quantità negative o nulle di denaro." << std::endl;
        return false;
    }
    Transazione *transazione = new TransazioneIngresso(descrizione, importo, mittente);
    saldo += importo;
    aggiungiTransazione(transazione);
    return true;
}

// Questo metodo sottrae fondi al conto corrente e salva la relativa transazione in uscita.
// Ritorna "true" se l'operazione va a buon fine, "false" altrimenti.
bool ContoCorrente::preleva(float importo, const std::string &descrizione, const std::string &destinatario) {
    if ( importo <= 0 ) {
        std::cout << "Impossibile prelevare quantità negative o nulle di denaro." << std::endl;
        return false;
    }
    if ( verificaDisponibilità(importo) ) {
        Transazione *transazione = new TransazioneUscita(descrizione, importo, destinatario);
        saldo -= importo;
        aggiungiTransazione(transazione);
        return true;
    }
    else {
        std::cout << "L'utente " << idUtente << " non ha fondi sufficienti per completare l'operazione."
                  << std::endl;
        return false;
    }
}

std::string ContoCorrente::getStoricoToString() const {
    std::ostringstream oss;
    for(const auto &transazione : storicoTransazioni) {
        oss << transazione->toString();
    }
    return oss.str();
}

// Questo metodo permette di salvare i dati di un conto corrente (saldo e storico transazioni) in un file ".txt".
// Ritorna "true" se l'operazione va a buon fine, "false" altrimenti.
bool ContoCorrente::salvaDati() const {
    std::ofstream file(percorsoFile);
    if ( file.is_open() ) {
        file << getStoricoToString() << std::endl;
        file << "Saldo disponibile: " << getSaldo() << " €" << std::endl << std::endl;
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
    std::string data;
    std::string importoStr;
    float importo;
    std::string descrizione;
    std::string mittente;
    std::string destinatario;
    std::string saldoStr;

    if ( file.is_open() ) {
        //svuoto il vettore delle transazioni
        this->storicoTransazioni.clear();
        std::string linea;
        while ( getline(file, linea) ) {
            if ( !linea.empty() ) {
                if ( linea.find(" -") != std::string::npos ) {
                    Transazione *transazione;

                    pos1 = linea.find(" -");                 // cerco la fine della data
                    data = linea.substr(0, pos1);           // salvo la data

                    stringaCercata = "Importo: ";                     // cerco l'importo
                    pos1 = linea.find(stringaCercata) + stringaCercata.size();
                    pos2 = linea.find(" €");
                    importoStr = linea.substr(pos1, pos2 - pos1);       // salvo l'importo
                    importo = stof(importoStr);

                    stringaCercata = "Descrizione: ";                         // cerco la descrizione
                    pos1 = linea.find(stringaCercata) + stringaCercata.size();
                    descrizione = linea.substr(pos1, linea.size() - pos1);       // salvo la descrizione

                    stringaCercata = "Ingresso - ";           // cerco se è una transazione in ingresso
                    if (linea.find(stringaCercata) != std::string::npos) {
                        pos1 = linea.find(stringaCercata) + stringaCercata.size();
                        if (linea[pos1] == 'M') {                 // vedo se c'è un mittente (altrimenti è un deposito)
                            stringaCercata = "Mittente: ";
                            pos1 += stringaCercata.size();
                            pos2 = linea.find(" -", pos1);
                            mittente = linea.substr(pos1, pos2 - pos1);     // salvo il mittente
                            transazione = new TransazioneIngresso(descrizione, importo, mittente, data);
                        } else {                  // se invece è un deposito...
                            transazione = new TransazioneIngresso(descrizione, importo, "", data);
                        }
                    } else {
                        stringaCercata = "Uscita - Destinatario: ";             // cerco se c'è il destinatario
                        if (linea.find(stringaCercata) != std::string::npos) {
                            pos1 = linea.find(stringaCercata) + stringaCercata.size();
                            pos2 = linea.find(" -", pos1);
                            destinatario = linea.substr(pos1, pos2 - pos1);     // salvo il destinatario
                            transazione = new TransazioneUscita(descrizione, importo, destinatario, data);
                        } else {          // altrimenti è un prelievo
                            transazione = new TransazioneUscita(descrizione, importo, "", data);
                        }
                    }
                    this->storicoTransazioni.push_back(transazione);
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

ContoCorrente::~ContoCorrente() {
    for(auto transazione: storicoTransazioni){
        delete transazione;
    }
}

