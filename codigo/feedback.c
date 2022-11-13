#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../cabecalhos/feedback.h"

int menuFeedback(cliente **dtbaseCliente, int *qtd_Cliente,
                 filme **dtbaseFilme, int *qtd_Filme) {
    int opc = INT32_MAX;

    while (opc != 0) {
        system("cls");
        printf("Digite a opcao referente a operacao que deseja executar\n\n");
        printf("\t 0 - Sair \t\t 1 - Listar Clientes \n\t 2 - Listar Filmes \t 3 - Locacoes restantes para que o filme se pague"
               "\n\t 4 - Listar Locacoes \t 5 - Contas a receber \n\t 6 - Contas a pagar \t 7 - Movimentacao de Caixa \n");
        scanf("%d", &opc);
        line(30, "-\0");

        switch (opc) {
            case 1:
                return relatorioListagemClientes(dtbaseCliente, *qtd_Cliente);
            case 2:
                return relatorioListagemFilmes(dtbaseFilme, *qtd_Filme);
            case 3:
                return locacoesRestantes();
            case 4:
                return listarLocacoes();
            case 5:
                return listarContasAReceber();
            case 6:
                return listarContasAPagar();
            case 7:
                return listarMovimentacaoCaixa();
            case 0:
                return 1;
            default:
                printf("Esta não é uma opção válida, favor selecionar novamente.\n");
                break;
        }
    }
    return opc;
}
int listarMovimentacaoCaixa() {
    printf("Relatorio de movimentacao do caixa\n\n");
    filtroData filtro = obterFaixaDatas();
    // TODO: ver como vai ser feito
    return INT32_MAX;
}

int listarContasAPagar() {
    int tipo = INT32_MAX;
    printf("Relatorio de contas a pagar\n\n");
    while (tipo != 0) {
        printf("Digite a opcao referente ao tipo de relatorio que deseja\n");
        printf("0 - Sair \n1 - Faixa de codigos \n2 - Data\n");
        scanf("%d", &tipo);
        line(30, "-\0");
        switch(tipo){
            case 1: {
                filtroCodigo filtro = obterFaixaCodigo();
                // TODO: ver como vai ser feito
                return INT32_MAX;
            }
            case 2: {
                filtroData filtro = obterFaixaDatas();
                // TODO: ver como vai ser feito
                return INT32_MAX;
            }
            case 0: {
                return INT32_MAX;
            }
            default:
                printf("Esta não é uma opção válida, favor selecionar novamente.\n");
                break;
        }
    }
    return INT32_MAX;
}

int listarContasAReceber() {
    int tipo = INT32_MAX;
    printf("Relatorio de contas a receber\n\n");
    while (tipo != 0) {
        printf("Digite a opcao referente ao tipo de relatorio que deseja\n");
        printf("0 - Sair \n1 - Faixa de codigos \n2 - Data\n");
        scanf("%d", &tipo);
        line(30, "-\0");
        switch(tipo){
            case 1: {
                filtroCodigo filtro = obterFaixaCodigo();
                // TODO: ver como vai ser feito
                return INT32_MAX;
            }
            case 2: {
                filtroData filtro = obterFaixaDatas();
                // TODO: ver como vai ser feito
                return INT32_MAX;
            }
            case 0: {
                return INT32_MAX;
            }
            default:
                printf("Esta não é uma opção válida, favor selecionar novamente.\n");
                break;
        }
    }
    return INT32_MAX;
}

int listarLocacoes() {
    int tipo = INT32_MAX;
    printf("Relatorio de locacoes\n\n");
    while (tipo != 0) {
        printf("Digite a opcao referente ao tipo de relatorio que deseja\n");
        printf("0 - Sair \n1 - Vendas a vista \n2 - Vendas a prazo \n3 - Por vendedor \n");
        scanf("%d", &tipo);
        line(30, "-\0");
        switch(tipo){
            case 1: {
                // TODO: ver como vai ser feito
                return INT32_MAX;
            }
            case 2: {
                // TODO: ver como vai ser feito
                return INT32_MAX;
            }
            case 3: {
                // TODO: ver como vai ser feito
                return INT32_MAX;
            }
            case 0: {
                return INT32_MAX;
            }
            default:
                printf("Esta não é uma opção válida, favor selecionar novamente.\n");
                break;
        }
    }
    return INT32_MAX;
}

int locacoesRestantes() {
    printf("Relatorio de locacoes restantes para que o filme se pague\n\n");
    filtroCodigo filtro = obterFaixaCodigo();
    system("cls");
    // TODO: ver como vai ser feito o calculo de pagamento do livro
    return INT32_MAX;
}

int relatorioListagemFilmes(filme **dtBaseFilme, int qtdFilme) {
    printf("Relatorio de listagem de filmes\n\n");
    filtroCodigo filtro = obterFaixaCodigo();
    system("cls");
    if (qtdFilme > 0) {
        printf("\nID \t Nome \t Descrição \t Quant. Exemplares \t ID categoria \t Lingua\n");
        for (int c = 0; c < qtdFilme; c++) {
            if ((*dtBaseFilme)[c].codigo >= filtro.inicio && (*dtBaseFilme)[c].codigo <= filtro.fim) {
                system("cls");
                printf("----------------------------------------------------------------------------------------------------------------------------------\n");
                system("cls");
                printf("(%d)\t %s\t\t\t\t %d\t\t %d\t\t %s\n", (*dtBaseFilme)[c].codigo,
                       (*dtBaseFilme)[c].nome,
                       (*dtBaseFilme)[c].qtd,
                       (*dtBaseFilme)[c].c_categoria,
                       (*dtBaseFilme)[c].lingua);
            }
        }
    } else {
        printf("\n\t>> Nenhum registro para o filtro informado");
    }
    printf("\n");
    return INT32_MAX;
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
                filtroCodigo filtro = obterFaixaCodigo();
                filtrarClientesPorFaixaCodigo(dtBaseCliente, qtdCliente, filtro.inicio, filtro.fim);
                return INT32_MAX;
            }
            case 0: {
                return INT32_MAX;
            }
            default:
                printf("Esta não é uma opção válida, favor selecionar novamente.\n");
                break;
        }
    }
    return INT32_MAX;
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

filtroCodigo obterFaixaCodigo() {
    filtroCodigo filtro;
    int opc = 0;
    while(opc == 0){
        system("cls");
        printf("Digite o numero inicial da faixa de codigo pela qual deseja filtrar os registros: ");
        scanf("%d", &filtro.inicio);
        system("cls");
        printf("Digite o numero final da faixa de codigo pela qual deseja filtrar os registros: ");
        scanf("%d", &filtro.fim);
        system("cls");
        if (filtro.inicio >= filtro.fim) {
            printf("Faixa de codigos invalida, selecione novamente\n");
            system("cls");
            opc = 0;
        } else {
            opc = 1;
        }
    }
    return filtro;
}

filtroData obterFaixaDatas() {
    filtroData filtro;
    system("cls");
    printf("Digite o dia da data inicial: ");
    scanf("%d", &filtro.inicio.dia);
    printf("Digite o mes da data inicial: ");
    scanf("%d", &filtro.inicio.mes);
    printf("Digite o ano da data inicial: ");
    scanf("%d", &filtro.inicio.ano);
    system("cls");
    printf("Digite o dia da data final: ");
    scanf("%d", &filtro.fim.dia);
    printf("Digite o mes da data final: ");
    scanf("%d", &filtro.fim.mes);
    printf("Digite o ano da data final: ");
    scanf("%d", &filtro.fim.ano);
    system("cls");
    return filtro;
}