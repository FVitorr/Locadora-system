#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "categoriaF.h"
#include "filmes.h"


int main(int argc, char** argv) {
    bd_filme = malloc(len_bd * sizeof(filme));
    bd_cat = malloc(len_cat * sizeof(fCategoria));

    while (1)
    {
        int i = menuFilme();
        if (i == 1) {
            break;
        }
    }
    free(bd_filme);
    free(bd_cat);

    return (EXIT_SUCCESS);
}
