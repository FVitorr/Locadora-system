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
               "\n\t7 - Exportar Locacao Filme  \n\t8 - Exportar Compra de Filme\n;");
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

void exportDadoslocadora(FILE *arq, locadora **dtbaselocadora, int qtdlocadora){
    if (arq == NULL){
        printf("\nErro na exportacao de dadps cliente\n\n");
        exit(1);
    }

    fprintf(arq,"\t<locadora>");
    for (int i = 0; i < qtdlocadora; i++)
    {
        fprintf(arq,"\n\t\t<registro>"
                    "\n\t\t\t<id>%d</id>"
                    "\n\t\t\t<nome_fantasia>%s</nome_fantasia>"
                    "\n\t\t\t<razaoSocial>%s</razaoSocial>"
                    "\n\t\t\t<inscricaoEstadual>%s</inscricaoEstadual>"
                    "\n\t\t\t<cnpj>%s</cnpj>"
                    "\n\t\t\t<endereco>%s, %d, %s, %s, %s </endereco>"
                    "\n\t\t\t<telefone>%s</telefone>"
                    "\n\t\t\t<email>%s</email>"
                    "\n\t\t\t<nome_responsavel>%s</nome_responsavel>"
                    "\n\t\t\t<telefone_responsavel>%s</telefone_responsavel>"
                    "\n\t\t\t<financeiro>%f,%f,%f</financeiro>"
                    "\n\t\t\t<user>%s</user>"
                    "\n\t\t\t<password>%s</password>"
                    "\n\t\t</registro>",(*dtbaselocadora)[i].id,
                (*dtbaselocadora)[i].nomeFantasia,
                (*dtbaselocadora)[i].razaoSocial,
                (*dtbaselocadora)[i].inscricaoEstadual,
                (*dtbaselocadora)[i].cnpj,
                (*dtbaselocadora)[i].endereco.rua,
                (*dtbaselocadora)[i].endereco.numero,
                (*dtbaselocadora)[i].endereco.bairro,
                (*dtbaselocadora)[i].endereco.cidade,
                (*dtbaselocadora)[i].endereco.estado,
                (*dtbaselocadora)[i].telefone,
                (*dtbaselocadora)[i].email,
                (*dtbaselocadora)[i].nomeResponsavel,
                (*dtbaselocadora)[i].telefoneResponsavel,
                (*dtbaselocadora)[i].monetario.caixa,
                (*dtbaselocadora)[i].monetario.despesas,
                (*dtbaselocadora)[i].monetario.contasReceber,
                (*dtbaselocadora)[i].user,
                (*dtbaselocadora)[i].password
        );
    }
    fprintf(arq,"\n\t</locadora>\n");
}

void exportDadosCliente(FILE *arq, cliente **dtbaseCliente, int qtdcliente){
    if (arq == NULL){
        printf("\nErro na exportacao de dadps cliente\n\n");
        exit(1);
    }

    fprintf(arq,"\t<cliente>\n");
    for (int i = 0; i < qtdcliente; i++)
    {
        fprintf(arq,"\t\t<registro>"
                "\n\t\t\t<id>%d</id>"
                "\n\t\t\t<nome>%s</nome>"
                "\n\t\t\t<endereco>%s, %d, %s, %s, %s </endereco>"
                "\n\t\t\t<cpf>%s</cpf>"
                "\n\t\t\t<telefone>%s</telefone>"
                "\n\t\t\t<email>%s</email>"
                "\n\t\t\t<sexo>%s</sexo>"
                "\n\t\t\t<est_civil>%s</est_civil>"
                "\n\t\t\t<dtNascimento>%s</dtNascimento>"
                "\n\t\t</registro>\n\t",(*dtbaseCliente)[i].id,
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

void exportDadosFilme(FILE *arq, filme **dtbaseFilme, int qtdfilme){
    if (arq == NULL){
        printf("\nErro na exportacao de dadps cliente\n\n");
        exit(1);
    }

    fprintf(arq,"\t<filmes>");
    for (int i = 0; i < qtdfilme; i++)
    {
        fprintf(arq,"\n\t\t<registro>"
                    "\n\t\t\t<id>%d</id>"
                    "\n\t\t\t<descricao>%s</descricao>"
                    "\n\t\t\t<quantidade>%d</quantidade>"
                    "\n\t\t\t<c_categoria>%d</c_categoria>"
                    "\n\t\t\t<lingua>%s</lingua>"
                    "\n\t\t\t<qtdEmprestado>%d</qtdEmprestado>"
                    "\n\t\t</registro>",(*dtbaseFilme)[i].codigo,
                (*dtbaseFilme)[i].nome,
                (*dtbaseFilme)[i].qtd,
                (*dtbaseFilme)[i].c_categoria,
                (*dtbaseFilme)[i].lingua,
                (*dtbaseFilme)[i].qtdEmprestado
        );
    }
    fprintf(arq,"\n\t</filmes>\n");
}

void exportDadosCategoria(FILE *arq, fCategoria **dtbasecategoria, int qtdcategoria){
    if (arq == NULL){
        printf("\nErro na exportacao de dadps cliente\n\n");
        exit(1);
    }

    fprintf(arq,"\t<categoria>");
    for (int i = 0; i < qtdcategoria; i++)
    {
        fprintf(arq,"\n\t\t<registro>"
                    "\n\t\t\t<id>%d</id>"
                    "\n\t\t\t<descricao>%s</descricao>"
                    "\n\t\t\t<vAlocacao>%f</vAlocacao>"
                    "\n\t\t\t<ativo>%d</ativo>"
                    ,(*dtbasecategoria)[i].codigo,
                (*dtbasecategoria)[i].descricao,
                (*dtbasecategoria)[i].vAlocacao,
                (*dtbasecategoria)[i].ativo
        );
    }
    fprintf(arq,"\n\t</categoria>\n");
}

void exportDadosFornecedor(FILE *arq, fornecedor **dtbasefornecedor, int qtdFornecedor){
    if (arq == NULL){
        printf("\nErro na exportacao de dadps cliente\n\n");
        exit(1);
    }

    fprintf(arq,"\t<cliente>\n");
    for (int i = 0; i < qtdFornecedor; i++)
    {
        fprintf(arq,"\t\t<registro>"
                    "\n\t\t\t<id>%d</id>"
                    "\n\t\t\t<nomeFantasia>%s</nomeFantasia>"
                    "\n\t\t\t<razaoSocial>%s</razaoSocial>"
                    "\n\t\t\t<inscricaoEstadual>%s</inscricaoEstadual>"
                    "\n\t\t\t<cnpj>%s</cnpj>"
                    "\n\t\t\t<endereco>%s, %d, %s, %s, %s </endereco>"
                    "\n\t\t\t<telefone>%s</telefone>"
                    "\n\t\t\t<email>%s</email>"
                    "\n\t\t</registro>\n\t",(*dtbasefornecedor)[i].id,
                (*dtbasefornecedor)[i].nomeFantasia,
                (*dtbasefornecedor)[i].razaoSocial,
                (*dtbasefornecedor)[i].inscricaoEstadual,
                (*dtbasefornecedor)[i].cnpj,
                (*dtbasefornecedor)[i].endereco.rua,
                (*dtbasefornecedor)[i].endereco.numero,
                (*dtbasefornecedor)[i].endereco.bairro,
                (*dtbasefornecedor)[i].endereco.cidade,
                (*dtbasefornecedor)[i].endereco.estado,
                (*dtbasefornecedor)[i].telefone,
                (*dtbasefornecedor)[i].email
        );
    }
    fprintf(arq,"</cliente>\n");
}

void exportDadosFuncionario(FILE *arq, funcionarios **dtbasefuncionarios, int qtdfuncionarios){
    if (arq == NULL){
        printf("\nErro na exportacao de dadps cliente\n\n");
        exit(1);
    }

    fprintf(arq,"\t<cliente>\n");
    for (int i = 0; i < qtdfuncionarios; i++)
    {
        fprintf(arq,"\t\t<registro>"
                    "\n\t\t\t<id>%d</id>"
                    "\n\t\t\t<nome>%s</nome>"
                    "\n\t\t\t<cargo>%s</cargo>"
                    "\n\t\t\t<endereco>%s, %d, %s, %s, %s </endereco>"
                    "\n\t\t\t<telefone>%s</telefone>"
                    "\n\t\t\t<email>%s</email>"
                    "\n\t\t\t<user>%s</user>"
                    "\n\t\t\t<password>%s</password>"
                    "\n\t\t</registro>\n\t",(*dtbasefuncionarios)[i].codigo,
                (*dtbasefuncionarios)[i].nome,
                (*dtbasefuncionarios)[i].cargo,
                (*dtbasefuncionarios)[i].endereco.rua,
                (*dtbasefuncionarios)[i].endereco.numero,
                (*dtbasefuncionarios)[i].endereco.bairro,
                (*dtbasefuncionarios)[i].endereco.cidade,
                (*dtbasefuncionarios)[i].endereco.estado,
                (*dtbasefuncionarios)[i].telefone,
                (*dtbasefuncionarios)[i].email,
                (*dtbasefuncionarios)[i].login.user,
                (*dtbasefuncionarios)[i].login.password

        );
    }
    fprintf(arq,"</cliente>\n");
}

void exportDadosLocacao(FILE *arq, contaCliente **dtbaseCCliente, int qtdCCliente){
    if (arq == NULL){
        printf("\nErro na exportacao de dadps cliente\n\n");
        exit(1);
    }

    fprintf(arq,"\t<locacao>\n");
    for (int i = 0; i < qtdCCliente; i++)
    {
        fprintf(arq,"\t\t<registro>"
                    "\n\t\t\t<id>%d</id>"
                    "\n\t\t\t<idCliente>%d</idCliente>"
                    "\n\t\t\t<nome>%s</nome>"
                    "\n\t\t\t<valorDeve>%.2f</valorDeve>"
                    "\n\t\t\t<valorPago>%.2f</valorPago>"
                    "\n\t\t\t<tamLocados>%d</tamLocados>"
                    "\n\t\t\t<IDlocado>%d</IDlocado>",(*dtbaseCCliente)[i].ID,
                (*dtbaseCCliente)[i].idCliente,
                (*dtbaseCCliente)[i].Nome,
                (*dtbaseCCliente)[i].valorDeve,
                (*dtbaseCCliente)[i].valorDeve,
                (*dtbaseCCliente)[i].tamLocados,
                (*dtbaseCCliente)[i].IDlocado);

        for (int j = 0; j < (*dtbaseCCliente)[i].tamLocados - 1; j++)
        {
            fprintf(arq,"\n\t\t\t<locados>"
                        "\n\t\t\t\t<id>%d</id>"
                        "\n\t\t\t\t<idFuncionario>%d</idFuncionario>"
                        "\n\t\t\t\t<qtdFilme>%d</qtdFilme>"
                        "\n\t\t\t\t<valorTotal>%.2f</valorTotal>"
                        "\n\t\t\t\t<valorDeve>%.2f</valorDeve>"
                        "\n\t\t\t\t<valorEntrada>%.2f</valorEntrada>"
                        "\n\t\t\t\t<tipo_pagamento>%d</tipo_pagamento>"
                        "\n\t\t\t\t<dtPagamento>%d/%d/%d</dtPagamento>"
                        "\n\t\t\t\t<qtdParcelas>%d</qtdParcelas>"
                        "\n\t\t\t\t<parcelasPagas>%d</parcelasPagas>"
                        "\n\t\t\t\t<TDdevolvido>%d</TDdevolvido>"
                        "\n\t\t\t\t<ultimoIDOperacao>%d</ultimoIDOperacao>"

                        "\n\t\t\t</locados>\n\t",(*dtbaseCCliente)[i].dEmprestimo[j].ID,
                    (*dtbaseCCliente)[i].dEmprestimo[j].IdFuncionario,
                    (*dtbaseCCliente)[i].dEmprestimo[j].qtdFilme,
                    (*dtbaseCCliente)[i].dEmprestimo[j].valorTotal,
                    (*dtbaseCCliente)[i].dEmprestimo[j].valordeve,
                    (*dtbaseCCliente)[i].dEmprestimo[j].valorEntrada,
                    (*dtbaseCCliente)[i].dEmprestimo[j].tipoPagamento,
                    (*dtbaseCCliente)[i].dEmprestimo[j].Dtpagamento.dia,
                    (*dtbaseCCliente)[i].dEmprestimo[j].Dtpagamento.mes,
                    (*dtbaseCCliente)[i].dEmprestimo[j].Dtpagamento.ano,
                    (*dtbaseCCliente)[i].dEmprestimo[j].qtdParcelas,
                    (*dtbaseCCliente)[i].dEmprestimo[j].parcelasPagas,
                    (*dtbaseCCliente)[i].dEmprestimo[j].TDdevolvido,
                    (*dtbaseCCliente)[i].dEmprestimo[j].ultimoIDOperacao
                    );
        }
    }
    fprintf(arq,"</locacao>\n");
}


void exportarDados(exportcamp camposExport, char *namepath, cliente **dtbaseCliente, int qtdCliente,filme **dtbaseFilme, int qtdfilme,
                   locadora **dtbaselocadora, int qtdlocadora){
    FILE *arq;

    arq = fopen(namepath,"w");

    if (arq == NULL){
        printf("[!] Erro na Exportacao de Dados");
        exit(1);
    }

    fprintf(arq,"<dados>\n");

    if (camposExport.locadora == 1){
        exportDadoslocadora(arq,dtbaselocadora,qtdlocadora);
    }

    if (camposExport.cliente == 1){
        exportDadosCliente(arq,dtbaseCliente,qtdCliente);
    }

    if (camposExport.filme == 1){
        exportDadosFilme(arq,dtbaseFilme,qtdfilme);
    }

    fprintf(arq,"</dados>");

    fclose(arq);
    arq = NULL;
}





int menuImportacaoExportcao(cliente **dtbaseCliente, int qtdcliente,filme **dtbaseFilme, int qtdfilme,
                            locadora **dtbaselocadora, int qtdlocadora){
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
            }
            exportarDados(exportcamp1,"test.xml",dtbaseCliente,qtdcliente,dtbaseFilme,qtdfilme,dtbaselocadora,qtdlocadora);
            system("cls");
            return 1; // Sair
        }

    }
    return 0;
}