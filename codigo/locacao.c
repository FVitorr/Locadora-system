#include "locacao.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <io.h>
#include "../cabecalhos/datas.h"

/*Ids 0 não serão aceitos*/

operacoe objetoOperacoe(filme **dtbaseFilme, int qtdFilme,fCategoria **dtbaseCategoria,int qtdCategoria,
                        int KEY_operator, int *idOperacao){
    int idtpm;
    operacoe newOpc;

    newOpc.ID = *idOperacao;
    *idOperacao = *idOperacao + 1;

    newOpc.KEY_operator = KEY_operator;

    line(100,"Filme\0");
    printf("[Operacao: %d]\n",KEY_operator);

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
//    newOpc.dtdevolucao.dia = 0;
//    newOpc.dtdevolucao.mes = 0;
//    newOpc.dtdevolucao.ano = 0;
    printf("\n>> Data da Devolucao: %d/%d/%d\n",newOpc.dtdevolucao.dia,newOpc.dtdevolucao.mes,newOpc.dtdevolucao.ano);

    newOpc.devolvido = 0; // 0 - Não
    return  newOpc;
}


locados objetoLocados (int idControleLocados,int idCliente,filme **dtbaseFilme,int qtdFilme,
                       operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                       fCategoria **dtbaseCategoria, int qtdCategoria, int *KEY_operacao,int Key_Cliente,
                       int tipoConfig){

    locados newObjeto;

    newObjeto.ID = idControleLocados; // valor guardado na struct cliente
    //*idControleLocados = *idControleLocados + 1; //Incrementar ID

    newObjeto.KEY_operator = *KEY_operacao; // Valor unico para cada cliente mas as operacoes apresenta o mesmo valor

    newObjeto.key_cliente = Key_Cliente;

    newObjeto.qtdFilme = 0;
    newObjeto.ultimoIDOperacao = 0;

    newObjeto.Dtpagamento.dia = 0;
    newObjeto.Dtpagamento.mes = 0;
    newObjeto.Dtpagamento.ano = 0;


    while (1){
        operacoe  op = objetoOperacoe(dtbaseFilme,qtdFilme,dtbaseCategoria,qtdCategoria,*KEY_operacao,&newObjeto.ultimoIDOperacao);

        if (op.valorFilme == -1){
            //Abortar Operação
            newObjeto.qtdFilme = -1;
            return newObjeto;
        }
        inserirOperacao(dtbaseOperacoe,op,qtdOperacoe,tamanhoOperacoe);
        saveOperacao(op, tipoConfig);

        newObjeto.qtdFilme =  newObjeto.qtdFilme + 1;

        int opc = 0;
        line(100,"1\0");
        printf("\nDigite: 1 - Adicionar mais Filme  \t0 - Finalizar \n>>OPC: ");
        scanf("%d",&opc);

        if (opc != 1){
            break;
        }
    }
    //Valor da Alocação
    newObjeto.valorTotal = 0;
    for (int i = 0; i < *qtdOperacoe; i++){
        if ((*dtbaseOperacoe)[i].KEY_operator == *KEY_operacao){
            newObjeto.valorTotal = newObjeto.valorTotal + (*dtbaseOperacoe)[i].valorFilme;
        }
    }
    //TIPO PAGAMENTO
    do{
        printf("\nValor total a ser Pago: R$ %.2f \n",newObjeto.valorTotal);
        printf("\nTipo do pagamento: [1- A vista \t2 - A prazo]: ");
        scanf("%d",&newObjeto.tipoPagamento);
    } while (newObjeto.tipoPagamento > 2 || newObjeto.tipoPagamento < 1);

    replacefloat(0,&newObjeto.valorEntrada);

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


            float valorParcelas = newObjeto.valorTotal/qtdParcelas;
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

    *KEY_operacao =  *KEY_operacao + 1;
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

                    int indexCliente = posicaoContaArray(dtBaseCCliente,qtdcliente,idCliente);

                    if (indexCliente == -1){
                        return -1;
                    }

                    int key_client = (*dtBaseCCliente)[indexCliente].key_cliente;

                    locados novaLocacao = objetoLocados((*dtBaseCCliente)[indexCliente].IDlocado,idCliente,dtbaseFilme,qtdFilme,
                                                        dtbaseOperacoe,qtdOperacoe,tamanhoOperacoe,dtbaseCategoria,qtdCategoria,KEY_Operacao,idCliente,tipoConfig);

                    (*dtBaseCCliente)[indexCliente].IDlocado = (*dtBaseCCliente)[indexCliente].IDlocado + 1;

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


                        inserirLocados(dtbaseLocados, novaLocacao, qtdLocados, tamanhoLocados);
                        saveLocacao(novaLocacao, tipoConfig);

                        refazDadosCCliente(dtBaseCCliente, *qtd_CCliente, tipoConfig);
                        break;
                    }else{
                        return -1;
                    }
                } else {

                    contaCliente novoCliente = objetoCCliente(IdContaCliente, idCliente, dtbaseCliente, qtdcliente,idCliente);
                    //Salvar conta cliente;
                    //Criar objeto Locado
                    locados novaLocacao = objetoLocados(novoCliente.IDlocado,idCliente,dtbaseFilme,qtdFilme,
                                                        dtbaseOperacoe,qtdOperacoe,tamanhoOperacoe,dtbaseCategoria,qtdCategoria,KEY_Operacao,idCliente,tipoConfig);

                    novoCliente.IDlocado++;

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

                        inserirLocados(dtbaseLocados, novaLocacao, qtdLocados, tamanhoLocados);
                        saveLocacao(novaLocacao, tipoConfig);
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
}


contaCliente objetoCCliente(int *IdContaCliente,int key_cliente,cliente **dtbaseCliente,int qtdcliente,int idCliente){
    line(100,"Conta Cliente");
    contaCliente novoCliente;

    novoCliente.ID = *IdContaCliente;
    *IdContaCliente = *IdContaCliente  + 1;

    novoCliente.key_cliente = key_cliente;

    novoCliente.Nome = nomeCliente(dtbaseCliente,qtdcliente,idCliente);
    novoCliente.idCliente = idCliente;

    novoCliente.valorDeve = 0;
    novoCliente.valorPago = 0;

    novoCliente.IDlocado = 0;

    return novoCliente;
}
int posicaoLocadosArray(locados **dtbaseLocados, int qtdLocados, int key_cliente, int IDlocado){
    for (int c = 0; c < qtdLocados; c++) {
        if ((*dtbaseLocados)[c].key_cliente == key_cliente && (*dtbaseLocados)[c].ID == IDlocado ){
            return c;
        }
    }
    return -1;
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


int listLocacao(locados **dtbaselocados, int qtdLocados, operacoe **dtbaseOperacoe, int qtdOpe, int key_cliente){
    data emprestimo,devolucao;
    char tipoPagamento[30];
    int test = 0;
    for (int c = 0; c < qtdLocados; c++) {
        for (int a = 0; a < qtdOpe; a++) {
            if ((*dtbaselocados)[c].KEY_operator == (*dtbaseOperacoe)[a].KEY_operator){
                emprestimo = (*dtbaseOperacoe)[c].dtemprestimo;
                devolucao = (*dtbaseOperacoe)[c].dtdevolucao;
                break;
            }
        }
        if ((key_cliente == (*dtbaselocados)[c].key_cliente || key_cliente == -1) && (*dtbaselocados)[c].TDdevolvido == 0){
            if ((*dtbaselocados)[c].tipoPagamento == 1){
                strcpy(tipoPagamento,"A Vista\0");
            }else{
                strcpy(tipoPagamento,"Parcelado\0");
            }
            printf("\n-----------------------------------------------------------------\n");
            printf("(%d) Codigo Cliente: %d\n"
                   "Registro da Operacao: %d\n"
                   "Data Emprestimo: %d/%d/%d\n"
                   "Quantidade de Filmes: %d\n"
                   "Data Devolucao Prevista: %d/%d/%d\n"
                   "Tipo Pagamento: %s\n"
                   "Valor Total: R$ %.2f\n"
                   "Data Pagamento %d/%d/%d\n",(*dtbaselocados)[c].ID,(*dtbaselocados)[c].key_cliente,(*dtbaselocados)[c].KEY_operator,emprestimo.dia,emprestimo.mes,emprestimo.ano,(*dtbaselocados)[c].qtdFilme,devolucao.dia,devolucao.mes,devolucao.ano,tipoPagamento,(*dtbaselocados)[c].valorTotal,(*dtbaselocados)[c].Dtpagamento.dia,(*dtbaselocados)[c].Dtpagamento.mes,(*dtbaselocados)[c].Dtpagamento.ano);
            test++;
        }
    }
    printf("\n");
    if (test > 0){
        return 1;
    }
    return 0;
}

void listOperacoes(operacoe **dtbaseOperacoe, int qtd, int KEY_operator) {
    for (int c = 0; c < qtd; c++) {
        if ((*dtbaseOperacoe)[c].KEY_operator == KEY_operator) {
            printf("\n-----------------------------------------------------------------\n");
            printf("(%d)\n"
                   "Codigo Filme: %d\n"
                   "Nome Filme: %s\n"
                   "Valor Total: R$ %.2f\n", (*dtbaseOperacoe)[c].ID, (*dtbaseOperacoe)[c].CodFilme,
                   (*dtbaseOperacoe)[c].nomeFilme, (*dtbaseOperacoe)[c].valorFilme);
        }
    }
    printf("\n");
}

int menuLocacao(filme **dtbaseFilme,int qtdFilme,
                cliente **dtbaseCliente,int qtdcliente,
                funcionarios **dtbaseFuncionarios, int qtdFuncionarios,int idFuncionarioLogado,
                locados **dtbaseLocados, int *qtdLocados, int *tamanhoLocados, int *idLocados,
                operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                contaCliente **dtbaseCCliente,int *qtdCCliente,int *tamanho_CCliente,int *idCCliente,
                fCategoria **dtbaseCategoria, int qtdCategoria,int *KEY_Operacao, int *KEY_Cliente,
                fornecedor **dtbaseFornecedor, int *qtdFornecedor,int *tamFornecedor,int *idEntradaFIlme,
                eFilme **dtBaseeFilme, int *tam_eFilme, int *qtd_eFilme,financeiro *monetario,int tipo_config){

    //carregarDados_CClientes(dtbaseCCliente,qtdCCliente,tamanhoCCliente,idCCliente,KEY_Cliente,tipo_config);
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



    int op = 0;
    printf("Funcionario: %s",nomefuncionario(dtbaseFuncionarios, qtdFuncionarios,idFuncionarioLogado));
    line(100,"Locacao\0");
    printf("\t 1- Emprestar \n\t 2- Devolver \n\t 3- Vizualizar Operacoes \n\t 4- Pagamento Cliente"
           "\n\t 5- Entrada de Filme"
           "\n\t 0- Sair");
    line(100,"1\0");

    do {
        printf(">>OPC: ");
        scanf("%d", &op);
    } while (op < 0 || op > 5);

    if (op == 1){
        emprestaFilme(dtbaseCCliente,qtdCCliente,tamanho_CCliente,idCCliente,KEY_Cliente,dtbaseCliente,qtdcliente,dtbaseFilme,qtdFilme,
                      dtbaseOperacoe,qtdOperacoe,tamanhoOperacoe,dtbaseLocados,qtdLocados,tamanhoLocados,dtbaseCategoria,qtdCategoria,KEY_Operacao,monetario,tipo_config);

    }else if (op == 2){
        //Devolução;
        devolucaoFilmes(dtbaseCCliente,*qtdCCliente,dtbaseLocados,*qtdLocados,dtbaseOperacoe,*qtdOperacoe,tipo_config);
    }else if (op == 3){
        //listCCliente(dtbaseCCliente,*qtdCCliente);
        listLocacao(dtbaseLocados,*qtdLocados,dtbaseOperacoe,*qtdCCliente,-1);
        system("pause");
    }else if (op == 4){
        pagarParcelas(dtbaseCCliente,*qtdCCliente,dtbaseLocados,*qtdLocados,monetario,tipo_config);
    } else if (op == 5){
        entradaFilmes(dtbaseFornecedor,qtdFornecedor,tamFornecedor,idEntradaFIlme,dtBaseeFilme,tam_eFilme,qtd_eFilme,tipo_config);
    }
    else{
        return 1;
    }
    return 0;
}

int inserirLocados(locados **dtbaseLocados,locados newEntry, int *qtdLocados, int *tamanhoLocados){
    //Se a quantidade de categorias for igual ao tamanho alocado da lista -> espandir
    if (*qtdLocados == *tamanhoLocados)
    {
        *tamanhoLocados = *tamanhoLocados + 1;
        *dtbaseLocados = (locados *) realloc(*dtbaseLocados, *tamanhoLocados * sizeof(locados));
    }
    if (*dtbaseLocados == NULL)
    {
        printf("\n  Erro na alocação de memória!");
        system("pause");
        return 0;
    }
    // adc obj ao bd local
    (*dtbaseLocados)[*tamanhoLocados - 1] = newEntry;
    *qtdLocados = *qtdLocados + 1;

    return 1;
}

int inserirOperacao(operacoe **dtbaseOperacao,operacoe newEntry, int *qtdOperacao, int *tamanhoOperacao){
    //Se a quantidade de categorias for igual ao tamanho alocado da lista -> espandir
    if (*qtdOperacao == *tamanhoOperacao)
    {
        *tamanhoOperacao = *tamanhoOperacao + 1;
        *dtbaseOperacao = (operacoe *) realloc(*dtbaseOperacao, *tamanhoOperacao * sizeof(operacoe));
    }
    if (*dtbaseOperacao == NULL)
    {
        printf("\n  Erro na alocação de memória!");
        system("pause");
        return 0;
    }
    // adc obj ao bd local
    (*dtbaseOperacao)[*tamanhoOperacao - 1] = newEntry;
    *qtdOperacao = *qtdOperacao + 1;

    return 1;
}


int saveOperacao(operacoe objeto, int tipo_config){
    FILE *operacaoF;

    if (tipo_config == 1){//Arquivo TXT
        if (verifica_arquivos(tipo_config,"cpyBdOperacao.txt\0") == 1){
            operacaoF = fopen("cpyBdOperacao.txt", "a");
        } else{
            operacaoF = fopen("cpyBdOperacao.txt", "w");
        }

        if (operacaoF == NULL){ // Se a abertura falhar
            return 1;
        }

        fprintf(operacaoF, "%d\n%d\n%d\n%s\n%f\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
                objeto.ID,
                objeto.KEY_operator,
                objeto.CodFilme,
                objeto.nomeFilme,
                objeto.valorFilme,
                objeto.dtemprestimo.dia,
                objeto.dtemprestimo.mes,
                objeto.dtemprestimo.ano,
                objeto.dtdevolucao.dia,
                objeto.dtdevolucao.mes,
                objeto.dtdevolucao.ano,
                objeto.devolvido);

    }else{ //Arquivo BINARIO
        operacaoF = fopen("cpyBdOperacao.bin", "ab");
        if (operacaoF == NULL){ // Se a abertura falhar
            return 1;
        }
        fwrite(&objeto, sizeof(operacoe), 1,operacaoF);
    }
    fclose(operacaoF);
    operacaoF = NULL;
    return 0;
}

void listCCliente(contaCliente **dtbaseCCcliente, int qtd, int key_cliente) {
    for (int c = 0; c < qtd; c++) {
        if ((*dtbaseCCcliente)[c].key_cliente == key_cliente || key_cliente == -1) {
            if (key_cliente == -1){printf("\n-----------------------------------------------------------------\n");}
            printf("(%d)\n"
                   "Chave Cliente: %d\n"
                   "ID Cliente: %d\n"
                   "Nome: %s\n"
                   "Valor a Receber: R$ %.2f\n"
                   "Valor Pago: R$ %.2f\n"
                   "ID Locados: %d\n", (*dtbaseCCcliente)[c].ID, (*dtbaseCCcliente)[c].key_cliente,
                   (*dtbaseCCcliente)[c].idCliente, (*dtbaseCCcliente)[c].Nome, (*dtbaseCCcliente)[c].valorDeve,
                   (*dtbaseCCcliente)[c].valorPago,
                   (*dtbaseCCcliente)[c].IDlocado);
        }
    }
    printf("\n");
}


int carregarDados_Operacoes(operacoe **dtbaseoperacoe, int *qtdOperacao, int *tamanhoOperaca, int *key_operator ,int tipo_config) {
    FILE *fOperacoe = NULL;
    operacoe new;
    int t = 0;
    if (tipo_config == 1){ //Arquivo TXT
        fOperacoe = fopen("cpyBdOperacao.txt", "r");

        if (fOperacoe == NULL){
            printf("\nErro na Leitura 'cpyBdOperacao.txt' \n");
            return 1;
        }

        while (!feof(fOperacoe)){
            if (!filelength(fileno(fOperacoe))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fscanf(fOperacoe, "%d\n", &new.ID);

            fscanf(fOperacoe, "%d\n", &new.KEY_operator);

            fscanf(fOperacoe, "%d\n", &new.CodFilme);

            char nameTemp[120];
            fgets(nameTemp, 120, fOperacoe);
            limpa_final_string(nameTemp);

            new.nomeFilme = string_to_pointer(nameTemp);

            fscanf(fOperacoe, "%f\n", &new.valorFilme);

            fscanf(fOperacoe, "%d\n", &new.dtemprestimo.dia);
            fscanf(fOperacoe, "%d\n", &new.dtemprestimo.mes);
            fscanf(fOperacoe, "%d\n", &new.dtemprestimo.ano);

            fscanf(fOperacoe, "%d\n", &new.dtdevolucao.dia);
            fscanf(fOperacoe, "%d\n", &new.dtdevolucao.mes);
            fscanf(fOperacoe, "%d\n", &new.dtdevolucao.ano);

            fscanf(fOperacoe, "%d\n", &new.devolvido);

            t = inserirOperacao(dtbaseoperacoe,new,qtdOperacao,tamanhoOperaca);

            if (*key_operator <= new.KEY_operator){
                *key_operator =  new.KEY_operator + 1;
            }

            if (t == 0){
                printf("\nAcao Interrompida");
                break;
            }
        }
    }
    else { //Arquivo BIN
        fOperacoe = fopen("cpyBdOperacao.bin", "rb");
        if (fOperacoe == NULL){
            printf("\nErro na Leitura 'cpyBdOperacao.bin' \n");
            return 1;
        }
        while (!feof(fOperacoe)){
            if (!filelength(fileno(fOperacoe))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fread(&new,sizeof(operacoe),1,fOperacoe);
            t = inserirOperacao(dtbaseoperacoe,new,qtdOperacao,tamanhoOperaca);
            if (t == 0){
                printf("\nAcao Interrompida");
                break;
            }
        }
    }
    fclose(fOperacoe);
    fOperacoe = NULL;
    return 0;
}

int saveLocacao(locados objeto, int tipo_config){
    FILE *locadosF = NULL;

    if (tipo_config == 1){//Arquivo TXT
        if (verifica_arquivos(tipo_config,"cpyBdLocados.txt\0") == 1){
            locadosF = fopen("cpyBdLocados.txt", "a");
        } else{
            locadosF = fopen("cpyBdLocados.txt", "w");
        }

        if (locadosF == NULL){ // Se a abertura falhar
            return 1;
        }

        fprintf(locadosF, "%d\n%d\n%d\n%d\n%f\n%f\n%f\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
                objeto.ID,
                objeto.KEY_operator,
                objeto.key_cliente,
                objeto.qtdFilme,
                objeto.valorTotal,
                objeto.valordeve,
                objeto.valorEntrada,
                objeto.tipoPagamento,
                objeto.Dtpagamento.dia,
                objeto.Dtpagamento.mes,
                objeto.Dtpagamento.ano,
                objeto.qtdParcelas,
                objeto.parcelasPagas,
                objeto.TDdevolvido,
                objeto.ultimoIDOperacao);

    }else{ //Arquivo BINARIO
        if (verifica_arquivos(tipo_config,"cpyBdLocados.bin\0") == 1){
            locadosF = fopen("cpyBdLocados.bin", "ab");
        } else{
            locadosF = fopen("cpyBdLocados.bin", "wb");
        }
        if (locadosF == NULL){ // Se a abertura falhar
            return 1;
        }
        fwrite(&objeto, sizeof(locados), 1,locadosF);
    }
    fclose(locadosF);
    locadosF = NULL;
    return 0;
}

int carregarDados_locacao(locados **dtbaseLocados, int *qtdlocados, int *tamanhoLocados, int *id,int tipo_config) {
    FILE *fileLocados = NULL;
    locados new;

    int *qtdTemp = qtdlocados;

    int t = 0;
    if (tipo_config == 1){ //Arquivo TXT
        fileLocados = fopen("cpyBdLocados.txt", "r");

        if (fileLocados == NULL){
            printf("\nErro na Leitura 'cpyBdLocados.txt' \n");
            return 1;
        }

        while (!feof(fileLocados)){
            if (!filelength(fileno(fileLocados))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fscanf(fileLocados, "%d\n", &new.ID);

            fscanf(fileLocados, "%d\n", &new.KEY_operator);

            fscanf(fileLocados, "%d\n", &new.key_cliente);

            fscanf(fileLocados, "%d\n", &new.qtdFilme);

            fscanf(fileLocados, "%f\n", &new.valorTotal);

            fscanf(fileLocados, "%f\n", &new.valordeve);

            fscanf(fileLocados, "%f\n", &new.valorEntrada);

            fscanf(fileLocados, "%d\n", &new.tipoPagamento);

            fscanf(fileLocados, "%d\n", &new.Dtpagamento.dia);
            fscanf(fileLocados, "%d\n", &new.Dtpagamento.mes);
            fscanf(fileLocados, "%d\n", &new.Dtpagamento.ano);


            fscanf(fileLocados, "%d\n", &new.qtdParcelas);

            fscanf(fileLocados, "%d\n", &new.parcelasPagas);

            fscanf(fileLocados, "%d\n", &new.TDdevolvido);

            fscanf(fileLocados, "%d\n", &new.ultimoIDOperacao);

//            if (verificaIdFilme(dtBase,*qtdLocados,new.codigo) == 0){
//                t = inserirFilme(dtBase,new,qtdFilme,tamanhoFilme,tipo_config);
//            }
            //printf("QTD: %d",*qtd_lo);
            t = inserirLocados(dtbaseLocados,new,qtdlocados,tamanhoLocados);
            if (*id <= new.ID) {
                *id = new.ID + 1;
            }

            if (t == 0){
                printf("\nAcao Interrompida");
                break;
            }
        }
    }
    else { //Arquivo BIN
        fileLocados = fopen("cpyBdLocados.bin", "rb");
        if (fileLocados == NULL){
            printf("\nErro na Leitura 'cpyBdLocados.bin' \n");
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
        if (verifica_arquivos(tipo_config,"cpyBdContaCliente.txt\0") == 1){
            contaclienteF = fopen("cpyBdContaCliente.txt", "a");
        } else{
            contaclienteF = fopen("cpyBdContaCliente.txt", "w");
        }

        if (contaclienteF == NULL){ // Se a abertura falhar
            return 1;
        }

        fprintf(contaclienteF, "%d\n%d\n%d\n%s\n%f\n%f\n%d\n",
                objeto.ID,
                objeto.key_cliente,
                objeto.idCliente,
                objeto.Nome,
                objeto.valorDeve,
                objeto.valorPago,
                objeto.IDlocado);

    }else{ //Arquivo BINARIO
        if (verifica_arquivos(tipo_config,"cpyBdContaCliente.bin\0") == 1){
            contaclienteF = fopen("cpyBdContaCliente.bin", "ab");
        } else{
            contaclienteF = fopen("cpyBdContaCliente.bin", "wb");
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
        fileLocados = fopen("cpyBdContaCliente.txt", "r");

        if (fileLocados == NULL){
            printf("\nErro na Leitura 'cpyBdContaCliente.txt' \n");
            return 1;
        }

        while (!feof(fileLocados)){
            if (!filelength(fileno(fileLocados))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fscanf(fileLocados, "%d\n", &new.ID);

            fscanf(fileLocados, "%d\n", &new.key_cliente);

            fscanf(fileLocados, "%d\n", &new.idCliente);

            char nome[120];
            fgets(nome, 120, fileLocados);
            new.Nome = string_to_pointer(nome);

            fscanf(fileLocados, "%f\n", &new.valorDeve);

            fscanf(fileLocados, "%f\n", &new.valorPago);

            fscanf(fileLocados, "%d\n", &new.IDlocado);

//            if (verificaIdFilme(dtBase,*qtdLocados,new.codigo) == 0){
//                t = inserirFilme(dtBase,new,qtdFilme,tamanhoFilme,tipo_config);
//            }
            //printf("QTD: %d",*qtd_lo);
            corrigirIdCCliente(dtBaseCCliente,*qtd_CCliente,&new.ID);

            t = inserirCCliente(dtBaseCCliente,new,qtd_CCliente,tamanhoCCliente);
            if (*idControle <= new.ID) {
                *idControle = new.ID + 1;
            }
            if (*Key_Cliente <= new.key_cliente){
                *Key_Cliente =  new.key_cliente + 1;
            }

            if (t == 0){
                printf("\nAcao Interrompida");
                break;
            }
        }
    }
    else { //Arquivo BIN
        fileLocados = fopen("cpyBdLocados.bin", "rb");
        if (fileLocados == NULL){
            printf("\nErro na Leitura 'cpyBdLocados.bin' \n");
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
    FILE *p;
    if (tipo_config== 1){
        p = fopen("cpyBdContaCliente.txt", "w");
        fclose(p);
        p = NULL;
        for (int i = 0; i < qtdCCliente; i++){
            saveContaCliente((*dtbase)[i],tipo_config);
        }
    }else if (tipo_config == 0){
        p = fopen("cpyBdContaCliente.bin", "wb");
        fclose(p);
        for (int i = 0; i < qtdCCliente; i++){
            saveContaCliente((*dtbase)[i],tipo_config);
        }
    }
    return 0;
}

int pagarParcelas(contaCliente **dtbaseCCliente,int qtdCCliente, locados **dtbaseLocados, int qtdLocados,financeiro *monetario,int tipoconfig){
    line(100,"Pagamento Parcelas\0");
    printf("\nContas Disponiveis:\n\n");
    for (int i = 0; i < qtdCCliente; i++){
        printf(" (ID: %d) Cliente: %s   ",(*dtbaseCCliente)[i].ID,(*dtbaseCCliente)[i].Nome);
    }
    int erroID = 0,IdCliente;
    do{
        if (erroID == 1){
            printf("\nID invalido por gentileza informe um valido\n");
        }
        printf("\n\nInforme o ID do Cliente: ");
        scanf("%d",&IdCliente);
        erroID = 1;
    } while (verificaConta(dtbaseCCliente,qtdCCliente,IdCliente) == 0);

    int key_cliente =  retornaChaveCliente(dtbaseCCliente,qtdCCliente,IdCliente);

    line(100,"Dados Cliente\0");
    printf("\n");
    listCCliente(dtbaseCCliente,qtdCCliente,key_cliente);

    line(100,"Locados\0");
    printf("\n");

    //printf("%d %d",key_cliente,key_operator);
    char tipoPag[10];
    int test = 0;
    for (int c = 0; c < qtdLocados; c++){
        if ((*dtbaseLocados)[c].key_cliente == IdCliente && (*dtbaseLocados)[c].tipoPagamento == 2 && ((*dtbaseLocados)[c].qtdParcelas - (*dtbaseLocados)[c].parcelasPagas) > 0) {
            float valorParcelas = ((*dtbaseLocados)[c].valorTotal - (*dtbaseLocados)[c].valorEntrada) / (float)(*dtbaseLocados)[c].qtdParcelas;
            float parcelasPagas = ((((*dtbaseLocados)[c].valorTotal - (*dtbaseLocados)[c].valorEntrada) - (*dtbaseLocados)[c].valordeve) / valorParcelas);
            if ((*dtbaseLocados)[c].tipoPagamento == 1){
                strcpy(tipoPag,"A vista\0");
            }else{
                strcpy(tipoPag,"Parcelado\0");
            }

            printf("(%d) Codigo Cliente: %d\n"
                   "Registro da Operacao: %d\n"
                   "Quantidade de Filmes: %d\n"
                   "Tipo Pagamento: %s\n"
                   "Valor Total: R$ %.2f\n"
                   "Valor Parcelas: R$ %.2f\n"
                   "Parcelas Pagas: %.1f\n"
                   "Data Pagamento %d/%d/%d\n",(*dtbaseLocados)[c].ID,
                   (*dtbaseLocados)[c].key_cliente,(*dtbaseLocados)[c].KEY_operator,
                   (*dtbaseLocados)[c].qtdFilme,
                   tipoPag,(*dtbaseLocados)[c].valorTotal,valorParcelas,parcelasPagas,
                   (*dtbaseLocados)[c].Dtpagamento.dia,(*dtbaseLocados)[c].Dtpagamento.mes,
                   (*dtbaseLocados)[c].Dtpagamento.ano);
            test++;
        }
    }
    if (test == 0){
        printf("\n\t>>Tudo Pago Pelo Cliente :)");
    }else {

        int IDlocados, erro = 0;
        do {
            if (erro == 1) { printf("\n[!] ID Invalido\n"); }
            printf("\n\n>> Informe o ID para realizar o pagamento: ");
            scanf("%d", &IDlocados);
            erro = 1;
        } while (verificaIDLocados(dtbaseLocados, qtdLocados, IDlocados, key_cliente) == 0);

        int indexlocados = posicaoLocadosArray(dtbaseLocados, qtdLocados, key_cliente, IDlocados);

        int qtdParcelas = 0;
        erro = 0;
        do {
            if (erro == 1) { printf("\n[!]Quantidade de parcelas Invalidas\n\n"); }
            printf("\n>>Quantidade de parcelas que deseja pagar  [MAX: %d]: ",
                   (*dtbaseLocados)[indexlocados].qtdParcelas - (*dtbaseLocados)[indexlocados].parcelasPagas);
            scanf("%d", &qtdParcelas);
            erro = 1;
        } while (qtdParcelas > (*dtbaseLocados)[indexlocados].qtdParcelas - (*dtbaseLocados)[indexlocados].parcelasPagas && qtdParcelas > 0);

        (*dtbaseLocados)[indexlocados].parcelasPagas = (*dtbaseLocados)[indexlocados].parcelasPagas + qtdParcelas;
        //preco das parcelas.
        float valorParcelas =
                ((*dtbaseLocados)[indexlocados].valorTotal - (*dtbaseLocados)[indexlocados].valorEntrada) /
                (float) (*dtbaseLocados)[indexlocados].qtdParcelas;

        //Valor pago Total Parcelas * ValorParcelas((float)qtdParcelas * valorParcelas);

        //Setar a Data do pagamento como hj
        (*dtbaseLocados)[indexlocados].valordeve =
                (*dtbaseLocados)[indexlocados].valordeve - ((float) qtdParcelas * valorParcelas);
        dataAtual(&(*dtbaseLocados)[indexlocados].Dtpagamento);

        //Qtd de parcelas Pagas
        float parcelasPagas = (
                (((*dtbaseLocados)[indexlocados].valorTotal - (*dtbaseLocados)[indexlocados].valorEntrada) -
                 (*dtbaseLocados)[indexlocados].valordeve) / valorParcelas);

        printf("\nValor Pago: R$%.2f\nValor em Debito: R$%.2f\nQuantidade de Parcelas Restante : %d \n"
               "Data pagamento: %d/%d/%d\n\n", valorParcelas * (float) qtdParcelas,
               (*dtbaseLocados)[indexlocados].valordeve,
               (*dtbaseLocados)[indexlocados].qtdParcelas - (int) parcelasPagas,
               (*dtbaseLocados)[indexlocados].Dtpagamento.dia, (*dtbaseLocados)[indexlocados].Dtpagamento.mes,
               (*dtbaseLocados)[indexlocados].Dtpagamento.ano);

        int indexConta = posicaoContaArray(dtbaseCCliente, qtdCCliente, IdCliente);
        (*dtbaseCCliente)[indexConta].valorPago =
                (*dtbaseCCliente)[indexConta].valorPago + (valorParcelas * (float) qtdParcelas);
        (*dtbaseCCliente)[indexConta].valorDeve =
                (*dtbaseCCliente)[indexConta].valorDeve - (valorParcelas * (float) qtdParcelas);

        //Enviar ao caixa da locadora
        monetario->caixa = monetario->caixa + (valorParcelas * (float) qtdParcelas);
        monetario->contasReceber = monetario->contasReceber - (valorParcelas * (float) qtdParcelas);

        refazDadosCCliente(dtbaseCCliente, qtdCCliente, tipoconfig);
        refazDadosLocados(dtbaseLocados, qtdLocados, tipoconfig);
        return 0;
    }
}



int refazDadosLocados(locados **dtbase, int qtdLocados, int tipo_config){
    FILE *p;
    if (tipo_config== 1){
        p = fopen("cpyBdLocados.txt", "w");
        fclose(p);
        p = NULL;
        for (int i = 0; i < qtdLocados; i++){
            saveLocacao((*dtbase)[i],tipo_config);
        }
    }else if (tipo_config == 0){
        p = fopen("cpyBdLocados.bin", "wb");
        fclose(p);
        for (int i = 0; i < qtdLocados; i++){
            saveLocacao((*dtbase)[i],tipo_config);
        }
    }
    return 0;
}

int refazDadosOperacao(operacoe **dtbase, int qtdOperacao, int tipo_config){
    FILE *p;
    if (tipo_config== 1){
        p = fopen("cpyBdOperacao.txt", "w");
        fclose(p);
        p = NULL;
        for (int i = 0; i < qtdOperacao; i++){
            saveOperacao((*dtbase)[i],tipo_config);
        }
    }else if (tipo_config == 0){
        p = fopen("cpyBdOperacao.bin", "wb");
        fclose(p);
        for (int i = 0; i < qtdOperacao; i++){
            saveOperacao((*dtbase)[i],tipo_config);
        }
    }
    return 0;
}



int verificaIDLocados(locados **dtbaselocados, int qtdLocados, int id, int key_cliente){ // 1 existe 0 nao existe
    for (int i = 0; i < qtdLocados; i++){
        if ((*dtbaselocados)[i].ID == id && (*dtbaselocados)[i].key_cliente == key_cliente){
            return 1;
        }
    }return 0;
}
int retornaChaveOperacao(locados **dtbaselocados, int qtdLocados, int id, int key_cliente){ // 1  Retorna a chave da operaçao
    for (int i = 0; i < qtdLocados; i++){
        if ((*dtbaselocados)[i].ID == id && (*dtbaselocados)[i].key_cliente == key_cliente){
            return (*dtbaselocados)[i].KEY_operator;
        }
    }return -1;
}

int retornaChaveCliente(contaCliente **dtbase, int qtd, int idCliente){ // Retorna a chave do cliente
    for (int i = 0; i < qtd; i++){
        if ((*dtbase)[i].idCliente == idCliente){
            return (*dtbase)[i].key_cliente;
        }
    }return -1;
}




int devolucaoFilmes(contaCliente **dtbaseCCliente,int qtdCCliente,locados **dtbaselocados, int qtdLocados,
                     operacoe **dtbaseOperacoes, int qtdOperacao,int tipoConfig){
    system("cls");
    line(100,"Devolucao Filmes\0");
    printf("\nContas Disponiveis:\n");
    for (int i = 0; i < qtdCCliente; i++){
        printf(" (ID: %d) Cliente: %s   ",(*dtbaseCCliente)[i].ID,(*dtbaseCCliente)[i].Nome);
    }
    int IdCliente,erroID = 0,entregaCompleta;
    line(100,"-\0");
    do{
        if (erroID == 1){
            printf("\nID invalido por gentileza informe um valido\n");
        }
        printf("\nInforme o ID do Cliente: ");
        scanf("%d",&IdCliente);
        erroID = 1;
    } while (verificaConta(dtbaseCCliente,qtdCCliente,IdCliente) == 0);

    int key_cliente =  retornaChaveCliente(dtbaseCCliente,qtdCCliente,IdCliente);

    //printf("%d %d",key_cliente,key_operator);

    printf("\nDevolucoes pendentes ");
    int temDevolver = listLocacao(dtbaselocados,qtdLocados,dtbaseOperacoes,qtdOperacao,key_cliente);

    if (temDevolver == 1){//tem algo para devolver
        int IDlocados,erro = 0;
        do {
            if (erro == 1){ printf("\n[!] ID Invalido\n");}
            printf("Informe o ID da Devolucao: ");
            scanf("%d", &IDlocados);
            erro = 1;
        }while(verificaIDLocados(dtbaselocados,qtdLocados,IDlocados,key_cliente) == 0);

        int key_operator = retornaChaveOperacao(dtbaselocados,qtdLocados,IDlocados,key_cliente);


        printf("\nVerifique os Filmes: ");
        listOperacoes(dtbaseOperacoes,qtdOperacao,key_operator);


        //Precisa Selecionar a Referencia dos Locados
        //Aqueles que apresenta tudo Devolvido Não serão listado


        printf("\nO cliente vai realizar a entrega completa ?  [1- Sim \t 0 - Nao]: ");
        scanf("%d",&entregaCompleta);

        if (entregaCompleta == 1){
            //Devolveu tudo
            for (int i = 0; i< qtdLocados; i++){
                if((*dtbaselocados)[i].key_cliente == key_cliente && (*dtbaselocados)[i].ID == IDlocados){
                    replaceInt(1,&(*dtbaselocados)[i].TDdevolvido);
                    break;
                }
            }
            for (int i = 0; i< qtdOperacao; i++){
                if((*dtbaseOperacoes)[i].KEY_operator == key_operator){
                    replaceInt(1,&(*dtbaseOperacoes)[i].devolvido);

                    //Setar data de Devoluçao como HJ
                    data *dtDevolucao = &(*dtbaseOperacoes)[i].dtdevolucaoReal;
                    dataAtual(dtDevolucao);
                    //Verificar se passou do prazo de entrega e calcular multa;

                    data hoje;
                    dataAtual(&hoje);
                    int t = diasEntreDatas((*dtbaseOperacoes)[i].dtdevolucao,hoje);

                    if (t > 0){
                        printf(">> MULTA APLICADA.");
                        //Adicionar Valor ao campo deve
                    }

                    printf("%d/%d/%d   %d/%d/%d  %d"  , (*dtbaseOperacoes)[i].dtdevolucao.dia,(*dtbaseOperacoes)[i].dtdevolucao.mes,(*dtbaseOperacoes)[i].dtdevolucao.ano,
                           hoje.dia,hoje.mes,hoje.ano,t );
                    //printf("%d / %d / %d",dtDevolucao->dia,dtDevolucao->mes,dtDevolucao->ano);
                }
            }
            //Verificar Tipo Pagamento - Se a prazo o valor deve ser quitado
            int indexLocados = posicaoLocadosArray(dtbaselocados,qtdLocados,key_cliente,IDlocados);
            int indexConta = posicaoContaArray(dtbaseCCliente,qtdCCliente,IdCliente);


            refazDadosLocados(dtbaselocados,qtdLocados,tipoConfig);
            refazDadosOperacao(dtbaseOperacoes,qtdOperacao,tipoConfig);
            refazDadosCCliente(dtbaseCCliente,qtdCCliente,tipoConfig);
        }else{
            int qtdDevolver;
            printf("Quantos Filmes serão devolvidos: ");
            scanf("%d",&qtdDevolver);

        }
    } else{
        printf("\n\n\t[!] O Cliente ja devolveu todos os filmes");
        system("pause");
        return 0;
    }
}

int entradaFilmes(fornecedor **dtbase, int *qtdFornecedor,int *tamFornecedor,int *idEntradaFIlme, eFilme **dtBase_eFilme, int *tam_eFilme, int *qtd_eFime,int tipo_config){


    carregarDados_Efilme(dtBase_eFilme, qtd_eFime, tam_eFilme, idEntradaFIlme,tipo_config);
    list_eFilme(dtBase_eFilme,*qtd_eFime);

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
            operacaoEFilme newOp = objOpEfilme(&(*dtBase_eFilme)[posArray].ultIDOp);
            inserirop_EFIlme(&(*dtBase_eFilme)[posArray].filmes, newOp, &(*dtBase_eFilme)[posArray].tamOp);
        }


    }else{
        while (1) {
            eFilme newEFilme = objetoefilme(&idFilme, dtbase, *qtdFornecedor, IDFornecedor);

            operacaoEFilme newOp = objOpEfilme(&newEFilme.ultIDOp);
            //newEFilme.nomefornecedor
            inserirop_EFIlme(&newEFilme.filmes, newOp, &newEFilme.tamOp);
            inserir_eFilme(dtBase_eFilme, newEFilme, qtd_eFime, tam_eFilme);
            save_eFilme(newEFilme,tipo_config);
            break;
        }
    }

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


operacaoEFilme objOpEfilme (int *id){
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
        printf(" %f ",newOpEfilme.valorTotal);
    }

    printf("\nFrete: R$ %.2f  Imposto : R$ %.2f Qtd: %d\n",newOpEfilme.fretePproduto,newOpEfilme.ImpostoPproduto,qtdTotalFilme);

    printf("\nValor total a ser Pago: R$ %.2f \n",newOpEfilme.valorTotal);
    //TIPO PAGAMENTO
    do{
        printf("\nTipo do pagamento: [1- A vista \t2 - A prazo]: ");
        scanf("%d",&newOpEfilme.tipoPagamento);
    } while (newOpEfilme.tipoPagamento > 2 || newOpEfilme.tipoPagamento < 1);

    replacefloat(0,&newOpEfilme.valorEntrada);

    if (newOpEfilme.tipoPagamento == 1){//Pagamento a vista
        newOpEfilme.qtdParcelas = 1;
        newOpEfilme.valorDeve = 0; // Cliente pagou tudo
//        //Adicionar valor ao caixa
//        monetario->caixa = monetario->caixa + newObjeto.valorPago;
//        //Adicionar valor pago a conta cliente fora da função
        dataAtual(&newOpEfilme.dtPagamento);

    }else {
        int ent = 0;
        float qtdParcelas;
        float valorE;
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
                    printf("\nValor Invalido, por gentileza informar um valor inferior a R$ %.2f",
                           newOpEfilme.valorTotal);
                }
                //Valor de entrada
                printf("\n>> Valor R$ ");
                scanf("%f", &valorE);

                valorInvalido = 1;
            } while (valorE >= newOpEfilme.valorTotal);
            //Calcular restante(valordeve) =  Valor Total menos valor de entrada
            newOpEfilme.valorDeve = newOpEfilme.valorTotal - valorE;
            //Adicionar valor de entrada
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
            printf("\nA conta foi dividida em %f parcelas \n O Valor de cada parcela e: R$ %.2f", qtdParcelas,
                   valorParcelas);
            newOpEfilme.qtdParcelas = (int) qtdParcelas;
            newOpEfilme.valorDeve = newOpEfilme.valorTotal;
        }
    }
    newOpEfilme.ultIDFilm = 0;
    return newOpEfilme;
}

filme objetoEntradaFIlme (int *id,filme **dtbase,int *tamFilm){
    while (1) {
        // realocar memoria
        if (*tamFilm > 1) {
            (*dtbase) = (filme *) realloc(*dtbase,*tamFilm * sizeof(filme));
        }
        filme novo;

        while (1) {
            novo.codigo = *id;
            *id = *id + 1;

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
                fprintf(entradaFilmeF, "%d\n%f\n%f\n%d\n%d\n%f\n%f\n%f\n%d\n%d\n%f\n%f\n%d\n%d\n%d\n%d\n%d\n%d\n",
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
        if (verifica_arquivos(tipo_config,"cpyBdLocados.bin\0") == 1){
            entradaFilmeF = fopen("cpyBdLocados.bin", "ab");
        } else{
            entradaFilmeF = fopen("cpyBdLocados.bin", "wb");
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


int carregarDados_Efilme(eFilme **dtbase, int *qtdeFilmes, int *tamanhoeFilmes, int *id,int tipo_config) {
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
            if (*id <= new.ID) {
                *id = new.ID + 1;
            }

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

int list_eFilme(eFilme **dtBase_eFilme, int qtd_eFime){
    for (int i = 0; i  < qtd_eFime; i++){
        printf("\nID Nota: (%d)\n| Fornecedor: %s  \t\tCNPJ: %s\n",(*dtBase_eFilme)[i].ID,(*dtBase_eFilme)[i].nomefornecedor,(*dtBase_eFilme)[i].cnpj);
        for (int j = 0; j  < (*dtBase_eFilme)[i].tamOp - 1; j++){
            printf("\n| (%d) Data da Nota: %d/%d/%d",(*dtBase_eFilme)[i].filmes[j].ID,(*dtBase_eFilme)[i].filmes[j].dtNota.dia,(*dtBase_eFilme)[i].filmes[j].dtNota.mes,(*dtBase_eFilme)[i].filmes[j].dtNota.ano);
            printf("\n\n| Frete: R$ %.2f    Imposto: R$ %.2f\n",(*dtBase_eFilme)[i].filmes[j].frete,(*dtBase_eFilme)[i].filmes[j].Imposto);
            printf("\n|%s|%s|%s|%s|%s|%s|%s|", formatstring(30, strlen("Descricao\0"),"Descricao\0"),
                        formatstring(13, strlen("Preco Custo\0"),"Preco Custo\0"),
                        formatstring(13, strlen("Frete\0"),"Frete\0"),
                        formatstring(13, strlen("Imposto\0"),"Imposto\0"),
                        formatstring(13, strlen("Preco Total\0"),"Preco Total\0"),
                        formatstring(13, strlen("Quantidade\0"),"Quantidade\0"),
                        formatstring(13, strlen("Total\0"),"Total\0"));
            for (int k = 0; k  < (*dtBase_eFilme)[i].filmes[j].tamFilm; k++){

                float precoTotal = 0;

                char precoCusto[100],auxprecoCusto[100] = "R$ \0";
                limpaString(precoCusto,sizeof(precoCusto));
                sprintf(precoCusto,"%.2f",(*dtBase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].valorCompra);
                strcat(auxprecoCusto,precoCusto);

                precoTotal = precoTotal + (*dtBase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].valorCompra;

                char frete[100],auxfrete[100] = "R$ \0";
                limpaString(frete,sizeof(frete));
                sprintf(frete,"%.2f",(*dtBase_eFilme)[i].filmes[j].fretePproduto);
                strcat(auxfrete,frete);

                precoTotal = precoTotal + (*dtBase_eFilme)[i].filmes[j].fretePproduto;

                char imposto[100],auximposto[100] = "R$ \0";
                limpaString(imposto,sizeof(imposto));
                sprintf(imposto,"%.2f",(*dtBase_eFilme)[i].filmes[j].ImpostoPproduto);
                strcat(auximposto,imposto);

                precoTotal = precoTotal + (*dtBase_eFilme)[i].filmes[j].ImpostoPproduto;

                char qtd[10];
                limpaString(qtd,sizeof(qtd));
                sprintf(qtd,"%d",(*dtBase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].qtd);

                char precoTotalChar[100];
                limpaString(precoTotalChar,sizeof(precoTotalChar));
                sprintf(precoTotalChar,"%.2f",precoTotal);

                precoTotal = precoTotal * (float)(*dtBase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].qtd;
                char ValorTotalPago[100];
                limpaString(ValorTotalPago,sizeof(ValorTotalPago));
                sprintf(ValorTotalPago,"%.2f",precoTotal);

                printf("\n|%s|%s|%s|%s|%s|%s|%s|",formatstring(30, (int)strlen((*dtBase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].nome),(*dtBase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].nome),
                       formatstring(13, (int)strlen(auxprecoCusto),auxprecoCusto),
                       formatstring(13, (int)strlen(auxfrete),auxfrete),
                       formatstring(13, (int)strlen(auximposto),auximposto),
                       formatstring(13, (int)strlen(precoTotalChar),precoTotalChar),
                       formatstring(13, (int)strlen(qtd),qtd),
                       formatstring(13, (int)strlen(ValorTotalPago),ValorTotalPago));
            }
        }
    }
}