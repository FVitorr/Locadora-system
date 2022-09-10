#include "locadora.h"
typedef struct
{
    char user[120];
    char *password;

} autentificacao;

typedef struct
{
    int codigo;
    char nome[50];
    char cargo[30];
    endereco endereco;
    char telefone[13];
    char email[50];

    autentificacao login;
}funcionarios;
/*
 * Função que permite a inserção de um novo funcionario ao array de funcionarios
 */
int criarFuncionario(funcionarios **dtbase, int *qtdFuncionarios,int *tamanhoFuncionarios,int atualizar,int id);
/*
 * Função que permite a listar os funcionario
 */
void listFuncionarios(funcionarios **dtbase, int qtd);
/*
 * Função que permite a Alterar os dados dos funcionario.
 */
void editaFuncionarios(funcionarios **dtbase,int *qtdFuncionarios,int *tamanhoFuncionarios,int id);
/*
 * Função que permite a "Exclusão" de determinado funcionario.
 */
int removerFuncionarios(funcionarios **dtbase, int *qtdFuncionarios, int id);
/*
 * Função que Gerencia as operaçoes de funcionario.
 */
int menuFuncionarios(funcionarios **dtbase, int *qtdFuncionarios,int *tamanhoFuncionarios,int *id);