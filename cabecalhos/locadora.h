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
    char nomeFantasia[50];
    char razaoSocial[50];
    char inscricaoEstadual[30];
    char cnpj[15];
    endereco endereco;
    char telefone[15];
    char email[50];
    char nomeResponsavel[50];
    char telefoneResponsavel[15];

    char user[120];
    char *password;
} locadora;

locadora criarLocadora(int *id);

int inserirLocadora(locadora **dtbase, locadora novaLocadora, int *qtdLocadora, int *tamanhoLocadora, int id);

int removerLocadora(locadora **dtbase, int id, int *qtdLocadora);

void listLocadora(locadora **dtbase, int qtd);

void editaLocadora(locadora **dtbase, int *qtdLocadora, int *tamanhoLocadora, int id);

int menuLocadora(locadora **dtbase, int *qtdLocadora,int *tamanhoLocadora,int *id);

int set_configuracao_Locadora(locadora **dtbase,char *user,char *password,int *qtdLocadora,int *tamanhoLocadora, int *id);

#endif //LOCADORA_H
