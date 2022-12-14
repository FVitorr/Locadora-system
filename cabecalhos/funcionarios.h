#include "locadora.h"
typedef struct
{
    char user[50];
    char password[16];

} autentificacao;

typedef struct
{
    int codigo;
    char nome[120];
    char cargo[50];
    endereco endereco;
    char telefone[17];
    char email[50];

    autentificacao login;
}funcionarios;
/*
 * Função que permite a inserção de dados para um novo funcionario
 */
funcionarios criarFuncionario(int *idFuncionario);
/*
 * Função que permite a inserção de um novo funcionario ao array de funcionarios
 */
int inserirFuncionario(funcionarios **dtbase, funcionarios novoFuncionario, int *qtdFuncionario, int *tamanhoFuncionario);
/*
 * Função que permite a listar os funcionario
 */
void listFuncionarios(funcionarios **dtbase, int qtd,int idfuncionariologado);
/*
 * Função que permite a Alterar os dados dos funcionario.
 */
void editaFuncionarios(funcionarios **dtbase,int qtdFuncionarios,int id, int tipo_config);
/*
 * Função que permite a "Exclusão" de determinado funcionario.
 */
int removerFuncionarios(funcionarios **dtbase, int *qtdFuncionarios, int id, int tipo_config);
/*
 * Função que Gerencia as operaçoes de funcionario.
 */
int menuFuncionarios(funcionarios **dtbase, int *qtdFuncionarios, int *tamanhoFuncionarios, int *idControleCliente,
                     int idFuncionarioLogado,int tipo_config);
/*
 * Função que salva os funcionarios no arquivo
 */
int saveFuncionario(funcionarios objeto, int tipo_config);
/*
 * Função que resgata os registros de funcionario do arquivo
 */
int carregarDadosFuncionarios(funcionarios **dtBase, int *qtdFuncionarios, int *tamanhoFuncionarios, int *id, int tipo_config);
/*
 * Função que refaz o arquivo de registros de funcionario
 */
int refazDadosFuncionario(funcionarios **dtbase, int *tamanhoFuncionario, int tipo_config);
/*
 *
 */
int verificaIdFuncionario(funcionarios **dtbase, int qtdFuncionarios, int id);


typedef struct {
    int id;
    char user[120];
    char password[17];
}adm;


int autentificacaoSystem(adm *set, funcionarios **dtBase,int qtdFuncionarios);

char *nomefuncionario(funcionarios **dtbase, int qtdFuncionarios,int id);
