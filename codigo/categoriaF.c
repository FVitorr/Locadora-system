#include "../cabecalhos/categoriaF.h"
#include "../cabecalhos/fucGlobal.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

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
int locID(fCategoria **dtbase,int qtd_Categoria, int ID) {
    for (int i = 0; i < qtd_Categoria; i++)
    {
        if ((*dtbase[i]).codigo == ID) {
            return 1;
            break;
        }
    }
    return 0;
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
    int escolha = INT32_MAX;

    while (escolha != 0) {
        printf("Digite a opcao referente a operacao que deseja executar\n\n");
        printf("0 - Sair \n1 - Cadastrar \n2 - Visualizar \n3 - Editar \n4 - Remover\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: {
                fCategoria newObjeto = objCategoria(*qtdCategoria,0);
                insCategoria(dtbase,newObjeto,qtdCategoria,tamanhoCategoria,*qtdCategoria);
                break;
            }
            case 2: {
                printf(">> Categorias Cadastradas  \t Total: %d\n\n", *qtdCategoria);
                listCategorias(dtbase,*qtdCategoria);
                system("pause");
            }
            case 3: {
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
            case 4: {
                int cod;
                printf("Remover:");
                scanf("%d", &cod);
                remCategoria(dtbase, cod, qtdCategoria);
            }
            case 0: {
                printf("Saindo...\n");
                return 1;
            }
            default: {
                printf("Esta não é uma opção válida, favor selecionar novamente.\n");
                break;
            }
        }
    }
    return escolha;
}