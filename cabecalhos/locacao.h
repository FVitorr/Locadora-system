#include "filmes.h"
#include "cliente.h"
#include "funcionarios.h"
#include "fornecedor.h"

//int PRIMEIRAEXECUCAO = 0; //0 NÃO
typedef struct {
    int ID;
    int CodFilme;
    char nomeFilme[120];
    float valorFilme;
    data dtemprestimo;
    data dtdevolucao; // Prevista
    data dtdevolucaoReal;
    int devolvido; // 0-Nao 1-Sim //Não Altera
}operacoe;

typedef struct {
    int ID;
    int IdFuncionario;
    operacoe *dFilme;
    int qtdFilme;
    float valorTotal; // Valor total da Locacao
    float valordeve; // Valor que o Cliente deve
    float valorEntrada; //Para pagamentos parcelados
    int tipoPagamento; // 1 - A vista  2 - A prazo
    data Dtpagamento;
    int qtdParcelas;
    int parcelasPagas;
    int TDdevolvido; // 0-Não 1-SIM 2-Alguns //Não Altera
    int ultimoIDOperacao;
}locados;

typedef struct {
    int ID;
    int idCliente;
    char *Nome;
    float valorDeve; // Valor que o Cliente deve
    float valorPago; // Valor que o Cliente paogu
    locados *dEmprestimo;
    int tamLocados;
    int IDlocado;
}contaCliente;

typedef struct
{
    int ID;
    float frete,Imposto;
    filme *entradaFilmesCadastro; // Nem todos os campos da struct são alterados, mas ainda o codigo funciona como quero
    //Campos Usados:
    //      Codigo (if filme cadastrado: -1
    //      else: ID respectivo ao do campo Codigo dtbaseFilme)
    //      Nome. (Comparação com dtbaseFIlme)
    //      ValorCompra.
    //      Quantidade.
    int tamFilm;
    float fretePproduto,ImpostoPproduto;

    //Adicionar chave estrangeria com dtBase Filme

    float valorTotal;
    int tipoPagamento; //1- A vista 2- A prazo
    int qtdParcelas;
    int parcelasPagas;
    float valorEntrada;
    float valorDeve;
    data dtNota;
    data dtPagamento;

    int ultIDFilm;
}operacaoEFilme;

typedef struct 
{
    int ID;
    int IDFornecedor;
    char *nomefornecedor;
    char cnpj[16];
    int key_fornecedorArray; // Id de referencia no array dtbaseFornecedor
    operacaoEFilme *filmes; //
    int tamOp;
    int ultIDOp; //Ultimo Id da Operacao;
}eFilme;



operacoe objetoOperacoe(filme **dtbaseFilme, int qtdFilme,fCategoria **dtbaseCategoria,int qtdCategoria,int *idOperacao);

locados objetoLocados (int *idControleLocados,int idCliente,filme **dtbaseFilme,int qtdFilme,int idFuncionario,
                       fCategoria **dtbaseCategoria, int qtdCategoria);

contaCliente objetoCCliente(int *IdContaCliente,int key_cliente,cliente **dtbaseCliente,int qtdcliente,int idCliente);

int menuLocacao(filme **dtbaseFilme,int *qtdFilme,int *tamanhoFilme ,int *iddtbasefilme,
                cliente **dtbaseCliente,int qtdcliente,
                funcionarios **dtbaseFuncionarios, int qtdFuncionarios,int idFuncionarioLogado,
                contaCliente **dtbaseCCliente,int *qtdCCliente,int *tamanho_CCliente,int *idCCliente,
                fCategoria **dtbaseCategoria, int *qtdCategoria,int *tamanhoCategoria,int *idControleCategoria,
                fornecedor **dtbaseFornecedor, int *qtdFornecedor,int *tamFornecedor,int *idEntradaFIlme,
                eFilme **dtBaseeFilme, int *tam_eFilme, int *qtd_eFilme,financeiro *monetario,int tipo_config);
int inserirLocados(locados **dtbaseLocados,locados newEntry,int *tamanhoLocados);

int inserirOperacao(operacoe **dtbaseOperacao,operacoe newEntry, int *tamanhoOperacao);

int  listLocacao(contaCliente **dtbase, int qtdCliente, int IDcliente, int IDlocado,int codigoDevolvido,int tipoPagamento, int mostraFilme, int mostrarNotas);

int carregarDados_locacao(locados **dtbaseLocados, int *qtdLocados, int *tamanhoLocados, int *id,int tipo_config);

int verificaConta(contaCliente **dtbaseCcliente, int qtdCcliente, int idCliente);

int carregarDados_Operacoes(operacoe **dtbaseoperacoe, int *qtdOperacao, int *tamanhoOperaca, int *key_operator ,int tipo_config);

int posicaoContaArray(contaCliente **dtbaseCCliente, int qtdCCliente, int idCliente);

int posicaoLocadosArray(locados **dtbaseLocados, int qtdLocados, int key_cliente, int IDlocado);

int inserirCCliente(contaCliente **dtbaseCCliente,contaCliente newEntry, int *qtdCCliente, int *tamanhoCCliente);

int refazDadosLocados(locados **dtbase, int qtdLocados, int tipo_config);

int refazDadosOperacao(operacoe **dtbase, int qtdOperacao, int tipo_config);

int saveContaCliente(contaCliente objeto, int tipo_config);

int carregarDados_CClientes(contaCliente **dtBaseCCliente, int *qtd_CCliente, int *tamanhoCCliente, int *idControle,cliente **dtbaseCLiente, int qtdCliente, filme **dtbaseFIlme, int qtdFilme,int tipo_config);

int refazDadosCCliente(contaCliente **dtbase, int qtdCCliente, int tipo_config);

int emprestaFilme(contaCliente **dtBaseCCliente,int *qtd_CCliente,int *tamanho_CCliente,int *IdContaCliente,cliente **dtbaseCliente,int qtdcliente,
                  filme **dtbaseFilme,int qtdFilme,int *iddtbasefilme,fCategoria **dtbaseCategoria, int qtdCategoria,int idFuncionarioLogado,financeiro *monetario,int tipoConfig);

int devolucaoFilmes(contaCliente **dtbaseCCliente,int qtdCCliente,filme **dtbaseFilme,int qtdFilme,financeiro *monetario,int tipoConfig);

int retornaChaveOperacao(locados **dtbaselocados, int qtdLocados, int id, int key_cliente);

int retornaChaveCliente(contaCliente **dtbase, int qtd, int idCliente);

int pagarParcelas(contaCliente **dtbaseCCliente,int qtdCCliente,financeiro *monetario,int tipoconfig);

int verificaIDLocados(contaCliente **dtbaseCCliente, int qtdCCliente, int idCliente,int idLocado, int tipoPagamento);

eFilme  objetoefilme(int *id,fornecedor **dtbase,int qtdForncecedor,int IDFornecedor);

int verificaID_eFilme(eFilme **dtbase, int qtd_eFilme, int id);

int inserir_eFilme(eFilme **dtbase,eFilme novaEntrada, int *qtd_eFilme, int *tam_eFilme);

int inserirop_EFIlme(operacaoEFilme **dtbase,operacaoEFilme novaEntrada,int *tam_op);

int save_eFilme(eFilme objeto,int tipo_config);

operacaoEFilme objOpEfilme (int *id,financeiro *monetario,filme **dtbaseFilme,int qtdDBFilme, int *IDdtbaseFilme, fCategoria **dtbaseCategoria,int *qtdCategoria ,int *tamanhoCategoria, int *idControleCategoria, int tipoConfig);

filme objetoEntradaFIlme (int *id,filme **dtbase,int *tamFilm,filme **dtbaseFilme,int qtdDBFilme,fCategoria **dtbaseCategoria,int *qtdCategoria ,int *tamanhoCategoria, int *idControleCategoria, int tipoConfig);

int entradaFilmes(fornecedor **dtbase, int *qtdFornecedor,int *tamFornecedor,int *idEntradaFIlme, eFilme **dtBase_eFilme, int *tam_eFilme, int *qtd_eFime,filme **dtbaseFilme,int *qtdFilme,int *tamanhoFilme,int *iddtbasefilme,fCategoria **dtbaseCategoria, int *qtdCategoria,int *tamanhoCategoria,int *idControleCategoria,financeiro *monetario,int tipo_config);

int carregarDados_Efilme(eFilme **dtbase, int *qtdeFilmes, int *tamanhoeFilmes,fornecedor **dtbaseFornecedor,int qtdFornecedor,int tipo_config);

int list_eFilme(eFilme **dtBase_eFilme, int qtd_eFime, int IDconta,int IDnota, int tipoPagamento, int filtrarPagos);

int pagarParcelaEmprestaFilme(eFilme **dtbase_eFilme, int qtd_eFilme, financeiro *monetario, int tipo_config);

int refazDadosEfIlme(eFilme **dtbase, int qtdCCliente, int tipo_config);

//int transportaDados(const char *namefilme,filme **dtbaseFilme, int qtdFilme, int *retornoIDFilme, int qtdEntrada);

int filme_in_dtbase(char namefile[],filme **dtbaseFilme, int qtdFilme, int *retornoIDFilme, int qtdTotal);

void refazNameCCliente(contaCliente *objeto,filme **dtbaseFIlme,int qtdfilme,cliente **dtbaseCliente,int qtdCLiente);

void refazNomeFornecedor(eFilme *objeto, fornecedor **dtbaseFornecedor, int qtdfornecedor);