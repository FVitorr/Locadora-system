cmake_minimum_required(VERSION 3.23)
project(Locadora_system C)

set(CMAKE_C_STANDARD 11)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)

include_directories(cabecalhos)

add_executable(Locadora_system
        cabecalhos/categoriaF.h
        cabecalhos/filmes.h
        cabecalhos/locadora.h
        cabecalhos/locacao.h
        cabecalhos/cliente.h
        cabecalhos/funcionarios.h
        cabecalhos/fornecedor.h
        cabecalhos/fucGlobal.h
        codigo/categoriaF.c
        codigo/filmes.c
        codigo/locadora.c
        codigo/locacao.c
        codigo/cliente.c
        codigo/funcionarios.c
        codigo/fornecedor.c
        fucGlobal.c
        main.c codigo/datas.c cabecalhos/datas.h)