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
         strcpy(msg[0],"\tDescricao Categoria: \0");
         strcpy(msg[1],"\tValor Locacao: \0");
     }

    obj.codigo = *id;
    *id = *id + 1;

    printf("%s ",msg[0]);

    fflush(stdin);
    scanf("%[^\n]s",obj.descricao);

    char *valocacaoTpm = calloc(9,sizeof (char));

    printf("%s ",msg[1]);
    fflush(stdin);

    scanf("%[^\n]s", valocacaoTpm);
    obj.vAlocacao = strtof(valocacaoTpm,NULL);

    fflush(stdin);
    free(valocacaoTpm);

    obj.ativo = 1;
    return obj;
}


int insCategoria(fCategoria **dtbase,fCategoria newEntry,int *qtdCategoria,int *tamanhoCategoria)
{
    //printf("%d",*tamanhoCategoria);
    //Se a quantidade de categorias for igual ao tamanho alocado da lista espandir
    if (*qtdCategoria == *tamanhoCategoria)
    {
        *tamanhoCategoria = *tamanhoCategoria + 1;
        *dtbase = (fCategoria *) realloc(*dtbase, *tamanhoCategoria * sizeof(fCategoria));
    }
    if (*dtbase == NULL)
        {
            printf("\n  Erro na alocação de memória!");
            system("pause");
            return 0;
        } 
    // adc obj ao bd local
    (*dtbase)[*tamanhoCategoria - 1] = newEntry;
    *qtdCategoria = *qtdCategoria + 1;
    return 1;
}
int remCategoria(fCategoria **dtbase, int id, int qtdCategoria,int tipo_config){
    for (int i = 0; i < qtdCategoria; i++){
        if ((*dtbase)[i].codigo == id){
            (*dtbase)[i].ativo = 0;
        }
    }
    refazDados_Categoria(dtbase,qtdCategoria,tipo_config);
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
int editaCategoria(fCategoria **dtbase,int qtdCategoria,int id,int tipo_config){
    for (int i = 0; i <qtdCategoria; i++) {
        if ((*dtbase)[i].codigo == id) {
            fCategoria newEntrada = objCategoria(&id,0);
            (*dtbase)[i] = newEntrada;
            break;
        }
    }
    refazDados_Categoria(dtbase,qtdCategoria,tipo_config);
    return 1;
}
int locID(fCategoria **dtbase,int qtd_Categoria, int ID) {
    for (int i = 0; i < qtd_Categoria; i++)
    {
        if ((*dtbase)[i].codigo == ID) {
            return 1;
        }
    }
    return 0;
}

float valorCategoria(fCategoria **dtbase,int qtd_Categoria, int ID) {
    for (int i = 0; i < qtd_Categoria; i++)
    {
        if ((*dtbase)[i].codigo == ID) {
            return (*dtbase)[i].vAlocacao;
        }
    }
    return 0;
}

int menuCategoria(fCategoria **dtbase, int *qtdCategoria,int *tamanhoCategoria,int *idCategoria, int tipo_config) {
    int escolha = INT32_MAX;
    char temEscolha[4];
    while (1) {
        system("cls");
        setbuf(stdin,NULL);
        lineBox(70,"MENU CATEGORIA\0",1);
        printf("\tDigite a opcao referente a operacao que deseja executar\n\n");
        printf("\t0 - Sair \n\t1 - Cadastrar \n\t2 - Visualizar \n\t3 - Editar \n\t4 - Remover\n");
        lineBox(70,"-\0",0);

        //Tratamento de entrada
        printf(">>");
        scanf("%s", temEscolha); //Permite a entrada de qualquer caracter
        setbuf(stdin,NULL);

        escolha = strtol(temEscolha,NULL,10); //Procura na entrada o numero na base 10


        switch (escolha) {
            case 1: {
                int correto = 0;
                printf("\n\tCadastrar Categoria: [1- Sim  0- Nao]\n\t>> ");
                scanf("%s", temEscolha);//Permite a entrada de qualquer caracter
                setbuf(stdin,NULL);
                correto = strtol(temEscolha,NULL,10);//Procura na entrada o numero na base 10

                if (correto == 0)break;

                fCategoria newObjeto = objCategoria(idCategoria,0);
                insCategoria(dtbase,newObjeto,qtdCategoria,tamanhoCategoria);
                saveCategoria(newObjeto,tipo_config);
                break;
            }
            case 2: {
                printf(">> Categorias Cadastradas  \t Total: %d\n\n", *qtdCategoria);
                listCategorias(dtbase,*qtdCategoria);
                system("pause");
                break;
            }
            case 3: {
                int cod;
                printf(">> Categorias Cadastradas  \t Total: %d\n\n", *qtdCategoria);
                listCategorias(dtbase,*qtdCategoria);

                printf("\n\tDigite o ID da Categoria que deseja editar (0- Sair).\n\t>>");
                scanf("%s", temEscolha);//Permite a entrada de qualquer caracter
                setbuf(stdin,NULL);
                cod = strtol(temEscolha,NULL,10);//Procura na entrada o numero na base 10
                if (cod == 0){ break;}
                editaCategoria(dtbase,*qtdCategoria,cod,tipo_config);
                break;
            }
            case 4: {
                int cod;
                listCategorias(dtbase,*qtdCategoria);
                printf("\tDigite o ID da Categoria que deseja excluir (0- Sair).\n\t>>");

                scanf("%s", temEscolha);//Permite a entrada de qualquer caracter
                setbuf(stdin,NULL);
                cod = strtol(temEscolha,NULL,10);//Procura na entrada o numero na base 10
                if (cod == 0){break;}

                remCategoria(dtbase, cod, *qtdCategoria, tipo_config);
                break;
            }
            case 0: {
                system("cls");
                return 1;
            }
            default: {
                printf("Esta não é uma opção válida, favor selecionar novamente.\n");
                break;
            }
        }
    }
}

int saveCategoria(fCategoria objeto,int tipo_config){
    FILE *fileCategoria = NULL;

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
    FILE *p = NULL;
    fCategoria new;
    int t = 0;


    if (tipo_config == 1){ //Arquivo TXT
        p = fopen("cpyBdCategoria.txt", "r");

        if (p == NULL){
            printf("\nErro na Leitura 'cpyBdCategoria.txt' \n");
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

            t = insCategoria(dtBase,new,qtdCategoria,tamanhoCategoria);
            if (*id <= new.codigo) {
                *id = new.codigo + 1;
            }

            if (t == 0){
                printf("\nAcao Interrompida \n");
                break;
            }
        }
    }
    else  if (tipo_config == 0){ //Arquivo BIN
        p = fopen("cpyBdCategoria.bin", "rb");
        if (p == NULL){
            printf("\nErro na Leitura 'cpyBdCategoria.bin' \n");
            return 1;
        }
        while (!feof(p)){
            if (!filelength(fileno(p))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fread(&new,sizeof(fCategoria),1,p);

            if (locID(dtBase,*qtdCategoria,new.codigo) == 0){
                t = insCategoria(dtBase,new,qtdCategoria,tamanhoCategoria);
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

int refazDados_Categoria(fCategoria **dtbase, int qtdCategoria, int tipo_config){
    FILE *p;
    if (tipo_config == 1){
        p = fopen("cpyBdCategoria.txt", "w");
        fclose(p);
        p = NULL;
        for (int i = 0; i < qtdCategoria; i++){
            saveCategoria((*dtbase)[i],1);
        }
    }else if (tipo_config == 0){
        p = fopen("cpyBdCategoria.bin", "wb");
        fclose(p);
        p = NULL;
        for (int i = 0; i < qtdCategoria; i++){
            saveCategoria((*dtbase)[i],0);
        }
    }
    return 0;
}