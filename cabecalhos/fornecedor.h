//
// Created by breno on 12/09/22.
//

#ifndef LOCADORA_SYSTEM_FORNECEDOR_H
#define LOCADORA_SYSTEM_FORNECEDOR_H
#include "locadora.h"

typedef struct {
    int id;
    char nomeFantasia[100];
    char razaoSocial[100];
    char inscricaoEstadual[30];
    char cnpj[16];
    endereco endereco;
    char telefone[15];
    char email[50];
} fornecedor;

fornecedor criarFornecedor(int id);

int inserirFornecedor(fornecedor **dtbase, fornecedor novoFornecedor, int *qtdFornecedor, int *tamanhoFornecedor);

int removerFornecedor(fornecedor **dtbase, int id, int *qtdFornecedor, int tipo_config);

void listFornecedor(fornecedor **dtbase, int qtd);

void editarFornecedor(fornecedor **dtbase, int qtdFornecedor, int *tamanhoFornecedor, int id, int tipo_config);

int menuFornecedor(fornecedor **bd_fornecedor, int *qtdFornecedor,int *tamanhoFornecedor,int *idControleFornecedor, int tipo_config);

int saveFornecedor(fornecedor objeto, int tipo_config);

int verificaIdFornecedor(fornecedor **dtbase, int qtdFornecedor, int id);

int carregarDadosFornecedores(fornecedor **dtBase, int *qtdFornecedor, int *tamanhoFornecedor, int *id, int tipo_config);

int refazDadosFornecedor(fornecedor **dtbase, int *tamanhoFornecedor, int tipo_config);

int retornarUltimoID_Fornecedor(fornecedor **dtBase, int qtdFornecedor);

char *retornarCNPJ(fornecedor **dtbase,int qtd, int id);

char *nomeFornecedor(fornecedor **dtbase, int qtd, int id);

int posArrayFornecedor(fornecedor **dtbase,int qtd_Locadora,int id);

#endif //LOCADORA_SYSTEM_FORNECEDOR_H
