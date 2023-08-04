cmake_minimum_required(VERSION 3.5)
project(transazioniFinanziarie)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(test)

set(SOURCE_FILES main.cpp Transazione.h ContoCorrente.h Utente.h ContoCorrente.cpp Transazione.cpp)
add_executable(transazioniFinanziarie main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(transazioniFinanziarie core)