cmake_minimum_required(VERSION 3.5)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES TestInvio.cpp)     #TODO aggiungere source dei test
add_executable(runTests ${TEST_SOURCE_FILES})      #TODO cambiare nome eseguibile
target_link_libraries(runTests gtest gtest_main core)      #TODO cambiare nome eseguibile