cmake_minimum_required(VERSION 3.5)
project(transazioniFinanziarie)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(test)

set(SOURCE_FILES )      #TODO aggiungere source files
add_executable(transazioniFinanziarie main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(transazioniFinanziarie core)