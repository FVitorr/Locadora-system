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

int menuImportacaoExportcao(cliente **dtbaseCliente, int qtdcliente,filme **dtbaseFilme, int qtdfilme,locadora **dtbaselocadora, int qtdlocadora,fCategoria **dtbasecategoria, int qtdcategoria,
                            fornecedor **dtbasefornecedor, int qtdFornecedor,funcionarios **dtbasefuncionarios, int qtdfuncionarios,
                            contaCliente **dtbaseCCliente, int qtdCCliente,eFilme **dtbase_eFilme, int qtdeFilme);

int menuexport(exportcamp *exportcampos);

int menuImport(exportcamp *importcampos);

void refazexportCamp(exportcamp *exportcamp1, int value);

void exportDadoslocadora(FILE *arq, locadora **dtbaselocadora, int qtdlocadora);

void importa_locadora(FILE *arq, locadora **dtbaselocadora, int qtdlocadora);

void exportDadosCliente(FILE *arq, cliente **dtbaseCliente, int qtdcliente);

void importa_Cliente(FILE *arq, cliente **dtbaseCliente, int qtdcliente);

void exportDadosFilme(FILE *arq, filme **dtbaseFilme, int qtdfilme);

void importa_Filme(FILE *arq, filme **dtbaseFilme, int qtdfilme);

void exportDadosCategoria(FILE *arq, fCategoria **dtbasecategoria, int qtdcategoria);

void importa_Categoria(FILE *arq, fCategoria **dtbasecategoria, int qtdcategoria);

void exportDadosFornecedor(FILE *arq, fornecedor **dtbasefornecedor, int qtdFornecedor);

void exportDadosFuncionario(FILE *arq, funcionarios **dtbasefuncionarios, int qtdfuncionarios);

void exportDadosLocacao(FILE *arq, contaCliente **dtbaseCCliente, int qtdCCliente);

void exportDadosEntFilme(FILE *arq, eFilme **dtbase_eFilme, int qtdeFilme);

void exportarDados(exportcamp camposExport, char *namepath, cliente **dtbaseCliente, int qtdCliente,filme **dtbaseFilme, int qtdfilme,
                   locadora **dtbaselocadora, int qtdlocadora,fCategoria **dtbasecategoria, int qtdcategoria,
                   fornecedor **dtbasefornecedor, int qtdFornecedor,funcionarios **dtbasefuncionarios, int qtdfuncionarios,
                   contaCliente **dtbaseCCliente, int qtdCCliente,eFilme **dtbase_eFilme, int qtdeFilme);

void importarDados(exportcamp camposImporta, char *namepath, cliente **dtbaseCliente, int qtdCliente,filme **dtbaseFilme, int qtdfilme,
                   locadora **dtbaselocadora, int qtdlocadora,fCategoria **dtbasecategoria, int qtdcategoria,
                   fornecedor **dtbasefornecedor, int qtdFornecedor,funcionarios **dtbasefuncionarios, int qtdfuncionarios,
                   contaCliente **dtbaseCCliente, int qtdCCliente,eFilme **dtbase_eFilme, int qtdeFilme);

