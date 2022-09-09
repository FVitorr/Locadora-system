cmake_minimum_required(VERSION 3.23)
project(Locadora_system C)

set(CMAKE_C_STANDARD 11)

include_directories(cabecalhos)

add_executable(Locadora_system
        cabecalhos/categoriaF.h
        cabecalhos/filmes.h
        cabecalhos/locadora.h
        cabecalhos/fucGlobal.h
        codigo/categoriaF.c
        codigo/filmes.c
        codigo/locadora.c
        fucGlobal.c
        main.c)