cmake_minimum_required(VERSION 3.10)

project("Venstuff")
set(SOURCES main.cpp)
set(HEADERS hash.hpp)

add_executable(cli.out ${SOURCES} ${HEADERS})