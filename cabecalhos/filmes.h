#pragma once


#ifndef FILMES_H
#define FILMES_H

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


    filme objFilme(int id);

    int inserirFilme(filme **dtbase,filme newEntry,int *qtdFilmes,int *tamanhoFilmes);

    int removerFilme(filme **dtbase, int id, int *qtdFilme);

    void listFilme(filme **dtbase, int qtd);

    void editaFilme(filme **dtbase,int *qtdFilme,int *tamanhoFilmes,int id);

    int menuFilme(filme **dtbase,int *qtdFilmes,int *tamanhoFilmes);



#ifdef __cplusplus
}
#endif

#endif /* FILMES_H */
