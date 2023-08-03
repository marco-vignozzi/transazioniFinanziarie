#include "Transazione.h"

#include <ctime>
#include <iomanip>

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

std::string Transazione::creaData() const {
    time_t now = time(0);
    tm* data = localtime(&now);
    std::ostringstream oss;

    oss << std::setfill('0');
    oss << std::setw(2) << data->tm_mday << "/"
        << std::setw(2) << data->tm_mon + 1 << "/"
        << data->tm_year + 1900 << " "
        << std::setw(2) << data->tm_hour << ":"
        << std::setw(2) << data->tm_min << ":"
        << std::setw(2) << data->tm_sec;
    return oss.str();
}
