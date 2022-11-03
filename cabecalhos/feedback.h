#ifndef LOCADORA_SYSTEM_FEEDBACK_H
#define LOCADORA_SYSTEM_FEEDBACK_H
#include "locacao.h"
#include "fornecedor.h"

int menuFeedback(cliente **dtbaseCliente, int *qtd_Cliente);
int relatorioListagemClientes(cliente **dtbaseCliente, int qtd_Cliente);
void filtrarClientesPorSexo(cliente **dtBaseCliente, int qtdCliente, const char sexo[15]);
void filtrarClientesPorFaixaCodigo(cliente **dtBaseCliente, int qtdCliente, int inicio, int fim);

#endif //LOCADORA_SYSTEM_FEEDBACK_H
