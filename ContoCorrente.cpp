#include <fstream>
#include "ContoCorrente.h"
#include "Transazione.h"

// Questo metodo esegue lo scambio di fondi tra due conti. Lo scambio è effettuato eseguendo un prelievo (se possibile)
// dal conto chiamante seguito da un deposito sul conto "destinatario", passato come parametro.
// Vengono create ed eseguite due transizioni, in ingresso per il destinatario e in uscita per il chiamante.
// Ritorna "true" se l'operazione va a buon fine, "false" altrimenti.
bool ContoCorrente::invia(float importo, std::shared_ptr<ContoCorrente> destinatario, const std::string &descrizione) {
    if ( importo <= 0 ) {
       std::cout << "Impossibile inviare quantità negative o nulle di denaro." << std::endl;
        return false;
    }
    if ( preleva(importo, descrizione, destinatario->getIDUtente()) ) {
        destinatario->deposita(importo, descrizione, destinatario->getIDUtente());
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
    std::shared_ptr<Transazione> transazione( new Transazione(descrizione, importo, "ingresso", mittente) );
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
        std::shared_ptr<Transazione> transazione( new Transazione(descrizione, importo, "uscita", destinatario) );
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

// TODO: aggiungere ricerca, modifica e cancellazione delle transazioni. ricerca restituisce vettore o lista.
// Questo metodo permette di salvare i dati di un conto corrente (saldo e storico transazioni) in un file ".txt".
// Ritorna "true" se l'operazione va a buon fine, "false" altrimenti.
bool ContoCorrente::salvaDati() const {
    std::ofstream file(percorsoFile);
    if ( file.is_open() ) {
        file << "Storico Transazioni Conto " << this->id << std::endl;
        file << getStoricoToString() << std::endl;
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
        this->storicoTransazioni.clear();
        std::string linea;
        getline(file, linea);
        while ( getline(file, linea) ) {
            if ( !linea.empty() ) {
                if ( linea.find(" -") != std::string::npos ) {
                    std::shared_ptr<Transazione> transazione( new Transazione());

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

ContoCorrente &ContoCorrente::cercaTransazioni(float importoMax, float importoMin) const {
    ContoCorrente nuovoconto = ContoCorrente();
    for( const auto &transazione : storicoTransazioni ) {
        if (transazione->getImporto() <= importoMax && transazione->getImporto() >= importoMin) {
            nuovoconto.getStoricoTransazioni().push_back(transazione);
        }
    }
    return nuovoconto;
}

ContoCorrente &ContoCorrente::cercaTransazioni(Data dataMax, Data dataMin) const {
    ContoCorrente nuovoconto = ContoCorrente();
    for( const auto &transazione : storicoTransazioni ) {
        if ( transazione->getData() < *(new Data(dataMax)) &&
                                        transazione->getData() > *(new Data(dataMin)) ) {
            nuovoconto.getStoricoTransazioni().push_back(transazione);
        }
    }
    return nuovoconto;
}

ContoCorrente &ContoCorrente::cercaTransazioni(std::string parolaCercata, std::string tipoRicerca) const {
    if(tipoRicerca == "tipo") {
        return ricercaTipoTrans(parolaCercata);
    }
    else if(tipoRicerca == "controparte") {
        return ricercaControparte(parolaCercata);
    }
    else if(tipoRicerca == "descrizione") {
        return ricercaDescrizione(parolaCercata);
    }
    else {
        std::cout << "Tipo di ricerca non disponibile." << std::endl;
        std::cout << "Tipi di ricerca possibili: 'tipo', 'controparte' e 'descrizione'." << std::endl;
    }
}

ContoCorrente &ContoCorrente::ricercaTipoTrans(std::string tipoTrans) const {
    ContoCorrente nuovoconto = ContoCorrente();
    for( const auto &transazione : storicoTransazioni ) {
        if ( transazione->getTipoTransazione() == tipoTrans )
            nuovoconto.getStoricoTransazioni().push_back(transazione);
    }
    return nuovoconto;
}

ContoCorrente &ContoCorrente::ricercaControparte(std::string controparte) const {
    ContoCorrente nuovoconto = ContoCorrente();
    for( const auto &transazione : storicoTransazioni ) {
        if ( transazione->getControparte() == controparte ) {
            nuovoconto.getStoricoTransazioni().push_back(transazione);
        }
    }
    return nuovoconto;
}

ContoCorrente &ContoCorrente::ricercaDescrizione(std::string descrizione) const {
    ContoCorrente nuovoconto = ContoCorrente();
    for( const auto &transazione : storicoTransazioni ) {
        if ( transazione->getDescrizione().find(descrizione) != std::string::npos ) {
            nuovoconto.getStoricoTransazioni().push_back(transazione);
            }
    }
    return nuovoconto;
}


// money pro
