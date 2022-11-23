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

int menuImportacaoExportcao(cliente **dtbaseCliente, int qtdcliente,filme **dtbaseFilme, int qtdfilme,locadora **dtbaselocadora, int qtdlocadora);

int menuexport(exportcamp *exportcampos);

void refazexportCamp(exportcamp *exportcamp1, int value);

void exportDadoslocadora(FILE *arq, locadora **dtbaselocadora, int qtdlocadora);

void exportarDados(exportcamp camposExport, char *namepath, cliente **dtbaseCliente, int qtdCliente,filme **dtbaseFilme, int qtdfilme,
                   locadora **dtbaselocadora, int qtdlocadora);

void exportDadosFilme(FILE *arq, filme **dtbaseFilme, int qtdfilme);

void exportDadosCliente(FILE *arq, cliente **dtbaseCliente, int qtdcliente);
