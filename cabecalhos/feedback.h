#ifndef LOCADORA_SYSTEM_FEEDBACK_H
#define LOCADORA_SYSTEM_FEEDBACK_H
#include "locacao.h"
#include "fornecedor.h"


typedef struct {
    int inicio;
    int fim;
} filtroCodigo;

typedef struct {
    data inicio;
    data fim;
} filtroData;

int menuFeedback(cliente **dtbaseCliente, int qtd_Cliente,
                 filme **dtbaseFilme, int qtd_Filme,
                 eFilme **dtbaseeFilme, int qtd_eFilme,
                 fCategoria **dtbaseCategoria, int qtdCategoria,
                 funcionarios **dtbaseFuncionario, int qtdFuncionario,
                 contaCliente **dtbaseContaCliente, int qtdContaCliente);

int relatorioListagemClientes(cliente **dtbaseCliente, int qtd_Cliente);

void filtrarClientesPorSexo(cliente **dtBaseCliente, int qtdCliente, char sexo[15]);

void filtrarClientesPorFaixaCodigo(cliente **dtBaseCliente, int qtdCliente, int inicio, int fim);

int relatorioListagemFilmes(filme **dtBaseFilme, int qtdFilme);

filtroCodigo obterFaixaCodigo();

int locacoesRestantes(filme **dtBaseFilme, int qtdFilme, eFilme **dtBaseEFilme, int qtdEFilme,
                      fCategoria **dtbaseCategoria, int qtdCategoria, contaCliente **bdContaCliente, int qtdContaCliente);

int listarLocacoes(contaCliente **bdContaCliente, int qtdContaCliente, funcionarios **dtbase,int qtdFuncionario);

int vendaFuncionario(funcionarios **dtbase,int qtdFuncionario,contaCliente **bdContaCliente, int qtdContaCliente);

int listarContasAReceber(contaCliente **bdContaCliente, int qtdContaCliente);

filtroData *obterFaixaDatas();

int listarContasAPagar(eFilme **bdEFilme, int qtdEFilme);

int listarMovimentacaoCaixa(eFilme **bdEFilme, int qtdEFilme, contaCliente **bdContaCliente, int qtdContaCliente);

int vendaTipoPagamento(contaCliente **bdContaCliente, int qtdContaCliente, int tipoPagamento);

#endif //LOCADORA_SYSTEM_FEEDBACK_H
