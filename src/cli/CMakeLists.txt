cmake_minimum_required(VERSION 3.10)

project("Venstuff")
set(SOURCES main.cpp)
set(HEADERS hash.hpp string_helpers.hpp uri_encode.hpp)

add_executable(cli.out ${SOURCES} ${HEADERS})