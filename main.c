#include <stdio.h>
#include  <stdlib.h>

#include "cabecalhos/filmes.h"
#include "cabecalhos/locadora.h"
#include "cabecalhos/cliente.h"
#include "cabecalhos/funcionarios.h"
#include "cabecalhos/fornecedor.h"

/*Arrays Dinamicos*/

fCategoria *bd_cat;
int qtdCategoria = 0, tamanhoCategoria = 1, idControleCategoria;

filme  *bd_filme;
int qtdFilmes = 0, tamanhoFilme = 1, idControleFilmes = 0;

funcionarios *bd_funcionarios;
int qtdFuncionarios = 0, tamanhoFuncionarios = 1, idControleFuncionarios = 0;

locadora *bd_locadora;
int qtdLocadora = 0, tamanhoLocadora = 1, idControleLocadora = 0;

cliente *bd_cliente;
int qtdCliente = 0, tamanhoCliente = 1, idControleCliente = 0;

fornecedor *bd_fornecedor;
int qtdFornecedor = 0, tamanhoFornecedor = 1, idControleFornecedor = 0;

int menuprincipal(int tipo_config,
                  fCategoria **dtbaseCategoria, int *qtd_Categoria,int *tamanho_Categoria,int *idCategoria,
                  filme **dtbaseFilme, int *qtd_Filmes,int *tamanhoFilmes, int *idFilme,
                  funcionarios **dtbasefuncionarios, int *qtd_Funcionarios,int *tamanho_Funcionarios,int *idFuncionarios,
                  locadora **dtbaseLocadora, int *qtd_Locadora,int *tamanho_Locadora,int *idLocadora,
                  cliente **dtbaseCliente, int *qtd_Cliente,int *tamanho_Cliente,int *idCliente,
                  fornecedor **dtbaseFornecedor, int *qtd_Fornecedor,int *tamanho_Fornecedor,int *idFornecedor){

    system("cls");
    int opc = 0, erro = 0;
    line(60,"Menu principal \0");
    printf("\t 1 - Locacao \t\t 2 - Clientes \n\t 3 - Categoria \t\t 4 - Filmes\n\t 5 - Funcionarios\t 6 - Fornecedor\n\t 7 - Locadora\t\t 8 - Exportar/Importar\n\t 0 - Exit");
    line(60,"s\0");
    do {
        if (erro == 1) {
            printf(">> Parametro Invalido:\n");
        }
        printf(">> Opc: ");
        scanf("%d", &opc);
        erro = 1;
    } while (opc < 0 || opc > 9);
    system("cls");
    switch (opc) {
        case 0:
            printf(">> Exit \n");
            return 1;
        case 1:
            return 0;
        case 2:
            while (1){
                int t = menuClientes(dtbaseCliente,qtd_Cliente,tamanho_Cliente,idCliente, tipo_config);
                if (t == 1){
                    return 0;
                }
            }
        case 3:
            while (1){
                int t = menuCategoria(dtbaseCategoria,qtd_Categoria,tamanho_Categoria,idCategoria,tipo_config);
                if (t == 1){
                    return 0;
                }
            }
        case 4:
            while (1){
                int t = menuFilme(dtbaseFilme,qtd_Filmes,tamanhoFilmes,dtbaseCategoria,qtd_Categoria,tamanho_Categoria,idFilme, tipo_config);
                if (t == 1){
                    return 0;
                }
            }
        case 5:
            while (1){
                int t = menuFuncionarios(dtbasefuncionarios,qtd_Funcionarios,tamanho_Funcionarios,idFuncionarios, tipo_config);
                if (t == 1){
                    return 0;
                }
            }

        case 6:
            while (1){
                int t = menuFornecedor(dtbaseFornecedor, qtd_Fornecedor, tamanho_Fornecedor, idFornecedor, tipo_config);
                if (t == 1){
                    return 0;
                }
            }
        case 7:
            while (1){
                int t = menuLocadora(dtbaseLocadora,qtd_Locadora,tamanho_Locadora,idLocadora, tipo_config);
                if (t == 1){
                    return 0;
                }
            }
        default: {
            printf("Esta não é uma opção válida, favor selecionar novamente.\n");
            break;
        }
    }
    return 0;
}



int carregaTodosDados(int *tipoConfig, config *config_system,
                      filme **dtbaseFilme, int *qtd_Filmes,int *tamanhoFilmes, int *idFilme,
                      locadora **dtbaseLocadora, int *qtd_Locadora,int *tamanho_Locadora,int *idLocadora,
                      fCategoria **dtbaseCategoria, int *qtd_Categoria, int *tamanho_Categoria, int *idCategoria,
                      cliente **dtBaseCliente, int *qtd_Cliente, int *tamanho_Cliente, int *idCliente,
                      fornecedor **dtBaseFornecedor, int *qtd_Fornecedor, int *tamanho_Fornecedor, int *idFornecedor){

    int newID = verifica_log(config_system,tipoConfig);
    carregarDados_filme(dtbaseFilme, qtd_Filmes, tamanhoFilmes, idFilme, *tipoConfig);
    carregarDados_Locadora(dtbaseLocadora,qtd_Locadora,tamanho_Locadora,idLocadora,*tipoConfig);
    carregarDados_Categoria(dtbaseCategoria, qtd_Categoria,tamanho_Categoria,idCategoria,*tipoConfig);
    carregarDadosClientes(dtBaseCliente, qtd_Cliente,tamanho_Cliente,idCliente,*tipoConfig);
    carregarDadosFornecedores(dtBaseFornecedor, qtd_Fornecedor, tamanho_Fornecedor, idFornecedor, *tipoConfig);

    return 0;
}

int main() {
    int tipoConfig = 1; // 0- BIN 1 - TXT

    config config_System;

    bd_cat = malloc(tamanhoCategoria * sizeof(fCategoria));
    bd_filme = malloc(tamanhoFilme * sizeof (filme));
    bd_funcionarios = malloc(tamanhoFuncionarios * sizeof (funcionarios));
    bd_cliente = malloc(tamanhoCliente * sizeof (cliente));
    bd_locadora = malloc(tamanhoLocadora * sizeof(locadora));
    bd_fornecedor = malloc(tamanhoFornecedor * sizeof(fornecedor));

    //Verifica se os arquivos existem caso contrario criar
    verifica_arquivos(tipoConfig);
    //Carrega os arquivos e Verifica se é primeira execursão
    carregaTodosDados(&tipoConfig,&config_System,
                      &bd_filme,&qtdFilmes,&tamanhoFilme,&idControleFilmes,
                      &bd_locadora,&qtdLocadora,&tamanhoLocadora,&idControleLocadora,
                      &bd_cat,&qtdCategoria,&tamanhoCategoria,&idControleCategoria,
                      &bd_cliente, &qtdCliente, &tamanhoCliente, &idControleCliente,
                      &bd_fornecedor, &qtdFornecedor, &tamanhoFornecedor, &idControleFornecedor);

    while (1){
        int v;
        v = menuprincipal(tipoConfig,
                          &bd_cat,&qtdCategoria,&tamanhoCategoria,&idControleCategoria,
                          &bd_filme,&qtdFilmes,&tamanhoFilme,&idControleFilmes,
                          &bd_funcionarios,&qtdFuncionarios,&tamanhoFuncionarios,&idControleFuncionarios,
                          &bd_locadora,&qtdLocadora,&tamanhoLocadora,&idControleLocadora,
                          &bd_cliente,&qtdCliente,&tamanhoCliente,&idControleCliente,
                          &bd_fornecedor, &qtdFornecedor, &tamanhoFornecedor, &idControleFornecedor);
        if (v == 1){
            break;
        }
    }
    free(bd_cat);
    free(bd_filme);
    free(bd_funcionarios);
    free(bd_cliente);
    free(bd_locadora);
    bd_cat = NULL;
    bd_filme = NULL;
    bd_funcionarios = NULL;
    bd_locadora = NULL;
    bd_cliente = NULL;
    return 0;
}