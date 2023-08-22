#include "Transazione.h"


std::string Transazione::toString() const {
    std::ostringstream oss;
    oss << data.toString()
        << " - Transazione in " << tipoTransazione << " - ";
    if ( !controparte.empty() ) {
        if (tipoTransazione == "ingresso") {
            oss << "Mittente: " << controparte << " - ";
        }
        else {
            oss << "Destinatario: " << controparte << " - ";
        }
    }
    oss << "Importo: " << FIXED_FLOAT(importo) << " € - "
        << "Descrizione: " << descrizione
        << std::endl;
    return oss.str();
}

//TODO: testare modifica
void Transazione::modifica(std::string campo, std::string nuovaStringa) {
    if(campo == "descrizione") {
        setDescrizione(nuovaStringa);
    }
    else if(campo == "controparte") {
        setControparte(nuovaStringa);
    }
    else {
        std::cout << "Impossibile modificare il campo indicato." << std::endl;
        std::cout << "Campi modificabili: 'descrizione' e 'controparte'." << std::endl;
    }
}

bool Transazione::operator==(const Transazione &other) const {
    return importo == other.importo && data == other.data && controparte == other.controparte &&
            descrizione == other.descrizione && tipoTransazione == other.tipoTransazione;
}
