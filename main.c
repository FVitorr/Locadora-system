#include <stdio.h>
#include  <stdlib.h>

#include "cabecalhos/filmes.h"
#include "cabecalhos/locadora.h"
#include "cabecalhos/cliente.h"
#include "cabecalhos/funcionarios.h"
#include "cabecalhos/fornecedor.h"

fCategoria *bd_cat;
int qtdCategoria = 0, tamanhoCategoria = 1;

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

int carregaTodosDados(int *tipoConfig,config *config_system,
                      filme **dtbaseFilme, int *qtd_Filmes,int *tamanhoFilmes, int *idFilme,
                      locadora **dtbaseLocadora, int *qtd_Locadora,int *tamanho_Locadora,int *idLocadora);

int menuprincipal(int tipo_config,
                  fCategoria **dtbaseCategoria, int *qtd_Categoria,int *tamanho_Categoria,
                  filme **dtbaseFilme, int *qtd_Filmes,int *tamanhoFilmes, int *idFilme,
                  funcionarios **dtbasefuncionarios, int *qtd_Funcionarios,int *tamanho_Funcionarios,int *idFuncionarios,
                  locadora **dtbaseLocadora, int *qtd_Locadora,int *tamanho_Locadora,int *idLocadora){

    system("cls");
    int opc = 0, erro = 0;
    line(60,"Menu principal \0");
    printf("\t 1 - Locacao \t\t 2 - Clientes \n\t 3 - Categoria \t\t 4 - Filmes");
    printf("\n\t 5 - Funcionarios \t 6 - Locadora \n\t 7 - Importar/Exportar \t 0 - Exit");
    line(60,"s\0");
    do {
        if (erro == 1){
            printf(">> Parametro Invalido:\n");
        }
        printf(">> Opc: ");
        scanf("%d", &opc);
        erro = 1;
    } while (opc < 0 || opc > 6);
    system("cls");
    switch (opc) {
        case 0:
            printf(">> Exit \n");
            return 1;
        case 1:
            while (1) {
                int t = menuLocadora(dtbaseLocadora, qtd_Locadora, tamanho_Locadora, idLocadora,tipo_config);
                if (t == 1) {
                    return 0;
                }
            }
        case 2:
            printf("Menu-Clientes\n");
            return 0;
        case 3:
            while (1){
                int t = menuCategoria(dtbaseCategoria,qtd_Categoria,tamanho_Categoria);
                if (t == 1){
                    return 0;
                }
            }
            return 0;
        case 4:
            while (1){
                int t = menuFilme(dtbaseFilme,qtd_Filmes,tamanhoFilmes,dtbaseCategoria,qtd_Categoria,tamanho_Categoria,idFilme,tipo_config);
                if (t == 1){
                    return 0;
                }
            }
        case 5:
            while (1){
                int t = menuFuncionarios(dtbasefuncionarios,qtd_Funcionarios,tamanho_Funcionarios,idFuncionarios);
                if (t == 1){
                    return 0;
                }
            }

        case 6:
            while (1){
                int t = menuLocadora(dtbaseLocadora,qtd_Locadora,tamanho_Locadora,idLocadora,tipo_config);
                if (t == 1){
                    return 0;
                }
            }
        default:
            return 0;
    }
}

int main() {
    int tipoConfig = 1; // 0- BIN 1 - TXT

    config config_System;

    bd_cat = malloc(tamanhoCategoria * sizeof(fCategoria));
    bd_filme = malloc(tamanhoFilme * sizeof (filme));
    bd_funcionarios = malloc(tamanhoFuncionarios * sizeof (funcionarios));
    bd_fornecedor = malloc(tamanhoFornecedor * sizeof (fornecedor));
    bd_locadora = malloc(tamanhoLocadora * sizeof(locadora));

    //Carrega os arquivos e Verifica se é primeira execursão
    carregaTodosDados(&tipoConfig,&config_System,
                      &bd_filme,&qtdFilmes,&tamanhoFilme,&idControleFilmes,
                      &bd_locadora,&qtdLocadora,&tamanhoLocadora,&idControleFornecedor);
    //Verifica se os arquivos existem caso contrario criar
    verifica_arquivos(tipoConfig);

    while (1){
        int v;
        v = menuprincipal(tipoConfig,
                          &bd_cat,&qtdCategoria,&tamanhoCategoria,
                          &bd_filme,&qtdFilmes,&tamanhoFilme,&idControleFilmes,
                          &bd_funcionarios,&qtdFuncionarios,&tamanhoFuncionarios,&idControleFuncionarios,
                          &bd_locadora,&qtdLocadora,&tamanhoLocadora,&idControleFornecedor);
        if (v == 1){
            break;
        }
    }
    free(bd_cat);
    free(bd_filme);
    free(bd_funcionarios);
    free(bd_locadora);
    bd_cat = NULL;
    bd_filme = NULL;
    bd_funcionarios = NULL;
    bd_locadora = NULL;
    return 0;
}

int carregaTodosDados(int *tipoConfig,config *config_system,
                      filme **dtbaseFilme, int *qtd_Filmes,int *tamanhoFilmes, int *idFilme,
                      locadora **dtbaseLocadora, int *qtd_Locadora,int *tamanho_Locadora,int *idLocadora){

    int newID = verifica_log(config_system,tipoConfig);
    //set_configuracao_Locadora(dtbaseLocadora,config_system->user,config_system->password,qtd_Locadora,tamanho_Locadora,newID);
    carregarDados_filme(dtbaseFilme,qtd_Filmes,tamanhoFilmes,idFilme,*tipoConfig);
    carregarDados_Locadora(dtbaseLocadora,qtd_Locadora,tamanho_Locadora,idLocadora,*tipoConfig);
}