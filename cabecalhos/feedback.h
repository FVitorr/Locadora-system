#ifndef LOCADORA_SYSTEM_FEEDBACK_H
#define LOCADORA_SYSTEM_FEEDBACK_H
#include "locacao.h"
#include "fornecedor.h"

int menuFeedback(fCategoria **dtbaseCategoria, int *qtd_Categoria,int *tamanho_Categoria,int *idCategoria,
                               filme **dtbaseFilme, int *qtd_Filmes,int *tamanhoFilmes, int *idFilme,
                               funcionarios **dtbasefuncionarios, int *qtd_Funcionarios,int *tamanho_Funcionarios,int *idFuncionarios,int idFuncionarioLogado,
                               locadora **dtbaseLocadora, int *qtd_Locadora,int *tamanho_Locadora,int *idLocadora,
                               locados **dtbaseLocados, int *qtd_Locados, int *tamanho_Locados, int *idLocados,
                               cliente **dtbaseCliente, int *qtd_Cliente,int *tamanho_Cliente,int *idCliente,
                               operacoe **dtbaseOperacoe, int *qtd_Operacoe, int *tamanho_Operacoe,int *Key_operacao,
                               contaCliente **dtbaseCCliente, int *qtd_CCliente,int *tamanho_CCliente,int *idCCliente,int *Key_cliente,
                               fornecedor **dtbaseFornecedor, int *qtd_Fornecedor,int *tamanho_Fornecedor,int *idFornecedor);
void relatorioListagemClientes();
void filtrarClientesPorSexo(char sexo[15]);
void filtrarClientesPorFaixaCodigo(int inicio, int fim);

#endif //LOCADORA_SYSTEM_FEEDBACK_H
