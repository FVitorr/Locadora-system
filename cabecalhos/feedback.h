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

int menuFeedback(cliente **dtbaseCliente, int *qtd_Cliente,
                 filme **dtbaseFilme, int *qtd_Filme);
int relatorioListagemClientes(cliente **dtbaseCliente, int qtd_Cliente);
void filtrarClientesPorSexo(cliente **dtBaseCliente, int qtdCliente, const char sexo[15]);
void filtrarClientesPorFaixaCodigo(cliente **dtBaseCliente, int qtdCliente, int inicio, int fim);
int relatorioListagemFilmes(filme **dtBaseFilme, int qtdFilme);
filtroCodigo obterFaixaCodigo();
int locacoesRestantes();
int listarLocacoes();
int listarContasAReceber();
filtroData obterFaixaDatas();
int listarContasAPagar();
int listarMovimentacaoCaixa();

#endif //LOCADORA_SYSTEM_FEEDBACK_H
