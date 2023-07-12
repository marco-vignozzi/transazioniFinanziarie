#ifndef MAIN_CPP_DATA_H
#define MAIN_CPP_DATA_H

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>


class Data {

private:
    int secondi;
    int minuti;
    int ore;
    int giorno;
    int mese;
    int anno;

public:
    Data() {
        time_t now = time(0);
        tm* currentTime = localtime(&now);
        secondi = currentTime -> tm_sec;
        minuti = currentTime -> tm_min;
        ore = currentTime -> tm_hour;
        giorno = currentTime -> tm_mday;
        mese = currentTime -> tm_mon + 1;
        anno = currentTime -> tm_year + 1900;
    }

    std::string stampaData() const {
        std::ostringstream oss;
        oss << std::setfill('0');
        oss << "Data corrente: "
            << std::setw(2) << giorno << "/"
            << std::setw(2) << mese << "/"
            << anno << " "
            << std::setw(2) << ore << ":"
            << std::setw(2) << minuti << ":"
            << std::setw(2) << secondi;

        return oss.str();
    }

};


#endif //MAIN_CPP_DATA_H
