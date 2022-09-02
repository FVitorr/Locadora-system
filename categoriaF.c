#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int codigo;
    char descricao[30];
    float vAlocacao;
} fCategoria;

fCategoria* bd_cat;
int qtdCat = 0, len_cat = 1;

fCategoria objCategoria(int id) {
    fCategoria obj;
    char a = "\t";
    obj.codigo = id;
    printf("%c Descrição Categoria: ",a);
    scanf("%s", &obj.descricao);
    printf("Valor Locação: ");
    scanf("%f", &obj.vAlocacao);
    return obj;
}

int insCategoria(fCategoria p)
{
    // Se a quantidade de categorias for igual ao tamanho alocado da lista -> espandir
    if (qtdCat == len_cat)
    {
        len_cat += 1;
        bd_cat = realloc(bd_cat, len_cat * sizeof(fCategoria));
    }
    // adc obj ao bd local
    bd_cat[qtdCat] = p;
    qtdCat++;
    return 1;
}
void remCategoria(fCategoria* bd, int codigo) {
    for (int i = 0; i < qtdCat; i++) {
        if (bd[i].codigo == codigo) {
            while (i < qtdCat - 1) {
                bd[i] = bd[i + 1];
                i++;
            }
            qtdCat--;
            break;
        }
    }
}
void listCategoria(fCategoria* bd, int qtd) {
    printf("\n ID \tDescrição Categoria \t Valor Locação\n");
    for (int c = 0; c < qtd; c++) {
        printf("----------------------------------------------------\n");
        printf("(%d)\t%15s\t\t %.2f\n", bd[c].codigo, bd[c].descricao, bd[c].vAlocacao);
    }
    printf("\n");
}
int alteraCat(fCategoria f, fCategoria* bd, int codigo) {
    int proc = 0;
    for (int i = 0; i < qtdCat; i++)
    {
        if (bd[i].codigo == codigo)
        {
            bd[i] = f;
            proc = 1;
            break;
        }
        else {
            proc = 0;
        }
    }
    return proc;
}
int locID(fCategoria *bd, int codigo) {
    int erro = 0;
    for (int i = 0; i < qtdCat; i++)
    {
        if (bd[i].codigo == codigo) {
            erro = 1;
            break;
        }
    }
    return erro;
}

int menuCategoria() {
    int opc = 0, erro = 0, exit = 0;
    system("cls");
    printf("------------- Categorias -------------\n\n");
    printf("\t 0 - Sair \n\t 1 - Cadastrar \n\t 2 - Cadastrar Multiplas \n");
    printf("\t 3 - Visualizar \n\t 4 - Editar \n\t 5 - Remover\n");
    printf("--------------------------------------\n");

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
        system("cls");
        printf(">> Exit\n");
        exit = 1;
        system("pause");
    }
    else if (opc == 1) {
        //Cadastrar uma categoria
        system("cls");
        printf(">> Nova Categoria     ID: %d \n\n", qtdCat);
        fCategoria new = objCategoria(qtdCat);
        insCategoria(new);
    }
    else if (opc == 2) {
        //Cadastrar multiplas categoria
        system("cls");
        printf(">> Cadastro Multiplo Categoria     ID: %d \n\n", qtdCat);
        int qtd_ = 1;
        while (1)
        {
            fCategoria new = objCategoria(qtdCat);
            insCategoria(new);
            printf("[1 - Mais] \t [0 - Exit]: ");
            scanf("%d", &qtd_);
            if (qtd_ == 0) {
                break;
            }
        }

    }
    else if (opc == 3) {
        //Visualizar 
        system("cls");
        printf(">> Categorias Cadastradas  \t Total: %d\n\n", qtdCat);
        listCategoria(bd_cat, qtdCat);
        system("pause");
    }
    else if (opc == 4) {
        // editar
    }
    else if (opc == 5) {
        // Remover
        int cod;
        printf("Remover:");
        scanf("%d", &cod);
        remCategoria(bd_cat, cod);
    }
    return exit;
}

