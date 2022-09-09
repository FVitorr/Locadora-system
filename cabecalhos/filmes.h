#pragma once


#ifndef FILMES_H
#define FILMES_H

#ifdef __cplusplus
extern "C" {
#endif
    #include "../cabecalhos/categoriaF.h"
    #include "../cabecalhos/fucGlobal.h"

    filme objFilme(fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoCategoria, int id);

    int inserirFilme(filme **dtbase,filme newEntry,int *qtdFilmes,int *tamanhoFilmes,int id);

    int removerFilme(filme **dtbase, int id, int *qtdFilme);

    void listFilme(filme **dtbase, int qtd);

    void editaFilme(filme **dtbase,int *qtdFilmes,int *tamanhoFilmes,fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoCategoria,int id);

    int categTry(fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoCategoria ,int id);

    int menuFilme(filme **dtbase,int *qtdFilmes,int *tamanhoFilmes, fCategoria **dtbaseCategoria, int *qtdCategoria, int *tamanhoCategoria, int *id);



#ifdef __cplusplus
}
#endif

#endif /* FILMES_H */
