//
// Created by breno on 05/09/22.
//

#ifndef LOCADORA_H
#define LOCADORA_H

typedef struct
{
    char rua[50];
    int numero;
    char bairro[50];
    char cidade[50];
    char estado[50];

} endereco;

typedef struct {
    float caixa;
    float despesas;
    float contasReceber;
}financeiro;

typedef struct
{
    int id;
    char nomeFantasia[120];
    char razaoSocial[50];
    char inscricaoEstadual[30];
    char cnpj[15];
    endereco endereco;
    char telefone[15];
    char email[50];
    char nomeResponsavel[50];
    char telefoneResponsavel[15];

    financeiro monetario;

    char user[30];
    char *password;
} locadora;

locadora criarLocadora(int *id);

int inserirLocadora(locadora **dtbase, locadora novaLocadora, int *qtdLocadora, int *tamanhoLocadora);

int removerLocadora(locadora **dtbase, int id, int *qtdLocadora, int tipo_config);

void listLocadora(locadora **dtbase, int qtd);

void editaLocadora(locadora **dtbase, int qtdLocadora, int id, int tipo_config);

int menuLocadora(locadora **dtbase, int *qtdLocadora,int *tamanhoLocadora,int *id, int tipo_config);

int saveLocadora(locadora objeto,int tipo_config);

int carregarDados_Locadora(locadora **dtBase, int *qtdLocadora, int *tamanhoLocadora, int *id,int tipo_config);

int refazDados_Locadora(locadora **dtbase, int qtdLocadora, int tipo_configuracao);

int verifica_IDLocadora(locadora **dtbase,int qtd_Locadora,int id);

int posArrayLocadora(locadora **dtbase,int qtd_Locadora,int id);

int set_configuracao_Locadora(locadora **dtbase,char *user,char *password,int *qtdLocadora,int *tamanhoLocadora, int *id);

#endif //LOCADORA_H
