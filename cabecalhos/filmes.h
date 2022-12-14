#pragma once


#ifndef FILMES_H
#define FILMES_H

#ifdef __cplusplus
extern "C" {
#endif
    #include "../cabecalhos/categoriaF.h"
    #include "../cabecalhos/fucGlobal.h"

    filme objFilme(fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoCategoria, int *id,
               int *idControleCategoria);

    int inserirFilme(filme **dtbase,filme newEntry,int *qtdFilmes,int *tamanhoFilmes);

    int removerFilme(filme **dtbase, int id, int *qtdFilmes,int tipo_config);

    void listFilme(filme **dtbase, int qtd);

    void editaFilme(filme **dtbase,int qtdFilmes,fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoCategoria,int id,int *idControleCategoria, int tipo_config);//Verificar se a categoria Existe, se não permite a criação

    int categTry(fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoCategoria ,int id,int *idControleCategoria);

    int menuFilme(filme **dtbase,int *qtdFilmes,int *tamanhoFilmes, fCategoria **dtbaseCategoria, int *qtdCategoria, int *tamanhoCategoria,int *idControleCategoria,int *id,int tipo_config);

    int saveFilme(filme objeto,int tipo_config);

    int carregarDados_filme(filme **dtBase, int *qtdFilme, int *tamanhoFilme, int *id,int tipo_config);

    int refazDados_filme(filme **dtbase, int qtdFilme, int tipo_config);

    int verificaIdFilme(filme **dtbase,int qtd_filme,int id);
    /*Retorna a categoria do filme*/
    int categoriaFilme(filme **dtbase,int qtd_filme,int id);

    int altQtdEmprestadaFilme(filme **dtbase,int qtd_filme,int id);

    int demQtdEmprestadaFilme(filme **dtbase,int qtd_filme,int id);

    char *nomeFilme(filme **dtbase,int qtd_filme, int ID);

#ifdef __cplusplus
}
#endif

#endif /* FILMES_H */
