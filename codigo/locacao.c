#include "locacao.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <io.h>

/*Ids 0 não serão aceitos*/

operacoe objetoOperacoe(filme **dtbaseFilme, int qtdFilme,fCategoria **dtbaseCategoria,int qtdCategoria,
                        int KEY_operator, int *idOperacao){
    int idtpm;
    operacoe newOpc;

    newOpc.ID = *idOperacao;
    *idOperacao = *idOperacao + 1;

    newOpc.KEY_operator = KEY_operator;



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
                return newOpc;
            }
            newOpc.CodFilme = idtpm;
            //Incrementar o valor do campo emprestados
            altQtdEmprestadaFilme(dtbaseFilme,qtdFilme,idtpm);

            refazDados_filme(dtbaseFilme,qtdFilme, 1);

            //Nome Filme
            newOpc.nomeFilme = nomeFilme(dtbaseFilme,qtdFilme,idtpm);

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


locados objetoLocados (int *idControleLocados,int idCliente,filme **dtbaseFilme,int qtdFilme,
                       operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                       fCategoria **dtbaseCategoria, int qtdCategoria, int *KEY_operacao,int Key_Cliente,
                       int tipoConfig){

    locados newObjeto;

    newObjeto.ID = *idControleLocados; // valor guardado na struct cliente
    *idControleLocados = *idControleLocados + 1; //Incrementar ID

    newObjeto.KEY_operator = *KEY_operacao; // Valor unico para cada cliente mas as operacoes apresenta o mesmo valor

    newObjeto.key_cliente = Key_Cliente;

    newObjeto.qtdFilme = 0;
    newObjeto.ultimoIDOperacao = 0;

    while (1){
        operacoe  op = objetoOperacoe(dtbaseFilme,qtdFilme,dtbaseCategoria,qtdCategoria,*KEY_operacao,&newObjeto.ultimoIDOperacao);

        if (op.valorFilme == 0){
            //Abortar Operação
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

    if (newObjeto.tipoPagamento == 1){//Pagamento a vista
        newObjeto.qtdParcelas = 1;
        newObjeto.valordeve = 0; // Cliente pagou tudo
//        //Adicionar valor ao caixa
//        monetario->caixa = monetario->caixa + newObjeto.valorPago;
//        //Adicionar valor pago a conta cliente fora da função

    }else{
        newObjeto.valorEntrada = 0;
        int ent = 0,qtdParcelas;
        float valorE,valorR;
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
                scanf("%d",&qtdParcelas);
                if (qtdParcelas > 3 || qtdParcelas < 0){ break;}
                else{ printf("\n[!] Quantidade de Parcelas invalido\n");}
            } while (1);


            printf("\nA conta foi dividida em %d parcelas \n O Valor de cada parcela e: R$ %.2f",qtdParcelas,newObjeto.valordeve/qtdParcelas);
            newObjeto.qtdParcelas = qtdParcelas;

        }else{
            //Caso não seja fornecido uma  entrada
            do{
                printf("\n>> Deseja dividir o valor R$ %2.f de quantas Vezes [3x Parcelas Maximas] ? ",newObjeto.valorTotal);
                scanf("%d",&qtdParcelas);
                if (qtdParcelas > 3 || qtdParcelas < 0){ break;}
                else{ printf("\n[!] Quantidade de Parcelas invalido\n");}
            } while (1);

            printf("\nA conta foi dividida em %d parcelas \n O Valor de cada parcela e: R$ %.2f",qtdParcelas,newObjeto.valordeve/qtdParcelas);
            newObjeto.qtdParcelas = qtdParcelas;
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

void emprestaFilme(contaCliente **dtBaseCCliente,int *qtd_CCliente,int *IdContaCliente
                   ,int *key_cliente,cliente **dtbaseCliente,int qtdcliente,
                   filme **dtbaseFilme,int qtdFilme,operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                   locados **dtbaseLocados, int *qtdLocados, int *tamanhoLocados,
                   fCategoria **dtbaseCategoria, int qtdCategoria, int *KEY_Operacao,financeiro *monetario,int tipoConfig){
    //Cliente
    int idCliente;
    do {
        printf("Informe ID do Cliente: ");
        scanf("%d", &idCliente);

        int confirm;
        if (verificaIdCliente(dtbaseCliente, qtdcliente, idCliente) == 1) { //Verifica se o cliente existe

            printf("\nNome do Cliente: %s \nCorreto [1 - SIM   0 - Nao]: ", nomeCliente(dtbaseCliente,qtdcliente,idCliente));
            scanf("%d",&confirm);

            if (confirm != 0) {
                //Verificar se conta cliente existe
                if (verificaConta(dtBaseCCliente, qtdcliente, idCliente) == 1) {
                    //Conta Cliente existe
                } else {
                    //conta Cliente nao existe
                    contaCliente novoCliente = objetoCCliente(IdContaCliente, *key_cliente, dtbaseCliente, qtdcliente,idCliente);
                    //Salvar conta cliente;
                    //Criar objeto Locado
                    locados novaLocacao = objetoLocados(&novoCliente.IDlocado,idCliente,dtbaseFilme,qtdFilme,
                                                        dtbaseOperacoe,qtdOperacoe,tamanhoOperacoe,dtbaseCategoria,qtdCategoria,KEY_Operacao,*key_cliente,tipoConfig);

                    //controle de caixa
                    if (novaLocacao.tipoPagamento == 1){ //Pagamento a Vista
                        novoCliente.valorPago = novoCliente.valorPago + novaLocacao.valorTotal; //Adicionar valor ao caixa da locadora
                        monetario->caixa = monetario->caixa + novaLocacao.valorTotal; //Adicionar valor pago a conta cliente
                    }else{ // pagamento a prazo
                        novoCliente.valorPago = novoCliente.valorPago + novaLocacao.valorEntrada;
                        monetario->caixa = monetario->caixa + novaLocacao.valorEntrada; //Adicionar valor pago a conta cliente

                        novoCliente.valorDeve = novoCliente.valorDeve + novaLocacao.valordeve;
                    }

                    //alterar chave cliente
                    *key_cliente = *key_cliente + 1;

                    inserirLocados(dtbaseLocados,novaLocacao,qtdLocados,tamanhoLocados);
                    //Salvar Cliente
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
    contaCliente novoCliente;

    novoCliente.ID = *IdContaCliente;
    *IdContaCliente = *IdContaCliente  + 1;

    novoCliente.key_cliente = key_cliente;

    novoCliente.Nome = nomeCliente(dtbaseCliente,qtdcliente,idCliente);

    novoCliente.valorDeve = 0;
    novoCliente.valorPago = 0;

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


void listLocacao(locados **dtbaselocados, int qtdLocados, operacoe **dtbaseOperacoe){
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
               "Registro da Operacao: %d\n"
               "Data: %d/%d/%d\n"
               "Quantidade de Filmes: %d\n"
               "Data Devolucao: %d/%d/%d\n"
               "Valor Total: R$ %.2f\n",(*dtbaselocados)[c].ID,(*dtbaselocados)[c].key_cliente,(*dtbaselocados)[c].KEY_operator,emprestimo.dia,emprestimo.mes,emprestimo.ano,(*dtbaselocados)[c].qtdFilme,devolucao.dia,devolucao.mes,devolucao.ano,(*dtbaselocados)[c].valorTotal);
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
                contaCliente **dtbaseCCliente,int *qtdCCliente,int *tamanhoCCliente,int *idCCliente,
                fCategoria **dtbaseCategoria, int qtdCategoria,int *KEY_Operacao, int *KEY_Cliente,financeiro *monetario,int tipo_config){

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
    printf("\t 1- Emprestar \n\t 2- Devolver \n\t 3- Vizualizar Operaçoes \n\t 0- Sair");
    line(100,"1\0");

    do {
        printf(">>OPC: ");
        scanf("%d", &op);
    } while (op < 0 || op > 3);


    if (op == 0){
        return 1;
    }else if (op == 1){
        emprestaFilme(dtbaseCCliente,qtdCCliente,idCCliente,KEY_Cliente,dtbaseCliente,qtdcliente,dtbaseFilme,qtdFilme,
                      dtbaseOperacoe,qtdOperacoe,tamanhoOperacoe,dtbaseLocados,qtdLocados,tamanhoLocados,dtbaseCategoria,qtdCategoria,KEY_Operacao,monetario,tipo_config);

//        if ((int)newLocados.valorPago != 0){
//            inserirLocados(dtbaseLocados,newLocados,qtdLocados,tamanhoLocados);
//            saveLocacao(newLocados,tipo_config);
//        }else{
//            printf("%f",newLocados.valorPago);
//            return 1;
//        }
    }else if (op == 2){
        //Devolução;
        devolucaoFilmes(dtbaseLocados,*qtdLocados,dtbaseOperacoe,*qtdOperacoe);
    }else{
        listLocacao(dtbaseLocados,*qtdLocados,dtbaseOperacoe);
        system("pause");
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

        fprintf(locadosF, "%d\n%d\n%d\n%d\n%f\n%f\n%f\n%d\n%d\n%d\n%d",
                objeto.ID,
                objeto.KEY_operator,
                objeto.key_cliente,
                objeto.qtdFilme,
                objeto.valorTotal,
                objeto.valordeve,
                objeto.valorEntrada,
                objeto.tipoPagamento,
                objeto.qtdParcelas,
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

            fscanf(fileLocados, "%d\n", &new.qtdParcelas);

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

int verificaIDConta(locados **dtbaselocados, int qtdLocados, int id){ // 1 existe 0 nao existe
    for (int i = 0; i < qtdLocados; i++){
        if ((*dtbaselocados)[i].ID == id){
            return 1;
        }
    }return 0;
}

int retornaChave(locados **dtbaselocados, int qtdLocados, int id){ // Retorna a chave da operaçao
    for (int i = 0; i < qtdLocados; i++){
        if ((*dtbaselocados)[i].ID == id){
            return (*dtbaselocados)[i].KEY_operator;
        }
    }return 0;
}

void devolucaoFilmes(locados **dtbaselocados, int qtdLocados, operacoe **dtbaseOperacoes, int qtdOperacao){
    system("cls");
    line(100,"Devolucao Filmes\0");
    printf("\nContas Disponiveis:\n");
    for (int i = 0; i < qtdLocados; i++){
        printf(" (ID: %d) Cliente: %s   ",(*dtbaselocados)[i].ID,(*dtbaselocados)[i].Nome);
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
    } while (verificaIDConta(dtbaselocados,qtdLocados,IdCliente) == 0);

    int key_operator = retornaChave(dtbaselocados,qtdLocados,IdCliente);

    printf("\nVerifique os Filmes Alugados: ");
    listOperacoes(dtbaseOperacoes,qtdOperacao,key_operator);

    printf("\nO cliente vai realizar a entrega completa ?  [1- Sim \t 0 - Nao]: ");
    scanf("%d",&entregaCompleta);

    if (entregaCompleta == 1){
        //Devolveu tudo
    }else{
        printf("Informe o ID do filme que sera Devolvido: ");
    }
}
