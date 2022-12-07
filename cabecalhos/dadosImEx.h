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

int menuImportacaoExportcao(cliente **dtbaseCliente, int *qtdcliente,int *tamCliente,filme **dtbaseFilme, int *qtdfilme,
                            int *tamFilme,locadora **dtbaselocadora, int *qtdlocadora, int *tamlocadora,fCategoria **dtbasecategoria, int *qtdcategoria,int *tamcategoria,
                            fornecedor **dtbasefornecedor, int *qtdFornecedor, int *tamFornecedor,funcionarios **dtbasefuncionarios, int *qtdfuncionarios, int *tamfuncionarios,
                            contaCliente **dtbaseCCliente, int *qtdCCliente, int *tamCCliente,eFilme **dtbase_eFilme, int *qtdeFilme, int *tameFilme,int tipo_config);

int menuexport(exportcamp *exportcampos);

int menuImport(exportcamp *importcampos);

void refazexportCamp(exportcamp *exportcamp1, int value);

void exportDadoslocadora(FILE *arq, locadora **dtbaselocadora, int qtdlocadora);

void importa_locadora(FILE *arq, locadora **dtbaselocadora, int *qtdlocadora ,int *tamLocadora);

void exportDadosCliente(FILE *arq, cliente **dtbaseCliente, int qtdcliente);

void importa_Cliente(FILE *arq, cliente **dtbaseCliente, int *qtdCliente ,int *tamCliente);

void exportDadosFilme(FILE *arq, filme **dtbaseFilme, int qtdfilme);

void importa_Filme(FILE *arq, filme **dtbaseFilme, int *qtdfilme ,int *tamfilme);

void exportDadosCategoria(FILE *arq, fCategoria **dtbasecategoria, int qtdcategoria);

void importa_Categoria(FILE *arq, fCategoria **dtbasecategoria, int *qtdcategoria ,int *tamcategoria);

void exportDadosFornecedor(FILE *arq, fornecedor **dtbasefornecedor, int qtdFornecedor);

void importa_Fornecedor(FILE *arq, fornecedor **dtbasefornecedor, int *qtdfornecedor ,int *tamfornecedor);

void exportDadosFuncionario(FILE *arq, funcionarios **dtbasefuncionarios, int qtdfuncionarios);

void importa_Funcionario(FILE *arq, funcionarios **dtbasefuncionarios, int *qtdfuncionarios ,int *tamfuncionarios);

void exportDadosLocacao(FILE *arq, contaCliente **dtbaseCCliente, int qtdCCliente);

void importa_Locacao(FILE *arq, contaCliente **dtbaseCCliente, int *qtdCCliente ,int *tamCCliente);

void exportDadosEntFilme(FILE *arq, eFilme **dtbase_eFilme, int qtdeFilme);

void importa_EntFilme(FILE *arq, eFilme **dtbase_eFilme, int *qtdeFilme ,int *tameFilme);

void exportarDados(exportcamp camposExport, char *namepath, cliente **dtbaseCliente, int qtdCliente,filme **dtbaseFilme, int qtdfilme,
                   locadora **dtbaselocadora, int qtdlocadora,fCategoria **dtbasecategoria, int qtdcategoria,
                   fornecedor **dtbasefornecedor, int qtdFornecedor,funcionarios **dtbasefuncionarios, int qtdfuncionarios,
                   contaCliente **dtbaseCCliente, int qtdCCliente,eFilme **dtbase_eFilme, int qtdeFilme);

void importarDados(exportcamp camposImporta, char *namepath,
                   cliente **dtbaseCliente, int *qtdCliente,int *tamCliente,
                   filme **dtbaseFilme, int *qtdfilme,int *tamFilme,
                   locadora **dtbaselocadora, int *qtdlocadora, int *tamlocadora,
                   fCategoria **dtbasecategoria, int *qtdcategoria,int *tamcategoria,
                   fornecedor **dtbasefornecedor, int *qtdFornecedor, int *tamFornecedor,
                   funcionarios **dtbasefuncionarios, int *qtdfuncionarios, int *tamfuncionarios,
                   contaCliente **dtbaseCCliente, int *qtdCCliente, int *tamCCliente,
                   eFilme **dtbase_eFilme, int *qtdeFilme, int *tameFilme, int tipo_config);

