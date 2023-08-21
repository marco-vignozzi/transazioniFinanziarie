#ifndef README_MD_DATA_H
#define README_MD_DATA_H

#include <iostream>
#include <ctime>
#include <sstream>


class Data {
private:
    int anno, mese, giorno, ora, minuto, secondo;

public:
    Data() {
        std::time_t now = std::time(nullptr);
        std::tm data = *std::localtime(&now);

        anno = 1900 + data.tm_year;
        mese = data.tm_mon + 1;
        giorno = data.tm_mday;
        ora = data.tm_hour;
        minuto = data.tm_min;
        secondo = data.tm_sec;
    }

    Data(const std::string& dataStr) {
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

    std::string toString() const;

    bool operator>(const Data& other) const;

    bool operator<(const Data& other) const {
        return !(*this > other) && !(*this == other);
    }

    bool operator==(const Data& other) const;
};


#endif //README_MD_DATA_H
