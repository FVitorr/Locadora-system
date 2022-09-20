#include <stdio.h>
#include  <stdlib.h>
#include <stdint.h>

#include "cabecalhos/filmes.h"
#include "cabecalhos/locadora.h"
#include "cabecalhos/cliente.h"
#include "cabecalhos/funcionarios.h"
#include "cabecalhos/fornecedor.h"

fCategoria *bd_cat;
int qtdCategoria = 0, tamanhoCategoria = 1;

filme  *bd_filme;
int qtdFilmes = 0, tamanhoFilme = 1, idControleFilme = 0;

funcionarios *bd_funcionarios;
int qtdFuncionarios = 0, tamanhoFuncionarios = 1, idControleFuncionarios = 0;

locadora *bd_locadora;
int qtdLocadora = 0, tamanhoLocadora = 1, idControleLocadora = 0;

cliente *bd_cliente;
int qtdCliente = 0, tamanhoCliente = 1, idControleCliente = 0;

fornecedor *bd_fornecedor;
int qtdFornecedor = 0, tamanhoFornecedor = 1, idControleFornecedor = 0;

int menuprincipal(fCategoria **dtbaseCategoria, int *qtd_Categoria,int *tamanho_Categoria,
                  filme **dtbaseFilme, int *qtd_Filmes,int *tamanhoFilmes, int *idFilme,
                  funcionarios **dtbasefuncionarios, int *qtd_Funcionarios, int *tamanho_Funcionarios, int *idFuncionarios,
                  cliente **dataBaseCliente, int *qtd_Cliente, int *tamanho_Cliente, int *idCliente) {

    system("cls");
    int opc = 0, erro = 1;
    printf("Olá, seja bem vindo!\n");
    printf("Digite a opção referente a operação que deseja executar\n\n");
    printf("1 - Locação \n2 - Clientes\n3 - Categoria \n4 - Filme \n0 - Sair\n");
    scanf("%d", &opc);
    while (opc != 0) {
        system("cls");
        switch (opc) {
            case 0:
                printf(">> Exit \n");
                return 1;
            case 1:
                printf("Menu-Locação\n");
                break;
            case 2:
                menuClientes(dataBaseCliente, qtd_Cliente, tamanho_Cliente, *idCliente);
                break;
            case 3:
                while (1) {
                    int t = menuCategoria(dtbaseCategoria, qtd_Categoria, tamanho_Categoria);
                    if (t == 1) {
                        break;
                    }
                }
                return 0;
            case 4:
                while (1) {
                    int t = menuFilme(dtbaseFilme, qtd_Filmes, tamanhoFilmes, dtbaseCategoria, qtd_Categoria,
                                      tamanho_Categoria, idFilme);
                    if (t == 1) {
                        break;
                    }
                }
            case 5:
                while (1) {
                    int t = menuFuncionarios(dtbasefuncionarios, qtd_Funcionarios, tamanho_Funcionarios,
                                             idFuncionarios);
                    if (t == 1) {
                        break;
                    }
                }
                return 0;
            default:

                break;
        }
    }
}

int main() {
    bd_cat = malloc(tamanhoCategoria * sizeof(fCategoria));
    bd_filme = malloc(tamanhoFilme * sizeof(filme));
    bd_funcionarios = malloc(tamanhoFuncionarios * sizeof(funcionarios));
    bd_cliente = malloc(tamanhoCliente * sizeof(cliente));

    menuprincipal(&bd_cat, &qtdCategoria, &tamanhoCategoria, &bd_filme, &qtdFilmes, &tamanhoFilme, &idControleFilme,
                  &bd_funcionarios, &qtdFuncionarios, &tamanhoFuncionarios, &idControleFuncionarios, &bd_cliente,
                  &qtdCliente, &tamanhoCliente, &idControleCliente);
}