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
    int cnpj;
    endereco endereco;
    char telefone[15];
    char email[50];
} fornecedor;

fornecedor criarFornecedor(int id);

int inserirFornecedor(fornecedor **dtbase, fornecedor novoFornecedor, int *qtdFornecedor, int *tamanhoFornecedor, int id);

int removerFornecedor(fornecedor **dtbase, int id, int *qtdFornecedor);

void listFornecedor(fornecedor **dtbase, int qtd);

void editarFornecedor(fornecedor **dtbase, int *qtdFornecedor, int *tamanghoFornecedor, int id);

int menuFornecedor(fornecedor **bd_fornecedor, int *qtdFornecedor,int *tamanhoFornecedor,int *idControleFornecedor);

#endif //LOCADORA_SYSTEM_FORNECEDOR_H
