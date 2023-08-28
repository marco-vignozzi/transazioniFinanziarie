#include <gtest/gtest.h>
#include "../Data.h"


TEST(DataSuite, VerificaData){
    //verifico anno, mese, giorno bisestile
    EXPECT_FALSE((new Data("-12-2-3 11:03:43"))->verificaData());
    EXPECT_FALSE((new Data("2-14-3 11:03:43"))->verificaData());
    EXPECT_FALSE((new Data("1900-2-29 11:03:43"))->verificaData());
    EXPECT_FALSE((new Data("2011-2-29 11:03:43"))->verificaData());
    //verifico ora, minuti, secondi
    EXPECT_FALSE((new Data("2012-2-3 11:03:60"))->verificaData());
    EXPECT_FALSE((new Data("2012-2-20 11:60:43"))->verificaData());
    EXPECT_FALSE((new Data("2012-2-20 24:03:43"))->verificaData());

    //verifico bisestile e un paio di date limite
    EXPECT_TRUE((new Data("2012-2-29 15:00:13"))->verificaData());
    EXPECT_TRUE((new Data("2012-12-31 23:59:59"))->verificaData());
    EXPECT_TRUE((new Data("2012-6-30 23:59:59"))->verificaData());
}
