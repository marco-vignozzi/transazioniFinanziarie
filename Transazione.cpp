#include "Transazione.h"


std::string Transazione::toString() const {
    std::ostringstream oss;
    oss << data
        << " - Transazione in " << tipoTransazione << " - ";
    if( tipoTransazione == "Ingresso" ) {
        if(!mittente.empty()) {
            oss << "Mittente: " << mittente << " - ";
        }
    }
    else {
        if(!destinatario.empty()){
            oss << "Destinatario: " << destinatario << " - ";
        }
    }
    oss << "Importo: " << FIXED_FLOAT(importo) << " € - "
        << "Descrizione: " << descrizione
        << std::endl;
    return oss.str();
}
