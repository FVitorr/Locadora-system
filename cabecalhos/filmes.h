#pragma once


#ifndef FILMES_H
#define FILMES_H
#include "categoriaF.h"

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct
    {
        int codigo;
        char nome[10];      // Substituir por str
        char descricao[10]; // Substituir por str
        int qtd;            // quantidade de m�dias existentes na locadora
        int c_categoria;
        char lingua[10]; // Substituir por str

    } filme;

    filme* bd_filme; // dataBase local
    int qtdFilme, len_bd;

    int categTry(fCategoria *bd, int ID);

    filme objFilme(fCategoria *bd, int id);

    void inserirFilme(filme p);

    void removerFilme(filme* bd, int codigo);

    void listFilme(filme* bd, int qtd);

    int alterFilme(filme f, filme* bd, int codigo);

    int menuFilme();



#ifdef __cplusplus
}
#endif

#endif /* FILMES_H */
