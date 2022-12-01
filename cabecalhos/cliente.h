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
    char cpf[12];
    char telefone[120];
    char email[120];
    char sexo[15];
    char estadoCivil[15];
    char dataNascimento[12];
} cliente;



cliente criarCliente(int *id);

int inserirCliente(cliente **dtbase, cliente novoCliente, int *qtdCliente, int *tamanhoCliente);

int removerCliente(cliente **dtbase, int id, int *qtdCliente, int tipo_config);

void listCliente(cliente **dtbase, int qtd);
/*
 * Função que permite editar os parametros de Cliente
 * Entrada: Array Dinamico de Clientes, Quantidade de Cliente, Id que deseja editar, Tipo de Configuraçao
 */
void editaCliente(cliente **dtbase, int qtdCliente, int id, int tipo_config);
/*
 Cria menu Clientes
 Parametros: 
    bd_client,qtdCliente, tamanhoCliente ,idControleCliente.
*/
int menuClientes(cliente **bd_cliente, int *qtdCliente,int *tamanhoCliente,int *idControleCliente, int tipo_config);

int verificaIdCliente(cliente **dtbase, int qtdClientes, int id);

char *nomeCliente(cliente **dtbase,int qtd_Cliente, int ID);

int saveCliente(cliente objeto, int tipo_config);

/*
 * Função que restaura o arquivo de dados clientes
 * Entrada: Array Dinamico de Clientes, Quantidade de Cliente, Tipo de Configuraçao
 * */

int refazDadosCliente(cliente **dtbase, int qtdCliente, int tipo_config);

int carregarDadosClientes(cliente **dtBase, int *qtdClientes, int *tamanhoCliente, int *id, int tipo_config);

#endif //CLIENTE_H
