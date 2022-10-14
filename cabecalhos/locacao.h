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

int menuLocacao(filme **dtbaseFilme,int qtdFilme,cliente **dtbaseCliente,int qtdcliente,
                funcionarios **dtbaseFuncionarios, int qtdFuncionarios,
                locados **dtbaseLocados, int *qtdLocados, int *tamanhoLocados, int *idLocados,
                operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                fCategoria **dtbaseCategoria, int qtdCategoria, int *KEY_Controle);

void listOperacoes(operacoe **dtbaseOperacoe, int qtd, int KEY_operator);