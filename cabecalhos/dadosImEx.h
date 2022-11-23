//
// Created by Alunos on 22/11/2022.
//

#ifndef LOCADORA_SYSTEM_DADOSIMEX_H
#define LOCADORA_SYSTEM_DADOSIMEX_H

#endif //LOCADORA_SYSTEM_DADOSIMEX_H

#include "feedback.h"
#include <stdio.h>

typedef struct {
    int locadora;
    int cliente;
    int filme;
    int categoria;
    int fornecedor;
    int funcionario;
    int locacao_filme;
    int compras_filme;
} exportcamp;

int menuImportacaoExportcao(cliente **dtbaseCliente, int qtdcliente);


void exportarDados(exportcamp camposExport, char *namepath, cliente **dtbaseCliente, int qtdCliente);

void exportDadosCliente(FILE *arq, cliente **dtbaseCliente, int qtdcliente);

void refazexportCamp(exportcamp *exportcamp1, int value);

int menuexport(exportcamp *exportcampos);