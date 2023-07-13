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
    return oss.str();
}

void ContoCorrente::salvaStoricoTransazioni() const {
    std::ofstream file(percorsoFile, std::ios::app);
    if ( file.is_open()) {
        file << getStoricoToString();
        file.close();
        std::cout << "Storico transazioni salvato nel file: " << percorsoFile << std::endl;
    } else {
        std::cout << "Impossibile aprire il file: " << percorsoFile << std::endl;
    }
}

void ContoCorrente::caricaStoricoTransazioni() {
    std::ifstream file(percorsoFile);
    if (file.is_open()) {
        std::string linea;
        while (getline(file, linea)) {
            Transazione *transazione;
            size_t pos1 = linea.find(" -");                 // cerco la fine della data

            std::string data = linea.substr(0, pos1);           // salvo la data


            std::string stringaCercata = "Importo: ";                     // cerco l'importo
            pos1 = linea.find(stringaCercata) + stringaCercata.size();
            size_t pos2 = linea.find(" €");

            std::string importoStr = linea.substr(pos1, pos2 - pos1);       // salvo l'importo
            float importo = stof(importoStr);

            stringaCercata = "Descrizione: ";                         // cerco la descrizione
            pos1 = linea.find(stringaCercata) + stringaCercata.size();

            std::string descrizione = linea.substr(pos1, linea.size() - pos1);       // salvo la descrizione

            //FIXME: non funziona la divisione in transazioni ingresso uscita

            stringaCercata = "Ingresso - Mittente: ";           // cerco se è una transazione in ingresso
            if( pos1 != std::string::npos ) {
                pos1 = linea.find(stringaCercata) + stringaCercata.size();
                pos2 = linea.find(" -", pos1);
                std::string mittente = linea.substr(pos1, pos2 - pos1);
                transazione = new TransazioneIngresso(descrizione, importo, mittente);
            }
            else {
                stringaCercata = "Uscita - Destinatario: ";
                pos1 = linea.find(stringaCercata) + stringaCercata.size() + 1;
                pos2 = linea.find(" -", pos1);
                std::string destinatario = linea.substr(pos1, pos2 - pos1);
                transazione = new TransazioneUscita(descrizione, importo, destinatario);
            }
            storicoTransazioni.push_back(transazione);
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

