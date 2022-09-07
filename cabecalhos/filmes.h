#pragma once


#ifndef FILMES_H
#define FILMES_H

#ifdef __cplusplus
extern "C" {
#endif
    #include "../cabecalhos/categoriaF.h"
    typedef struct
    {
        int codigo;
        char nome[10];      // Substituir por str
        char descricao[10]; // Substituir por str
        int qtd;            // quantidade de m�dias existentes na locadora
        int c_categoria;
        char lingua[10]; // Substituir por str

    } filme;


    filme objFilme(fCategoria **dtbaseCategoria,int *qtdCategoria, int id);

    int inserirFilme(filme **dtbase,filme newEntry,int *qtdFilmes,int *tamanhoFilmes,int id);

    int removerFilme(filme **dtbase, int id, int *qtdFilme);

    void listFilme(filme **dtbase, int qtd);

    void editaFilme(filme **dtbase,int *qtdFilmes,fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoFilmes,int id);

    int categTry(fCategoria **dtbaseCategoria,int *qtdCategoria ,int id);

    int menuFilme(filme **dtbase,int *qtdFilmes,int *tamanhoFilmes, fCategoria **dtbaseCategoria, int *qtdCategoria);



#ifdef __cplusplus
}
#endif

#endif /* FILMES_H */
