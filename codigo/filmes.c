#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include "../cabecalhos/filmes.h"

// +++++++++++++++++++++++++++++++++++++++++ Subrotinas para controle dos filmes +++++++++++++++++

filme objFilme(fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoCategoria, int *id) // Bloco para receber as entradas e "compartar" na struct
{
    filme p;
    p.codigo = *id;

    *id = *id + 1;

    setbuf(stdin,NULL);

    printf("Nome: ");
    scanf("%[^\n]s", p.nome);

    setbuf(stdin,NULL);

    printf("Descricao: ");
    scanf("%[^\n]s", p.descricao);

    setbuf(stdin,NULL);

    printf("Quantidade de Exemplares: ");
    scanf("%d%*c", &p.qtd);

    //https://homepages.dcc.ufmg.br/~rodolfo/aedsi-2-10/printf_scanf/printfscanf.html

    printf("Codigo Categoria: ");
    scanf("%d%*c", &p.c_categoria); //Possivelmente este campo precisa ser comparado ...

    categTry(dtbaseCategoria,qtdCategoria,tamanhoCategoria , p.c_categoria);

    setbuf(stdin,NULL);

    printf("Lingua: ");
    scanf("%[^\n]s", p.lingua);
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

    saveFilme(newEntry);
    return 1;
}
int removerFilme(filme **dtbase, int *id, int *qtdFilmes, int *tamanhoFilmes){
    for (int i = 0; i < *qtdFilmes; i ++){
        if((*dtbase)[i].codigo == *id){
            while (i < *qtdFilmes - 1)
            {
                (*dtbase)[i] = (*dtbase)[i + 1];
                i++;
            }
            *qtdFilmes = *qtdFilmes - 1;
            break;
        }
    }
    refazDados_filme(dtbase,qtdFilmes,tamanhoFilmes,id ,1);
    return 0;
}


void listFilme(filme **dtbase, int qtd){
    if (qtd > 0) {
        printf("\nID \t Nome \t Descrição \t Quant. Exemplares \t ID categoria \t Lingua\n");
        for (int c = 0; c < qtd; c++) {
            printf("---------------------------------------------------------------------------------\n");
            printf("(%d)\t %s\t %s\t\t\t %d\t\t %d\t\t %s\n", (*dtbase)[c].codigo,
                   (*dtbase)[c].nome,
                   (*dtbase)[c].descricao,
                   (*dtbase)[c].qtd,
                   (*dtbase)[c].c_categoria,
                   (*dtbase)[c].lingua);
        }
    }
    else{
        printf("\n\t>> Nada para mostrar aqui");
    }
    printf("\n");
}

void editaFilme(filme **dtbase,int *qtdFilmes,int *tamanhoFilmes,fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoCategoria,int id)
{
    for (int i = 0; i < *qtdFilmes; i++) {
        if ((*dtbase)[i].codigo == id) {
            filme newEntrada = objFilme(dtbaseCategoria,qtdCategoria,tamanhoCategoria,&id);
            (*dtbase)[i] = newEntrada;
            break;
        }
    }
    refazDados_filme(dtbase,qtdFilmes,tamanhoFilmes,&id ,1);
}

int categTry(fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoCategoria ,int id) {
    int tem = locID(dtbaseCategoria,qtdCategoria,id),opc = 0;
    //int tem = 0;cc
    if (tem == 0) {
        printf("\n\t>> Categoria nao encontrada\n ");
        printf("\t>> Cadastrar [1 - Sim] [ 0 - Nao]: ");
        scanf("%d", &opc);
        if (opc == 0) {
            return 1;
        }
        else {
            printf("\n");
            fCategoria new = objCategoria(id,1);
            int suc = insCategoria(dtbaseCategoria,new,qtdCategoria,tamanhoCategoria,*qtdCategoria);
            if (suc == 1) {
                printf("\n\t>> Nova categoria adicionada");
            }
            printf("\n");
        }
    }
    return 0;
}

void locFilme(filme **dtbase,int *qtdFilmes,int *tamanhoFilmes){

}


int menuFilme(filme **dtbase,int *qtdFilmes,int *tamanhoFilmes, fCategoria **dtbaseCategoria, int *qtdCategoria, int *tamanhoCategoria, int *id){
    int opc = 0, erro = 0, exit = 0;

    //carregarDados_filme(dtbase,qtdFilmes,tamanhoFilmes,id);
    system("cls");
    line(30,"Filmes\0");
    printf("\t 0 - Sair \n\t 1 - Cadastrar \n\t 2 - Cadastrar Multiplas \n");
    printf("\t 3 - Visualizar \n\t 4 - Editar \n\t 5 - Remover");
    line(30,"-\0");

    do
    {
        if (erro == 1)
        {
            printf("MenuFilme:>> Parametro Invalido\n");
        }
        printf(">> Opc: ");
        scanf("%d", &opc);
        erro = 1;
    } while (opc < 0 || opc > 5);

    if (opc == 0)
    {
        printf(">> Exit");
        return 1;
    }
    else if (opc == 1)
    {
        // Cadastrar um Filme
        system("cls");
        printf(">> Novo filme     \tID: %d \n", *id);
        filme new = objFilme(dtbaseCategoria,qtdCategoria,tamanhoCategoria,id);
        inserirFilme(dtbase,new,qtdFilmes,tamanhoFilmes);
        *id = *id + 1;
    }
    else if (opc == 2)
    {
        // Cadastrar multiplas categoria
        system("cls");
        int op = 1;
        printf(">> Multiplos filme     \tID: %d \n", *id);
        while (1)
        {
            filme new = objFilme(dtbaseCategoria,qtdCategoria,tamanhoCategoria,id);
            inserirFilme(dtbase,new,qtdFilmes,tamanhoFilmes);
            printf("\n >> [1 - Mais] \t [0 - Exit]: ");
            scanf("%d", &op);
            *id = *id + 1;
            if (op == 0)
            {
                break;
            }

        }
    }
    else if (opc == 3)
    {
        // Visualizar
        system("cls");
        printf(">> Filmes Cadastrados  \t Total: %d\n\n", *qtdFilmes);
        listFilme(dtbase, *qtdFilmes);
        system("pause");
    }
    else if (opc == 4)
    {
        // editar
        system("cls");
        printf(">> Filmes Cadastrados  \t Total: %d\n\n", *qtdFilmes);
        listFilme(dtbase, *qtdFilmes);
        int cod;
        printf("Editar (ID):");
        scanf("%d", &cod);
        editaFilme(dtbase,qtdFilmes,tamanhoFilmes,dtbaseCategoria,qtdCategoria,tamanhoCategoria,cod);

    }
    else if (opc == 5)
    {
        // Remover
        system("cls");
        listFilme(dtbase, *qtdFilmes);
        int cod;
        printf("Remover (ID):");
        scanf("%d", &cod);
        removerFilme(dtbase,&cod,qtdFilmes,tamanhoFilmes);
    }
    return exit;
}

int saveFilme(filme objeto){
    FILE *filme_;
   
    filme_ = fopen("cpyBdFilme.txt", "a");
   
    if (filme_ == NULL){ // Se a abertura falhar
        return -1;
    }
   
    fprintf(filme_, "%d\n%s\n%s\n%d\n%d\n%s\n",
                objeto.codigo,
                objeto.nome,
                objeto.descricao,
                objeto.qtd,
                objeto.c_categoria,
                objeto.lingua);
    fclose(filme_);
}

int verifica_ID(filme **dtbase,int qtd_filme,int id) {
    for (int i = 0; i < qtd_filme; i++) {
        if ((*dtbase)[i].codigo == id) {
            return 1;
        }
    }
    return 0;
}
int refazDados_filme(filme **dtbase, int *qtdFilme, int *tamanhoFilme, int *id, int tipo_configuracao){

    FILE *p;
    if (tipo_configuracao == 1){
        p = fopen("cpyBdFilme.txt", "w");
        fclose(p);

        p = fopen("cpyBdFilme.txt", "a");
        if (p == NULL){
            printf("Falha ao Escrever no Arquivo.");
            return 1;
        }
        for (int i = 0; i < *tamanhoFilme; i++){
            fprintf(p, "%d\n%s\n%s\n%d\n%d\n%s\n",
                    (*dtbase)[i].codigo,
                    (*dtbase)[i].nome,
                    (*dtbase)[i].descricao,
                    (*dtbase)[i].qtd,
                    (*dtbase)[i].c_categoria,
                    (*dtbase)[i].lingua);
        }
        fclose(p);
        p = NULL;
    }
    return 0;
}


int carregarDados_filme(filme **dtBase, int *qtdFilme, int *tamanhoFilme, int *id) {
    FILE *p;
    p = fopen("cpyBdFilme.txt", "r");

    if (p == NULL){
        printf("\nErro na Leitura 'cpyBdFilme.txt' \n");
        system("Pause");
        return 1;
    }
    filme new;

    int t = 0;


    while (!feof(p)){
        if (!filelength(fileno(p))){  /* teste para saber se o tamanho do arquivo é zero */
            break;
        }
        fscanf(p, "%d\n", &new.codigo);
        //fgets(filmeCadastrado[n].descricao, 50, p);
        fgets(new.nome, 50, p);
        limpa_final_string(new.nome);

        fgets(new.descricao, 120, p);
        limpa_final_string(new.descricao);

        fscanf(p, "%d\n", &new.qtd);

        fscanf(p, "%d\n", &new.c_categoria);

        fgets(new.lingua, 100, p);
        limpa_final_string(new.lingua);

        if (verifica_ID(dtBase,*qtdFilme,new.codigo) == 0){
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