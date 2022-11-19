#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include "../cabecalhos/filmes.h"

// +++++++++++++++++++++++++++++++++++++++++ Subrotinas para controle dos filmes +++++++++++++++++

filme objFilme(fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoCategoria, int *id,
               int *idControleCategoria) // Bloco para receber as entradas e "compartar" na struct
{
    filme p;
    p.codigo = *id;

    *id = *id + 1;

    setbuf(stdin,NULL);

    printf("Nome: ");
    scanf("%[^\n]s", p.nome);

    setbuf(stdin,NULL);

//    printf("Descricao: ");
//    scanf("%[^\n]s", p.descricao);

    setbuf(stdin,NULL);

    printf("Quantidade de Exemplares: ");
    scanf("%d%*c", &p.qtd);

    //https://homepages.dcc.ufmg.br/~rodolfo/aedsi-2-10/printf_scanf/printfscanf.html

    line(100,"Categorias\0");
    printf(" (0)Nova Categoria");
    for (int i = 0; i < *qtdCategoria; i++){
        printf("   (%d)%s ",(*dtbaseCategoria)[i].codigo,(*dtbaseCategoria)[i].descricao);
    }
    line(100,"-\0");

    printf("Codigo Categoria: ");
    scanf("%d%*c", &p.c_categoria); //Possivelmente este campo precisa ser comparado ...

    p.c_categoria = categTry(dtbaseCategoria,qtdCategoria,tamanhoCategoria ,p.c_categoria,idControleCategoria);

    setbuf(stdin,NULL);

    printf("Lingua: ");
    scanf("%[^\n]s", p.lingua);

    p.qtdEmprestado = 0;

    return p;
}


int inserirFilme(filme **dtbase,filme newEntry,int *qtdFilmes,int *tamanhoFilmes){
    //Se a quantidade de categorias for igual ao tamanho alocado da lista -> espandir
    if (*qtdFilmes == *tamanhoFilmes)
    {
        *tamanhoFilmes = *tamanhoFilmes + 1;
        *dtbase = (filme *) realloc(*dtbase, *tamanhoFilmes * sizeof(filme));
    }
    if (*dtbase == NULL)
    {
        printf("\n  Erro na alocação de memória!");
        system("pause");
        return 0;
    }
    // adc obj ao bd local
    (*dtbase)[*tamanhoFilmes - 1] = newEntry;
    *qtdFilmes = *qtdFilmes + 1;

    return 1;
}
int removerFilme(filme **dtbase, int id, int *qtdFilmes, int *tamanhoFilmes,int tipo_config){
    for (int i = 0; i < *qtdFilmes; i ++){
        if((*dtbase)[i].codigo == id){
            while (i < *qtdFilmes - 1)
            {
                (*dtbase)[i] = (*dtbase)[i + 1];
                i++;
            }
            *qtdFilmes = *qtdFilmes - 1;
            *tamanhoFilmes = *tamanhoFilmes - 1;
            break;
        }
    }
    refazDados_filme(dtbase,*qtdFilmes,tipo_config);
    return 0;
}


void listFilme(filme **dtbase, int qtd){
    if (qtd > 0) {
        printf("\n|%s|%s|%s|%s|%s|\n",
        formatstring(4, strlen("ID\0"),"ID\0"),
        formatstring(30, strlen("Nome\0"),"Nome\0"),
        formatstring(30, strlen("Quantidade Exemplares\0"),"Quantidade Exemplares\0"),
        formatstring(20, strlen("Codigo Categoria\0"),"Codigo Categoria\0"),
        formatstring(15, strlen("Lingua\0"),"Lingua\0"));

        for (int c = 0; c < qtd; c++) {
            char codigo[10];
            char qtdChar[10];
            char codCategoria[10];
            sprintf(codigo,"%d",(*dtbase)[c].codigo);
            sprintf(qtdChar,"%d",(*dtbase)[c].qtd);
            sprintf(codCategoria,"%d",(*dtbase)[c].c_categoria);

            printf("---------------------------------------------------------------------------------------------------------\n");
            printf("|%s|%s|%s|%s|%s|\n", formatstring(4, (int)strlen(codigo),codigo),
                   formatstring(30, (int)strlen((*dtbase)[c].nome),(*dtbase)[c].nome),
                   formatstring(30, (int)strlen(qtdChar),qtdChar),
                   formatstring(20, (int)strlen(codCategoria),codCategoria),
                   formatstring(15, (int)strlen((*dtbase)[c].lingua),(*dtbase)[c].lingua));
//                   (*dtbase)[c].codigo,
//                   (*dtbase)[c].nome,
//                   (*dtbase)[c].qtd,
//                   (*dtbase)[c].c_categoria,
//                   (*dtbase)[c].lingua);
        }
    }
    else{
        printf("\n\t>> Nada para mostrar aqui");
    }
    printf("\n");
}
int qtdEmprestada(filme **dtbase,int qtdFilmes, int id){
    for (int i = 0; i < qtdFilmes; i++) {
        if ((*dtbase)[i].codigo == id) {
            return (*dtbase)[i].qtdEmprestado;
        }\
    }
    return 0;
}


void editaFilme(filme **dtbase,int qtdFilmes,fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoCategoria,int id,int *idControleCategoria, int tipo_config)
{
    int qtd_emprestada = qtdEmprestada(dtbase,qtdFilmes,id);
    for (int i = 0; i < qtdFilmes; i++) {
        if ((*dtbase)[i].codigo == id) {
            filme newEntrada = objFilme(dtbaseCategoria,qtdCategoria,tamanhoCategoria,&id,idControleCategoria);
            newEntrada.qtdEmprestado = qtd_emprestada;
            (*dtbase)[i] = newEntrada;
            break;
        }
    }
    refazDados_filme(dtbase,qtdFilmes, tipo_config);
}

int categTry(fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoCategoria ,int id,int *idControleCategoria) {
    int opc = 0;
    int tem = locID(dtbaseCategoria,*qtdCategoria,id);
    if (tem == 1){
        return id;
    }
    //int tem = 0;cc
    if (id == 0 || tem == 0) {
        printf("\n\t>> Categoria nao encontrada\n ");
        printf("\t>> Cadastrar [1 - Sim] [ 0 - Nao]: ");
        scanf("%d", &opc);
        if (opc == 0) {
            return 1;
        }
        else {
            printf("\n");
            fCategoria new = objCategoria(idControleCategoria,1);
            int suc = insCategoria(dtbaseCategoria,new,qtdCategoria,tamanhoCategoria);
            if (suc == 1) {
                printf("\n\t>> Nova categoria adicionada");
            }
            printf("\n");
        }
    }
    return *idControleCategoria - 1;
}

int menuFilme(filme **dtbase,int *qtdFilmes,int *tamanhoFilmes, fCategoria **dtbaseCategoria, int *qtdCategoria, int *tamanhoCategoria,int *idControleCategoria,int *id,int tipo_config){
    int opc, erro = 0, exit = 0;
    int correto;
    char temEscolha[4];

    system("cls");
    setbuf(stdin,NULL);

    lineBox(70,"MENU FILME\0",1);
    printf("\tDigite a opcao referente a operacao que deseja executar\n\n");
    printf("\t0 - Sair \n\t1 - Cadastrar \n\t2 - Cadastrar Multiplos \n\t3 - Visualizar \n\t4 - Editar \n\t5 - Remover\n");
    lineBox(70,"-\0",0);


    do
    {
        if (erro == 1)
        {
            printf(">> Parametro Invalido\n");
        }
        printf(">>");
        scanf("%s", temEscolha); //Permite a entrada de qualquer caracter
        setbuf(stdin,NULL);

        opc = strtol(temEscolha,NULL,10); //Procura na entrada um numero na base 10

        erro = 1;
    } while (opc < 0 || opc > 5);

    if (opc == 0)
    {
        system("cls");
        return 1;
    }
    else if (opc == 1)
    {
        // Cadastrar um Filme
        printf(">> Novo filme     \tID: %d \n", *id);

        int correto;

        printf("\n\tCadastrar Filme: [1- Sim  0- Nao]\n\t>> ");
        scanf("%s", temEscolha);//Permite a entrada de qualquer caracter
        setbuf(stdin,NULL);
        correto = strtol(temEscolha,NULL,10);//Procura na entrada um numero na base 10

        if (correto == 0)return 0;

        filme new = objFilme(dtbaseCategoria,qtdCategoria,tamanhoCategoria,id,idControleCategoria);
        inserirFilme(dtbase,new,qtdFilmes,tamanhoFilmes);
        saveFilme(new, tipo_config);
    }
    else if (opc == 2)
    {
        // Cadastrar multiplas categoria
        int op;
        printf(">> Multiplos filme     \tID: %d \n", *id);



        printf("\n\tCadastrar Filme: [1- Sim  0- Nao]\n\t>> ");
        scanf("%s", temEscolha);//Permite a entrada de qualquer caracter
        setbuf(stdin,NULL);
        correto = strtol(temEscolha,NULL,10);//Procura na entrada um numero na base 10

        if (correto == 0)return 0;

        while (1)
        {
            filme new = objFilme(dtbaseCategoria,qtdCategoria,tamanhoCategoria,id,idControleCategoria);
            inserirFilme(dtbase,new,qtdFilmes,tamanhoFilmes);
            saveFilme(new,tipo_config);

            printf("\n >> [1 - Mais] \t [0 - Exit]: ");
            scanf("%s", temEscolha);//Permite a entrada de qualquer caracter
            setbuf(stdin,NULL);

            op = strtol(temEscolha,NULL,10);//Procura na entrada um numero na base 10
            if (op == 0)
            {
                break;
            }

        }
    }
    else if (opc == 3)
    {
        // Visualizar
        printf(">> Filmes Cadastrados  \t Total: %d\n\n", *qtdFilmes);
        listFilme(dtbase, *qtdFilmes);
        system("pause");
    }
    else if (opc == 4)
    {
        // editar
        printf(">> Filmes Cadastrados  \t Total: %d\n\n", *qtdFilmes);
        listFilme(dtbase, *qtdFilmes);
        int cod;
        printf("\n\tDigite o ID do Filme que deseja editar (0- Sair).\n\t>>");

        scanf("%s", temEscolha);//Permite a entrada de qualquer caracter
        setbuf(stdin,NULL);
        cod = strtol(temEscolha,NULL,10);//Procura na entrada um numero na base 10

        if (id == 0){ return 0;}

        editaFilme(dtbase,*qtdFilmes,dtbaseCategoria,qtdCategoria,tamanhoCategoria,cod,idControleCategoria,tipo_config);
    }
    else if (opc == 5)
    {
        // Remover
        listFilme(dtbase, *qtdFilmes);
        int cod;
        printf("\n\tDigite o ID do Filme que deseja remover (0- Sair).\n\t>>");

        scanf("%s", temEscolha);//Permite a entrada de qualquer caracter
        setbuf(stdin,NULL);
        cod = strtol(temEscolha,NULL,10);//Procura na entrada um numero na base 10

        if (cod == 0){ return 0;}
        removerFilme(dtbase,cod,qtdFilmes,tamanhoFilmes,tipo_config);
    }
    return exit;
}


int saveFilme(filme objeto, int tipo_config){
    FILE *filmeF = NULL;

    if (tipo_config == 1){//Arquivo TXT
        if (verifica_arquivos(tipo_config,"cpyBdFilme.txt\0") == 1){
            filmeF = fopen("cpyBdFilme.txt", "a");
        } else{
            filmeF = fopen("cpyBdFilme.txt", "w");
        }

        if (filmeF == NULL){ // Se a abertura falhar
            return 1;
        }

        fprintf(filmeF, "%d\n%s\n%d\n%d\n%s\n%d\n",
                objeto.codigo,
                objeto.nome,
                objeto.qtd,
                objeto.c_categoria,
                objeto.lingua,
                objeto.qtdEmprestado);

    }else if (tipo_config == 0){ //Arquivo BINARIO
        if (verifica_arquivos(tipo_config,"cpyBdFilme.bin\0") == 1){
            filmeF = fopen("cpyBdFilme.bin", "ab");
        } else{
            filmeF = fopen("cpyBdFilme.bin", "wb");
        }
        if (filmeF == NULL){ // Se a abertura falhar
            return 1;
        }
        fwrite(&objeto, sizeof(filme), 1,filmeF);
    }
    fclose(filmeF);
    filmeF = NULL;
    return 0;
}


int verificaIdFilme(filme **dtbase,int qtd_filme,int id) {
    for (int i = 0; i < qtd_filme; i++) {
        if ((*dtbase)[i].codigo == id) {
            return 1;
        }
    }
    return 0;
}

char *nomeFilme(filme **dtbase,int qtd_filme, int ID){
    for (int i = 0; i < qtd_filme; i++)
    {
        if ((*dtbase)[i].codigo == ID) {
            return (*dtbase)[i].nome;
        }
    }
    return NULL;
}


int categoriaFilme(filme **dtbase,int qtd_filme,int id) {
    for (int i = 0; i < qtd_filme; i++) {
        if ((*dtbase)[i].codigo == id) {
            return (*dtbase)[i].c_categoria;
        }
    }
    return -1;
}

int altQtdEmprestadaFilme(filme **dtbase,int qtd_filme,int id) {
    for (int i = 0; i < qtd_filme; i++) {
        if ((*dtbase)[i].codigo == id) {
            (*dtbase)[i].qtdEmprestado = (*dtbase)[i].qtdEmprestado + 1;
        }
    }
    return 0;
}

int demQtdEmprestadaFilme(filme **dtbase,int qtd_filme,int id){
    for (int i = 0; i < qtd_filme; i++) {
        if ((*dtbase)[i].codigo == id) {
            (*dtbase)[i].qtdEmprestado = (*dtbase)[i].qtdEmprestado - 1;
        }
    }
    return 0;
}



int carregarDados_filme(filme **dtBase, int *qtdFilme, int *tamanhoFilme, int *id,int tipo_config) {
    FILE *p = NULL;
    filme new;
    int t = 0;
    if (tipo_config == 1){ //Arquivo TXT
        p = fopen("cpyBdFilme.txt", "r");

        if (p == NULL){
            printf("\n[503] Erro na Leitura ou Arquivo não encontrado: 'cpyBdFilme.txt' \n");
            return 1;
        }

        while (!feof(p)){
            if (!filelength(fileno(p))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fscanf(p, "%d\n", &new.codigo);
            //fgets(filmeCadastrado[n].descricao, 50, p);
            fgets(new.nome, 120, p);
            limpa_final_string(new.nome);

//            fgets(new.descricao, 120, p);
//            limpa_final_string(new.descricao);

            fscanf(p, "%d\n", &new.qtd);

            fscanf(p, "%d\n", &new.c_categoria);

            fgets(new.lingua, 120, p);
            limpa_final_string(new.lingua);

            fscanf(p, "%d\n", &new.qtdEmprestado);

            if (verificaIdFilme(dtBase,*qtdFilme,new.codigo) == 0){
                t = inserirFilme(dtBase,new,qtdFilme,tamanhoFilme);
                if (*id <= new.codigo) {
                    *id = new.codigo + 1;
                }
            }

            if (t == 0){
                printf("\nAcao Interrompida");
                break;
            }
        }
    }
    else  if (tipo_config == 0){ //Arquivo BIN
        p = fopen("cpyBdFilme.bin", "rb");
        if (p == NULL){
            printf("Arquivo não Encontrado: 'cpyBdFilme.bin'");
            return 1;
        }

        while (!feof(p)){
            if (!filelength(fileno(p))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fread(&new,sizeof(filme),1,p);
            if (verificaIdFilme(dtBase,*qtdFilme,new.codigo) == 0){
                t = inserirFilme(dtBase,new,qtdFilme,tamanhoFilme);
                if (*id <= new.codigo) {
                    *id = new.codigo + 1;
                }
            }

            if (t == 0){
                printf("\nAcao Interrompida");
                break;
            }
        }
    }
    fclose(p);
    return 0;
}


int refazDados_filme(filme **dtbase, int qtdFilme, int tipo_config){

    FILE *p;
    if (tipo_config== 1){
        p = fopen("cpyBdFilme.txt", "w");
        fclose(p);
        p = NULL;
        for (int i = 0; i < qtdFilme; i++){
            saveFilme((*dtbase)[i],1);
        }
    }else if (tipo_config == 0){
        p = fopen("cpyBdFilme.bin", "wb");
        fclose(p);
        for (int i = 0; i < qtdFilme; i++){
            saveFilme((*dtbase)[i],0);
        }
    }
    return 0;
}
