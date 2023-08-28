#ifndef README_MD_DATA_H
#define README_MD_DATA_H


#include <iomanip>
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

    Data(const std::string& dataStr);

    bool verificaData() const;

    std::string toString() const;

    bool operator==(const Data& other) const;

    bool operator>(const Data& other) const;

    bool operator<(const Data& other) const {
        return !(*this > other) && !(*this == other);
    }
};


#endif //README_MD_DATA_H
