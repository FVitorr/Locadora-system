#include "filmes.h"
#include "cliente.h"
#include "funcionarios.h"

typedef struct {
    int KEY_operator;
    int CodFilme;
    char *nomeFilme;
    float valorPago;
    data dtemprestimo;
    data dtdevolucao;
    int devolvido; // 0-Sim 1-Não //Não Altera
}operacoe;


typedef struct {
    int ID;
    int KEY_operator;
    int CodCliente; //Não Altera
    char *Nome;
    int qtdFilme;
    float valorPago;
    int tipoPagamento; // 1 - A vista  2 - A prazo
    int qtdParcelas;
    int TDdevolvido; // 0-Sim 1-Não //Não Altera
}locados;


operacoe objetoOperacoe(locados *newObjeto, filme **dtbaseFilme, int qtdFilme,fCategoria **dtbaseCategoria,int qtdCategoria,
                        int KEY_operator);

locados objetoLocados (int *id,cliente **dtbaseCliente,int qtdcliente,filme **dtbaseFilme,int qtdFilme,
                       operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                       fCategoria **dtbaseCategoria, int qtdCategoria, int *KEY_Controle);

int menuLocacao(filme **dtbaseFilme,int qtdFilme,cliente **dtbaseCliente,int qtdcliente,
                funcionarios **dtbaseFuncionarios, int qtdFuncionarios,
                locados **dtbaseLocados, int *qtdLocados, int *tamanhoLocados, int *idLocados,
                operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                fCategoria **dtbaseCategoria, int qtdCategoria, int *KEY_Controle, int tipo_config);

int inserirLocados(locados **dtbaseLocados,locados newLocados, int *qtdLocados, int *tamanhoLocados);

void listOperacoes(operacoe **dtbaseOperacoe, int qtd, int KEY_operator);

void listLocacao(locados **dtbaselocados, int qtdLocados, operacoe **dtbaseOperacoe, int qtdOperacoes);

int saveLocacao(locados objeto, int tipo_config);

int carregarDados_locacao(locados **dtbaseLocados, int *qtdLocados, int *tamanhoLocados,int tipo_config);