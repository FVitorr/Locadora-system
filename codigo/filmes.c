#include <stdlib.h>
#include <stdio.h>
#include "../cabecalhos/filmes.h"
//#include "../cabecalhos/categoriaF.h"

//int categTry(int ID);
// +++++++++++++++++++++++++++++++++++++++++ Subrotinas para controle dos filmes +++++++++++++++++

filme objFilme(fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoCategoria, int id) // Bloco para receber as entradas e "compartar" na struct
{
    filme p;
    p.codigo = id;
    printf("Nome: ");
    scanf("%s", p.nome);
    printf("Descricao: ");
    scanf("%s", p.descricao);
    printf("Quantidade de Exemplares: ");
    scanf("%d", &p.qtd);
    printf("Codigo Categoria: ");
    scanf("%d", &p.c_categoria); //Possivelmente este campo precisa ser comparado ...
    categTry(dtbaseCategoria,qtdCategoria,tamanhoCategoria , p.c_categoria);
    printf("Lingua: ");
    scanf("%s", p.lingua);
    return p;
}

int inserirFilme(filme **dtbase,filme newEntry,int *qtdFilmes,int *tamanhoFilmes,int id){
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
    (*dtbase)[id] = newEntry;
    *qtdFilmes = *qtdFilmes + 1;
    return 1;
}
int removerFilme(filme **dtbase, int id, int *qtdFilmes){
    for (int i = 0; i < *qtdFilmes; i ++){
        if((*dtbase)[i].codigo == id){
            while (i < *qtdFilmes - 1)
            {
                (*dtbase)[i] = (*dtbase)[i + 1];
                i++;
            }
            *qtdFilmes = *qtdFilmes - 1;
            break;
        }
    }
    return 0;
}


void listFilme(filme **dtbase, int qtd){
    printf("\nID \t Nome \t Descrição \t Quant. Exemplares \t ID categoria \t Lingua\n");
    for (int c = 0; c < qtd; c++)
    {
        printf("---------------------------------------------------------------------------------\n");
        printf("(%d)\t %s\t %s\t\t\t %d\t\t %d\t\t %s\n", (*dtbase)[c].codigo,
               (*dtbase)[c].nome,
               (*dtbase)[c].descricao,
               (*dtbase)[c].qtd,
               (*dtbase)[c].c_categoria,
               (*dtbase)[c].lingua);
    }
    printf("\n");

}

void editaFilme(filme **dtbase,int *qtdFilmes,int *tamanhoFilmes,fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoCategoria,int id)
{
    for (int i = 0; i < *qtdFilmes; i++) {
        if ((*dtbase)[i].codigo == id) {
            filme newEntrada = objFilme(dtbaseCategoria,qtdCategoria,tamanhoCategoria,id);
            inserirFilme(dtbase,newEntrada,qtdFilmes,tamanhoFilmes,id);
        }
    }
}

int categTry(fCategoria **dtbaseCategoria,int *qtdCategoria,int *tamanhoCategoria ,int id) {
    int tem = locID(dtbaseCategoria,qtdCategoria,id),opc = 0;
    //int tem = 0;cc
    if (tem == 0) {
        printf("\n\t>> Categoria não encontrada \n");
        printf("\t>> Cadastrar [1 - Sim] [ 0 - N�o]: ");
        scanf("%d", &opc);
        if (opc == 0) {
            return 1;
        }
        else {
            fCategoria new = objCategoria(id,1);
            int suc = insCategoria(dtbaseCategoria,new,qtdCategoria,tamanhoCategoria);
            if (suc == 1) {
                printf("\n>> Sucess");
            }
            printf("\n");
        }
    }
    return 0;
}

int menuFilme(filme **dtbase,int *qtdFilmes,int *tamanhoFilmes, fCategoria **dtbaseCategoria, int *qtdCategoria, int *tamanhoCategoria){
    int opc = 0, erro = 0, exit = 0;
    system("cls");
    line(20,"Filmes\0");
    printf("\t 0 - Sair \n\t 1 - Cadastrar \n\t 2 - Cadastrar Multiplas \n");
    printf("\t 3 - Visualizar \n\t 4 - Editar \n\t 5 - Remover\n");
    line(20,"-\0");

    do
    {
        if (erro == 1)
        {
            printf(">> Parametro Invalido\n");
        }
        printf("Opc: ");
        scanf("%d", &opc);
        erro = 1;
    } while (opc < 0 || opc > 5);

    if (opc == 0)
    {
        printf("Sair");
        exit = 1;
    }
    else if (opc == 1)
    {
        // Cadastrar um Filme
        system("cls");
        printf(">> Novo filme     ID: %d \n\n", *qtdFilmes);
        filme new = objFilme(dtbaseCategoria,qtdCategoria,tamanhoCategoria,*qtdFilmes);
        inserirFilme(dtbase,new,qtdFilmes,tamanhoFilmes,*qtdFilmes);
    }
    else if (opc == 2)
    {
        // Cadastrar multiplas categoria
        system("cls");
        int op = 1;
        printf(">> Multiplos filme     ID: %d \n\n", *qtdFilmes);
        while (1)
        {
            filme new = objFilme(dtbaseCategoria,qtdCategoria,tamanhoCategoria,*qtdFilmes);
            inserirFilme(dtbase,new,qtdFilmes,tamanhoFilmes,*qtdFilmes);
            printf("\n >> [1 - Mais] \t [0 - Exit]: ");
            scanf("%d", &op);
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
    }
    else if (opc == 5)
    {
        // Remover
        int cod;
        printf("Remover:");
        scanf("%d", &cod);
        removerFilme(dtbase,cod,qtdFilmes);
    }
    return exit;
}

