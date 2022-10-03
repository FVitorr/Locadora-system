#include "../cabecalhos/categoriaF.h"
#include "../cabecalhos/fucGlobal.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <io.h>

fCategoria objCategoria (int *id,int tab){
    fCategoria obj;

    char msg[2][35];

    strcpy(msg[0],"Descricao Categoria: \0");
    strcpy(msg[1],"Valor Locacao: \0");

     if (tab == 1){
         addTab(msg[0]);
         addTab(msg[1]);
     }

    obj.codigo = *id;
    *id = *id + 1;

    printf("%s ",msg[0]);

    fflush(stdin);
    scanf("%[^\n]s",obj.descricao);

    printf("%s ",msg[1]);
    scanf("%f%*c", &obj.vAlocacao);

    obj.ativo = 1;
    return obj;
}


int insCategoria(fCategoria **dtbase,fCategoria newEntry,int *qtdCategoria,int *tamanhoCategoria, int tipo_config)
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
    (*dtbase)[*tamanhoCategoria - 1] = newEntry;
    *qtdCategoria = *qtdCategoria + 1;
    saveCategoria(newEntry,tipo_config);
    return 0;
}
int remCategoria(fCategoria **dtbase, int id, int *qtdCategoria,int *tamanhoCategoria,int tipo_config){
    for (int i = 0; i < *qtdCategoria; i++){
        if ((*dtbase)[i].codigo == id){
            (*dtbase)[i].ativo = 0;
        }
    }
    refazDados_Categoria(dtbase,qtdCategoria,tamanhoCategoria,tipo_config);
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
int editaCategoria(fCategoria **dtbase,int *qtdCategoria,int *tamanhoCategoria,int id,int tipo_config){
    for (int i = 0; i < *qtdCategoria; i++) {
        if ((*dtbase)[i].codigo == id) {
            fCategoria newEntrada = objCategoria(&id,0);
            (*dtbase)[i] = newEntrada;
            break;
        }
    }
    refazDados_Categoria(dtbase,qtdCategoria,tamanhoCategoria,tipo_config);
    return 1;
}
int locID(fCategoria **dtbase,int qtd_Categoria, int ID) {
    for (int i = 0; i < qtd_Categoria; i++)
    {
        if ((*dtbase[i]).codigo == ID) {
            return 1;
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


int menuCategoria(fCategoria **dtbase, int *qtdCategoria,int *tamanhoCategoria,int *idCategoria, int tipo_config) {
    int escolha = INT32_MAX;

    while (escolha != 0) {
        printf("Digite a opcao referente a operacao que deseja executar\n\n");
        printf("0 - Sair \n1 - Cadastrar \n2 - Visualizar \n3 - Editar \n4 - Remover\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: {
                fCategoria newObjeto = objCategoria(idCategoria,0);
                insCategoria(dtbase,newObjeto,qtdCategoria,tamanhoCategoria,tipo_config);
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
                int t = editaCategoria(dtbase,qtdCategoria,tamanhoCategoria,cod,tipo_config);
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
                remCategoria(dtbase, cod, qtdCategoria,tamanhoCategoria, tipo_config);
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

int saveCategoria(fCategoria objeto,int tipo_config){
    FILE *fileCategoria;

    if (tipo_config == 1){//Arquivo TXT
        fileCategoria = fopen("cpyBdCategoria.txt", "a");

        if (fileCategoria == NULL){ // Se a abertura falhar
            return 1;
        }

        fprintf(fileCategoria, "%d\n%s\n%f\n%d\n",
                objeto.codigo,
                objeto.descricao,
                objeto.vAlocacao,
                objeto.ativo);

    }else if (tipo_config == 0){ //Arquivo BINARIO
        fileCategoria = fopen("cpyBdCategoria.bin", "ab");
        if (fileCategoria == NULL){ // Se a abertura falhar
            return 1;
        }
        fwrite(&objeto, sizeof(fCategoria), 1,fileCategoria);
    }
    fclose(fileCategoria);
    return 0;

}

int carregarDados_Categoria(fCategoria **dtBase, int *qtdCategoria, int *tamanhoCategoria, int *id,int tipo_config){
    FILE *p;
    fCategoria new;
    int t = 0;
    if (tipo_config == 1){ //Arquivo TXT
        p = fopen("cpyBdCategoria.txt", "r");

        if (p == NULL){
            printf("\nErro na Leitura 'cpyBdCategoria.txt' \n");
            system("Pause");
            return 1;
        }

        while (!feof(p)){
            if (!filelength(fileno(p))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fscanf(p, "%d\n", &new.codigo);

            fgets(new.descricao, 120, p);
            limpa_final_string(new.descricao);

            fscanf(p,"%f\n" ,&new.vAlocacao);


            fscanf(p, "%d\n", &new.ativo);

            t = insCategoria(dtBase,new,qtdCategoria,tamanhoCategoria,tipo_config);
            if (*id <= new.codigo) {
                *id = new.codigo + 1;
            }

            if (t == 0){
                printf("\nAcao Interrompida");
                break;
            }
        }
    }
    else  if (tipo_config == 0){ //Arquivo BIN
        p = fopen("cpyBdCategoria.bin", "rb");
        while (!feof(p)){
            if (!filelength(fileno(p))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fread(&new,sizeof(filme),1,p);

            t = insCategoria(dtBase,new,qtdCategoria,tamanhoCategoria,tipo_config);
            if (*id <= new.codigo) {
                *id = new.codigo + 1;
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

int refazDados_Categoria(fCategoria **dtbase, int *qtdCategoria, int *tamanhoCategoria, int tipo_config){
    FILE *p;
    if (tipo_config == 1){
        p = fopen("cpyBdCategoria.txt", "w");
        fclose(p);
        p = NULL;
        for (int i = 0; i < *tamanhoCategoria; i++){
            saveCategoria((*dtbase)[i],1);
        }
    }else if (tipo_config == 0){
        p = fopen("cpyBdCategoria.bin", "wb");
        fclose(p);
        p = NULL;
        for (int i = 0; i < *tamanhoCategoria; i++){
            saveCategoria((*dtbase)[i],0);
        }
    }
    return 0;
}