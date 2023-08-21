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
    ss << anno << '-' << mese << '-' << giorno << ' ' << ora << ':' << minuto << ':' << secondo;
    return ss.str();
}

