#include <stdio.h>
#include  <stdlib.h>
#include "cabecalhos/categoriaF.h"
#include "cabecalhos/filmes.h"

fCategoria *bd_cat;
int qtdCategoria = 0,TamanhoCategoria = 1;

filme  *bd_filme;
int qtdFilmes = 0,TamanhoFilme = 1;

int main() {
    //printf("\n%p\n",&bd_cat);
    bd_cat = malloc(TamanhoCategoria * sizeof(fCategoria));
    bd_filme = malloc(TamanhoFilme * sizeof (filme));

    while (1){
        int a = menuFilme(&bd_filme,&qtdFilmes,&TamanhoFilme);
        if (a==1){
            break;
        }
    }

    return 0;
}