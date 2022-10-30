#include "filmes.h"
#include "cliente.h"
#include "funcionarios.h"
#include "fornecedor.h"

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

typedef struct
{
    int ID;
    float frete,Imposto;
    filme *entradaFilmesCadastro; // Nem todos os campos da struct são alterados, mas ainda o codigo funciona como quero
    //Campos Usados: Nome: (Talvez vai ter que comparar nomes) ValorCompra: E quantidade
    int tamFilm;
    int ultIDFilm;
}operacaoEFilme;

typedef struct 
{
    int ID;
    int IDFornecedor;
    char *nomefornecedor;
    char cnpj[15];
    int key_fornecedorArray; // Id de referencia no array dtbaseFornecedor
    operacaoEFilme *filmes;
    int tamOp;
    int ultIDOp; //Ultimo Id da Operacao;
}eFilme;






operacoe objetoOperacoe(filme **dtbaseFilme, int qtdFilme,fCategoria **dtbaseCategoria,int qtdCategoria,
                        int KEY_operator, int *idOperacao);

locados objetoLocados (int idControleLocados,int idCliente,filme **dtbaseFilme,int qtdFilme,
                       operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                       fCategoria **dtbaseCategoria, int qtdCategoria, int *KEY_operacao,int Key_Cliente,
                       int tipoConfig);

contaCliente objetoCCliente(int *IdContaCliente,int key_cliente,cliente **dtbaseCliente,int qtdcliente,int idCliente);

int menuLocacao(filme **dtbaseFilme,int qtdFilme,
                cliente **dtbaseCliente,int qtdcliente,
                funcionarios **dtbaseFuncionarios, int qtdFuncionarios,int idFuncionarioLogado,
                locados **dtbaseLocados, int *qtdLocados, int *tamanhoLocados, int *idLocados,
                operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                contaCliente **dtbaseCCliente,int *qtdCCliente,int *tamanho_CCliente,int *idCCliente,
                fCategoria **dtbaseCategoria, int qtdCategoria,int *KEY_Operacao, int *KEY_Cliente,
                fornecedor **dtbaseFornecedor, int *qtdFornecedor,int *tamFornecedor,int *idEntradaFIlme,
                eFilme **dtBaseeFilme, int *tam_eFilme, int *qtd_eFilme,financeiro *monetario,int tipo_config);

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

void listCCliente(contaCliente **dtbaseCCcliente, int qtd, int key_cliente);

int pagarParcelas(contaCliente **dtbaseCCliente,int qtdCCliente, locados **dtbaseLocados, int qtdLocados,financeiro *monetario,int tipoconfig);

int verificaIDLocados(locados **dtbaselocados, int qtdLocados, int id, int key_cliente);

eFilme  objetoefilme(int *id,fornecedor **dtbase,int qtdForncecedor,int IDFornecedor);

int verificaID_eFilme(eFilme **dtbase, int qtd_eFilme, int id);

int inserir_eFilme(eFilme **dtbase,eFilme novaEntrada, int *qtd_eFilme, int *tam_eFilme);

int inserirop_EFIlme(operacaoEFilme **dtbase,operacaoEFilme novaEntrada,int *tam_op);

int save_eFilme(eFilme objeto,int tipo_config);

operacaoEFilme objOpEfilme (int *id);

filme objetoEntradaFIlme (int *id,filme **dtbase,int *tamFilm);

int entradaFilmes(fornecedor **dtbase, int *qtdFornecedor,int *tamFornecedor,int *idEntradaFIlme, eFilme **dtBase_eFilme, int *tam_eFilme, int *qtd_eFime,int tipo_config);