//
// Created by breno on 05/09/22.
//

#ifndef CLIENTE_H
#define CLIENTE_H
#include "locadora.h"

typedef struct
{
    int id;
    char nome[50];
    endereco endereco;
    char cpf[11];
    char telefone[15];
    char email[50];
    char sexo[15];
    char estadoCivil[15];
    char dataNascimento[12];
} cliente;

cliente criarCliente(int *id);

int inserirCliente(cliente **dtbase, cliente novoCliente, int *qtdCliente, int *tamanhoCliente, int id);

int removerCliente(cliente **dtbase, int id, int *qtdCliente);

void listCliente(cliente **dtbase, int qtd);

void editaCliente(cliente **dtbase, int qtdCliente, int *tamanhoCliente, int id);
/*
 Cria menu Filme
 Parametros: 
    bd_client,qtdCliente, tamanhoCliente ,idControleCliente.
*/
int menuClientes(cliente **bd_cliente, int *qtdCliente,int *tamanhoCliente,int *idControleCliente);

#endif //CLIENTE_H
