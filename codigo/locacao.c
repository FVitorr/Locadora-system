#include "locacao.h"
#include <stdlib.h>
#include <stdio.h>

operacoe objetoOperacoe(locados *newObjeto, filme **dtbaseFilme, int qtdFilme,fCategoria **dtbaseCategoria,int qtdCategoria,
                        int KEY_operator){
    int idtpm;
    int tamanhoArray = 1;

    operacoe newOpc;
    newOpc.KEY_operator = KEY_operator;
    line(100,"Filme\0");
    do {
        printf("Informe ID do Filme: ");
        scanf("%d", &idtpm);

        if (verificaIdFilme(dtbaseFilme, qtdFilme, idtpm) == 1) { //Verificar se o ID do filme Existe
            newOpc.CodFilme = idtpm;
            //Incrementar o valor do campo emprestados
            altQtdEmprestadaFilme(dtbaseFilme,qtdFilme,idtpm);

            refazDados_filme(dtbaseFilme,qtdFilme, 1);

            //Nome Filme
            newOpc.nomeFilme = nomeFilme(dtbaseFilme,qtdFilme,idtpm);

            //Valor Pago

            int idCategoria = categoriaFilme(dtbaseFilme,qtdFilme, idtpm);
            newOpc.valorPago = valorCategoria(dtbaseCategoria,qtdCategoria,idCategoria);

            break;
        } else {
            printf("ID Invalido");
            //Mostrar ID de filmes Existentes
        }
    }while (1);

    obterData(&newOpc.dtemprestimo);
    printf("\n>> Data do emprestimo: %d/%d/%d\n",newOpc.dtemprestimo.dia,newOpc.dtemprestimo.mes,newOpc.dtemprestimo.ano);

    newOpc.dtdevolucao.dia = 0;
    newOpc.dtdevolucao.mes = 0;
    newOpc.dtdevolucao.ano = 0;

    newOpc.devolvido = 0; // 0 - Não
    return  newOpc;
}


locados objetoLocados (int *id,cliente **dtbaseCliente,int qtdcliente,filme **dtbaseFilme,int qtdFilme,
                       operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                       fCategoria **dtbaseCategoria, int qtdCategoria, int *KEY_Controle){
    
    locados newObjeto;

    newObjeto.ID = *id;
    *id = *id + 1; //Incrementar ID

    //Operaçoes
    newObjeto.KEY_operator = *KEY_Controle;

    //Cliente
    int idtpm;
    do {
        printf("Informe ID do Cliente: ");
        scanf("%d", &idtpm);

        int confirm;
        if (verificaIdCliente(dtbaseCliente, qtdcliente, idtpm) == 1) { //Verifica se o cliente existe
            //Guardar Codico do cliente
            newObjeto.CodCliente = idtpm;
            //Retornar o nome do cliente
            newObjeto.Nome = nomeCliente(dtbaseCliente,qtdcliente,idtpm);
            printf("\nNome do Cliente: %s \nCorreto: [1 - SIM   0 - Nao] \n >> OPC: ", newObjeto.Nome);
            scanf("%d",&confirm);
            break;
        } else {
            printf("\nID invalido");
            //Permitir que clientes sejam listados
        }
    } while(1);

    newObjeto.qtdFilme = 0;
    int tamanhoArray = 1;


    while (1){
        operacoe  op = objetoOperacoe(&newObjeto,dtbaseFilme,qtdFilme,dtbaseCategoria,qtdCategoria,*KEY_Controle);

        if (*qtdOperacoe >= *tamanhoOperacoe)
        {
            *tamanhoOperacoe = *tamanhoOperacoe + 1;
            *dtbaseOperacoe = (operacoe *) realloc(*dtbaseOperacoe, *tamanhoOperacoe * sizeof(operacoe));
        }
        if (*dtbaseOperacoe == NULL)
        {
            printf("\n  Erro na alocação de memória!");
            exit(0);
        }
        // adc obj ao bd local
        (*dtbaseOperacoe)[*tamanhoOperacoe - 1] = op;
        *qtdOperacoe = *qtdOperacoe + 1;
        //listOperacoes(dtbaseOperacoe,*qtdOperacoe,*KEY_Controle);

        newObjeto.qtdFilme =  newObjeto.qtdFilme + 1;

        int opc = 0;
        line(100,"1\0");
        printf("\n 1- Adicionar Mais Filme  0 - Finalizar \n>>OPC: ");
        scanf("%d",&opc);

        if (opc != 1){
            break;
        }
    }
    //Valor da Alocação
    newObjeto.valorPago = 0;
    for (int i = 0; i < *qtdOperacoe; i++){
        if ((*dtbaseOperacoe)[i].KEY_operator == *KEY_Controle){
            newObjeto.valorPago = newObjeto.valorPago + (*dtbaseOperacoe)[i].valorPago;
        }
    }

    //TIPO PAGAMENTO
    do{
        printf("\nTipo do pagamento: [1- A vista \t2 - A prazo]\n>>OPC: ");
        scanf("%d",&newObjeto.tipoPagamento);
    } while (newObjeto.tipoPagamento > 2 || newObjeto.tipoPagamento < 1);

    if (newObjeto.tipoPagamento == 1){
        //Adc a contas
    }else{
        int ent = 0,qtdParcelas;
        float valor;
        do{
            printf("\n >>Mais Filmes ?  [ 1 - Sim \t0 - Nao ]");
            scanf("%d",&ent);
            if (ent == 0 || ent == 1){break;}
            else{ printf("\n>> Opc Invalida");}
        } while (1);

        if (ent == 1){
            printf("\n>> Valor R$ ");
            scanf("%f",&valor);
            //Adc a contas
            //Dividir
            printf("\n>> Dividir de quantas Vezes [3x Valor Maximo] ? ");
            scanf("%f",&qtdParcelas);
        }
    }
    newObjeto.TDdevolvido = 0; // 0 - Não

    *KEY_Controle =  *KEY_Controle + 1;
//    printf("(%d)\nCodigo Cliente: %d\n"
//           "Nome Cliente: %s\n"
//           "Quantidade de Filmes: %d\n"
//           "Valor Total: R$ %.2f\n",newObjeto.ID,newObjeto.CodCliente,newObjeto.Nome,newObjeto.qtdFilme,newObjeto.valorPago);
    return newObjeto;
}

int inserirLocados(locados **dtbaseLocados,locados newLocados, int *qtdLocados, int *tamanhoLocados){
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
    (*dtbaseLocados)[*tamanhoLocados - 1] = newLocados;
    *qtdLocados = *qtdLocados + 1;
    return 1;
}

void listLocacao(locados **dtbaselocados, int qtdLocados, operacoe **dtbaseOperacoe, int qtdOperacoes){
    data emprestimo,devolucao;
    for (int c = 0; c < qtdLocados; c++) {
        for (int a = 0; a < qtdLocados; a++) {
            if ((*dtbaselocados)[c].KEY_operator == (*dtbaseOperacoe)[c].KEY_operator){
                emprestimo = (*dtbaseOperacoe)[c].dtemprestimo;
                devolucao = (*dtbaseOperacoe)[c].dtdevolucao;
                break;
            }
        }
        printf("\n-----------------------------------------------------------------\n");
        printf("(%d)\nCodigo Cliente: %d\n"
               "Data: %d/%d/%d\n"
               "Nome Cliente: %s\n"
               "Quantidade de Filmes: %d\n"
               "Valor Total: R$ %.2f\n",(*dtbaselocados)[c].ID,(*dtbaselocados)[c].CodCliente,emprestimo.dia,emprestimo.mes,emprestimo.ano,(*dtbaselocados)[c].Nome,(*dtbaselocados)[c].qtdFilme,(*dtbaselocados)[c].valorPago);
    }
    printf("\n");
}

void listOperacoes(operacoe **dtbaseOperacoe, int qtd, int KEY_operator) {
    for (int c = 0; c < qtd; c++) {
        if ((*dtbaseOperacoe)[c].KEY_operator == KEY_operator) {
            printf("\n-----------------------------------------------------------------\n");
            printf("(%d)\n"
                   "Codigo Filme: %d\n"
                   "Nome Filme: %s\n"
                   "Valor Total: R$ %.2f\n", (*dtbaseOperacoe)[c].KEY_operator, (*dtbaseOperacoe)[c].CodFilme,
                   (*dtbaseOperacoe)[c].nomeFilme, (*dtbaseOperacoe)[c].valorPago);
        }
    }
    printf("\n");
}


int menuLocacao(filme **dtbaseFilme,int qtdFilme,
                cliente **dtbaseCliente,int qtdcliente,
                funcionarios **dtbaseFuncionarios, int qtdFuncionarios,
                locados **dtbaseLocados, int *qtdLocados, int *tamanhoLocados, int *idLocados,
                operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                fCategoria **dtbaseCategoria, int qtdCategoria, int *KEY_Controle){
    int op = 0;
    line(100,"Locacao\0");
    printf("\t 1- Emprestar \n\t 2- Devolver \n\t 3- Vizualizar Operaçoes \n\t 0- Sair");
    line(100,"1\0");

    do {
        printf(">>OPC: ");
        scanf("%d", &op);
    } while (op < 0 || op > 3);


    if (op == 0){
        return 1;
    }
    else if (op == 1){
        locados newLocados = objetoLocados(idLocados,dtbaseCliente,qtdcliente,dtbaseFilme,qtdFilme,dtbaseOperacoe,qtdOperacoe,tamanhoOperacoe,dtbaseCategoria,qtdCategoria,KEY_Controle);
        inserirLocados(dtbaseLocados,newLocados,qtdLocados,tamanhoLocados);
    }else if (op == 3){
        listLocacao(dtbaseLocados,*qtdLocados,dtbaseOperacoe,*qtdOperacoe);
        systemPause();
    }
    return 0;
}