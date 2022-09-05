//
// Created by breno on 05/09/22.
//

#ifndef CLIENTE_H
#define CLIENTE_H
#include "locadora.h"

typedef struct
{
    int id;
    char nome[10];
    endereco endereco;
    int cpf;
    char telefone[10];
    char email[10];
    char sexo[1];
    char estadoCivil[10];
    char dataNascimento[10];
} cliente;

cliente criarCliente(cliente *dados, int atualizar);

void imprimirCliente(cliente obj);

void imprimirClienteList(cliente *dados);

void removerCliente(cliente *dados, int id);

void atualizarCliente(cliente *dados, int id);

#endif //CLIENTE_H
