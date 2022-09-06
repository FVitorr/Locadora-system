#include <stdio.h>
#include  <stdlib.h>
#include "cabecalhos/categoriaF.h"

fCategoria *bd_cat;
int qtdCategoria = 0,TamanhoCategoria = 1;


int main() {
    //printf("\n%p\n",&bd_cat);
    bd_cat = malloc(TamanhoCategoria * sizeof(fCategoria));

    while (1){
        int a = menuCategoria(&bd_cat,&qtdCategoria,&TamanhoCategoria);
        if (a==1){
            break;
        }
    }

    return 0;
}