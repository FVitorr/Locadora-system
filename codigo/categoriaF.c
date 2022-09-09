#include "../cabecalhos/categoriaF.h"
#include "../cabecalhos/fucGlobal.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

fCategoria objCategoria (int id,int tab){
    fCategoria obj;

    char msg[2][35];

    strcpy(msg[0],"Descricao Categoria: \0");
    strcpy(msg[1],"Valor Locacao: \0");

     if (tab == 1){
         addTab(msg[0]);
         addTab(msg[1]);
     }

    obj.codigo = id;
    printf("%s ",msg[0]);

    fflush(stdin);
    scanf("%[^\n]s",obj.descricao);

    printf("%s ",msg[1]);
    scanf("%f%*c", &obj.vAlocacao);

    obj.ativo = 1;
    return obj;
}


int insCategoria(fCategoria **dtbase,fCategoria newEntry,int *qtdCategoria,int *tamanhoCategoria, int id)
{
    //printf("%d",*tamanhoCategoria);
    //Se a quantidade de categorias for igual ao tamanho alocado da lista -> espandir
    if (*qtdCategoria == *tamanhoCategoria)
    {
        *tamanhoCategoria = *tamanhoCategoria + 1;
        *dtbase = (fCategoria *) realloc(*dtbase, *tamanhoCategoria * sizeof(fCategoria));
    }
    if (*dtbase == NULL)
        {
            printf("\n  Erro na alocação de memória!");
            system("pause");
            return 1;
        } 
    // adc obj ao bd local
    (*dtbase)[id] = newEntry;
    *qtdCategoria = *qtdCategoria + 1;
    return 1;
    
}
int remCategoria(fCategoria **dtbase, int id, int *qtdCategoria){
    for (int i = 0; i < *qtdCategoria; i++){
//        printf("\nCod: %d",id);
//        printf("\tCod: %d",(*dtbase)[i].codigo);
        if ((*dtbase)[i].codigo == id){
            (*dtbase)[i].ativo = 0;
        }
    }
    return 0;
}


//0  int codigo;   1  char descricao[30];    2  float vAlocacao;    3  int ativo;
void listCategorias(fCategoria **dtbase, int qtd){
    printf("\n ID \tDescrição Categoria \t Valor Locação\t Ativo \n");
    for (int c = 0; c < qtd; c++) {
        if ((*dtbase)[c].ativo == 1){
        printf("-----------------------------------------------------------------\n");
        printf("(%d)\t%15s\t\t%f\t\t%d\n",(*dtbase)[c].codigo,(*dtbase)[c].descricao,(*dtbase)[c].vAlocacao,(*dtbase)[c].ativo);
        }
    }
    printf("\n");
}
int editaCategoria(fCategoria **dtbase,int *qtdCategoria,int *tamanhoCategoria,int id){
    for (int i = 0; i < *qtdCategoria ; i++){
        if ((*dtbase)[i].codigo == id){
            fCategoria new = objCategoria((*dtbase)[i].codigo,0);
            insCategoria(dtbase,new,qtdCategoria,tamanhoCategoria,id);
            *qtdCategoria = *qtdCategoria - 1;
            return 0;
        }
    }
    return 1;
}
int locID(fCategoria **dtbase,int *qtdCategoria, int ID) {
    int erro = 0;
    for (int i = 0; i < *qtdCategoria; i++)
    {
        if ((*dtbase[i]).codigo == ID) {
            erro = 1;
            break;
        }
    }
    return erro;
}

int *obterID(fCategoria **dtbase,int *qtdCategoria){
    int *ids;
    ids = malloc((*qtdCategoria) * sizeof (int));
    for (int i = 0; i < *qtdCategoria; i++){
        ids[i] = (*dtbase)[0].codigo;
    }
    return  ids;
}


int menuCategoria(fCategoria **dtbase, int *qtdCategoria,int *tamanhoCategoria) {
    int opc = 0, erro = 0, exit = 0;
    system("cls");

    line(30,"Categorias \0");
    printf("\t 0 - Sair \n\t 1 - Cadastrar \n\t 2 - Cadastrar Multiplas \n");
    printf("\t 3 - Visualizar \n\t 4 - Editar \n\t 5 - Remover\n");
    line(30,"-\0");

    do
    {
        if (erro == 1) {
            printf(">> Parametro Invalido\n");
        }
        printf("Opc: ");
        scanf("%d", &opc);
        erro = 1;
    } while (opc < 0 || opc > 5);

    if (opc == 0) {
        printf(">> Exit\n");
        exit = 1;
    }
    else if (opc == 1) {
        //Cadastrar uma categoria
        printf(">> Nova Categoria     ID: %d \n\n", *qtdCategoria);
        fCategoria newObjeto = objCategoria(*qtdCategoria,0);
        insCategoria(dtbase,newObjeto,qtdCategoria,tamanhoCategoria,*qtdCategoria);
    }
    else if (opc == 2) {
        //Cadastrar multiplas categoria
        system("cls");
        printf(">> Cadastro Multiplo Categoria     ID: %d \n\n", *qtdCategoria);
        int qtd_ = 1;
        while (1)
        {
            fCategoria new = objCategoria(*qtdCategoria,0);
            insCategoria(dtbase,new,qtdCategoria,tamanhoCategoria,*qtdCategoria);
            printf("[1 - Mais] \t [0 - Exit]: ");
            scanf("%d", &qtd_);
            if (qtd_ == 0) {
                break;
            }
        }

    }
    else if (opc == 3) {
        //Visualizar
        printf(">> Categorias Cadastradas  \t Total: %d\n\n", *qtdCategoria);
        listCategorias(dtbase,*qtdCategoria);
        system("pause");
    }
    else if (opc == 4) {
        // editar
        int cod;

        printf(">> Categorias Cadastradas  \t Total: %d\n\n", *qtdCategoria);
        listCategorias(dtbase,*qtdCategoria);

        printf(">>Editar:");
        scanf("%d", &cod);

        int t = editaCategoria(dtbase,qtdCategoria,tamanhoCategoria,cod);
        if (t == 1){
            printf("\n\t>> ID não encontrado");
            abortOp();
        }else{
            sucess();
        }
    }
    else if (opc == 5) {
        // Remover
        int cod;
        printf("Remover:");
        scanf("%d", &cod);
        remCategoria(dtbase, cod, qtdCategoria);
    }
    return exit;
}

//
//
//fCategoria *bd_cat;
//int qtdCategoria = 0,tamanhoCategoria = 1;
//
//int main() {
//
//    bd_cat = malloc(tamanhoCategoria * sizeof(fCategoria));
//    fCategoria new = objCategoria(qtdCategoria,0);
//    insCategoria(&bd_cat,new,&qtdCategoria,&tamanhoCategoria);
//    // printf("QTD: %d\n",qtdCategoria);
//    // printf("Cod: %d\n",bd_cat[0].codigo);
//    // printf("Des: %s\n",bd_cat[0].descricao);
//    // printf("FLAg: %d\n",bd_cat[0].ativo);
//    listCategorias(&bd_cat,qtdCategoria);
//    fCategoria new1 = objCategoria(qtdCategoria,0);
//    insCategoria(&bd_cat,new1,&qtdCategoria,&tamanhoCategoria);
//    listCategorias(&bd_cat,qtdCategoria);
//    // printf("QTD: %d\n",qtdCategoria);
//    // printf("Cod: %d\n",bd_cat[1].codigo);
//    // printf("Des: %s\n",bd_cat[1].descricao);
//    // printf("Ativo: %d\n",bd_cat[1].ativo);
//
//    int id = 0;
//    printf("\nRemove:\n");
//    //scanf("%d",&id);
//    remCategoria(&bd_cat, id, &qtdCategoria);
//    printf("Ativo: %d\n",bd_cat[0].ativo);
//
//    listCategorias(&bd_cat,qtdCategoria);
//    editaCategoria(&bd_cat,&qtdCategoria,&tamanhoCategoria,0);
//    listCategorias(&bd_cat,qtdCategoria);
//    free(bd_cat);
//    return 0;
//}