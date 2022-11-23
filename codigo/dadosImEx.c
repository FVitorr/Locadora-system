//
// Created by Ghost on 22/11/2022.
//

#include "dadosImEx.h"
#include <stdlib.h>
#include <stdint.h>
#include <io.h>


void refazexportCamp(exportcamp *exportcamp1, int value){ //0 e 1
    exportcamp1->locadora = value;
    exportcamp1->cliente = value;
    exportcamp1->filme = value;
    exportcamp1->categoria = value;
    exportcamp1->fornecedor = value;
    exportcamp1->funcionario = value;
    exportcamp1->locacao_filme = value;
    exportcamp1->compras_filme = value;
}



int menuexport(exportcamp *exportcampos){
    system("cls");
    setbuf(stdin,NULL);
    lineBox(70,"EXPORTACAO DE DADOS\0",1);
    printf("\tDeseja exportar ?\n\n");
    printf("\t0 - Sair \n\t1 - Tabelas Especificas de Dados  \n\t2 - TODAS as tabelas de dados\n");
    lineBox(70,"-\0",0);

    int erro = 0, opc;
    char temEscolha[4];

    do
    {
        if (erro == 1)
        {
            printf(">> Parametro Invalido\n");
        }
        //Tratamento de entrada
        printf(">>");
        scanf("%s", temEscolha); //Permite a entrada de qualquer caracter
        setbuf(stdin,NULL);

        opc = strtol(temEscolha,NULL,10); //Procura na entrada um numero na base 10
        erro = 1;
    } while (opc < 0 || opc > 2);

    if (opc == 0){ //Sair
        system("cls");
        return 0; // SAIR
    }
    else if (opc == 1)
    {
        lineBox(50,"Tabela DE DADOS\0",1);
        printf("\tDeseja exportar quais tabelas ?\n\n");
        printf("\t0 - Sair \n\t1 - Exportar Locadoras  \n\t2 - Exportar Clientes \n\t3 - Exportar Filmes"
               "\n\t4 - Exportar Categorias\n\t5 - Exportar Fornecedores\n\t6 - Exportar Funcionarios"
               "\n\t7 - Exportar Locacao Filme  \n\t8 - Exportar Compra de Filme\");");
        lineBox(50,"-\0",0);


        char opcexport[5];
        int opcEx;
        while (1){
            printf("\n>>");
            scanf("%s",opcexport);

            opcEx = strtol(opcexport,NULL,10);

            if (opcEx == 0){
                return 1;
            }

            switch (opcEx) {
                case 1:
                    exportcampos->locadora = 1;
                    break;
                case 2:
                    exportcampos->cliente = 1;
                    break;
                case 3:
                    exportcampos->filme = 1;
                    break;
                case 4:
                    exportcampos->categoria = 1;
                    break;
                case 5:
                    exportcampos->fornecedor = 1;
                    break;
                case 6:
                    exportcampos->funcionario = 1;
                    break;
                case 7:
                    exportcampos->locacao_filme = 1;
                    break;
                case 8:
                    exportcampos->compras_filme = 1;
                    break;
                default:
                    printf("Opcao Invalida");
                    break;
            }
        }
    }
    else if (opc == 2)
    {
        //2 - TODAS as tabelas de dados
        refazexportCamp(exportcampos,1);
        return 2; ////2 - TODAS as tabelas de dados
    }
    return 0;
}


void exportDadosCliente(FILE *arq, cliente **dtbaseCliente, int qtdcliente){
    if (arq == NULL){
        printf("\nErro na exportacao de dadps cliente\n\n");
        exit(1);
    }

    fprintf(arq,"<cliente>\n");
    for (int i = 0; i < qtdcliente; i++)
    {
        fprintf(arq,"\t<registro>"
                "\n\t\t<id>%d</id>"
                "\n\t\t<nome>%s</nome>"
                "\n\t\t<endereco>%s, %d, %s, %s, %s </endereco>"
                "\n\t\t<cpf>%s</cpf>"
                "\n\t\t<telefone>%s</telefone>"
                "\n\t\t<email>%s</email>"
                "\n\t\t<sexo>%s</sexo>"
                "\n\t\t<est_civil>%s</est_civil>"
                "\n\t\t<dtNascimento>%s</dtNascimento>"
                "\n\t</registro>",(*dtbaseCliente)[i].id,
                (*dtbaseCliente)[i].nome,
                (*dtbaseCliente)[i].endereco.rua,
                (*dtbaseCliente)[i].endereco.numero,
                (*dtbaseCliente)[i].endereco.bairro,
                (*dtbaseCliente)[i].endereco.cidade,
                (*dtbaseCliente)[i].endereco.estado,
                (*dtbaseCliente)[i].cpf,
                (*dtbaseCliente)[i].telefone,
                (*dtbaseCliente)[i].email,
                (*dtbaseCliente)[i].sexo,
                (*dtbaseCliente)[i].estadoCivil,
                (*dtbaseCliente)[i].dataNascimento
                );
    }
    fprintf(arq,"</cliente>\n");
}

void exportarDados(exportcamp camposExport, char *namepath, cliente **dtbaseCliente, int qtdCliente){
    FILE *arq;

    arq = fopen(namepath,"w");

    if (arq == NULL){
        printf("[!] Erro na Exportacao de Dados");
        exit(1);
    }

    fprintf(arq,"<dados>");
    exportDadosCliente(arq,dtbaseCliente,qtdCliente);
    fprintf(arq,"</dados>");



}





int menuImportacaoExportcao(cliente **dtbaseCliente, int qtdcliente){
    int erro = 0, opc;
    char temEscolha[4];

    system("cls");
    setbuf(stdin,NULL);
    lineBox(70,"MENU EXPORTACAO / IMPORTA\0",1);
    printf("\tDigite a opcao referente a operacao que deseja executar\n\n");
    printf("\t0 - Sair \n\t1 - Importar \n\t2 - Exportar\n");
    lineBox(70,"-\0",0);

    do
    {
        if (erro == 1)
        {
            printf(">> Parametro Invalido\n");
        }
        //Tratamento de entrada
        printf(">>");
        scanf("%s", temEscolha); //Permite a entrada de qualquer caracter
        setbuf(stdin,NULL);

        opc = strtol(temEscolha,NULL,10); //Procura na entrada um numero na base 10
        erro = 1;
    } while (opc < 0 || opc > 2);

    if (opc == 0){ //Sair
        system("cls");
        return 1; // Sair
    }
    else if (opc == 1)
    {
        //IMPORTAR
    }
    else if (opc == 2)
    {
        //EXPORTAR DADOS
        exportcamp exportcamp1;
        refazexportCamp(&exportcamp1,0);
        while (1){
            int t = menuexport(&exportcamp1);
            if (t == 0){
                break;
            } else if (t == 1){ // Tabelas Especificas
                //exportDadosCliente(dtbaseCliente,qtdcliente,);
            }else if (t == 2){ // Todas as tabelas de dados

            }
        }

    }
    return 0;
}