#include "Transazione.h"

#include <iomanip>

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
