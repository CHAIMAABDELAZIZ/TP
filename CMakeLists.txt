cmake_minimum_required(VERSION 3.21.1)
project(TPSFSD C)

set(CMAKE_C_STANDARD 99)

add_executable(TPSFSD main.c  fonctions.h MachineAbstraite.h fonctions.c MachineAbstraite.c)

