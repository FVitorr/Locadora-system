#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../cabecalhos/feedback.h"

int menuFeedback(cliente **dtbaseCliente, int *qtd_Cliente) {
    int opc = INT32_MAX;

    while (opc != 0) {
        system("cls");
        printf("Digite a opcao referente a operacao que deseja executar\n\n");
        printf("0 - Sair\n1 - Listar Clientes\n");
        scanf("%d", &opc);
        line(30, "-\0");

        switch (opc) {
            case 1:
                return relatorioListagemClientes(dtbaseCliente, *qtd_Cliente);
            case 2:
                break;
            case 3:
                break;
            case 0:
                return 1;
            default:
                printf("Digite uma opção válida.");
                break;
        }
    }
    return opc;
}

int relatorioListagemClientes(cliente **dtBaseCliente, int qtdCliente) {
    int tipo = INT32_MAX;
    system("cls");
    printf("Relatorio de listagem de clientes\n\n");
    while (tipo != 0) {
        printf("Existem dois tipos de filtro para o relatorio\n");
        printf("Digite a opcao referente ao tipo de relatorio que deseja\n");
        printf("0 - Sair \n1 - Sexo \n2 - Faixa de codigos\n");
        scanf("%d", &tipo);
        line(30, "-\0");
        switch(tipo){
            case 1: {
                char sexo[15];
                printf("Digite o sexo pelo qual deseja filtrar os registros: ");
                scanf("%[^\n]s", sexo);
                filtrarClientesPorSexo(dtBaseCliente, qtdCliente, sexo);
                return INT32_MAX;
            }
            case 2: {
                int inicio = 0, fim = 0;
                system("cls");
                printf("Digite o numero inicial da faixa de codigo pela qual deseja filtrar os registros: ");
                scanf("%d", &inicio);
                system("cls");
                printf("Digite o numero final da faixa de codigo pela qual deseja filtrar os registros: ");
                scanf("%d", &fim);
                system("cls");
                filtrarClientesPorFaixaCodigo(dtBaseCliente, qtdCliente, inicio, fim);
                return INT32_MAX;
            }
            case 0: {
                return INT32_MAX;
            }
            default:
                printf("Digite uma opção válida.");
                break;
        }
    }
}

void filtrarClientesPorSexo(cliente **dtBaseCliente, int qtdCliente, const char sexo[15]) {
    system("cls");
    if (qtdCliente > 0) {
        printf("\n ID \tNome \tCPF \tTelefone \tE-mail \tSexo \tEstado Civil \tData de Nascimento \tRua \tNumero \tBairo \tCidade \tEstado  \n");
        for (int c = 0; c < qtdCliente; c++) {
            if ((*dtBaseCliente)[c].sexo == sexo) {
                printf("----------------------------------------------------------------------------------------------------------------------------------\n");
                printf("%d\t %s \t %s \t %s \t %s \t %s \t %s\t %s \t %s \t %d \t %s \t %s \t %s",
                       (*dtBaseCliente)[c].id,
                       (*dtBaseCliente)[c].nome,
                       (*dtBaseCliente)[c].cpf,
                       (*dtBaseCliente)[c].telefone,
                       (*dtBaseCliente)[c].email,
                       (*dtBaseCliente)[c].sexo,
                       (*dtBaseCliente)[c].estadoCivil,
                       (*dtBaseCliente)[c].dataNascimento,
                       (*dtBaseCliente)[c].endereco.rua,
                       (*dtBaseCliente)[c].endereco.numero,
                       (*dtBaseCliente)[c].endereco.bairro,
                       (*dtBaseCliente)[c].endereco.cidade,
                       (*dtBaseCliente)[c].endereco.estado);
            }
        }
    } else {
        printf("\n\t>> Nenhum registro para o filtro informado");
    }
    printf("\n");
}

void filtrarClientesPorFaixaCodigo(cliente **dtBaseCliente, int qtdCliente, int inicio, int fim) {
    system("cls");
    if (qtdCliente > 0) {
        printf("\n ID \tNome \tCPF \tTelefone \tE-mail \tSexo \tEstado Civil \tData de Nascimento \tRua \tNumero \tBairo \tCidade \tEstado  \n");
        for (int c = 0; c < qtdCliente; c++) {
            if ((*dtBaseCliente)[c].id >= inicio && (*dtBaseCliente)[c].id <= fim) {
                system("cls");
                printf("----------------------------------------------------------------------------------------------------------------------------------\n");
                system("cls");
                printf("%d\t %s \t %s \t %s \t %s \t %s \t %s\t %s \t %s \t %d \t %s \t %s \t %s",
                       (*dtBaseCliente)[c].id,
                       (*dtBaseCliente)[c].nome,
                       (*dtBaseCliente)[c].cpf,
                       (*dtBaseCliente)[c].telefone,
                       (*dtBaseCliente)[c].email,
                       (*dtBaseCliente)[c].sexo,
                       (*dtBaseCliente)[c].estadoCivil,
                       (*dtBaseCliente)[c].dataNascimento,
                       (*dtBaseCliente)[c].endereco.rua,
                       (*dtBaseCliente)[c].endereco.numero,
                       (*dtBaseCliente)[c].endereco.bairro,
                       (*dtBaseCliente)[c].endereco.cidade,
                       (*dtBaseCliente)[c].endereco.estado);
            }
        }
    } else {
        printf("\n\t>> Nenhum registro para o filtro informado");
    }
    printf("\n");
}