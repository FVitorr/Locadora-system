#include "locacao.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <io.h>
#include "../cabecalhos/datas.h"

/*Ids 0 não serão aceitos*/

operacoe objetoOperacoe(filme **dtbaseFilme, int qtdFilme,fCategoria **dtbaseCategoria,int qtdCategoria,
                        int KEY_operator){
    int idtpm;

    operacoe newOpc;
    newOpc.KEY_operator = KEY_operator;
    line(100,"Filme\0");
    printf("[Operacao: %d]\n",KEY_operator);

    do {
        printf("[0 - IDs Cadastrados ]Informe ID do Filme: ");
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

    newOpc.dtemprestimo = dataAtual();
    printf("\n>> Data do emprestimo: %d/%d/%d\n",newOpc.dtemprestimo.dia,newOpc.dtemprestimo.mes,newOpc.dtemprestimo.ano);

    newOpc.dtdevolucao.dia = 0;
    newOpc.dtdevolucao.mes = 0;
    newOpc.dtdevolucao.ano = 0;

    newOpc.devolvido = 0; // 0 - Não
    return  newOpc;
}


locados objetoLocados (int *id,cliente **dtbaseCliente,int qtdcliente,filme **dtbaseFilme,int qtdFilme,
                       operacoe **dtbaseOperacoe, int *qtdOperacoe, int *tamanhoOperacoe,
                       fCategoria **dtbaseCategoria, int qtdCategoria, int *KEY_Controle, int tipoConfig){
    
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
            printf("\nNome do Cliente: %s \nCorreto [1 - SIM   0 - Nao]: ", newObjeto.Nome);
            scanf("%d",&confirm);
            break;
        } else {
            printf("\nID invalido");
            //Permitir que clientes sejam listados
        }
    } while(1);

    newObjeto.qtdFilme = 0;

    while (1){
        operacoe  op = objetoOperacoe(dtbaseFilme,qtdFilme,dtbaseCategoria,qtdCategoria,*KEY_Controle);

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
        newObjeto.qtdParcelas = 1;
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
            scanf("%d",&qtdParcelas);
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

void listLocacao(locados **dtbaselocados, int qtdLocados, operacoe **dtbaseOperacoe){
    data emprestimo, devolucao;
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
               "Nome Cliente: %s\n"
               "Quantidade de Filmes: %d\n"
               "Data Devolucao: %d/%d/%d\n"
               "Valor Total: R$ %.2f\n",(*dtbaselocados)[c].ID,(*dtbaselocados)[c].CodCliente,(*dtbaselocados)[c].KEY_operator,emprestimo.dia,emprestimo.mes,emprestimo.ano,(*dtbaselocados)[c].Nome,(*dtbaselocados)[c].qtdFilme,devolucao.dia,devolucao.mes,devolucao.ano,(*dtbaselocados)[c].valorPago);
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
                fCategoria **dtbaseCategoria, int qtdCategoria, int *KEY_Controle, int tipo_config){
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
        locados newLocados = objetoLocados(idLocados,dtbaseCliente,qtdcliente,dtbaseFilme,qtdFilme,dtbaseOperacoe,qtdOperacoe,tamanhoOperacoe,dtbaseCategoria,qtdCategoria,KEY_Controle,tipo_config);
        inserirLocados(dtbaseLocados,newLocados,qtdLocados,tamanhoLocados);
        saveLocacao(newLocados,tipo_config);
    }else if (op == 3){
        listLocacao(dtbaseLocados,*qtdLocados,dtbaseOperacoe);
        systemPause();
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

        fprintf(operacaoF, "%d\n%d\n%s\n%f\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
                objeto.KEY_operator,
                objeto.CodFilme,
                objeto.nomeFilme,
                objeto.valorPago,
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
            system("Pause");
            return 1;
        }

        while (!feof(fOperacoe)){
            if (!filelength(fileno(fOperacoe))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fscanf(fOperacoe, "%d\n", &new.KEY_operator);

            fscanf(fOperacoe, "%d\n", &new.CodFilme);

            char nameTemp[120];
            fgets(nameTemp, 120, fOperacoe);
            limpa_final_string(nameTemp);

            new.nomeFilme = string_to_pointer(nameTemp);

            fscanf(fOperacoe, "%f\n", &new.valorPago);

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

        fprintf(locadosF, "%d\n%d\n%d\n%s\n%d\n%f\n%d\n%d\n%d\n",
                objeto.ID,
                objeto.KEY_operator,
                objeto.CodCliente,
                objeto.Nome,
                objeto.qtdFilme,
                objeto.valorPago,
                objeto.tipoPagamento,
                objeto.qtdParcelas,
                objeto.TDdevolvido);

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
    printf("QTD: %d",*qtdTemp);
    system("Pause");
    int t = 0;
    if (tipo_config == 1){ //Arquivo TXT
        fileLocados = fopen("cpyBdLocados.txt", "r");

        if (fileLocados == NULL){
            printf("\nErro na Leitura 'cpyBdLocados.txt' \n");
            system("Pause");
            return 1;
        }

        while (!feof(fileLocados)){
            if (!filelength(fileno(fileLocados))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fscanf(fileLocados, "%d\n", &new.ID);

            fscanf(fileLocados, "%d\n", &new.KEY_operator);

            fscanf(fileLocados, "%d\n", &new.CodCliente);

            fgets(new.Nome, 120, fileLocados);
            limpa_final_string(new.Nome);

            fscanf(fileLocados, "%d\n", &new.qtdFilme);

            fscanf(fileLocados, "%f\n", &new.valorPago);

            fscanf(fileLocados, "%d\n", &new.tipoPagamento);

            fscanf(fileLocados, "%d\n", &new.qtdParcelas);

            fscanf(fileLocados, "%d\n", &new.TDdevolvido);

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