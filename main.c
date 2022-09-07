#include <stdio.h>
#include  <stdlib.h>
//#include "cabecalhos/categoriaF.h"
#include "../cabecalhos/filmes.h"
//#include "../cabecalhos/fucGlobal.h"

fCategoria *bd_cat;
int qtdCategoria = 0,TamanhoCategoria = 1;

filme  *bd_filme;
int qtdFilmes = 0,TamanhoFilme = 1, idControle = 0;

int menuprincipal(fCategoria **dtbaseCategoria, int *qtdCategoria,int *tamanhoCategoria,
                   filme **dtbaseFilme, int *qtdFilmes,int *tamanhoFilmes, int *id){

    system("cls");
    int opc = 0, erro = 1;
    line(30,"Menu principal \0");
    printf("\t 1 - Locacao \n\t 2 - Clientes \n\t 3 - Categoria \n\t 4 - Filmes");
    line(30,"s\0");
    do {
        if (erro != 1){
            printf(">> Parametro Invalido:\n");
        }
        printf(">> Opc: ");
        scanf("%d", &opc);
        erro = 0;
    } while (opc < 0 || opc > 4);
    system("cls");
    switch (opc) {
        case 0:
            printf(">> Exit \n");
            return 1;
        case 1:
            printf("Menu-Locação\n");
            break;
        case 2:
            printf("Menu-Clientes\n");
            break;
        case 3:
            menuCategoria(dtbaseCategoria,qtdCategoria,tamanhoCategoria);
            return 0;
        case 4:
            menuFilme(dtbaseFilme,qtdFilmes,tamanhoFilmes,dtbaseCategoria,qtdCategoria,tamanhoCategoria,id);
            return 0;
    }
}

int main() {
    //printf("\n%p\n",&bd_cat);
    bd_cat = malloc(TamanhoCategoria * sizeof(fCategoria));
    bd_filme = malloc(TamanhoFilme * sizeof (filme));

    while (1){
        int v;
        v = menuprincipal(&bd_cat,&qtdCategoria,&TamanhoCategoria,
                    &bd_filme,&qtdFilmes,&TamanhoFilme,&idControle);
        if (v == 1){
            break;
        }
    }
    return 0;
}