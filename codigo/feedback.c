#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../cabecalhos/feedback.h"


int menuFeedback(cliente **dtbaseCliente, int qtd_Cliente,
                 filme **dtbaseFilme, int qtd_Filme,
                 eFilme **dtbaseeFilme, int qtd_eFilme,
                 fCategoria **dtbaseCategoria, int qtdCategoria,
                 funcionarios **dtbaseFuncionario, int qtdFuncionario,
                 contaCliente **dtbaseContaCliente, int qtdContaCliente) {
    int opc = INT32_MAX;

    while (opc != 0) {
        system("cls");
        printf("Digite a opcao referente a operacao que deseja executar\n\n");
        printf("\t 0 - Sair \t\t 1 - Listar Clientes \n\t 2 - Listar Filmes \t 3 - Locacoes restantes para que o filme se pague"
               "\n\t 4 - Listar Locacoes \t 5 - Contas a receber \n\t 6 - Contas a pagar \t 7 - Movimentacao de Caixa \n>> ");
        scanf("%d", &opc);
        line(30, "-\0");

        switch (opc) {
            case 1:
                return relatorioListagemClientes(dtbaseCliente, qtd_Cliente);
            case 2:
                return relatorioListagemFilmes(dtbaseFilme, qtd_Filme);
            case 3:
                return locacoesRestantes(dtbaseFilme, qtd_Filme, dtbaseeFilme,
                                         qtd_eFilme, dtbaseCategoria, qtdCategoria,
                                         dtbaseContaCliente, qtdContaCliente);
            case 4:
                return listarLocacoes(dtbaseContaCliente, qtdContaCliente,dtbaseFuncionario,qtdFuncionario);
            case 5:
                return listarContasAReceber(dtbaseContaCliente, qtdContaCliente);
            case 6:
                return listarContasAPagar(dtbaseeFilme, qtd_eFilme);
            case 7:
                return listarMovimentacaoCaixa(dtbaseeFilme, qtd_eFilme, dtbaseContaCliente, qtdContaCliente);
            case 0:
                return 1;
            default:
                printf("Esta não é uma opção válida, favor selecionar novamente.\n");
                break;
        }
    }
    return opc;
}
int listarMovimentacaoCaixa(eFilme **bdEFilme, int qtdEFilme, contaCliente **bdContaCliente, int qtdContaCliente) {
    printf("Relatorio de movimentacao do caixa\n\n");
    filtroData *filtro = obterFaixaDatas();
    printf("COMPRAS\n");
    printf("\n ID \tID Fornecedor \tValor Restante \t Data Compra\n");
    for (int j = 0; j < qtdEFilme; ++j) {
        if ((*bdEFilme)[j].filmes->dtNota.dia >= filtro->inicio.ano &&
            (*bdEFilme)[j].filmes->dtNota.mes >= filtro->inicio.mes &&
            (*bdEFilme)[j].filmes->dtNota.ano >= filtro->inicio.ano &&
            (*bdEFilme)[j].filmes->dtNota.dia <= filtro->fim.dia &&
            (*bdEFilme)[j].filmes->dtNota.mes <= filtro->fim.mes &&
            (*bdEFilme)[j].filmes->dtNota.ano <= filtro->fim.ano)
        {
            printf("%d \t %d \t %f \t %d %d %d\n", (*bdEFilme)[j].ID, (*bdEFilme)[j].IDFornecedor,
                   (*bdEFilme)[j].filmes->valorDeve, (*bdEFilme)[j].filmes->dtNota.dia,
                   (*bdEFilme)[j].filmes->dtNota.mes,
                   (*bdEFilme)[j].filmes->dtNota.ano);
        }
    }

    printf("VENDAS\n");
    printf("\n ID \tID Cliente \tValor a Receber \t Data Emprestimo\n");
    for (int j = 0; j < qtdContaCliente; ++j) {
        if ((*bdContaCliente)[j].valorDeve > 0 &&
            (*bdContaCliente)[j].dEmprestimo->dFilme->dtemprestimo.dia >= filtro->inicio.ano &&
            (*bdContaCliente)[j].dEmprestimo->dFilme->dtemprestimo.mes >= filtro->inicio.mes &&
            (*bdContaCliente)[j].dEmprestimo->dFilme->dtemprestimo.ano >= filtro->inicio.ano &&
            (*bdContaCliente)[j].dEmprestimo->dFilme->dtemprestimo.dia <= filtro->fim.dia &&
            (*bdContaCliente)[j].dEmprestimo->dFilme->dtemprestimo.mes <= filtro->fim.mes &&
            (*bdContaCliente)[j].dEmprestimo->dFilme->dtemprestimo.ano <= filtro->fim.ano)
        {
            printf("%d \t %d \t %f \t %d %d %d\n", (*bdContaCliente)[j].ID, (*bdContaCliente)[j].idCliente,
                   (*bdContaCliente)[j].valorDeve, (*bdContaCliente)[j].dEmprestimo->dFilme->dtemprestimo.dia,
                   (*bdContaCliente)[j].dEmprestimo->dFilme->dtemprestimo.mes,
                   (*bdContaCliente)[j].dEmprestimo->dFilme->dtemprestimo.ano);
        }
    }
    return INT32_MAX;
}

int listarContasAPagar(eFilme **bdEFilme, int qtdEFilme) {
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
                printf("\n ID \tID Fornecedor \tValor Restante \t Data Compra\n");
                for (int j = 0; j < qtdEFilme; ++j) {
                    if ((*bdEFilme)[j].IDFornecedor >= filtro.inicio && (*bdEFilme)[j].IDFornecedor <= filtro.fim &&
                            (*bdEFilme)[j].filmes->qtdParcelas != (*bdEFilme)[j].filmes->parcelasPagas && (*bdEFilme)[j].filmes->tipoPagamento == 2) {

                        printf("%d \t %d \t %f \t %d %d %d\n", (*bdEFilme)[j].ID, (*bdEFilme)[j].IDFornecedor,
                               (*bdEFilme)[j].filmes->valorDeve, (*bdEFilme)[j].filmes->dtNota.dia,
                               (*bdEFilme)[j].filmes->dtNota.mes,
                               (*bdEFilme)[j].filmes->dtNota.ano);
                    }
                }
                return INT32_MAX;
            }
            case 2: {
                filtroData *filtro = obterFaixaDatas();
                printf("\n ID \tID Fornecedor \tValor Restante \t Data Compra\n");
                for (int j = 0; j < qtdEFilme; ++j) {
                    if ((*bdEFilme)[j].filmes->dtNota.dia >= filtro->inicio.ano &&
                        (*bdEFilme)[j].filmes->dtNota.mes >= filtro->inicio.mes &&
                        (*bdEFilme)[j].filmes->dtNota.ano >= filtro->inicio.ano &&
                        (*bdEFilme)[j].filmes->dtNota.dia <= filtro->fim.dia &&
                        (*bdEFilme)[j].filmes->dtNota.mes <= filtro->fim.mes &&
                        (*bdEFilme)[j].filmes->dtNota.ano <= filtro->fim.ano)
                    {
                        printf("%d \t %d \t %f \t %d %d %d\n", (*bdEFilme)[j].ID, (*bdEFilme)[j].IDFornecedor,
                               (*bdEFilme)[j].filmes->valorDeve, (*bdEFilme)[j].filmes->dtNota.dia,
                               (*bdEFilme)[j].filmes->dtNota.mes,
                               (*bdEFilme)[j].filmes->dtNota.ano);
                    }
                }
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

int listarContasAReceber(contaCliente **bdContaCliente, int qtdContaCliente) {
    int tipo = INT32_MAX;
    printf("Relatorio de contas a receber\n\n");
    while (tipo != 0) {
        printf("Digite a opcao referente ao tipo de relatorio que deseja\n");
        printf("0 - Sair \n1 - Faixa de codigos \n2 - Data\n");
        scanf("%d", &tipo);
        line(30, "-\0");
        int execute = 0;
        switch(tipo){
            case 1: {
                filtroCodigo filtro = obterFaixaCodigo();
                for (int j = 0; j < qtdContaCliente; ++j) {
                    if ((*bdContaCliente)[j].idCliente >= filtro.inicio && (*bdContaCliente)[j].idCliente <= filtro.fim) {
                        if ((int)(*bdContaCliente)[j].valorDeve > 0){
                            if (execute ==0){
                                printf("\n ID \tID Cliente \tValor a Receber \t Data Emprestimo\n");
                                execute = 1;
                            }
                            printf("%.4d \t %d \t %f \t %.2d/%.2d/.4%d\n", (*bdContaCliente)[j].ID, (*bdContaCliente)[j].idCliente,
                                   (*bdContaCliente)[j].valorDeve, (*bdContaCliente)[j].dEmprestimo->dFilme->dtemprestimo.dia,
                                   (*bdContaCliente)[j].dEmprestimo->dFilme->dtemprestimo.mes,
                                   (*bdContaCliente)[j].dEmprestimo->dFilme->dtemprestimo.ano);
                        }
                    }
                }
                system("pause");
                return INT32_MAX;
            }
            case 2: {
                filtroData *filtro = obterFaixaDatas();
                printf("\n ID \tID Cliente \tValor a Receber \t Data Emprestimo\n");
                for (int j = 0; j < qtdContaCliente; j++) {
                    for (int k = 0; k < (*bdContaCliente)[j].tamLocados -1 ;k++) {
                        for (int l = 0; l < (*bdContaCliente)[j].tamLocados -1 ;l++) {
                            //printf("\n\n%d %d",diasEntreDatas((*bdContaCliente)[j].dEmprestimo[k].dFilme[l].dtemprestimo,filtro->inicio),diasEntreDatas(filtro->fim,(*bdContaCliente)[j].dEmprestimo[k].dFilme[l].dtemprestimo));

                            if ((*bdContaCliente)[j].valorDeve > 0 &&
                                diasEntreDatas(filtro->inicio,(*bdContaCliente)[j].dEmprestimo[k].dFilme[l].dtemprestimo) >= 0 &&
                                diasEntreDatas((*bdContaCliente)[j].dEmprestimo[k].dFilme[l].dtemprestimo,filtro->fim) >= 0){
                                printf("%.4d \t %.4d \t %.2f \t %.2d %.2d %.4d\n", (*bdContaCliente)[j].ID,
                                       (*bdContaCliente)[j].idCliente,
                                       (*bdContaCliente)[j].valorDeve,
                                       (*bdContaCliente)[j].dEmprestimo[k].dFilme[l].dtemprestimo.dia,
                                       (*bdContaCliente)[j].dEmprestimo[k].dFilme[l].dtemprestimo.mes,
                                       (*bdContaCliente)[j].dEmprestimo[k].dFilme[l].dtemprestimo.ano);
                            }
                        }
                    }
                }
                system("pause");
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

int listarLocacoes(contaCliente **bdContaCliente, int qtdContaCliente, funcionarios **dtbase,int qtdFuncionario) {
    int tipo = INT32_MAX;
    printf("Relatorio de locacoes\n\n");
    while (tipo != 0) {
        printf("Digite a opcao referente ao tipo de relatorio que deseja\n");
        printf("0 - Sair \n1 - Vendas a vista \n2 - Vendas a prazo \n3 - Por vendedor \n>>");
        scanf("%d", &tipo);
        switch(tipo){
            case 1: {
                return vendaTipoPagamento(bdContaCliente, qtdContaCliente, 1);
            }
            case 2: {
                return vendaTipoPagamento(bdContaCliente, qtdContaCliente, 2);
            }
            case 3: {
                return vendaFuncionario(dtbase,qtdFuncionario,bdContaCliente,qtdContaCliente);
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

int vendaFuncionario(funcionarios **dtbase,int qtdFuncionario,contaCliente **bdContaCliente, int qtdContaCliente){
    int IDFuncionario = 0,erro = 0,execute = 0;
    do {
        for (int i = 0; i < qtdContaCliente; i++){
            printf(" (%d) %s ", (*dtbase)[i].codigo, (*dtbase)[i].nome);
        }
        char idtemp[5];
        printf("\n>>Informe o ID do Fornecedor: ");
        scanf("%s", idtemp);

        IDFuncionario = strtol(idtemp,NULL,10);
    }while (verificaIdFuncionario(dtbase,qtdFuncionario,IDFuncionario) == 0);

    for (int j = 0; j < qtdContaCliente; ++j) {
        for (int i = 0; i < (*bdContaCliente)[j].tamLocados - 1; i++){
            if ((*bdContaCliente)[j].dEmprestimo[i].IdFuncionario == IDFuncionario) {
                if (execute == 0) {
                    printf("\nFiltro: Funcionario %s\n\n", nomefuncionario(dtbase,qtdFuncionario,IDFuncionario));
                    printf("\n|%s|%s|%s|%s|%s|", formatstring(5, strlen("ID\0"), "ID\0"),
                           formatstring(30, strlen("Nome Cliente\0"), "Nome Cliente\0"),
                           formatstring(14, strlen("Valor Total\0"), "Valor Total\0"),
                           formatstring(22, strlen("Quantidade de Filmes\0"), "Quantidade de Filmes\0"),
                           formatstring(18, strlen("Data Pagamento\0"), "Data Pagamento\0"));
                    execute = 1;
                }
                printf("\n-----------------------------------------------------------------------------------------------");

                char valorTotal[10] = "\0\0\0\0\0\0\0\0\0\0";
                char qtdFilme[10] = "\0\0\0\0\0\0\0\0\0\0";

                sprintf(valorTotal, "%.2f", (*bdContaCliente)[j].dEmprestimo[i].valorTotal);
                sprintf(qtdFilme, "%d", (*bdContaCliente)[j].dEmprestimo[i].qtdFilme);

                printf("\n| %.3d |%s|%s|%s|    %.2d/%.2d/%.4d    |", (*bdContaCliente)[j].ID,
                       formatstring(30, (int)strlen((*bdContaCliente)[j].Nome), (*bdContaCliente)[j].Nome),
                       formatstring(14, (int)strlen(valorTotal), valorTotal),
                       formatstring(22, (int)strlen(qtdFilme), qtdFilme),(*bdContaCliente)[j].dEmprestimo[i].Dtpagamento.dia,
                       (*bdContaCliente)[j].dEmprestimo[i].Dtpagamento.mes,
                       (*bdContaCliente)[j].dEmprestimo[i].Dtpagamento.ano);

            }
        }
    }
    printf("\n");
    system("pause");
    return 0;
}


int vendaTipoPagamento(contaCliente **bdContaCliente, int qtdContaCliente, int tipoPagamento) {
    int execute = 0;

    char tipoPg[11]="A vista\0";
    if (tipoPagamento == 2){
        strcpy(tipoPg,"Parcelado\0");
    }

    for (int j = 0; j < qtdContaCliente; ++j) {
        for (int i = 0; i < (*bdContaCliente)[j].tamLocados - 1; i++){
            if ((*bdContaCliente)[j].dEmprestimo[i].tipoPagamento == tipoPagamento) {
                if (execute == 0) {
                    printf("\nFiltro: Pagamentos %s",tipoPg);
                    printf("\n|%s|%s|%s|%s|%s|", formatstring(5, strlen("ID\0"), "ID\0"),
                           formatstring(30, strlen("Nome Cliente\0"), "Nome Cliente\0"),
                           formatstring(14, strlen("Valor Total\0"), "Valor Total\0"),
                           formatstring(22, strlen("Quantidade de Filmes\0"), "Quantidade de Filmes\0"),
                           formatstring(18, strlen("Data Pagamento\0"), "Data Pagamento\0"));
                    execute = 1;
                }
                printf("\n-----------------------------------------------------------------------------------------------");

                char valorTotal[10] = "\0\0\0\0\0\0\0\0\0\0";
                char qtdFilme[10] = "\0\0\0\0\0\0\0\0\0\0";

                sprintf(valorTotal, "%.2f", (*bdContaCliente)[j].dEmprestimo[i].valorTotal);
                sprintf(qtdFilme, "%d", (*bdContaCliente)[j].dEmprestimo[i].qtdFilme);

                printf("\n| %.3d |%s|%s|%s|    %.2d/%.2d/%.4d    |", (*bdContaCliente)[j].ID,
                       formatstring(30, (int)strlen((*bdContaCliente)[j].Nome), (*bdContaCliente)[j].Nome),
                       formatstring(14, (int)strlen(valorTotal), valorTotal),
                       formatstring(22, (int)strlen(qtdFilme), qtdFilme),(*bdContaCliente)[j].dEmprestimo[i].Dtpagamento.dia,
                       (*bdContaCliente)[j].dEmprestimo[i].Dtpagamento.mes,
                       (*bdContaCliente)[j].dEmprestimo[i].Dtpagamento.ano);

            }
        }
    }
    printf("\n");
    system("pause");
    return INT32_MAX;
}

int locacoesRestantes(filme **dtBaseFilme, int qtdFilme, eFilme **dtBaseEFilme, int qtdEFilme,
                      fCategoria **dtbaseCategoria, int qtdCategoria, contaCliente **bdContaCliente, int qtdContaCliente) {
    printf("Relatorio de locacoes restantes para que o filme se pague\n\n");
    filtroCodigo filtro = obterFaixaCodigo();
    system("cls");
    if (qtdFilme > 0) {
        printf("\nNome \t Quantidade de Locacoes restante\n");
        for (int i = 0; i < qtdFilme; i++) {
            if ((*dtBaseFilme)[i].codigo >= filtro.inicio && (*dtBaseFilme)[i].codigo <= filtro.fim) {

                for (int f = 0; f < qtdEFilme; f++) {
                    if ((*dtBaseEFilme)[f].filmes->entradaFilmesCadastro->nome == (*dtBaseFilme)[i].nome) {

                        for (int c = 0; c < qtdCategoria; c++) {
                            if ((*dtBaseEFilme)[f].filmes->entradaFilmesCadastro->c_categoria == (*dtbaseCategoria)[c].codigo) {

                                float qtdLocada = 0;
                                for (int j = 0; j < qtdContaCliente; ++j) {
                                    if ((*bdContaCliente)[f].dEmprestimo->dFilme->nomeFilme == (*dtBaseFilme)[i].nome) {
                                        qtdLocada++;
                                    }
                                }
                                float qtdNecessaria = (*dtBaseEFilme)[f].filmes->valorTotal / (*dtbaseCategoria)[c].vAlocacao;
                                float qtdRestante = qtdNecessaria - qtdLocada;
                                system("cls");
                                printf("----------------------------------------------------------------------------------------------------------------------------------\n");
                                system("cls");
                                if (qtdRestante > 0) {
                                    printf("%s\t %f\n", (*dtBaseFilme)[i].nome, qtdNecessaria);
                                }
                                system("cls");

                            }
                        }
                    }
                }
            }
        }
    } else {
        printf("\n\t>> Nenhum registro para o filtro informado");
    }
    return INT32_MAX;
}


int relatorioListagemFilmes(filme **dtBaseFilme, int qtdFilme) {
    printf("Relatorio de listagem de filmes\n\n");
    filtroCodigo filtro = obterFaixaCodigo();
    system("cls");

    //Verfificar se tem algo para mostrar
    int mostrar = 0;
    for (int c = 0; c < qtdFilme; c++) {
        if ((*dtBaseFilme)[c].codigo >= filtro.inicio && (*dtBaseFilme)[c].codigo <= filtro.fim){
            mostrar++;
        }
    }

    if (qtdFilme > 0 && mostrar > 0) {
        printf("Filtro: Faixa de Codigo %d ate %d",filtro.inicio,filtro.fim);
        printf("\n---------------------------------------------------------------------------------------------------------");
        printf("\n|%s|%s|%s|%s|%s|\n",
               formatstring(4, strlen("ID\0"), "ID\0"),
               formatstring(30, strlen("Nome\0"), "Nome\0"),
               formatstring(30, strlen("Quantidade Exemplares\0"), "Quantidade Exemplares\0"),
               formatstring(20, strlen("Codigo Categoria\0"), "Codigo Categoria\0"),
               formatstring(15, strlen("Lingua\0"), "Lingua\0"));


        for (int c = 0; c < qtdFilme; c++) {
            if ((*dtBaseFilme)[c].codigo >= filtro.inicio && (*dtBaseFilme)[c].codigo <= filtro.fim){

                char codigo[10];
                char qtdChar[10];
                char codCategoria[10];
                sprintf(codigo, "%d", (*dtBaseFilme)[c].codigo);
                sprintf(qtdChar, "%d", (*dtBaseFilme)[c].qtd);
                sprintf(codCategoria, "%d", (*dtBaseFilme)[c].c_categoria);

                printf("---------------------------------------------------------------------------------------------------------\n");
                printf("|%s|%s|%s|%s|%s|\n", formatstring(4, (int) strlen(codigo), codigo),
                       formatstring(30, (int) strlen((*dtBaseFilme)[c].nome), (*dtBaseFilme)[c].nome),
                       formatstring(30, (int) strlen(qtdChar), qtdChar),
                       formatstring(20, (int) strlen(codCategoria), codCategoria),
                       formatstring(15, (int) strlen((*dtBaseFilme)[c].lingua), (*dtBaseFilme)[c].lingua));
            }
        }
        printf("\n---------------------------------------------------------------------------------------------------------");
    } else {
        printf("\n\t>> Nenhum registro para o filtro informado");
    }
    printf("\n");
    system("pause");
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
                scanf("%s", sexo);
                filtrarClientesPorSexo(dtBaseCliente, qtdCliente, sexo);
                system("pause");
                return INT32_MAX;
            }
            case 2: {
                filtroCodigo filtro = obterFaixaCodigo();
                filtrarClientesPorFaixaCodigo(dtBaseCliente, qtdCliente, filtro.inicio, filtro.fim);
                system("pause");
                return INT32_MAX;
            }
            case 0: {
                return INT32_MAX;
            }
            default:
                printf("Esta não é uma opção válida, favor selecionar novamente.\n");
                break;
        }
        system("pause");
    }
    return 0;
}

void filtrarClientesPorSexo(cliente **dtBaseCliente, int qtdCliente, char sexo[15]) {
    system("cls");
    //Tratamento String Sexo
    int execute = 0;
    if (qtdCliente > 0) {
        for (int c = 0; c < qtdCliente; c++) {
            char dtbaseSex[20];
            //Transformar string para minusculo e remover espaco em branco
            strcpy(dtbaseSex,(*dtBaseCliente)[c].sexo);

            stringLower(sexo);
            removeSpace(sexo);

            stringLower(dtbaseSex);
            removeSpace(dtbaseSex);

            if (strncmp(sexo, dtbaseSex, 1) == 0) {

                printf("---------------------------------------------------------------------------------\n");
                printf("(%d)\nNome: %s\nCPF: %s\nTelefone: %s\nE-mail: %s\nSexo: %s\nEstado civil: %s"
                       "\nData de Nascimento: %s \nRua: %s, %d \tBairo: %s \tCidade: %s - %s\n",
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
                execute = 1;
            }
        }
        printf("---------------------------------------------------------------------------------\n");
        if (execute != 1) {
            printf("\n\t>> Nenhum registro para o filtro informado");
        }
    } else{
        printf("\n\t>> Nenhum registro de cliente encontrado");
    }
    printf("\n");
}

void filtrarClientesPorFaixaCodigo(cliente **dtBaseCliente, int qtdCliente, int inicio, int fim) {
    system("cls");
    if (qtdCliente > 0) {
        printf(">> Filtro: Faixa de Codigo %d ate %d\n\n",inicio,fim);
        for (int c = 0; c < qtdCliente; c++) {
            if ((*dtBaseCliente)[c].id >= inicio && (*dtBaseCliente)[c].id <= fim) {
                printf("---------------------------------------------------------------------------------\n");
                printf("(%d)\nNome: %s\nCPF: %s\nTelefone: %s\nE-mail: %s\nSexo: %s\nEstado civil: %s"
                       "\nData de Nascimento: %s \nRua: %s, %d \tBairo: %s \tCidade: %s - %s\n",
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
    while(1){
        system("cls");
        printf("Digite o numero INICIAL da faixa de codigo pela qual deseja filtrar os registros: ");
        scanf("%d", &filtro.inicio);
        system("cls");
        printf("Digite o numero FINAL da faixa de codigo pela qual deseja filtrar os registros: ");
        scanf("%d", &filtro.fim);
        system("cls");
        if (filtro.inicio >= filtro.fim) {
            printf("[!] Faixa de codigos invalida, selecione novamente\n");
            system("cls");
        } else {
            break;
        }
    }
    return filtro;
}

filtroData *obterFaixaDatas() {
    //Alteração dos Scanf para evitar quebra no codigo
    filtroData *filtro = malloc(1 * sizeof(filtroData));

    char dia[3], mes[3], ano[5];

    system("cls");

    printf("Digite o dia da data INICIAL: ");
    scanf("%s", dia);
    filtro[0].inicio.dia = strtol(dia, NULL, 10);

    printf("Digite o mes da data INICIAL: ");
    scanf("%s", mes);
    filtro[0].inicio.mes = strtol(mes, NULL, 10);

    printf("Digite o ano da data INICIAL: ");
    scanf("%s", ano);
    filtro[0].inicio.ano = strtol(ano, NULL, 10);

    system("cls");

    printf("Digite o dia da data FINAL: ");
    scanf("%s", dia);
    filtro[0].fim.dia = strtol(dia, NULL, 10);

    printf("Digite o mes da data FINAL: ");
    scanf("%s", mes);
    filtro[0].fim.mes = strtol(mes, NULL, 10);

    printf("Digite o ano da data FINAL: ");
    scanf("%s", ano);
    filtro[0].fim.ano = strtol(ano, NULL, 10);

    system("cls");
    return filtro;
}