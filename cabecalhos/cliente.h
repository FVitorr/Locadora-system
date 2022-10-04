//
// Created by breno on 05/09/22.
//

#ifndef CLIENTE_H
#define CLIENTE_H
#include "locadora.h"

typedef struct
{
    int id;
    char nome[120];
    endereco endereco;
    char cpf[11];
    char telefone[15];
    char email[50];
    char sexo[15];
    char estadoCivil[15];
    char dataNascimento[12];
} cliente;

cliente criarCliente(int *id);

int inserirCliente(cliente **dtbase, cliente novoCliente, int *qtdCliente, int *tamanhoCliente, int tipo_config);

int removerCliente(cliente **dtbase, int id, int *qtdCliente, int tipo_config);

void listCliente(cliente **dtbase, int qtd);

void editaCliente(cliente **dtbase, int qtdCliente, int *tamanhoCliente, int id, int tipo_config);
/*
 Cria menu Filme
 Parametros: 
    bd_client,qtdCliente, tamanhoCliente ,idControleCliente.
*/
int menuClientes(cliente **bd_cliente, int *qtdCliente,int *tamanhoCliente,int *idControleCliente, int tipo_config);

int saveCliente(cliente objeto, int tipo_config);

int refazDadosCliente(cliente **dtbase, int *tamanhoCliente, int tipo_config);

int carregarDadosClientes(cliente **dtBase, int *qtdClientes, int *tamanhoCliente, int *id, int tipo_config);

#endif //CLIENTE_H
