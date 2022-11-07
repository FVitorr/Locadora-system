#include "locacao.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <io.h>
//#include "../cabecalhos/datas.h"

/*Ids 0 não serão aceitos*/

operacoe objetoOperacoe(filme **dtbaseFilme, int qtdFilme,fCategoria **dtbaseCategoria,int qtdCategoria,int *idOperacao){
    int idtpm;
    operacoe newOpc;

    newOpc.ID = *idOperacao;
    *idOperacao = *idOperacao + 1;


    line(100,"Filme\0");

    do {
        printf("[0 - IDs Cadastrados ]Informe ID do Filme: ");
        scanf("%d", &idtpm);

        if (verificaIdFilme(dtbaseFilme, qtdFilme, idtpm) == 1) { //Verificar se o ID do filme Existe
            //Valor Pago
            int idCategoria = categoriaFilme(dtbaseFilme,qtdFilme, idtpm);
            newOpc.valorFilme = valorCategoria(dtbaseCategoria,qtdCategoria,idCategoria);

            if (newOpc.valorFilme == 0){
                printf("\n[!] Ocorreu um problema e nao foi possivel retornar o valor do Filme\n Por Favor verifique se as categorias foram cadastradas de maneira correta.\n");
                newOpc.valorFilme = -1;
                return newOpc;
            }
            newOpc.CodFilme = idtpm;
            //Incrementar o valor do campo emprestados
            altQtdEmprestadaFilme(dtbaseFilme,qtdFilme,idtpm);

            refazDados_filme(dtbaseFilme,qtdFilme, 1);

            //Nome Filme
            newOpc.nomeFilme = nomeFilme(dtbaseFilme,qtdFilme,idtpm);
            printf("\n>> Nome Filme: %s\n",newOpc.nomeFilme);

            printf("\n>> Valor Filme: R$ %.2f\n",newOpc.valorFilme);

            break;
        } else {
            printf("ID Invalido");
            //Mostrar ID de filmes Existentes
        }
    }while (1);

    dataAtual(&newOpc.dtemprestimo);
    printf("\n>> Data do emprestimo: %d/%d/%d\n",newOpc.dtemprestimo.dia,newOpc.dtemprestimo.mes,newOpc.dtemprestimo.ano);

    newOpc.dtdevolucao = somaDataDias(newOpc.dtemprestimo,7); //prevista
    newOpc.dtdevolucaoReal.dia = 0;
    newOpc.dtdevolucaoReal.mes = 0;
    newOpc.dtdevolucaoReal.ano = 0;
    printf("\n>> Data da Devolucao: %d/%d/%d\n",newOpc.dtdevolucao.dia,newOpc.dtdevolucao.mes,newOpc.dtdevolucao.ano);

    newOpc.devolvido = 0; // 0 - Não
    return  newOpc;
}


locados objetoLocados (int *idControleLocados,int idCliente,filme **dtbaseFilme,int qtdFilme,
                       fCategoria **dtbaseCategoria, int qtdCategoria){

    locados newObjeto;

    newObjeto.ID = *idControleLocados; // valor guardado na struct cliente
    *idControleLocados = *idControleLocados + 1; //Incrementar ID

    newObjeto.qtdFilme = 1;

    newObjeto.dFilme = malloc(newObjeto.qtdFilme * sizeof (operacoe));

    if ( newObjeto.dFilme == NULL){
        printf("Errp");
        system("pause");
    }

    newObjeto.ultimoIDOperacao = 0;

    newObjeto.Dtpagamento.dia = 0;
    newObjeto.Dtpagamento.mes = 0;
    newObjeto.Dtpagamento.ano = 0;


    while (1){
        operacoe  op = objetoOperacoe(dtbaseFilme,qtdFilme,dtbaseCategoria,qtdCategoria,&newObjeto.ultimoIDOperacao);

        if (op.valorFilme == -1){
            //Abortar Operação
            newObjeto.qtdFilme = -1;
            return newObjeto;
        }
        inserirOperacao(&newObjeto.dFilme,op, &newObjeto.qtdFilme);
        //saveOperacao(op, tipoConfig);

        char tmpOpc[2];
        int opc = 0;

        line(100,"1\0");

        printf("\nDigite: 1 - Adicionar mais Filme  \t0 - Finalizar \n>>OPC: ");
        scanf("%s",tmpOpc);

        opc = strtol(tmpOpc,NULL,10);

        if (opc != 1){
            break;
        }
    }
    //Valor da Alocação
    newObjeto.valorTotal = 0;
    for (int i = 0; i < newObjeto.qtdFilme -1; i++){
        newObjeto.valorTotal = newObjeto.valorTotal + (newObjeto.dFilme)[i].valorFilme;
    }
    //TIPO PAGAMENTO
    do{
        printf("\nValor total a ser Pago: R$ %.2f \n",newObjeto.valorTotal);
        printf("\nTipo do pagamento: [1- A vista \t2 - A prazo]: ");
        scanf("%d",&newObjeto.tipoPagamento);
    } while (newObjeto.tipoPagamento > 2 || newObjeto.tipoPagamento < 1);

    replacefloat(0,&newObjeto.valorEntrada);

    newObjeto.valordeve = 0;
    if (newObjeto.tipoPagamento == 1){//Pagamento a vista
        newObjeto.qtdParcelas = 1;
        newObjeto.parcelasPagas = 1;
        newObjeto.valordeve = 0; // Cliente pagou tudo
//        //Adicionar valor ao caixa
//        monetario->caixa = monetario->caixa + newObjeto.valorPago;
//        //Adicionar valor pago a conta cliente fora da função
        dataAtual(&newObjeto.Dtpagamento);

    }else{
        int ent = 0;
        float qtdParcelas;
        float valorE;
        newObjeto.qtdParcelas = 0;
        newObjeto.parcelasPagas = 0;
        // Valores de entrada
        do{
            printf("\n >>Deseja dar entrada ?  [ 1 - Sim \t0 - Nao ]: ");
            scanf("%d",&ent);
            if (ent == 0 || ent == 1){break;}
            else{ printf("\n>> Opc Invalida");}
        } while (1);

        int valorInvalido = 0;
        if (ent == 1){
            do {
                if (valorInvalido == 1){
                    printf("\nValor Invalido, por gentileza informar um valor inferior a R$ %.2f",newObjeto.valorTotal);
                }
                //Valor de entrada
                printf("\n>> Valor R$ ");
                scanf("%f", &valorE);

                valorInvalido = 1;
            } while (valorE >= newObjeto.valorTotal);
            //Calcular restante(valordeve) =  Valor Total menos valor de entrada
            newObjeto.valordeve = newObjeto.valorTotal - valorE;
            //Adicionar valor de entrada
            newObjeto.valorEntrada = valorE;

            //monetario->caixa = monetario->caixa + valorE;


            //Dividir o restante
            do{
                printf("\n>> Deseja dividir o valor R$ %.2f de quantas Vezes [3x Parcelas Maximas] ? ", newObjeto.valordeve);
                scanf("%f",&qtdParcelas);
                if (qtdParcelas <= 3 && qtdParcelas > 0){ break;}
                else{ printf("\n[!] Quantidade de Parcelas invalido\n");}
            } while (1);


            float valorParcelas = newObjeto.valordeve/qtdParcelas;
            printf("\nA conta foi dividida em %f parcelas \n O Valor de cada parcela e: R$ %.2f\n",qtdParcelas,valorParcelas);
            newObjeto.qtdParcelas = (int)qtdParcelas;

        }else{
            //Caso não seja fornecido uma  entrada
            do{
                printf("\n>> Deseja dividir o valor R$ %.2f de quantas Vezes [3x Parcelas Maximas] ? ",newObjeto.valorTotal);
                scanf("%f",&qtdParcelas);
                if (qtdParcelas <= 3 && qtdParcelas > 0){ break;}
                else{ printf("\n[!] Quantidade de Parcelas invalido\n");}
            } while (1);

            float valorParcelas = newObjeto.valorTotal/qtdParcelas;
            printf("\nA conta foi dividida em %f parcelas \n O Valor de cada parcela e: R$ %.2f",qtdParcelas,valorParcelas);
            newObjeto.qtdParcelas = (int)qtdParcelas;
            newObjeto.valordeve = newObjeto.valorTotal;
        }
        //monetario->contasReceber = monetario->contasReceber + newObjeto.valorPago;
    }
    newObjeto.TDdevolvido = 0; // 0 - Não

//    printf("(%d)\nCodigo Cliente: %d\n"
//           "Nome Cliente: %s\n"
//           "Quantidade de Filmes: %d\n"
//           "Valor Total: R$ %.2f\n",newObjeto.ID,newObjeto.CodCliente,newObjeto.Nome,newObjeto.qtdFilme,newObjeto.valorPago);
    return newObjeto;
}

int emprestaFilme(contaCliente **dtBaseCCliente,int *qtd_CCliente,int *tamanho_CCliente,int *IdContaCliente
                   ,int *key_cliente,cliente **dtbaseCliente,int qtdcliente,
                   filme **dtbaseFilme,int qtdFilme,operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                   locados **dtbaseLocados, int *qtdLocados, int *tamanhoLocados,
                   fCategoria **dtbaseCategoria, int qtdCategoria, int *KEY_Operacao,financeiro *monetario,int tipoConfig){
    //Cliente
    int idCliente;
    do {
        printf("\n\nClientes Disponiveis: ");
        for (int i = 0; i < qtdcliente; i++){
            printf("  (%d) %s  ",(*dtbaseCliente)[i].id,(*dtbaseCliente)[i].nome);
        }

        printf("\n\nInforme ID do Cliente: ");
        scanf("%d", &idCliente);

        int confirm;
        if (verificaIdCliente(dtbaseCliente, qtdcliente, idCliente) == 1) { //Verifica se o cliente existe

            printf("\nNome do Cliente: %s \nCorreto [1 - SIM   0 - Nao]: ", nomeCliente(dtbaseCliente,qtdcliente,idCliente));
            scanf("%d",&confirm);

            if (confirm != 0) {
                //Verificar se conta cliente existe
                if (verificaConta(dtBaseCCliente, *qtd_CCliente, idCliente) == 1) {
                    //Conta Cliente existe
                    printf("\nConta CLiente Existe\n");

                    int indexCliente = posicaoContaArray(dtBaseCCliente,*qtd_CCliente,idCliente);

                    if (indexCliente == -1){
                        return -1;
                    }

                    //int key_client = (*dtBaseCCliente)[indexCliente].key_cliente;

                    locados novaLocacao = objetoLocados(&(*dtBaseCCliente)[indexCliente].IDlocado,idCliente,dtbaseFilme,qtdFilme,
                                                        dtbaseCategoria,qtdCategoria);

                    //(*dtBaseCCliente)[indexCliente].IDlocado = (*dtBaseCCliente)[indexCliente].IDlocado + 1;

                    if (novaLocacao.qtdFilme != -1) {
                        //controle de caixa
                        if (novaLocacao.tipoPagamento == 1) { //Pagamento a Vista
                            (*dtBaseCCliente)[indexCliente].valorPago = (*dtBaseCCliente)[indexCliente].valorPago +
                                                                        novaLocacao.valorTotal; //Adicionar valor ao caixa da locadora
                            monetario->caixa = monetario->caixa + novaLocacao.valorTotal; //Adicionar valor pago a conta cliente
                        } else { // pagamento a prazo
                            (*dtBaseCCliente)[indexCliente].valorPago =
                                    (*dtBaseCCliente)[indexCliente].valorPago + novaLocacao.valorEntrada;
                            monetario->caixa = monetario->caixa + novaLocacao.valorEntrada; //Adicionar valor pago a conta cliente

                            (*dtBaseCCliente)[indexCliente].valorDeve =
                                    (*dtBaseCCliente)[indexCliente].valorDeve + novaLocacao.valordeve;

                            monetario->contasReceber = monetario->contasReceber + novaLocacao.valordeve;
                        }
                        //listCCliente(dtbaseCliente, qtdcliente);


                        inserirLocados(&(*dtBaseCCliente)[indexCliente].dEmprestimo, novaLocacao, &(*dtBaseCCliente)[indexCliente].tamLocados);
                        //saveLocacao(novaLocacao, tipoConfig);

                        refazDadosCCliente(dtBaseCCliente, *qtd_CCliente, tipoConfig);
                        break;
                    }
                    return 1;
                } else {

                    contaCliente novoCliente = objetoCCliente(IdContaCliente, idCliente, dtbaseCliente, qtdcliente,idCliente);
                    //Criar objeto Locado
                    locados novaLocacao = objetoLocados(&novoCliente.IDlocado,idCliente,dtbaseFilme,qtdFilme,
                                                        dtbaseCategoria,qtdCategoria);

                    if (novaLocacao.qtdFilme != -1) {
                        //controle de caixa
                        if (novaLocacao.tipoPagamento == 1) { //Pagamento a Vista
                            novoCliente.valorPago = novoCliente.valorPago +
                                                    novaLocacao.valorTotal; //Adicionar valor ao caixa da locadora
                            monetario->caixa = monetario->caixa + novaLocacao.valorTotal; //Adicionar valor pago a conta cliente
                        } else { // pagamento a prazo
                            novoCliente.valorPago = novoCliente.valorPago + novaLocacao.valorEntrada;
                            monetario->caixa = monetario->caixa + novaLocacao.valorEntrada; //Adicionar valor pago a conta cliente

                            novoCliente.valorDeve = novoCliente.valorDeve + novaLocacao.valordeve;

                            monetario->contasReceber = monetario->contasReceber + novaLocacao.valordeve;
                        }

                        //alterar chave cliente
                        //*key_cliente = *key_cliente + 1;

                        inserirLocados(&novoCliente.dEmprestimo, novaLocacao, &novoCliente.tamLocados);
                        //saveLocacao(novaLocacao, tipoConfig);
                        //Salvar Cliente
                        inserirCCliente(dtBaseCCliente, novoCliente, qtd_CCliente, tamanho_CCliente);
                        saveContaCliente(novoCliente, tipoConfig);
                    }
                }
                break;
            }
        } else {
            printf("\nID invalido");
            //Permitir que clientes sejam listados
        }
    } while(1);
    return 0;
}


contaCliente objetoCCliente(int *IdContaCliente,int key_cliente,cliente **dtbaseCliente,int qtdcliente,int idCliente){
    line(100,"Conta Cliente");
    contaCliente novoCliente;

    novoCliente.ID = *IdContaCliente;
    *IdContaCliente = *IdContaCliente  + 1;

    novoCliente.idCliente = idCliente;

    novoCliente.Nome = nomeCliente(dtbaseCliente,qtdcliente,idCliente);

    novoCliente.valorDeve = 0;
    novoCliente.valorPago = 0;

    novoCliente.tamLocados = 1;
    novoCliente.dEmprestimo = malloc(novoCliente.tamLocados * sizeof (locados));

    novoCliente.IDlocado = 0;

    return novoCliente;
}


int posicaoContaArray(contaCliente **dtbaseCCliente, int qtdCCliente, int idCliente){
    for (int c = 0; c < qtdCCliente; c++) {
        if ((*dtbaseCCliente)[c].idCliente == idCliente ){
            return c;
        }
    }
    return 0;
}


int verificaConta(contaCliente **dtbaseCcliente, int qtdCcliente, int idCliente){ // Verifica se o cliente ja realizou uma Locação antes
    for (int c = 0; c < qtdCcliente; c++) {
        if ((*dtbaseCcliente)[c].idCliente == idCliente ){
            return 1;
        }
    }
    return 0;
}


int listLocacao(contaCliente **dtbase, int qtdCliente, int IDcliente, int IDlocado, int mostraDevolvidos){ //0 - não 1- sim
    int temFilme = 0;
    for (int i = 0; i  < qtdCliente; i++){
        if (((*dtbase)[i].idCliente == IDcliente) || (IDcliente == -1)){

            printf("(%d) Nome Cliente: %s \n"
                   "Valor Pago: R$ %f\n"
                   "Valor a Receber: R$ %f\n",(*dtbase)[i].ID,(*dtbase)[i].Nome,(*dtbase)[i].valorPago,(*dtbase)[i].valorDeve);

            for (int j = 0; j < (*dtbase)[i].tamLocados - 1 ; j++){
                if ((*dtbase)[i].dEmprestimo[j].ID == IDlocado || IDlocado == -1) {
                    printf("\nID Nota (%d)\n", (*dtbase)[i].dEmprestimo[j].ID);

                    for (int k = 0; k < (*dtbase)[i].dEmprestimo[j].qtdFilme - 1; k++) {
                        char devolvido[4];
                        if ((*dtbase)[i].dEmprestimo[j].dFilme[k].devolvido == 1) {
                            strcpy(devolvido, "Sim\0");
                        } else {
                            strcpy(devolvido, "Nao\0");
                        }
                        if ((*dtbase)[i].dEmprestimo[j].dFilme[k].devolvido == 0 || mostraDevolvidos == 1){

                            printf("\n  (%d) Codigo Filme: %d\n  Descricao Filme: %s\n  Valor Emprestimo: R$ %.2f\n"
                                   "  Data Emprestimo: %d/%d/%d\t"
                                   "  Data Devolucao Prevista: %d/%d/%d\t"
                                   "  Data Devolucao Real: %d/%d/%d\n"
                                   "  Devolvido: %s\n",
                                   (*dtbase)[i].dEmprestimo[j].dFilme[k].ID,
                                   (*dtbase)[i].dEmprestimo[j].dFilme[k].CodFilme,
                                   (*dtbase)[i].dEmprestimo[j].dFilme[k].nomeFilme,
                                   (*dtbase)[i].dEmprestimo[j].dFilme[k].valorFilme,
                                   (*dtbase)[i].dEmprestimo[j].dFilme[k].dtemprestimo.dia,
                                   (*dtbase)[i].dEmprestimo[j].dFilme[k].dtemprestimo.mes,
                                   (*dtbase)[i].dEmprestimo[j].dFilme[k].dtemprestimo.ano,
                                   (*dtbase)[i].dEmprestimo[j].dFilme[k].dtdevolucao.dia,
                                   (*dtbase)[i].dEmprestimo[j].dFilme[k].dtdevolucao.mes,
                                   (*dtbase)[i].dEmprestimo[j].dFilme[k].dtdevolucao.ano,
                                   (*dtbase)[i].dEmprestimo[j].dFilme[k].dtdevolucaoReal.dia,
                                   (*dtbase)[i].dEmprestimo[j].dFilme[k].dtdevolucaoReal.mes,
                                   (*dtbase)[i].dEmprestimo[j].dFilme[k].dtdevolucaoReal.ano,
                                   devolvido);
                            temFilme++;
                        }
                    }
                    printf("\nQuantidade Filme: %d \t"
                           "Valor Total: R$ %.2f\t", (*dtbase)[i].dEmprestimo[j].qtdFilme - 1,
                           (*dtbase)[i].dEmprestimo[j].valorTotal);
                    if ((*dtbase)[i].dEmprestimo[j].tipoPagamento == 2) {
                        printf("Valor em Debito: %.2f \tValor entrada: R$ %.2f\n"
                               "Qtd Parcelas: %d de %d\t", (*dtbase)[i].dEmprestimo[j].valordeve,
                               (*dtbase)[i].dEmprestimo[j].valorEntrada,
                               (*dtbase)[i].dEmprestimo[j].parcelasPagas, (*dtbase)[i].dEmprestimo[j].qtdParcelas);
                    }
                    //Mais para frente talvez usar lista Dinamica para Data do pagamento
                    printf("Data Pagamento: %d/%d/%d \n\n", (*dtbase)[i].dEmprestimo[j].Dtpagamento.dia,
                           (*dtbase)[i].dEmprestimo[j].Dtpagamento.mes, (*dtbase)[i].dEmprestimo[j].Dtpagamento.ano);
                }
            }
        }
    }
    return temFilme;
}

int primeiraexecute = 0;
int menuLocacao(filme **dtbaseFilme,int qtdFilme,
                cliente **dtbaseCliente,int qtdcliente,
                funcionarios **dtbaseFuncionarios, int qtdFuncionarios,int idFuncionarioLogado,
                locados **dtbaseLocados, int *qtdLocados, int *tamanhoLocados, int *idLocados,
                operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                contaCliente **dtbaseCCliente,int *qtdCCliente,int *tamanho_CCliente,int *idCCliente,
                fCategoria **dtbaseCategoria, int qtdCategoria,int *KEY_Operacao, int *KEY_Cliente,
                fornecedor **dtbaseFornecedor, int *qtdFornecedor,int *tamFornecedor,int *idEntradaFIlme,
                eFilme **dtBaseeFilme, int *tam_eFilme, int *qtd_eFilme,financeiro *monetario,int tipo_config){

    if (primeiraexecute == 0){
        //carregarDados_CClientes(dtbaseCCliente,qtdCCliente,tamanho_CCliente,idCCliente,KEY_Cliente,tipo_config);
        carregarDados_Efilme(dtBaseeFilme, qtd_eFilme, tam_eFilme,tipo_config);
        primeiraexecute = 1;
    }
    //system("cls");
    if ( qtdCategoria == 0){
        printf("\n\n\t[!] Menu Nao disponivel, Precisamos que os dados de Categoria sejam preenchidos.\n"
               "\t\tPreencha e retorne aqui\n\n\n\n");
        system("pause");
        return 1;
    }

    if ( qtdFilme == 0){
        printf("\n\n\t[!] Menu Nao disponivel, Precisamos que os dados de FIlme sejam preenchidos.\n"
               "\t\tPreencha e retorne aqui\n\n\n\n");
        system("pause");
        return 1;
    }


    printf("Funcionario: %s",nomefuncionario(dtbaseFuncionarios, qtdFuncionarios,idFuncionarioLogado));
    line(100,"Locacao\0");
    printf("\t 1- Emprestar \n\t 2- Devolver \n\t 3- Vizualizar Operacoes \n\t 4- Pagamento Cliente"
           "\n\t 5- Entrada de Filme"
           "\n\t 6- Pagamento Fornecedor"
           "\n\t 7- Vizualizar Entrada Filme"
           "\n\t 0- Sair");
    line(100,"1\0");

    int op;
    char opc[2];
    do {
        printf(">>OPC: ");
        scanf("%s", opc);

        op = strtol(opc,NULL,10);
    } while (op < 0 || op > 7);

    if (op == 1){
        emprestaFilme(dtbaseCCliente,qtdCCliente,tamanho_CCliente,idCCliente,KEY_Cliente,dtbaseCliente,qtdcliente,dtbaseFilme,qtdFilme,
                      dtbaseOperacoe,qtdOperacoe,tamanhoOperacoe,dtbaseLocados,qtdLocados,tamanhoLocados,dtbaseCategoria,qtdCategoria,KEY_Operacao,monetario,tipo_config);

    }else if (op == 2){
        //Devolução;
        devolucaoFilmes(dtbaseCCliente,*qtdCCliente,tipo_config);
    }else if (op == 3){
        listLocacao(dtbaseCCliente, *qtdCCliente, -1,-1,0);
        //listCCliente(dtbaseCCliente,*qtdCCliente);
        //listLocacao(dtbaseLocados,*qtdLocados,dtbaseOperacoe,*qtdCCliente,-1);
        system("pause");
    }else if (op == 4){
        //pagarParcelas(dtbaseCCliente,*qtdCCliente,dtbaseLocados,*qtdLocados,monetario,tipo_config);
    } else if (op == 5){
        entradaFilmes(dtbaseFornecedor,qtdFornecedor,tamFornecedor,idEntradaFIlme,dtBaseeFilme,tam_eFilme,qtd_eFilme,monetario,tipo_config);
    }else if (op == 6){
        pagarParcelaEmprestaFilme(dtBaseeFilme,*qtd_eFilme,monetario,tipo_config);
    }else if (op == 7){
        list_eFilme(dtBaseeFilme,*qtd_eFilme,-1,-1,-1,0);
        printf("\n\n");
        system("pause");
    }
    else{
        return 1;
    }
    return 0;
}

int inserirLocados(locados **dtbaseLocados,locados newEntry,int *tamanhoLocados){
    //Se a quantidade de categorias for igual ao tamanho alocado da lista -> espandir
    *dtbaseLocados = (locados *) realloc(*dtbaseLocados, *tamanhoLocados * sizeof(locados));

    if (*dtbaseLocados == NULL){
        printf("\n  Erro na alocação de memória!");
        system("pause");
        return 0;
    }
    // adc obj ao bd local
    (*dtbaseLocados)[*tamanhoLocados - 1] = newEntry;
    *tamanhoLocados = *tamanhoLocados + 1;

    return 1;
}

int inserirOperacao(operacoe **dtbaseOperacao,operacoe newEntry, int *tamanhoOperacao){

    *dtbaseOperacao = (operacoe *) realloc(*dtbaseOperacao, *tamanhoOperacao * sizeof(operacoe));

    if (*dtbaseOperacao == NULL){
        printf("\n  Erro na alocação de memória!");
        system("pause");
        return 0;
    }
    // adc obj ao bd local
    (*dtbaseOperacao)[*tamanhoOperacao - 1] = newEntry;
    *tamanhoOperacao = *tamanhoOperacao + 1;

    return 1;
}

int inserirCCliente(contaCliente **dtbaseCCliente,contaCliente newEntry, int *qtdCCliente, int *tamanhoCCliente){
    //Se a quantidade de categorias for igual ao tamanho alocado da lista -> espandir
    if (*qtdCCliente == *tamanhoCCliente)
    {
        *tamanhoCCliente = *tamanhoCCliente + 1;
        *dtbaseCCliente = (contaCliente *) realloc((*dtbaseCCliente), *tamanhoCCliente * sizeof(contaCliente));
    }
    if (*dtbaseCCliente == NULL)
    {
        printf("\n  Erro na alocação de memória!");
        system("pause");
        return 0;
    }
    // adc obj ao bd local
    (*dtbaseCCliente)[*tamanhoCCliente - 1] = newEntry;
    *qtdCCliente = *qtdCCliente + 1;

    return 1;
}

int saveContaCliente(contaCliente objeto, int tipo_config){
    FILE *contaclienteF = NULL;

    if (tipo_config == 1){//Arquivo TXT
        if (verifica_arquivos(tipo_config,"cpyLocacao.txt\0") == 1){
            contaclienteF = fopen("cpyLocacao.txt", "a");
        } else{
            contaclienteF = fopen("cpyLocacao.txt", "w");
        }

        if (contaclienteF == NULL){ // Se a abertura falhar
            return 1;
        }

        fprintf(contaclienteF, "%d\n%d\n%s\n%f\n%f\n%d\n%d\n",
                objeto.ID,
                objeto.idCliente,
                objeto.Nome,
                objeto.valorDeve,
                objeto.valorPago,
                objeto.tamLocados,
                objeto.IDlocado);
        for (int i = 0; i < objeto.tamLocados - 1; i++){
            fprintf(contaclienteF, "%d\n%d\n%f\n%f\n%f\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
                    objeto.dEmprestimo[i].ID,
                    objeto.dEmprestimo[i].qtdFilme,
                    objeto.dEmprestimo[i].valorTotal,
                    objeto.dEmprestimo[i].valordeve,
                    objeto.dEmprestimo[i].valorEntrada,
                    objeto.dEmprestimo[i].tipoPagamento,
                    objeto.dEmprestimo[i].Dtpagamento.dia,
                    objeto.dEmprestimo[i].Dtpagamento.mes,
                    objeto.dEmprestimo[i].Dtpagamento.ano,
                    objeto.dEmprestimo[i].qtdParcelas,
                    objeto.dEmprestimo[i].parcelasPagas,
                    objeto.dEmprestimo[i].TDdevolvido,
                    objeto.dEmprestimo[i].ultimoIDOperacao);
            for (int j = 0; j < objeto.dEmprestimo[i].qtdFilme - 1; j++){
                fprintf(contaclienteF, "%d\n%d\n%s\n%f\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
                        objeto.dEmprestimo[i].dFilme[j].ID,
                        objeto.dEmprestimo[i].dFilme[j].CodFilme,
                        objeto.dEmprestimo[i].dFilme[j].nomeFilme,
                        objeto.dEmprestimo[i].dFilme[j].valorFilme,
                        objeto.dEmprestimo[i].dFilme[j].dtemprestimo.dia,
                        objeto.dEmprestimo[i].dFilme[j].dtemprestimo.mes,
                        objeto.dEmprestimo[i].dFilme[j].dtemprestimo.ano,
                        objeto.dEmprestimo[i].dFilme[j].dtdevolucao.dia,
                        objeto.dEmprestimo[i].dFilme[j].dtdevolucao.mes,
                        objeto.dEmprestimo[i].dFilme[j].dtdevolucao.ano,
                        objeto.dEmprestimo[i].dFilme[j].dtdevolucaoReal.dia,
                        objeto.dEmprestimo[i].dFilme[j].dtdevolucaoReal.mes,
                        objeto.dEmprestimo[i].dFilme[j].dtdevolucaoReal.ano,
                        objeto.dEmprestimo[i].dFilme[j].devolvido);
            }
        }

    }else{ //Arquivo BINARIO
        if (verifica_arquivos(tipo_config,"cpyLocacao.bin\0") == 1){
            contaclienteF = fopen("cpyLocacao.bin", "ab");
        } else{
            contaclienteF = fopen("cpyLocacao.bin", "wb");
        }
        if (contaclienteF == NULL){ // Se a abertura falhar
            return 1;
        }
        fwrite(&objeto, sizeof(contaCliente), 1,contaclienteF);
    }
    fclose(contaclienteF);
    contaclienteF = NULL;
    return 0;
}

void corrigirIdCCliente(contaCliente  **dtbase, int qtdLocados,int *codigo){
    for (int i = 0; i < qtdLocados ; i++){
        if((*dtbase)[i].ID == *codigo ){
            *codigo =  (*dtbase)[i].ID + 1;
        }
    }
}


int carregarDados_CClientes(contaCliente **dtBaseCCliente, int *qtd_CCliente, int *tamanhoCCliente, int *idControle, int * Key_Cliente,int tipo_config) {
    FILE *fileLocados = NULL;
    contaCliente new;

    int *qtdTemp = qtd_CCliente;

    int t = 0;
    if (tipo_config == 1){ //Arquivo TXT
        fileLocados = fopen("cpyLocacao.txt", "r");

        if (fileLocados == NULL){
            printf("\nErro na Leitura 'cpyLocacao.txt' \n");
            return 1;
        }

        while (!feof(fileLocados)){
            if (!filelength(fileno(fileLocados))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fscanf(fileLocados, "%d\n", &new.ID);
            fscanf(fileLocados, "%d\n", &new.idCliente);

            char nome[120];
            fgets(nome, 120, fileLocados);
            new.Nome = string_to_pointer(nome);

            fscanf(fileLocados, "%f\n", &new.valorDeve);
            fscanf(fileLocados, "%f\n", &new.valorPago);
            fscanf(fileLocados, "%d\n", &new.tamLocados);
            fscanf(fileLocados, "%d\n", &new.IDlocado);

            new.dEmprestimo = malloc(new.tamLocados * sizeof (locados));

            if (new.dEmprestimo == NULL){
                printf("Erro na Alocaocao de Memoria -> new.dEmprestimo");
                system("pause");
                exit(1);
            }

            for (int i = 0; i < new.tamLocados - 1; i++){
                char ID[4];
                fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].ID);
                fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].qtdFilme);
                fscanf(fileLocados, "%f\n", &new.dEmprestimo[i].valorTotal);
                fscanf(fileLocados, "%f\n", &new.dEmprestimo[i].valordeve);
                fscanf(fileLocados, "%f\n", &new.dEmprestimo[i].valorEntrada);
                fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].tipoPagamento);
                fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].Dtpagamento.dia);
                fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].Dtpagamento.mes);
                fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].Dtpagamento.ano);
                fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].qtdParcelas);
                fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].parcelasPagas);
                fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].TDdevolvido);
                fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].ultimoIDOperacao);

                new.dEmprestimo[i].dFilme = malloc(new.dEmprestimo[i].qtdFilme * sizeof (operacoe));

                if (new.dEmprestimo[i].dFilme == NULL){
                    printf("Erro na Alocaocao de Memoria -> new.dEmprestimo[i].dFilme");
                    system("pause");
                    exit(1);
                }
                for (int j = 0; j < new.dEmprestimo[i].qtdFilme - 1; j++){

                    fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].dFilme[j].ID);
                    fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].dFilme[j].CodFilme);

                    char nome[120];
                    fgets(nome, 120, fileLocados);
                    new.dEmprestimo[i].dFilme[j].nomeFilme = string_to_pointer(nome);

                    fscanf(fileLocados, "%f\n", &new.dEmprestimo[i].dFilme[j].valorFilme);
                    fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].dFilme[j].dtemprestimo.dia);
                    fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].dFilme[j].dtemprestimo.mes);
                    fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].dFilme[j].dtemprestimo.ano);
                    fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].dFilme[j].dtdevolucao.dia);
                    fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].dFilme[j].dtdevolucao.mes);
                    fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].dFilme[j].dtdevolucao.ano);
                    fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].dFilme[j].dtdevolucaoReal.dia);
                    fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].dFilme[j].dtdevolucaoReal.mes);
                    fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].dFilme[j].dtdevolucaoReal.ano);
                    fscanf(fileLocados, "%d\n", &new.dEmprestimo[i].dFilme[j].devolvido);
                }
            }

            t = inserirCCliente(dtBaseCCliente,new,qtd_CCliente,tamanhoCCliente);

            if (t == 0){
                printf("\nAcao Interrompida");
                break;
            }

            if (*idControle >= new.ID){
                *idControle = new.ID + 1;
            }
        }
    }
    else { //Arquivo BIN
        fileLocados = fopen("cpyLocacao.bin", "rb");
        if (fileLocados == NULL){
            printf("\nErro na Leitura 'cpyLocacao.bin' \n");
            return 1;
        }
        while (!feof(fileLocados)){
            if (!filelength(fileno(fileLocados))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fread(&new,sizeof(locados),1,fileLocados);
//            if (verificaIdFilme(dtBase,*qtdFilme,new.codigo) == 0){
//                t = inserirFilme(dtBase,new,qtdFilme,tamanhoFilme,tipo_config);
//                if (*id <= new.codigo) {
//                    *id = new.codigo + 1;
//                }
//            }

            if (t == 0){
                printf("\nAcao Interrompida");
                break;
            }
        }
    }
    fclose(fileLocados);
    fileLocados = NULL;
    return 0;
}

int refazDadosCCliente(contaCliente **dtbase, int qtdCCliente, int tipo_config){
    return 0;
}
//
//int pagarParcelas(contaCliente **dtbaseCCliente,int qtdCCliente, locados **dtbaseLocados, int qtdLocados,financeiro *monetario,int tipoconfig){
//    line(100,"Pagamento Parcelas\0");
//    printf("\nContas Disponiveis:\n\n");
//    for (int i = 0; i < qtdCCliente; i++){
//        printf(" (ID: %d) Cliente: %s   ",(*dtbaseCCliente)[i].ID,(*dtbaseCCliente)[i].Nome);
//    }
//    int erroID = 0,IdCliente;
//    do{
//        if (erroID == 1){
//            printf("\nID invalido por gentileza informe um valido\n");
//        }
//        printf("\n\nInforme o ID do Cliente: ");
//        scanf("%d",&IdCliente);
//        erroID = 1;
//    } while (verificaConta(dtbaseCCliente,qtdCCliente,IdCliente) == 0);
//
//    int key_cliente =  retornaChaveCliente(dtbaseCCliente,qtdCCliente,IdCliente);
//
//
//    printf("\n>> Dados Clientes: \n");
//
//    listCCliente(dtbaseCCliente,qtdCCliente,key_cliente);
//
//    line(100,"Locados\0");
//    printf("\n");
//
//    //printf("%d %d",key_cliente,key_operator);
//    char tipoPag[10];
//    int test = 0;
//    for (int c = 0; c < qtdLocados; c++){
//        if ((*dtbaseLocados)[c].key_cliente == key_cliente && (*dtbaseLocados)[c].tipoPagamento == 2 && ((*dtbaseLocados)[c].qtdParcelas - (*dtbaseLocados)[c].parcelasPagas) > 0) {
//            float valorParcelas = ((*dtbaseLocados)[c].valorTotal - (*dtbaseLocados)[c].valorEntrada) / (float)(*dtbaseLocados)[c].qtdParcelas;
//            float parcelasPagas = ((((*dtbaseLocados)[c].valorTotal - (*dtbaseLocados)[c].valorEntrada) - ((*dtbaseLocados)[c].valordeve)) / valorParcelas);
//            if ((*dtbaseLocados)[c].tipoPagamento == 1){
//                strcpy(tipoPag,"A vista\0");
//            }else{
//                strcpy(tipoPag,"Parcelado\0");
//            }
//
//            printf("(%d) Codigo Cliente: %d\n"
//                   "Registro da Operacao: %d\n"
//                   "Quantidade de Filmes: %d\n"
//                   "Tipo Pagamento: %s\n"
//                   "Valor Total: R$ %.2f\n"
//                   "Valor Entrada: R$ %.2f\n"
//                   "Valor Parcelas: R$ %.2f\n"
//                   "Parcelas Pagas: %.1f\n"
//                   "Data Pagamento %d/%d/%d\n",(*dtbaseLocados)[c].ID,
//                   (*dtbaseLocados)[c].key_cliente,(*dtbaseLocados)[c].KEY_operator,
//                   (*dtbaseLocados)[c].qtdFilme,
//                   tipoPag,(*dtbaseLocados)[c].valorTotal,
//                   (*dtbaseLocados)[c].valorEntrada,valorParcelas,parcelasPagas,
//                   (*dtbaseLocados)[c].Dtpagamento.dia,(*dtbaseLocados)[c].Dtpagamento.mes,
//                   (*dtbaseLocados)[c].Dtpagamento.ano);
//            test++;
//        }
//    }
//    if (test == 0){
//        printf("\n\t>>Tudo Pago Pelo Cliente :)\n\n\n");
//        system("pause");
//    }else {
//
//        int IDlocados, erro = 0;
//        do {
//            if (erro == 1) { printf("\n[!] ID Invalido\n"); }
//            printf("\n\n>> Informe o ID para realizar o pagamento: ");
//            scanf("%d", &IDlocados);
//            erro = 1;
//        } while (verificaIDLocados(dtbaseLocados, qtdLocados, IDlocados, key_cliente) == 0);
//
//        int indexlocados = posicaoLocadosArray(dtbaseLocados, qtdLocados, key_cliente, IDlocados);
//
//        int qtdParcelas = 0;
//        erro = 0;
//        do {
//            if (erro == 1) { printf("\n[!]Quantidade de parcelas Invalidas\n\n"); }
//            printf("\n>>Quantidade de parcelas que deseja pagar  [MAX: %d]: ",
//                   (*dtbaseLocados)[indexlocados].qtdParcelas - (*dtbaseLocados)[indexlocados].parcelasPagas);
//            scanf("%d", &qtdParcelas);
//            erro = 1;
//        } while (qtdParcelas > (*dtbaseLocados)[indexlocados].qtdParcelas - (*dtbaseLocados)[indexlocados].parcelasPagas && qtdParcelas > 0);
//
//        (*dtbaseLocados)[indexlocados].parcelasPagas = (*dtbaseLocados)[indexlocados].parcelasPagas + qtdParcelas;
//        //preco das parcelas.
//        float valorParcelas =
//                ((*dtbaseLocados)[indexlocados].valorTotal - (*dtbaseLocados)[indexlocados].valorEntrada) /
//                (float) (*dtbaseLocados)[indexlocados].qtdParcelas;
//
//        //Valor pago Total Parcelas * ValorParcelas((float)qtdParcelas * valorParcelas);
//
//
//        (*dtbaseLocados)[indexlocados].valordeve = (*dtbaseLocados)[indexlocados].valordeve - (valorParcelas * (float) qtdParcelas );
//
//        //Setar a Data do pagamento como hj
//        dataAtual(&(*dtbaseLocados)[indexlocados].Dtpagamento);
//
//        //Qtd de parcelas Pagas
//        float parcelasPagas = (
//                (((*dtbaseLocados)[indexlocados].valorTotal - (*dtbaseLocados)[indexlocados].valorEntrada) -
//                 (*dtbaseLocados)[indexlocados].valordeve) / valorParcelas);
//
//        printf("\nValor Pago: R$%.2f\nValor em Debito: R$%.2f\nQuantidade de Parcelas Restante : %d \n"
//               "Data pagamento: %d/%d/%d\n\n", valorParcelas * (float) qtdParcelas,
//               (*dtbaseLocados)[indexlocados].valordeve,
//               (*dtbaseLocados)[indexlocados].qtdParcelas - (int) parcelasPagas,
//               (*dtbaseLocados)[indexlocados].Dtpagamento.dia, (*dtbaseLocados)[indexlocados].Dtpagamento.mes,
//               (*dtbaseLocados)[indexlocados].Dtpagamento.ano);
//
//        int indexConta = posicaoContaArray(dtbaseCCliente, qtdCCliente, IdCliente);
//
//        (*dtbaseCCliente)[indexConta].valorPago =
//                (*dtbaseCCliente)[indexConta].valorPago + (valorParcelas * (float) qtdParcelas);
//        (*dtbaseCCliente)[indexConta].valorDeve =
//                (*dtbaseCCliente)[indexConta].valorDeve - (valorParcelas * (float) qtdParcelas);
//
//        //Enviar ao caixa da locadora
//        monetario->caixa = monetario->caixa + (valorParcelas * (float) qtdParcelas);
//        monetario->contasReceber = monetario->contasReceber - (valorParcelas * (float) qtdParcelas);
//
//        refazDadosCCliente(dtbaseCCliente, qtdCCliente, tipoconfig);
//        refazDadosLocados(dtbaseLocados, qtdLocados, tipoconfig);
//        return 0;
//    }
//    return 0;
//}

int verificaIDLocados(contaCliente **dtbaseCCliente, int qtdCCliente, int idCliente,int idLocado){
    for (int i = 0; i < qtdCCliente; i++){
        if ((*dtbaseCCliente)[i].idCliente == idCliente){
            for (int k = 0; k < (*dtbaseCCliente)[i].tamLocados; k++){
                if ((*dtbaseCCliente)[i].dEmprestimo[k].ID == idLocado){
                    return 1;
                }
            }
        }
    }
    return 0;
}

int devolucaoFilmes(contaCliente **dtbaseCCliente,int qtdCCliente,int tipoConfig){
    system("cls");
    line(100,"Devolucao Filmes\0");
    printf("\nContas Disponiveis:\n");
    for (int i = 0; i < qtdCCliente; i++){
        printf(" (ID: %d) Cliente: %s   ",(*dtbaseCCliente)[i].idCliente,(*dtbaseCCliente)[i].Nome);
    }

    int IdCliente,erroID = 0,entregaCompleta;
    line(100,"-\0");
    do{
        if (erroID == 1){
            printf("\nID invalido por gentileza informe um valido\n");
        }
        printf("\nInforme o ID do Conta Cliente: ");
        scanf("%d",&IdCliente);
        erroID = 1;
    } while (verificaConta(dtbaseCCliente,qtdCCliente,IdCliente) == 0);

    //int key_cliente =  retornaChaveCliente(dtbaseCCliente,qtdCCliente,IdCliente);

    //printf("%d %d",key_cliente,key_operator);

    printf("\nDevolucoes pendentes:\n ");
    int temDevolver = listLocacao(dtbaseCCliente,qtdCCliente,IdCliente,-1,0);

    if (temDevolver >= 1){//tem algo para devolver
        int IDlocados,erro = 0;
        do {
            if (erro == 1){ printf("\n[!] ID Invalido\n");}
            printf("Informe o ID da Nota para a Devolucao: ");
            scanf("%d", &IDlocados);
            erro = 1;
        }while(verificaIDLocados(dtbaseCCliente,qtdCCliente,IdCliente,IDlocados) == 0);

        //int key_operator = retornaChaveOperacao(dtbaselocados,qtdLocados,IDlocados,key_cliente);


        printf("\nVerifique os Filmes:\n ");

        int temoperacao = listLocacao(dtbaseCCliente,qtdCCliente,IdCliente,IDlocados,0);


        //Precisa Selecionar a Referencia dos Locados
        //Aqueles que apresenta tudo Devolvido Não serão listado


        printf("\nO cliente vai realizar a entrega completa ?  [1- Sim \t 0 - Nao]: ");
        scanf("%d",&entregaCompleta);

        if (entregaCompleta == 1){
            //Devolveu tudo
            for (int i = 0; i< qtdCCliente; i++){
                if((*dtbaseCCliente)[i].idCliente == IdCliente){
                    for (int j = 0; j < (*dtbaseCCliente)[i].tamLocados - 1; j++){
                        if((*dtbaseCCliente)[i].dEmprestimo[j].ID == IDlocados){
                            if ((*dtbaseCCliente)[i].dEmprestimo[j].TDdevolvido == 1){
                                break;
                            }else{
                                (*dtbaseCCliente)[i].dEmprestimo[j].TDdevolvido = 1;
                            }

                            for (int k = 0; k < (*dtbaseCCliente)[i].dEmprestimo[j].qtdFilme - 1; k++){
                                (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].devolvido = 1;

                                data *dtDevolucao = &(*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucaoReal;
                                dataAtual(dtDevolucao);
                                //Verificar se passou do prazo de entrega e calcular multa;

                                data hoje;
                                dataAtual(&hoje);

                                //Calcular Diferenca entre datas
                                int t = diasEntreDatas((*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucao,hoje);

                                if (t > 0){
                                    printf(">> MULTA APLICADA.");
                                    //Adicionar Valor ao campo deve
                                }

                                printf("%d/%d/%d menos %d/%d/%d = %d Dias\n" ,(*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucao.dia,(*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucao.mes,(*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucao.ano,
                                       hoje.dia,hoje.mes,hoje.ano,t );
                                //printf("%d / %d / %d",dtDevolucao->dia,dtDevolucao->mes,dtDevolucao->ano);
                            }
                            break;
                        }
                    }
                    break;
                }
            }

            refazDadosCCliente(dtbaseCCliente,qtdCCliente,tipoConfig);
        }else{
            int qtdDevolver;
            printf("Quantos Filmes serao devolvidos: ");
            scanf("%d",&qtdDevolver);


            for (int i = 0; i < qtdCCliente; i++) {
                if ((*dtbaseCCliente)[i].idCliente == IdCliente) {

                    for (int j = 0; j < (*dtbaseCCliente)[i].tamLocados; j++) {

                        if ((*dtbaseCCliente)[i].dEmprestimo[j].ID == IDlocados) {

                            for (int l = 0; l < qtdDevolver; l++){
                                int IDfilme,IDvalido = 0;
                                printf("\nInforme o ID: ");
                                scanf("%d",&IDfilme);

                                for (int k = 0; k < (*dtbaseCCliente)[i].dEmprestimo[j].qtdFilme; k++) {
                                    if ((*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].ID == IDfilme) {

                                        (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].devolvido = 1;

                                        data *dtDevolucao = &(*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucaoReal;
                                        dataAtual(dtDevolucao);
                                        //Verificar se passou do prazo de entrega e calcular multa;

                                        data hoje;
                                        dataAtual(&hoje);

                                        //Calcular Diferenca entre datas
                                        int t = diasEntreDatas(hoje,
                                                (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucao);

                                        if (t < 0) {
                                            printf(">> MULTA APLICADA.");
                                            //Adicionar Valor ao campo deve
                                        }

                                        printf("%d/%d/%d menos %d/%d/%d = %d Dias\n",
                                               (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucao.dia,
                                               (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucao.mes,
                                               (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucao.ano,
                                               hoje.dia, hoje.mes, hoje.ano, t);
                                        //printf("%d / %d / %d",dtDevolucao->dia,dtDevolucao->mes,dtDevolucao->ano);
                                        IDvalido++;
                                    }
                                }
                                if (IDvalido == 0){
                                    printf("[!]ID Invalido");
                                    qtdDevolver ++;
                                }
                            }
                            (*dtbaseCCliente)[i].dEmprestimo[j].TDdevolvido = 1;
                            //Verificar valor de tudo devolvido
                            for (int k = 0; k < (*dtbaseCCliente)[i].dEmprestimo[j].qtdFilme; k++){
                                if ((*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].devolvido == 0){
                                    (*dtbaseCCliente)[i].dEmprestimo[j].TDdevolvido = 2;
                            }

                        }
                        break;
                    }
                    break;
                }
            }
            refazDadosCCliente(dtbaseCCliente,qtdCCliente,tipoConfig);
        }
    }}else{
        printf("\n\n\t[!] O Cliente ja devolveu todos os filmes");
        system("pause");
        return 0;
    }
    return 0;
}

int entradaFilmes(fornecedor **dtbase, int *qtdFornecedor,int *tamFornecedor,int *idEntradaFIlme, eFilme **dtBase_eFilme, int *tam_eFilme, int *qtd_eFime,financeiro *monetario,int tipo_config){


    //carregarDados_Efilme(dtBase_eFilme, qtd_eFime, tam_eFilme, idEntradaFIlme,tipo_config);

    // ----------------------- Verifica ID Fornecedor --------------------------------
    int IDFornecedor = 0,erro = 0;
    int idFilme = 0;
    do {
        int cadastrar;
        if (erro == 1){
            do{
                printf("\n[!] ID Invalido\n\t>>Deseja Cadastrar [ 1 - Sim 0 - Não ]");
                scanf("%d",&cadastrar);
            } while (cadastrar != 0 & cadastrar != 1);
            if (cadastrar == 1) {
                // --------------------------------------------- Cadastrar Fornecedor Caso Não exista--------------------------
                IDFornecedor = retornarUltimoID_Fornecedor(dtbase, *qtdFornecedor);
                fornecedor novoFornecedor = criarFornecedor(IDFornecedor);
                inserirFornecedor(dtbase, novoFornecedor, qtdFornecedor, tamFornecedor);
                //Salvar Fornecedor
            }else{
                return 1;
            }

        }
        if (qtdFornecedor > 0) {
            line(100, "ID Fornecedores\0");
            for (int i = 0; i < *qtdFornecedor; i++) { //Listar Fornecedores disponiveis
                printf(" (%d) %s ", (*dtbase)[i].id, (*dtbase)[i].nomeFantasia);
            }
            line(100, "-\0");
        }

        printf("\n>>Informe o ID do Fornecedor: ");
        scanf("%d", &IDFornecedor);
        erro = 1;
    }while(verificaIdFornecedor(dtbase,*qtdFornecedor,IDFornecedor) == 0);
    // Verificar objetoefilme
    //printf("%d",verificaID_eFilme(dtBase_eFilme,*qtd_eFime,IDFornecedor));
    int existe = verificaID_eFilme(dtBase_eFilme,*qtd_eFime,IDFornecedor);

    if (existe != -1){
        printf("Existe");
        //encontrar posiçaoi no array
        int posArray = -1;
        for (int i = 0; i < *qtd_eFime; i++){
            if ((*dtBase_eFilme)[i].IDFornecedor == IDFornecedor){
                posArray = i;
                break;
            }
        }

        if (posArray != -1){
            int *ultimoId = &(*dtBase_eFilme)[posArray].ultIDOp;
            operacaoEFilme newOp = objOpEfilme(&(*dtBase_eFilme)[posArray].ultIDOp,monetario);
            inserirop_EFIlme(&(*dtBase_eFilme)[posArray].filmes, newOp, &(*dtBase_eFilme)[posArray].tamOp);
        }
        //Refaz Arquivos
        refazDadosEfIlme(dtBase_eFilme, *qtd_eFime,tipo_config);
    }else{
        while (1) {
            //Ultimo ID FIlme
            for (int i = 0; i < *qtd_eFime; i++){
                if ((*dtBase_eFilme)[i].ID == idFilme){
                    idFilme = (*dtBase_eFilme)[i].ID + 1;
                }
            }

            eFilme newEFilme = objetoefilme(&idFilme, dtbase, *qtdFornecedor, IDFornecedor);

            operacaoEFilme newOp = objOpEfilme(&newEFilme.ultIDOp,monetario);
            //newEFilme.nomefornecedor
            inserirop_EFIlme(&newEFilme.filmes, newOp, &newEFilme.tamOp);
            inserir_eFilme(dtBase_eFilme, newEFilme, qtd_eFime, tam_eFilme);
            save_eFilme(newEFilme,tipo_config);
            break;
        }
    }
    return 0;
}

// Verificar objetoefilme
int verificaID_eFilme(eFilme **dtbase, int qtd_eFilme, int id){
    for (int i = 0; i < qtd_eFilme ; i++){
        if((*dtbase)[i].IDFornecedor == id){
            return 1;
        }
    }
    return -1;
}

int inserir_eFilme(eFilme **dtbase,eFilme novaEntrada, int *qtd_eFilme, int *tam_eFilme){
    if (*qtd_eFilme >= *tam_eFilme){
        *tam_eFilme = *tam_eFilme + 1;
        (*dtbase) = realloc((*dtbase), *tam_eFilme * sizeof(eFilme));
    }

    if ((*dtbase) == NULL){
        return -1;
    }

    (*dtbase)[*tam_eFilme - 1] = novaEntrada;
    *qtd_eFilme = *qtd_eFilme + 1;
    return 0;
}
int inserirop_EFIlme(operacaoEFilme **dtbase,operacaoEFilme novaEntrada,int *tam_op){
    (*dtbase) = realloc((*dtbase), *tam_op * sizeof(eFilme));

    if ((*dtbase) == NULL){
        return -1;
    }

    (*dtbase)[*tam_op - 1] = novaEntrada;
    *tam_op = *tam_op + 1;
    return 0;
}

eFilme  objetoefilme(int *id,fornecedor **dtbase,int qtdFornecedor,int IDFornecedor){

    int indexDtBaseLocados = posArrayFornecedor(dtbase,qtdFornecedor, IDFornecedor);
    eFilme objetoEfilme;

    objetoEfilme.ID = *id;
    *id = *id + 1;

    objetoEfilme.IDFornecedor = IDFornecedor;

    // ---------------------------    Preencher objetoEfilme --------------------------------------
    printf("\n\nNome Fonecedor: %s ",nomeFornecedor(dtbase,qtdFornecedor,IDFornecedor));
    objetoEfilme.nomefornecedor = nomeFornecedor(dtbase,qtdFornecedor,IDFornecedor);
    //objetoEfilme.cnpj = retornarCNPJ(dtbase,qtdFornecedor,IDFornecedor);
    strcpy(objetoEfilme.cnpj,(*dtbase)[indexDtBaseLocados].cnpj);
    printf("\n\nCNPJ: %s ",objetoEfilme.cnpj);

    objetoEfilme.key_fornecedorArray = (*dtbase)[indexDtBaseLocados].id;
    objetoEfilme.tamOp = 1;

    objetoEfilme.ultIDOp = 0;

    objetoEfilme.filmes = (operacaoEFilme *)malloc(objetoEfilme.tamOp * sizeof (operacaoEFilme));

    return objetoEfilme;
}


operacaoEFilme objOpEfilme (int *id,financeiro *monetario){
    // ---------------------------    Preencher Operaçoes --------------------------------------
    operacaoEFilme newOpEfilme;

    newOpEfilme.ID = *id;
    *id = *id + 1;

    float vFrete, vImposto;
    int test = 0;
    do {
        printf("\t>> Frete: R$");
        scanf("%f", &vFrete);

        printf("\t>> Imposto: R$");
        scanf("%f", &vImposto);

        printf("\n\t>> Informacoes Corretas ? [1 - Sim 0 - Não]");
        scanf("%d", &test);
        if (test == 1){
            break;
        }
    } while (1);

    newOpEfilme.frete = vFrete;
    newOpEfilme.Imposto = vImposto;

    newOpEfilme.tamFilm = 1;
    newOpEfilme.entradaFilmesCadastro =(filme * ) malloc(newOpEfilme.tamFilm * sizeof (filme));

    newOpEfilme.ultIDFilm = 0;

    objetoEntradaFIlme(&newOpEfilme.ultIDFilm,&newOpEfilme.entradaFilmesCadastro,&newOpEfilme.tamFilm);


    dataAtual(&newOpEfilme.dtNota);


    int qtdTotalFilme = 0;
    for (int i = 0; i < newOpEfilme.tamFilm;i++){
        qtdTotalFilme = qtdTotalFilme + newOpEfilme.entradaFilmesCadastro[i].qtd;
    }
    //Calcular Frete por produto
    float vFreteProduto = newOpEfilme.frete /(float)qtdTotalFilme;
    float vImpostoProduto = newOpEfilme.Imposto /(float)qtdTotalFilme;

    newOpEfilme.fretePproduto = vFreteProduto;
    newOpEfilme.ImpostoPproduto = vImpostoProduto;

    newOpEfilme.valorTotal = 0;
    //Calcular Valor Total
    for (int i =0; i < newOpEfilme.tamFilm;i++){
        newOpEfilme.valorTotal = newOpEfilme.valorTotal + (newOpEfilme.entradaFilmesCadastro[i].valorCompra + newOpEfilme.fretePproduto + newOpEfilme.ImpostoPproduto) * (float)newOpEfilme.entradaFilmesCadastro[i].qtd;
    }

    printf("\n  >> Frete (Und. Produto): R$ %.2f\n  >> Imposto (Und. Produto): R$ %.2f \n  >> Quantidade Produtos: %d\n",newOpEfilme.fretePproduto,newOpEfilme.ImpostoPproduto,qtdTotalFilme);

    printf("\n[!] Valor total a ser Pago: R$ %.2f \n",newOpEfilme.valorTotal);
    //TIPO PAGAMENTO
    do{
        printf("\n>>Tipo do pagamento: [1- A vista \t2 - A prazo]: ");
        scanf("%d",&newOpEfilme.tipoPagamento);
    } while (newOpEfilme.tipoPagamento > 2 || newOpEfilme.tipoPagamento < 1);

    replacefloat(0,&newOpEfilme.valorEntrada);

    newOpEfilme.parcelasPagas = 0;

    int pagouaVista = -1; // 0 Não
    while (newOpEfilme.tipoPagamento == 1){//Pagamento a vista
        int opc = 0;
        if (newOpEfilme.valorTotal > monetario->caixa){
            newOpEfilme.tipoPagamento = 2;
            pagouaVista = 0;
            break;
        }else{
            newOpEfilme.qtdParcelas = 1;
            newOpEfilme.parcelasPagas = 1;
            newOpEfilme.valorDeve = 0; // Locadora pagou tudo
            //Tirar valor do caixa

            monetario->caixa = monetario->caixa - newOpEfilme.valorTotal;

            dataAtual(&newOpEfilme.dtPagamento);
            pagouaVista = 1;
            break;
        }
    }
    if (newOpEfilme.tipoPagamento == 2 || pagouaVista == 0) {
        int ent = 0;
        float qtdParcelas;
        float valorE;

        if (pagouaVista == 0){
            printf("\n\n  [!]Saldo Insuficiente.\n    Saldo: R$ %.2f \n\n>> Pagamento Parcelado\n\n",monetario->caixa);
        }
        // Valores de entrada
        do {
            printf("\n >>Deseja dar entrada ?  [ 1 - Sim \t0 - Nao ]: ");
            scanf("%d", &ent);
            if (ent == 0 || ent == 1) { break; }
            else { printf("\n>> Opc Invalida"); }
        } while (1);



        int valorInvalido = 0;
        if (ent == 1) {
            do {
                if (valorInvalido == 1) {
                    printf("\n[!]Valor Invalido\nPagar: R$ %.2f\nCaixa: R$ %.2f",
                           newOpEfilme.valorTotal,monetario->caixa);
                }
                //Valor de entrada
                printf("\n>> Valor R$ ");
                scanf("%f", &valorE);

                valorInvalido = 1;
            } while (valorE >= newOpEfilme.valorTotal || valorE > monetario->caixa);
            //Calcular restante(valordeve) =  Valor Total menos valor de entrada
            newOpEfilme.valorDeve = newOpEfilme.valorTotal - valorE;
            //Alterar caixa LOCADORA
            monetario->caixa = monetario->caixa - valorE;
            monetario->despesas = monetario->despesas + newOpEfilme.valorDeve;
            //Valor de Entrada
            newOpEfilme.valorEntrada = valorE;

            do {
                printf("\n>> Deseja dividir o valor R$ %.2f de quantas Vezes [3x Parcelas Maximas] ? ",
                       newOpEfilme.valorDeve);
                scanf("%f", &qtdParcelas);
                if (qtdParcelas <= 3 && qtdParcelas > 0) { break; }
                else { printf("\n[!] Quantidade de Parcelas invalido\n"); }
            } while (1);


            float valorParcelas = newOpEfilme.valorTotal / qtdParcelas;
            printf("\nA conta foi dividida em %f parcelas \n O Valor de cada parcela e: R$ %.2f\n", qtdParcelas,
                   valorParcelas);
            newOpEfilme.qtdParcelas = (int) qtdParcelas;

        } else {
            //Caso não seja fornecido uma  entrada
            do {
                printf("\n>> Deseja dividir o valor R$ %.2f de quantas Vezes [3x Parcelas Maximas] ? ",
                       newOpEfilme.valorTotal);
                scanf("%f", &qtdParcelas);
                if (qtdParcelas <= 3 && qtdParcelas > 0) { break; }
                else { printf("\n[!] Quantidade de Parcelas invalido\n"); }
            } while (1);

            float valorParcelas = newOpEfilme.valorTotal / qtdParcelas;
            printf("\nA conta foi dividida em %f parcelas \n O Valor de cada parcela e: R$ %.2f\n\n", qtdParcelas,
                   valorParcelas);
            newOpEfilme.qtdParcelas = (int) qtdParcelas;
            newOpEfilme.valorDeve = newOpEfilme.valorTotal;
        }
    }
    newOpEfilme.dtPagamento.dia = 0;
    newOpEfilme.dtPagamento.mes = 0;
    newOpEfilme.dtPagamento.ano = 0;

    newOpEfilme.ultIDFilm = 0;
    system("pause");
    return newOpEfilme;
}

filme objetoEntradaFIlme (int *id,filme **dtbase,int *tamFilm){
    filme novo;
    while (1) {
        // realocar memoria
        if (*tamFilm > 1) {
            (*dtbase) = (filme *) realloc(*dtbase,*tamFilm * sizeof(filme));
        }


        novo.codigo = *id;
        *id = *id + 1;
        while (1) {
            setbuf(stdin,NULL);
            printf(">>Descrição Filme:");
            scanf("%[^\n]s", novo.nome);

            setbuf(stdin,NULL);

            printf(">>Valor Compra(UNIDADE):");
            scanf("%f", &novo.valorCompra);

            printf(">>Quantidade:");
            scanf("%d", &novo.qtd);

            int opc = 0;
            printf("\n\t>> Informaçoes Correta ? [1 - Sim 0 - Não] :");
            scanf("%d", &opc);

            if (opc == 1) {
                break;
            }
        }//Preencher Infos do Filme

        (*dtbase)[*tamFilm - 1] = novo; //Adicionar Infos do Filme

        int opc =0;
        printf("\n\t>> Adicionar mais Filmes ? [1 - Sim 0 - Não]: ");
        scanf("%d", &opc);

        if(opc == 0){
            break;
        }else{
            (*tamFilm) = (*tamFilm) + 1;
        }
    }
    return novo;
}

int save_eFilme(eFilme objeto,int tipo_config){
    FILE *entradaFilmeF = NULL;

    if (tipo_config == 1){//Arquivo TXT
        if (verifica_arquivos(tipo_config,"cpyBdEntradaFilme.txt\0") == 1){
            entradaFilmeF = fopen("cpyBdEntradaFilme.txt", "a");
        } else{
            entradaFilmeF = fopen("cpyBdEntradaFilme.txt", "w");
        }

        if (entradaFilmeF == NULL){ // Se a abertura falhar
            return 1;
        }

        fprintf(entradaFilmeF, "%d\n%d\n%s\n%s\n%d\n%d\n%d\n",
                objeto.ID,
                objeto.IDFornecedor,
                objeto.nomefornecedor,
                objeto.cnpj,
                objeto.key_fornecedorArray,
                objeto.tamOp,
                objeto.ultIDOp);

            for (int i = 0; i < objeto.tamOp - 1; i++){
                fprintf(entradaFilmeF, "%d\n%f\n%f\n%d\n%d\n%f\n%f\n%f\n%d\n%d\n%d\n%f\n%f\n%d\n%d\n%d\n%d\n%d\n%d\n",
                        objeto.filmes[i].ID,
                        objeto.filmes[i].frete,
                        objeto.filmes[i].Imposto,
                        objeto.filmes[i].tamFilm,
                        objeto.filmes[i].ultIDFilm,

                        objeto.filmes[i].fretePproduto,
                        objeto.filmes[i].ImpostoPproduto,
                        objeto.filmes[i].valorTotal,
                        objeto.filmes[i].tipoPagamento,
                        objeto.filmes[i].qtdParcelas,
                        objeto.filmes[i].parcelasPagas,
                        objeto.filmes[i].valorEntrada,
                        objeto.filmes[i].valorDeve,
                        objeto.filmes[i].dtNota.dia,
                        objeto.filmes[i].dtNota.mes,
                        objeto.filmes[i].dtNota.ano,
                        objeto.filmes[i].dtPagamento.dia,
                        objeto.filmes[i].dtPagamento.mes,
                        objeto.filmes[i].dtPagamento.ano
                        );
                for (int j = 0; j < objeto.filmes[i].tamFilm; j++){
                    fprintf(entradaFilmeF, "%d\n%s\n%f\n%d\n",
                            objeto.filmes[i].entradaFilmesCadastro[j].codigo,
                            objeto.filmes[i].entradaFilmesCadastro[j].nome,
                            objeto.filmes[i].entradaFilmesCadastro[j].valorCompra,
                            objeto.filmes[i].entradaFilmesCadastro[j].qtd);
                }
            }
    }else{ //Arquivo BINARIO
        if (verifica_arquivos(tipo_config,"cpyBdEntradaFilme.bin\0") == 1){
            entradaFilmeF = fopen("cpyBdEntradaFilme.bin", "ab");
        } else{
            entradaFilmeF = fopen("cpyBdEntradaFilme.bin", "wb");
        }
        if (entradaFilmeF == NULL){ // Se a abertura falhar
            return 1;
        }
        fwrite(&objeto, sizeof(eFilme), 1,entradaFilmeF);
    }
    fclose(entradaFilmeF);
    entradaFilmeF = NULL;
    return 0;
}


int carregarDados_Efilme(eFilme **dtbase, int *qtdeFilmes, int *tamanhoeFilmes,int tipo_config) {
    FILE *Efilmef = NULL;
    eFilme new;

    int *qtdTemp = qtdeFilmes;

    int t = 0;
    if (tipo_config == 1){ //Arquivo TXT
        Efilmef = fopen("cpyBdEntradaFilme.txt", "r");

        if (Efilmef == NULL){
            printf("\nErro na Leitura 'cpyBdEntradaFilme.txt' \n");
            return 1;
        }

        while (!feof(Efilmef)){
            if (!filelength(fileno(Efilmef))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fscanf(Efilmef, "%d\n", &new.ID);

            fscanf(Efilmef, "%d\n", &new.IDFornecedor);

            char nomeFornecedor[120];
            fgets(nomeFornecedor,120,Efilmef);
            new.nomefornecedor = string_to_pointer(nomeFornecedor);

            fgets(new.cnpj,15,Efilmef);
            limpa_final_string(new.cnpj);

            fscanf(Efilmef, "%d\n", &new.key_fornecedorArray);

            fscanf(Efilmef, "%d\n", &new.tamOp);

            fscanf(Efilmef, "%d\n", &new.ultIDOp);

            new.filmes = malloc(new.tamOp * sizeof (operacaoEFilme));
            for (int i = 0 ; i < new.tamOp - 1; i++){
                fscanf(Efilmef, "%d\n", &new.filmes[i].ID);
                fscanf(Efilmef, "%f\n", &new.filmes[i].frete);
                fscanf(Efilmef, "%f\n", &new.filmes[i].Imposto);
                fscanf(Efilmef, "%d\n", &new.filmes[i].tamFilm);
                fscanf(Efilmef, "%d\n", &new.filmes[i].ultIDFilm);

                fscanf(Efilmef, "%f\n", &new.filmes[i].fretePproduto);
                fscanf(Efilmef, "%f\n", &new.filmes[i].ImpostoPproduto);
                fscanf(Efilmef, "%f\n", &new.filmes[i].valorTotal);
                fscanf(Efilmef, "%d\n", &new.filmes[i].tipoPagamento);
                fscanf(Efilmef, "%d\n", &new.filmes[i].qtdParcelas);
                fscanf(Efilmef, "%d\n", &new.filmes[i].parcelasPagas);
                fscanf(Efilmef, "%f\n", &new.filmes[i].valorEntrada);
                fscanf(Efilmef, "%f\n", &new.filmes[i].valorDeve);
                fscanf(Efilmef, "%d\n", &new.filmes[i].dtNota.dia);
                fscanf(Efilmef, "%d\n", &new.filmes[i].dtNota.mes);
                fscanf(Efilmef, "%d\n", &new.filmes[i].dtNota.ano);
                fscanf(Efilmef, "%d\n", &new.filmes[i].dtPagamento.dia);
                fscanf(Efilmef, "%d\n", &new.filmes[i].dtPagamento.mes);
                fscanf(Efilmef, "%d\n", &new.filmes[i].dtPagamento.ano);


                new.filmes[i].entradaFilmesCadastro = malloc((new.filmes[i].tamFilm + 1) * sizeof (filme));
                for (int j = 0 ; j < new.filmes[i].tamFilm; j++){
                    fscanf(Efilmef, "%d\n", &new.filmes[i].entradaFilmesCadastro[j].codigo);

                    fgets(new.filmes[i].entradaFilmesCadastro[j].nome,120,Efilmef);
                    limpa_final_string(new.filmes[i].entradaFilmesCadastro[j].nome);

                    fscanf(Efilmef, "%f\n", &new.filmes[i].entradaFilmesCadastro[j].valorCompra);
                    fscanf(Efilmef, "%d\n", &new.filmes[i].entradaFilmesCadastro[j].qtd);

                }
            }

            t = inserir_eFilme(dtbase,new,qtdeFilmes,tamanhoeFilmes);

            if (t != 0){
                printf("\nAcao Interrompida");
                break;
            }
        }
    }
    else { //Arquivo BIN
        Efilmef = fopen("cpyBdEntradaFilme.txt", "rb");
        if (Efilmef == NULL){
            printf("\nErro na Leitura 'cpyBdEntradaFilme.txt' \n");
            return 1;
        }
        while (!feof(Efilmef)){
            if (!filelength(fileno(Efilmef))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fread(&new,sizeof(eFilme),1,Efilmef);
//            if (verificaIdFilme(dtBase,*qtdFilme,new.codigo) == 0){
//                t = inserirFilme(dtBase,new,qtdFilme,tamanhoFilme,tipo_config);
//                if (*id <= new.codigo) {
//                    *id = new.codigo + 1;
//                }
//            }

            if (t == 0){
                printf("\nAcao Interrompida");
                break;
            }
        }
    }
    fclose(Efilmef);
    Efilmef = NULL;
    return 0;
}
 
int list_eFilme(eFilme **dtBase_eFilme, int qtd_eFime, int IDconta,int IDnota, int tipoPagamento, int filtrarPagos){ // filtrarPagos 0 - Retorna tudo       1 - Retorna os que não foram Pagos
    int controle = 0;
    for (int i = 0; i  < qtd_eFime; i++){
        if (((*dtBase_eFilme)[i].ID == IDconta) || (IDconta == -1)){
            printf("| ID Conta: (%d)  \t Fornecedor:  %s  \t\tCNPJ: %s", (*dtBase_eFilme)[i].ID,
                   (*dtBase_eFilme)[i].nomefornecedor, (*dtBase_eFilme)[i].cnpj);
            for (int j = 0; j < (*dtBase_eFilme)[i].tamOp - 1; j++) {
               if (((*dtBase_eFilme)[i].filmes[j].tipoPagamento == tipoPagamento || tipoPagamento == -1) && ((*dtBase_eFilme)[i].filmes[j].ID == IDnota || IDnota == -1) && ((*dtBase_eFilme)[i].filmes[j].parcelasPagas < (*dtBase_eFilme)[i].filmes[j].qtdParcelas || (int)(*dtBase_eFilme)[i].filmes[j].valorDeve > 0 || filtrarPagos == 0)) {
                    printf("\n\n| (%d) Data da Nota: %d/%d/%d  ", (*dtBase_eFilme)[i].filmes[j].ID,
                           (*dtBase_eFilme)[i].filmes[j].dtNota.dia, (*dtBase_eFilme)[i].filmes[j].dtNota.mes,
                           (*dtBase_eFilme)[i].filmes[j].dtNota.ano);
                    printf("| Frete: R$ %.2f      Imposto: R$ %.2f %s |", (*dtBase_eFilme)[i].filmes[j].frete,
                           (*dtBase_eFilme)[i].filmes[j].Imposto,
                           formatstring(41, 1, " "));
                    printf("\n|%s|%s|%s|%s|%s|%s|%s|", formatstring(30, strlen("Descricao\0"), "Descricao\0"),
                           formatstring(13, strlen("Preco Custo\0"), "Preco Custo\0"),
                           formatstring(13, strlen("Frete\0"), "Frete\0"),
                           formatstring(13, strlen("Imposto\0"), "Imposto\0"),
                           formatstring(13, strlen("Preco Total\0"), "Preco Total\0"),
                           formatstring(13, strlen("Quantidade\0"), "Quantidade\0"),
                           formatstring(13, strlen("Total\0"), "Total\0"));
                    for (int k = 0; k < (*dtBase_eFilme)[i].filmes[j].tamFilm; k++) {

                        float precoTotal = 0;

                        char precoCusto[100], auxprecoCusto[100] = "R$ \0";
                        limpaString(precoCusto, sizeof(precoCusto));
                        sprintf(precoCusto, "%.2f", (*dtBase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].valorCompra);
                        strcat(auxprecoCusto, precoCusto);

                        precoTotal = precoTotal + (*dtBase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].valorCompra;

                        char frete[100], auxfrete[100] = "R$ \0";
                        limpaString(frete, sizeof(frete));
                        sprintf(frete, "%.2f", (*dtBase_eFilme)[i].filmes[j].fretePproduto);
                        strcat(auxfrete, frete);

                        precoTotal = precoTotal + (*dtBase_eFilme)[i].filmes[j].fretePproduto;

                        char imposto[100], auximposto[100] = "R$ \0";
                        limpaString(imposto, sizeof(imposto));
                        sprintf(imposto, "%.2f", (*dtBase_eFilme)[i].filmes[j].ImpostoPproduto);
                        strcat(auximposto, imposto);

                        precoTotal = precoTotal + (*dtBase_eFilme)[i].filmes[j].ImpostoPproduto;

                        char qtd[10];
                        limpaString(qtd, sizeof(qtd));
                        sprintf(qtd, "%d", (*dtBase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].qtd);

                        char precoTotalChar[100];
                        limpaString(precoTotalChar, sizeof(precoTotalChar));
                        sprintf(precoTotalChar, "%.2f", precoTotal);

                        precoTotal = precoTotal * (float) (*dtBase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].qtd;
                        char ValorTotalPago[100];
                        limpaString(ValorTotalPago, sizeof(ValorTotalPago));
                        sprintf(ValorTotalPago, "%.2f", precoTotal);

                        printf("\n|%s|%s|%s|%s|%s|%s|%s|",
                               formatstring(30,
                                            (int) strlen((*dtBase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].nome),
                                            (*dtBase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].nome),
                               formatstring(13, (int) strlen(auxprecoCusto), auxprecoCusto),
                               formatstring(13, (int) strlen(auxfrete), auxfrete),
                               formatstring(13, (int) strlen(auximposto), auximposto),
                               formatstring(13, (int) strlen(precoTotalChar), precoTotalChar),
                               formatstring(13, (int) strlen(qtd), qtd),
                               formatstring(13, (int) strlen(ValorTotalPago), ValorTotalPago));
                    }
                    if ((*dtBase_eFilme)[i].filmes[j].tipoPagamento == 1) {
                        printf("\n|%s| Valor Total : R$ %.2f \t\t Data Pagamento: %d/%d/%d %s ",
                               formatstring(30, (int) strlen("Tipo Pagamento: A vista\0"), "Tipo Pagamento: A vista\0"),
                               (*dtBase_eFilme)[i].filmes[j].valorDeve, (*dtBase_eFilme)[i].filmes[j].dtPagamento.dia,
                               (*dtBase_eFilme)[i].filmes[j].dtPagamento.mes,
                               (*dtBase_eFilme)[i].filmes[j].dtPagamento.ano, formatstring(17, 1, " \0"));
                    } else {
                        printf("\n|%s|  Valor Total : R$ %.2f \t\t  | Qtd Parcelas Pagas: %d de %d ",
                               formatstring(30, (int) strlen("Tipo Pagamento: Parcelado\0"),
                                            "Tipo Parcelado: Parcelado\0"),
                               (*dtBase_eFilme)[i].filmes[j].valorDeve,(*dtBase_eFilme)[i].filmes[j].parcelasPagas ,(*dtBase_eFilme)[i].filmes[j].qtdParcelas);
                    }
                    controle++;
                }
            }
        }
    }
    if (controle == 0){
        return -1;
    }
    return 0;
}

int verifica_eFilme(eFilme **dtbase_eFilme, int qtd_eFilme, int id){
    for (int i = 0 ; i < qtd_eFilme; i++){
        if ((*dtbase_eFilme)[i].ID == id){
            return 1;
        }
    }
    return 0;
}

int possArray_eFilme(eFilme **dtbase_eFilme, int qtd_eFilme, int id){
    for (int i = 0 ; i < qtd_eFilme; i++){
        if ((*dtbase_eFilme)[i].ID == id){
            return i;
        }
    }
    return -1;
}

int verifica_OpeFilme(eFilme **dtbase_eFilme, int qtd_eFilme, int IDConta,int IDnota, int tipoPagamento, int filtrarPagos){
    for (int i = 0 ; i < qtd_eFilme; i++){
        if ((*dtbase_eFilme)[i].ID == IDConta){
            for (int j = 0; j < (*dtbase_eFilme)[i].tamOp; j++){
                if ((*dtbase_eFilme)[i].filmes[j].ID == IDnota && (*dtbase_eFilme)[i].filmes[j].tipoPagamento == tipoPagamento && ((*dtbase_eFilme)[i].filmes[j].parcelasPagas < (*dtbase_eFilme)[i].filmes[j].qtdParcelas || (int)(*dtbase_eFilme)[i].filmes[j].valorDeve > 0 || filtrarPagos == 0)){
                    return j;
                }
            }
        }
    }
    return -1;
}




int pagarParcelaEmprestaFilme(eFilme **dtbase_eFilme, int qtd_eFilme, financeiro *monetario, int tipo_config){
    line(100,"Pagamento de Parcela Fornecedor");
    printf("ID disponiveis: \n");
    printf("(-1) Sair  ");
    int i;
    for (i = 0 ; i < qtd_eFilme; i++){
        printf("(%d) %s  ",(*dtbase_eFilme)[i].ID,(*dtbase_eFilme)[i].nomefornecedor);
    }
    char tempId[4];
    int IDfornecedor = -1;
    if (qtd_eFilme == 0){
        printf("\n\t [!] Nada para Mostrar Aqui ...\n\n");
        system("pause");
        system("cls");
        return -1;
    }
    int er = 0 ;
    do {
        if (er == 1){
            printf("\n [!] ID Invalido \n Informe um ID valido ou -1 para sair\n");
        }
        printf("\n\nID Fornecedor: ");
        scanf("%s", tempId);

        IDfornecedor = strtol(tempId,NULL,10);
        if (IDfornecedor == -1){
            return -1;
        }
        er++;
    }while (verifica_eFilme(dtbase_eFilme,qtd_eFilme,IDfornecedor) == 0);
    //IDfornecedor ja verificado
    int indexArray = possArray_eFilme(dtbase_eFilme,qtd_eFilme,IDfornecedor);

    int IDnota;
    if (indexArray != -1){
        int t = list_eFilme(dtbase_eFilme,qtd_eFilme,IDfornecedor,-1,2,1);

        if (t == 0){
            printf("\n\n  [!] Não tem Contas a prazo para Este Fornecedor ");
            int cf = 0;
            do{
                printf("\n\n >> Deseja ver as Notas: [1 - Sim 0 - Nao]:");
                scanf("%d",&cf);
            } while (cf != 1 && cf != 0);

            if (cf == 1){
                printf("\n\n ");
                list_eFilme(dtbase_eFilme,qtd_eFilme,IDfornecedor,-1,-1,0);
                printf("\n ");
                system("pause");
            }


            return -1;
        }

        do{
            printf("\n\nID Nota: ");
            scanf("%d",&IDnota);
        } while (verifica_OpeFilme(dtbase_eFilme,qtd_eFilme,IDfornecedor,IDnota,2,1) == -1);


        list_eFilme(dtbase_eFilme,qtd_eFilme,IDfornecedor,IDnota,2,1);

        int qtdParcelas = 0;
        float valorParcelas = ((*dtbase_eFilme)[indexArray].filmes[IDnota].valorTotal -
                               (*dtbase_eFilme)[indexArray].filmes[IDnota].valorEntrada) /
                              (float) (*dtbase_eFilme)[indexArray].filmes[IDnota].qtdParcelas;

        float parcelasPagas = (((*dtbase_eFilme)[indexArray].filmes[IDnota].valorTotal -
        (*dtbase_eFilme)[indexArray].filmes[IDnota].valorEntrada) - (*dtbase_eFilme)[indexArray].filmes[IDnota].valorDeve) / valorParcelas;

    int erro = 0;
        do {
            printf("\n\n>> Parcelas Pagas: %d/3\n", (*dtbase_eFilme)[indexArray].filmes[IDnota].parcelasPagas);
            printf(">> Valor em Caixa: %.2f\n", monetario->caixa);
            printf(">> Valor Parcelas: %.2f\n\n", valorParcelas);
            do {
                if (erro >= 1){
                    printf("[!] Valor Invalido\n Informe um valor valido para quantidade de parcelas ou 0 para sair\n");
                }
                printf(">> Deseja pagar quantas parcelas: [Max: %d]: ",
                       (*dtbase_eFilme)[indexArray].filmes[IDnota].qtdParcelas - (int)parcelasPagas);
                scanf("%d", &qtdParcelas);
                if (qtdParcelas <= (*dtbase_eFilme)[indexArray].filmes[IDnota].qtdParcelas - (int)parcelasPagas || qtdParcelas == 0){
                    break;
                }
                erro++;
            } while (1);

            (*dtbase_eFilme)[indexArray].filmes[IDnota].parcelasPagas = (*dtbase_eFilme)[indexArray].filmes[IDnota].parcelasPagas + qtdParcelas;

            //qtdParcelas > (*dtbaseLocados)[indexlocados].qtdParcelas - (*dtbaseLocados)[indexlocados].parcelasPagas && qtdParcelas > 0
            if (monetario->caixa < (float) qtdParcelas * valorParcelas || qtdParcelas == 0){
                if (qtdParcelas == 0){
                    return -1;
                }
                printf("\n\nValor Parcelas: R$ %.2f \t Quantidade Parcelas: %d \t Valor Total Pagamento: R$ %.2f \n[!] Valor em caixa insulficiente para o pagamento\n\n",valorParcelas,qtdParcelas,valorParcelas * (float)qtdParcelas);
                system("pause");
                return -1;
            }

            printf("\nValor Pago: R$ %.2f\n", (float) qtdParcelas * valorParcelas);

            int confirm = 0;
            printf("Correto [1- SIM  0- NAO]: ");
            scanf("%d", &confirm);

            if (confirm == 1) {
                break;
            }
        } while (1);

        //Alterar Monetario
        monetario->caixa = monetario->caixa - (float) qtdParcelas * valorParcelas;
        monetario->despesas = monetario->despesas - (float) qtdParcelas * valorParcelas;

        (*dtbase_eFilme)[indexArray].filmes[IDnota].valorDeve = (*dtbase_eFilme)[indexArray].filmes[IDnota].valorDeve - ((float) qtdParcelas * valorParcelas);

        //Setar DtPagamento como hj
        dataAtual(&(*dtbase_eFilme)[indexArray].filmes[IDnota].dtPagamento);

        refazDadosEfIlme(dtbase_eFilme,qtd_eFilme,tipo_config);
    }
    return 0;
}

int refazDadosEfIlme(eFilme **dtbase, int qtdCCliente, int tipo_config) {
    FILE *p;
    if (tipo_config == 1) {
        p = fopen("cpyBdEntradaFilme.txt", "w");
        fclose(p);
        p = NULL;
        for (int i = 0; i < qtdCCliente; i++) {
            save_eFilme((*dtbase)[i], tipo_config);
        }
    } else if (tipo_config == 0) {
        p = fopen("cpyBdEntradaFilme.bin", "wb");
        fclose(p);
        p = NULL;
        for (int i = 0; i < qtdCCliente; i++) {
            save_eFilme((*dtbase)[i], tipo_config);
        }
    }
    return 0;
}
