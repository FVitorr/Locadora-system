#include "filmes.h"
#include "cliente.h"
#include "funcionarios.h"

typedef struct {
    int ID;
    int KEY_operator;
    int CodFilme;
    char *nomeFilme;
    float valorFilme;
    data dtemprestimo;
    data dtdevolucao; // Prevista
    data dtdevolucaoReal;
    int devolvido; // 0-Sim 1-Não //Não Altera
}operacoe;

typedef struct {
    int ID;
    int KEY_operator;
    int key_cliente;; //Valor unico para cliente
    int qtdFilme;
    float valorTotal; // Valor total da Locacao
    float valordeve; // Valor que o Cliente deve
    float valorEntrada; //Para pagamentos parcelados
    int tipoPagamento; // 1 - A vista  2 - A prazo
    data Dtpagamento;
    int qtdParcelas;
    int TDdevolvido; // 0-Não 1-SIM //Não Altera
    int ultimoIDOperacao;
}locados;

typedef struct {
    int ID;
    int key_cliente;
    int idCliente;
    char *Nome;
    float valorDeve; // Valor que o Cliente deve
    float valorPago; // Valor que o Cliente deve
    int IDlocado;
}contaCliente;


operacoe objetoOperacoe(filme **dtbaseFilme, int qtdFilme,fCategoria **dtbaseCategoria,int qtdCategoria,
                        int KEY_operator, int *idOperacao);

locados objetoLocados (int *idControleLocados,int idCliente,filme **dtbaseFilme,int qtdFilme,
                       operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                       fCategoria **dtbaseCategoria, int qtdCategoria, int *KEY_operacao,int Key_Cliente,
                       int tipoConfig);

contaCliente objetoCCliente(int *IdContaCliente,int key_cliente,cliente **dtbaseCliente,int qtdcliente,int idCliente);

int menuLocacao(filme **dtbaseFilme,int qtdFilme,
                cliente **dtbaseCliente,int qtdcliente,
                funcionarios **dtbaseFuncionarios, int qtdFuncionarios,int idFuncionarioLogado,
                locados **dtbaseLocados, int *qtdLocados, int *tamanhoLocados, int *idLocados,
                operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                contaCliente **dtbaseCCliente,int *qtdCCliente,int *tamanhoCCliente,int *idCCliente,
                fCategoria **dtbaseCategoria, int qtdCategoria,int *KEY_Operacao, int *KEY_Cliente,financeiro *monetario,int tipo_config);

int inserirLocados(locados **dtbaseLocados,locados newEntry, int *qtdLocados, int *tamanhoLocados);

int inserirOperacao(operacoe **dtbaseOperacao,operacoe newEntry, int *qtdOperacao, int *tamanhoOperacao);

void listOperacoes(operacoe **dtbaseOperacoe, int qtd, int KEY_operator);

//Key -1 listar todas as locadas
int listLocacao(locados **dtbaselocados, int qtdLocados, operacoe **dtbaseOperacoe, int qtdOpe, int key_cliente);

int saveLocacao(locados objeto, int tipo_config);

int saveOperacao(operacoe objeto, int tipo_config);

int carregarDados_locacao(locados **dtbaseLocados, int *qtdLocados, int *tamanhoLocados, int *id,int tipo_config);

int verificaConta(contaCliente **dtbaseCcliente, int qtdCcliente, int idCliente);

int carregarDados_Operacoes(operacoe **dtbaseoperacoe, int *qtdOperacao, int *tamanhoOperaca, int *key_operator ,int tipo_config);

int posicaoContaArray(contaCliente **dtbaseCCliente, int qtdCCliente, int idCliente);

int posicaoLocadosArray(locados **dtbaseLocados, int qtdLocados, int key_cliente, int IDlocado);

int inserirCCliente(contaCliente **dtbaseCCliente,contaCliente newEntry, int *qtdCCliente, int *tamanhoCCliente);

int refazDadosLocados(locados **dtbase, int qtdLocados, int tipo_config);

int refazDadosOperacao(operacoe **dtbase, int qtdOperacao, int tipo_config);

int saveContaCliente(contaCliente objeto, int tipo_config);

int carregarDados_CClientes(contaCliente **dtBaseCCliente, int *qtd_CCliente, int *tamanhoCCliente, int *idControle, int * Key_Cliente,int tipo_config);

int refazDadosCCliente(contaCliente **dtbase, int qtdCCliente, int tipo_config);

int emprestaFilme(contaCliente **dtBaseCCliente,int *qtd_CCliente,int *tamanho_CCliente,int *IdContaCliente,int *key_cliente,cliente **dtbaseCliente,int qtdcliente,
                   filme **dtbaseFilme,int qtdFilme,operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                   locados **dtbaseLocados, int *qtdLocados, int *tamanhoLocados,
                   fCategoria **dtbaseCategoria, int qtdCategoria, int *KEY_Operacao,financeiro *monetario,int tipoConfig);

int devolucaoFilmes(contaCliente **dtbaseCCliente,int qtdCCliente,locados **dtbaselocados, int qtdLocados,
                     operacoe **dtbaseOperacoes, int qtdOperacao,int tipoconfig);

int retornaChaveOperacao(locados **dtbaselocados, int qtdLocados, int id, int key_cliente);

int retornaChaveCliente(contaCliente **dtbase, int qtd, int idCliente);

void listCCliente(contaCliente **dtbaseCCcliente, int qtd);

int verificaIDLocados(locados **dtbaselocados, int qtdLocados, int id, int key_cliente);