#include <stdio.h>
#include  <stdlib.h>
#include <string.h>

#include "cabecalhos/locadora.h"
#include "cabecalhos/fornecedor.h"
//#include "cabecalhos/feedback.h"
#include "cabecalhos/dadosImEx.h"

/*Arrays Dinamicos*/

const char HORIZONTAL = (char)186;

fCategoria *bd_cat;
int qtdCategoria = 0, tamanhoCategoria = 1, idControleCategoria = 1;


filme  *bd_filme;
int qtdFilmes = 0, tamanhoFilme = 1, idControleFilmes = 1;

funcionarios *bd_funcionarios;
int qtdFuncionarios = 0, tamanhoFuncionarios = 1, idControleFuncionarios = 1;

locadora *bd_locadora;
int qtdLocadora = 0, tamanhoLocadora = 1, idControleLocadora = 1;

cliente *bd_cliente;
int qtdCliente = 0, tamanhoCliente = 1, idControleCliente = 1;

fornecedor *bd_fornecedor;
int qtdFornecedor = 0, tamanhoFornecedor = 1, idControleFornecedor = 1;

contaCliente *bd_CCliente = NULL;
int qtdCCliente = 0, tamanhoCCliente = 1, idControleCCliente = 1;

eFilme *bd_eFilme = NULL;
int tameFilme = 1,qtdeFilme = 0, idCOntroleeFIlme = 0;

int IdfuncionarioLogado = -1;
financeiro monetario;


int menuprincipal(int *tipo_config,financeiro *monetario_,config *config_system,
                  fCategoria **dtbaseCategoria, int *qtd_Categoria,int *tamanho_Categoria,int *idCategoria,
                  filme **dtbaseFilme, int *qtd_Filmes,int *tamanho_Filmes, int *idFilme,
                  funcionarios **dtbasefuncionarios, int *qtd_Funcionarios,int *tamanho_Funcionarios,int *idFuncionarios,int idFuncionarioLogado,
                  locadora **dtbaseLocadora, int *qtd_Locadora,int *tamanho_Locadora,int *idLocadora,
                  cliente **dtbaseCliente, int *qtd_Cliente,int *tamanho_Cliente,int *idCliente,
                  contaCliente **dtbaseCCliente, int *qtd_CCliente,int *tamanho_CCliente,int *idCCliente,
                  fornecedor **dtbaseFornecedor, int *qtd_Fornecedor,int *tamanho_Fornecedor,int *idFornecedor,
                  eFilme **dtBaseeFilme, int *tam_eFilme,int *qtd_eFilme,int *idEntradaFilme){



    int opc, erro = 0;
    lineBox(78,"MENU PRINCIPAL\0",1);
    printf("%c\t\t 1 - LOCACAO \t\t\t 2 - Clientes\t\t\t%c\n"
           "%c\t\t 3 - Categoria \t\t\t 4 - Filmes \t\t\t%c\n"
           "%c\t\t 5 - Funcionarios\t\t 6 - Fornecedor \t\t%c\n"
           "%c\t\t 7 - Locadora\t\t\t 8 - Exportar/Importar \t\t%c\n"
           "%c\t\t 9 - FeedBack\t\t\t 10 - Configuracoe/Ajuda \t%c\n"
           "%c\t\t 0 - Sair\t\t\t\t\t\t\t%c\n",HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL,HORIZONTAL);
    lineBox(78,"-\0",0);

    char opcTm[10];
    do {
        if (erro == 1) {
            printf(">> Parametro Invalido:\n");
        }
        printf(">> ");
        scanf("%s", opcTm);

        opc = strtol(opcTm,NULL,10);
        erro = 1;
    } while (opc < 0 || opc > 10);
    //system("cls");
    switch (opc) {
        case 0:
            printf(">> Exit \n");
            return 1;
        case 1:
            system("cls");

            while (1){
                int t = menuLocacao(dtbaseFilme,qtd_Filmes,tamanho_Filmes,idFilme,dtbaseCliente,*qtd_Cliente,dtbasefuncionarios,*qtd_Funcionarios,idFuncionarioLogado,
                                    dtbaseCCliente,qtd_CCliente,tamanho_CCliente,idCCliente,dtbaseCategoria,qtd_Categoria,tamanho_Categoria,idCategoria,
                                    dtbaseFornecedor,qtd_Fornecedor,tamanho_Fornecedor,idEntradaFilme,dtBaseeFilme,tam_eFilme,qtd_eFilme,monetario_,*tipo_config);
                (*dtbaseLocadora)[0].monetario = *monetario_;
                refazDados_Locadora(dtbaseLocadora,1,*tipo_config);
                if (t == 1){
                    break;
                }
            }
            break;
        case 2:
            while (1){
                int t = menuClientes(dtbaseCliente,qtd_Cliente,tamanho_Cliente,idCliente, *tipo_config);
                if (t == 1){
                    break;
                }
            }
            break;
        case 3:
            while (1){
                int t = menuCategoria(dtbaseCategoria,qtd_Categoria,tamanho_Categoria,idCategoria,*tipo_config);
                if (t == 1){
                    break;
                }
            }
            break;
        case 4:
            while (1){
                int t = menuFilme(dtbaseFilme,qtd_Filmes,tamanho_Filmes,dtbaseCategoria,qtd_Categoria,tamanho_Categoria,idCategoria,idFilme, *tipo_config);
                refazDados_Categoria(dtbaseCategoria,*qtd_Categoria,*tipo_config);
                if (t == 1){
                    break;
                }
            }
            break;
        case 5:
            while (1){
                int t = menuFuncionarios(dtbasefuncionarios,qtd_Funcionarios,tamanho_Funcionarios,idFuncionarios, *tipo_config);
                if (t == 1){
                    break;
                }
            }
            break;

        case 6:
            while (1){
                int t = menuFornecedor(dtbaseFornecedor, qtd_Fornecedor, tamanho_Fornecedor, idFornecedor, *tipo_config);
                if (t == 1){
                    break;
                }
            }
            break;
        case 7:
            while (1){
                int t = menuLocadora(dtbaseLocadora,qtd_Locadora,tamanho_Locadora,idLocadora, *tipo_config);
                if (t == 1){
                    break;
                }
            }
            break;
        case 8:
            while (1){
                while (1){
                    int t = menuImportacaoExportcao(dtbaseCliente,qtd_Cliente,tamanho_Cliente,dtbaseFilme,qtd_Filmes,tamanho_Filmes,dtbaseLocadora,qtd_Locadora,tamanho_Locadora,dtbaseCategoria,qtd_Categoria,tamanho_Categoria,dtbaseFornecedor,qtd_Fornecedor,tamanho_Fornecedor,dtbasefuncionarios,qtd_Funcionarios,tamanho_Funcionarios,dtbaseCCliente,qtd_CCliente,tamanho_CCliente,dtBaseeFilme,qtd_eFilme,tam_eFilme);
                    if (t == 1){
                        break;
                    }
                }
                break;
            }
            break;
        case 9:
            while (1){
                int t = menuFeedback(dtbaseCliente, *qtd_Cliente, dtbaseFilme, *qtd_Filmes, dtBaseeFilme, *qtd_eFilme,
                                     dtbaseCategoria, *qtd_Categoria,dtbasefuncionarios,*qtd_Funcionarios, dtbaseCCliente, *qtd_CCliente);

                if (t == 1) {
                    break;
                }
            }
            break;
        case 10:
            //printf("Menu Configuração e Ajuda");
            system("cls");
            menuConfiguracao(config_system,tipo_config);
            //return 0;
            break;
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
                      fornecedor **dtBaseFornecedor, int *qtd_Fornecedor, int *tamanho_Fornecedor, int *idFornecedor,
                      contaCliente **dtbaseCCliente, int *qtd_CCliente,int *tamanho_CCliente,int *idCCliente,
                      eFilme **dtBase_efilme, int *qtd_efilme, int *tamanho_efilme, int *idefilme,
                      funcionarios **dtBaseFuncionario, int *qtd_Funcionario, int *tamanho_Funcionario, int *idFuncionario,int *idFuncionarioLogado){

    int pExecute = verifica_log(config_system,tipoConfig);
    carregarDados_filme(dtbaseFilme, qtd_Filmes, tamanhoFilmes, idFilme, *tipoConfig);
    carregarDados_Locadora(dtbaseLocadora,qtd_Locadora,tamanho_Locadora,idLocadora,*tipoConfig);

    monetario = (*dtbaseLocadora)[0].monetario ;

    printf("%d %d",*qtd_Categoria,*tamanho_Categoria);
    carregarDados_Categoria(dtbaseCategoria, qtd_Categoria,tamanho_Categoria,idCategoria,*tipoConfig);
    carregarDadosClientes(dtBaseCliente, qtd_Cliente,tamanho_Cliente,idCliente,*tipoConfig);
    carregarDadosFornecedores(dtBaseFornecedor, qtd_Fornecedor, tamanho_Fornecedor, idFornecedor, *tipoConfig);
    carregarDadosFuncionarios(dtBaseFuncionario, qtd_Funcionario, tamanho_Funcionario, idFuncionario, *tipoConfig);
    carregarDados_Efilme(dtBase_efilme,qtd_efilme,tamanho_efilme,dtBaseFornecedor,qtdFuncionarios,*tipoConfig);
    carregarDados_CClientes(dtbaseCCliente,qtd_CCliente,tamanho_CCliente,idCCliente,dtBaseCliente,*qtd_Cliente,dtbaseFilme,*qtd_Filmes,*tipoConfig);
    system("cls");
    char nConfig[10];
    printf("Tipo Configuracao: %d ",*tipoConfig);
    if (*tipoConfig == 1){
        strcpy(nConfig,".txt\0");
    }else if (*tipoConfig == 0){
        strcpy(nConfig,".bin\0");
    }else{
        strcpy(nConfig,"Memoria\0");
    }
    if (*qtd_Locadora == 0){

        line(100,"Informacoes da Locadora\0");
        printf("\nOs dados estao sendo salvos no formato: %s\ne pode ser alterado no Menu de configuracao\n",nConfig);
        printf("\nPrecisamos de algumas infomacoes para inicializar o Sistema\n");
        line(100,"-\0");

        locadora newLocadora = criarLocadora(idLocadora);
        inserirLocadora(dtbaseLocadora,newLocadora,qtd_Locadora,tamanho_Locadora);
        saveLocadora(newLocadora,*tipoConfig);

        //Passar os parametros de Autentificação(Administrador)  para o arquivo de LOG
        //Id 0 - Retorno de ADM
        strcpy(config_system->user,newLocadora.user);
        strcpy(config_system->password,newLocadora.password);
        refazLog(config_system);
    }
    if (pExecute == 0){
        adm set;
        set.id = 0;
        strcpy(set.user,config_system->user);
        strcpy(set.password,config_system->password);


        //*idFuncionarioLogado = autentificacaoSystem(&set,&bd_funcionarios,*qtd_Funcionario);
        printf("ID: %d",*idFuncionarioLogado);
        *idFuncionarioLogado = 1;

        system("cls");
    }

    return 0;
}

int main() {
    int tipoConfig; // 0- BIN 1 - TXT

//    lineBox(100, "TEST\0",1);
//    lineBox(100, "a\0",0);
//    system("pause");
//    exit(1);

    config config_System;

    bd_cat = malloc(tamanhoCategoria * sizeof(fCategoria));
    bd_filme = malloc(tamanhoFilme * sizeof (filme));
    bd_funcionarios = malloc(tamanhoFuncionarios * sizeof (funcionarios));
    bd_cliente = malloc(tamanhoCliente * sizeof (cliente));
    bd_locadora = malloc(tamanhoLocadora * sizeof(locadora));
    bd_fornecedor = malloc(tamanhoFornecedor * sizeof(fornecedor));
    bd_CCliente = (contaCliente *)malloc(tamanhoCCliente * sizeof(contaCliente));

    bd_eFilme = calloc(tameFilme,sizeof(eFilme));

    //Verifica se os arquivos existem caso contrario criar
    //verifica_arquivos(tipoConfig);
    //Carrega os arquivos e Verifica se é primeira execursão
    carregaTodosDados(&tipoConfig,&config_System,
                      &bd_filme,&qtdFilmes,&tamanhoFilme,&idControleFilmes,
                      &bd_locadora,&qtdLocadora,&tamanhoLocadora,&idControleLocadora,
                      &bd_cat,&qtdCategoria,&tamanhoCategoria,&idControleCategoria,
                      &bd_cliente, &qtdCliente, &tamanhoCliente, &idControleCliente,
                      &bd_fornecedor, &qtdFornecedor, &tamanhoFornecedor, &idControleFornecedor,
                      &bd_CCliente,&qtdCCliente,&tamanhoCCliente,&idControleCCliente,
                      &bd_eFilme,&qtdeFilme,&tameFilme,&idCOntroleeFIlme,
                      &bd_funcionarios, &qtdFuncionarios, &tamanhoFuncionarios, &idControleFuncionarios,&IdfuncionarioLogado);


    while (1){
        int v;
        v = menuprincipal(&tipoConfig,&monetario,&config_System,
                          &bd_cat,&qtdCategoria,&tamanhoCategoria,&idControleCategoria,
                          &bd_filme,&qtdFilmes,&tamanhoFilme,&idControleFilmes,
                          &bd_funcionarios,&qtdFuncionarios,&tamanhoFuncionarios,&idControleFuncionarios,IdfuncionarioLogado,
                          &bd_locadora,&qtdLocadora,&tamanhoLocadora,&idControleLocadora,
                          &bd_cliente,&qtdCliente,&tamanhoCliente,&idControleCliente,
                          &bd_CCliente,&qtdCCliente,&tamanhoCCliente,&idControleCCliente,
                          &bd_fornecedor,&qtdFornecedor,&tamanhoFornecedor,&idControleFornecedor,
                          &bd_eFilme,&tameFilme,&qtdeFilme,&idCOntroleeFIlme);
        if (v == 1){
            break;
        }
    }
    free(bd_cat);
    free(bd_filme);
    free(bd_funcionarios);
    free(bd_cliente);
    free(bd_locadora);
    free(bd_fornecedor);
    free(bd_CCliente);
    bd_cat = NULL;
    bd_filme = NULL;
    bd_funcionarios = NULL;
    bd_locadora = NULL;
    bd_cliente = NULL;
    bd_CCliente = NULL;
    return 0;
}