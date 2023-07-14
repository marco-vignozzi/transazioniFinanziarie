#include <fstream>
#include "ContoCorrente.h"
#include "TransazioneIngresso.h"
#include "TransazioneUscita.h"


bool ContoCorrente::invia(float importo, ContoCorrente *destinatario, const std::string &descrizione) {
    if ( importo <= 0 ) {
       std::cout << "Impossibile inviare quantità negative o nulle di denaro." << std::endl;
        return false;
    }
    if ( preleva(importo, descrizione, destinatario -> getIDUtente()) ) {
        destinatario -> deposita(importo, descrizione, getIDUtente());
        return true;
    }
    else {
        return false;
    }
}

void ContoCorrente::deposita(float importo, const std::string &descrizione, const std::string &mittente) {
    if ( importo <= 0 ) {
        std::cout << "Impossibile depositare quantità negative o nulle di denaro." << std::endl;
        return;
    }
    Transazione *transazione = new TransazioneIngresso(descrizione, importo, mittente);
    saldo += importo;
    aggiungiTransazione(transazione);
}

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
    oss << std::endl << "Saldo disponibile: " << getSaldo() << " €" << std::endl << std::endl;
    return oss.str();
}

void ContoCorrente::salvaStoricoTransazioni() const {
    std::ofstream file(percorsoFile);
    if ( file.is_open() ) {
        file << getStoricoToString();
        file.close();
        std::cout << "Storico transazioni salvato nel file: " << percorsoFile << std::endl;
    } else {
        std::cout << "Impossibile aprire il file: " << percorsoFile << std::endl;
    }
}

void ContoCorrente::caricaDati() {
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
        std::cout << "Storico transazioni caricato dal file: " << percorsoFile << std::endl;
    }
    else {
        std::cout << "Impossibile aprire il file: " << percorsoFile << std::endl;
    }
}

ContoCorrente::~ContoCorrente() {
    for(auto transazione: storicoTransazioni){
        delete transazione;
    }
}

