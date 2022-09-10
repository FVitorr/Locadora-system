#include <stdio.h>
#include  <stdlib.h>

#include "cabecalhos/filmes.h"
#include "cabecalhos/locadora.h"
#include "cabecalhos/cliente.h"
#include "cabecalhos/funcionarios.h"

fCategoria *bd_cat;
int qtdCategoria = 0, tamanhoCategoria = 1;

filme  *bd_filme;
int qtdFilmes = 0, tamanhoFilme = 1, idControle = 0;

funcionarios *bd_funcionarios;
int qtdFuncionarios = 0, tamanhoFuncionarios = 1, idControleFuncionarios = 0;

locadora *bd_locadora;
int qtdLocadora = 0, tamanhoLocadora = 1, idControleLocadora = 0;

cliente *bd_cliente;
int qtdCliente = 0, tamanhoCliente = 1, idControleCliente = 0;

int menuprincipal(fCategoria **dtbaseCategoria, int *qtd_Categoria,int *tamanho_Categoria,
                  filme **dtbaseFilme, int *qtd_Filmes,int *tamanhoFilmes, int *idFilme,
                  funcionarios **dtbasefuncionarios, int *qtd_Funcionarios,int *tamanho_Funcionarios,int *idFuncionarios){

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
                int t = menuCategoria(dtbaseCategoria,qtd_Categoria,tamanho_Categoria);
                if (t == 1){
                    break;
                }
            }
            return 0;
        case 4:
            while (1){
                int t = menuFilme(dtbaseFilme,qtd_Filmes,tamanhoFilmes,dtbaseCategoria,qtd_Categoria,tamanho_Categoria,idFilme);
                if (t == 1){
                    break;
                }
            }
        case 5:
            while (1){
                int t = menuFuncionarios(dtbasefuncionarios,qtd_Funcionarios,tamanho_Funcionarios,idFuncionarios);
                if (t == 1){
                    break;
                }
            }
            return 0;
    }
}

int main() {
    bd_cat = malloc(tamanhoCategoria * sizeof(fCategoria));
    bd_filme = malloc(tamanhoFilme * sizeof (filme));
    bd_funcionarios = malloc(tamanhoFuncionarios * sizeof (funcionarios));

    while (1){
        int v;
        v = menuprincipal(&bd_cat,&qtdCategoria,&tamanhoCategoria,
                          &bd_filme,&qtdFilmes,&tamanhoFilme,&idControle,
                          &bd_funcionarios,&qtdFuncionarios,&tamanhoFuncionarios,&idControleFuncionarios);
        if (v == 1){
            break;
        }
    }
    free(bd_cat);
    free(bd_filme);
    free(bd_funcionarios);
    bd_cat = NULL;
    bd_filme = NULL;
    bd_funcionarios = NULL;
    return 0;
}