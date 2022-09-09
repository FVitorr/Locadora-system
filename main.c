#include <stdio.h>
#include  <stdlib.h>
#include "cabecalhos/filmes.h"
#include "cabecalhos/locadora.h"

fCategoria *bd_cat;
int qtdCategoria = 0,TamanhoCategoria = 1;

filme  *bd_filme;
int qtdFilmes = 0,TamanhoFilme = 1, idControle = 0;

int menuprincipal(fCategoria **dtbaseCategoria, int *qtdCategoria,int *tamanhoCategoria,
                   filme **dtbaseFilme, int *qtdFilmes,int *tamanhoFilmes, int *id){

    system("cls");
    int opc = 0, erro = 1;
    line(60,"Menu principal \0");
    printf("\t 1 - Locacao \t\t 2 - Clientes \n\t 3 - Categoria \t\t 4 - Filmes");
    printf("\n\t 5 - Funcionarios \t 6 - Importar/Exportar \n\t 7 - Configuraçoes \t 0 - Exit");
    line(60,"s\0");
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
            while (1){
                int t = menuCategoria(dtbaseCategoria,qtdCategoria,tamanhoCategoria);
                if (t == 1){
                    break;
                }
            }
            return 0;
        case 4:
            while (1){
                int t = menuFilme(dtbaseFilme,qtdFilmes,tamanhoFilmes,dtbaseCategoria,qtdCategoria,tamanhoCategoria,id);
                if (t == 1){
                    break;
                }
            }
            return 0;
    }
}

int main() {
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
    free(bd_cat);
    free(bd_filme);
    bd_cat = NULL;
    bd_filme = NULL;
    return 0;
}