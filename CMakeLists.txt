cmake_minimum_required(VERSION 4.1)
project(Strukturinis_programavimas)

set(CMAKE_CXX_STANDARD 14)

include_directories(.idea)

add_executable(Strukturinis_programavimas
        .idea/pd1.h
        Praktinis-darbas-1.cpp
        praktinis-darbas-2.cpp
)
