#pragma once

#ifndef CATEGORIAF_H
#define CATEGORIAF_H

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    int codigo;
    char descricao[30];
    float vAlocacao;
} fCategoria;

fCategoria objCategoria(int id);

int insCategoria(fCategoria p);

void remCategoria(fCategoria* bd, int codigo);

void listCategoria(fCategoria* bd, int qtd);

int alteraCat(fCategoria f, fCategoria* bd, int codigo);

int menuCategoria();

int locID(fCategoria* bd, int codigo);


#ifdef __cplusplus
}
#endif

#endif /* CATEGORIAF_H */

