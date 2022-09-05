//
// Created by breno on 05/09/22.
//

#ifndef LOCADORA_H
#define LOCADORA_H

typedef struct
{
    char rua[10];
    int numero;
    char bairro[10];
    char cidade[10];
    char estado[2];

} endereco;

typedef struct
{
    int id;
    char nomeFantasia[10];
    char razaoSocial[10];
    char inscricaoEstadual[10];
    int cnpj;
    endereco endereco;
    char telefone[10];
    char email[10];
    char nomeResponsavel[10];
    char telefoneResponsavel[10];
} locadora;

locadora criarLocadora(int atualizar);

void imprimirLocadora(locadora obj);

void imprimirLocadoraList();

void removerLocadora(int id);

void atualizarLocadora(int id);

#endif //LOCADORA_H
