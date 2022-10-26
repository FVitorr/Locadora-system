#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../cabecalhos/feedback.h"

int menuFeedback(fCategoria **dtbaseCategoria, int *qtd_Categoria,int *tamanho_Categoria,int *idCategoria,
                 filme **dtbaseFilme, int *qtd_Filmes,int *tamanhoFilmes, int *idFilme,
                 funcionarios **dtbasefuncionarios, int *qtd_Funcionarios,int *tamanho_Funcionarios,int *idFuncionarios,int idFuncionarioLogado,
                 locadora **dtbaseLocadora, int *qtd_Locadora,int *tamanho_Locadora,int *idLocadora,
                 locados **dtbaseLocados, int *qtd_Locados, int *tamanho_Locados, int *idLocados,
                 cliente **dtbaseCliente, int *qtd_Cliente,int *tamanho_Cliente,int *idCliente,
                 operacoe **dtbaseOperacoe, int *qtd_Operacoe, int *tamanho_Operacoe,int *Key_operacao,
                 contaCliente **dtbaseCCliente, int *qtd_CCliente,int *tamanho_CCliente,int *idCCliente,int *Key_cliente,
                 fornecedor **dtbaseFornecedor, int *qtd_Fornecedor,int *tamanho_Fornecedor,int *idFornecedor) {
    int opc = INT32_MAX;

    while (opc != 0) {
        system("cls");
        printf("Digite a opcao referente a operacao que deseja executar\n\n");
        printf("0 - Sair \n1 - Cadastrar \n2 - Visualizar \n3 - Editar \n4 - Remover\n");
        scanf("%d", &opc);
        line(30, "-\0");

        switch (opc) {
            case 1:
                relatorioListagemClientes();
                break;
            case 2:
                break;
            case 3:
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Digite uma opção válida.");
                break;
        }
    }
    return opc;
}

void relatorioListagemClientes() {
    int tipo = INT32_MAX;
    printf("Relatório de listagem de clientes\n\n");
    while (tipo != 0) {
        system("cls");
        printf("Existem dois tipos de filtro para o relatório\n");
        printf("Digite a opcao referente ao tipo de relatório que deseja\n");
        printf("0 - Sair \n1 - Sexo \n2 - Faixa de códigos\n");
        scanf("%d", &tipo);
        line(30, "-\0");
        switch(tipo){
            case 1: {
                char sexo[15];
                printf("Digite o sexo pelo qual deseja filtrar os registros: ");
                scanf("%[^\n]s", sexo);
                filtrarClientesPorSexo(sexo);
                break;
            }
            case 2: {
                int inicio = 0, fim = 0;
                printf("Digite o número inicial da faixa de códigod pela qual deseja filtrar os registros: ");
                scanf("%d", &inicio);
                printf("Digite o número final da faixa de códigod pela qual deseja filtrar os registros: ");
                scanf("%d", &fim);
                filtrarClientesPorFaixaCodigo(inicio, fim);
                break;
            }
            case 0: {
                printf("Voltando...\n");
                break;
            }
            default:
                printf("Digite uma opção válida.");
                break;
        }
    }
}

void filtrarClientesPorSexo(char sexo[15]) {

}

void filtrarClientesPorFaixaCodigo(int inicio, int fim) {

}