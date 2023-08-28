#include "Data.h"


Data::Data(const std::string &dataStr) {
    std::istringstream ss(dataStr);
    ss >> anno;
    ss.ignore();
    ss >> mese;
    ss.ignore();
    ss >> giorno;
    ss.ignore();
    ss >> ora;
    ss.ignore();
    ss >> minuto;
    ss.ignore();
    ss >> secondo;

    if (!verificaData()) {
        std::cout << "ATTENZIONE: " << toString() << " non è una data valida." << std::endl;
    }
}

bool Data::verificaData() const {
    if (anno < 0 || mese < 1 || mese > 12 || giorno < 1)
        return false;

    int giorniMese;
    if (mese == 2) {
        giorniMese = (anno % 4 == 0 && (anno % 100 != 0 || anno % 400 == 0)) ? 29 : 28;
    } else if (mese == 4 || mese == 6 || mese == 9 || mese == 11) {
        giorniMese = 30;
    } else {
        giorniMese = 31;
    }

    return  giorno <= giorniMese &&
            ora >= 0 && ora < 24 &&
            minuto >= 0 && minuto < 60 &&
            secondo >= 0 && secondo < 60;
}

bool Data::operator>(const Data &other) const {
    if (anno > other.anno)
        return true;
    else if (anno < other.anno)
        return false;

    if (mese > other.mese)
        return true;
    else if (mese < other.mese)
        return false;

    if (giorno > other.giorno)
        return true;
    else if (giorno < other.giorno)
        return false;

    if (ora > other.ora)
        return true;
    else if (ora < other.ora)
        return false;

    if (minuto > other.minuto)
        return true;
    else if (minuto < other.minuto)
        return false;

    return secondo > other.secondo;
}

bool Data::operator==(const Data &other) const {
    return anno == other.anno &&
           mese == other.mese &&
           giorno == other.giorno &&
           ora == other.ora &&
           minuto == other.minuto &&
           secondo == other.secondo;
}

std::string Data::toString() const {
    std::ostringstream ss;
    ss << std::setfill('0'); // Imposta il riempimento con '0'

    // Formatta l'anno, il mese e il giorno
    ss << anno << '-' << std::setw(2) << mese << '-' << std::setw(2) << giorno << ' ';

    // Formatta l'ora, il minuto e il secondo
    ss << std::setw(2) << ora << ':' << std::setw(2) << minuto << ':' << std::setw(2) << secondo;

    return ss.str();
}
