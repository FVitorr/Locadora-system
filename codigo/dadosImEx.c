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

int menuImport(exportcamp *importcampos){
    system("cls");
    setbuf(stdin,NULL);
    lineBox(70,"IMPORTACAO DE DADOS\0",1);
    printf("\tDeseja Importar ?\n\n");
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
        printf("\tDeseja Importar quais tabelas ?\n\n");
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
                    importcampos->locadora = 1;
                    break;
                case 2:
                    importcampos->cliente = 1;
                    break;
                case 3:
                    importcampos->filme = 1;
                    break;
                case 4:
                    importcampos->categoria = 1;
                    break;
                case 5:
                    importcampos->fornecedor = 1;
                    break;
                case 6:
                    importcampos->funcionario = 1;
                    break;
                case 7:
                    importcampos->locacao_filme = 1;
                    break;
                case 8:
                    importcampos->compras_filme = 1;
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
        refazexportCamp(importcampos,1);
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
                    "\n\t\t\t<nomeFantasia>%s</nomeFantasia>"
                    "\n\t\t\t<razaoSocial>%s</razaoSocial>"
                    "\n\t\t\t<inscricaoEstadual>%s</inscricaoEstadual>"
                    "\n\t\t\t<cnpj>%s</cnpj>"
                    "\n\t\t\t<endereco>%s, %d, %s, %s, %s </endereco>"
                    "\n\t\t\t<telefone>%s</telefone>"
                    "\n\t\t\t<email>%s</email>"
                    "\n\t\t\t<nomeResponsavel>%s</nomeResponsavel>"
                    "\n\t\t\t<telefoneResponsavel>%s</telefoneResponsavel>"
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

void importa_locadora(FILE *arq, locadora **dtbaselocadora, int qtdlocadora){
    int achou = 0;
    //char *linha = calloc(200,sizeof (char));
    char linha[200];
    resetstring(linha);
    if (arq == NULL) {
        return;
    }

    int line = 0;
    while ((achou == 0) && (!feof(arq))) {
        fgets(linha, 200, arq);
        if (strcmp(linha, "\t<locadora>\n") == 0) {
            achou = 1;
            break;
        }
        line++;
    }

    if (achou == 0) {
        printf("Dados de locadora nao encontrado");
        return;
    }

    char *tok;
    locadora newLocadora;

    int lineRead = 0;
    while ((strcmp(linha, "\t</locadora>\n") != 0)  || (!feof(arq) || strstr(linha,"</locadora>") != NULL)){
        if (lineRead >= line) {
            fgets(linha, 200, arq); //pega <registro>
            if (strcmp(linha, "\t</locadora>\n") == 0 || strstr(linha,"</locadora>") != NULL) {
                break;
            }

            fgets(linha, 200, arq); //pega <id>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            newLocadora.id = strtol(tok,NULL,10);

            fgets(linha, 200, arq); //pega <nomeFantasia>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(newLocadora.nomeFantasia,tok);

            fgets(linha, 200, arq); //pega <razaoSocial>
            //printf("%s",linha);
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(newLocadora.razaoSocial,tok);

            fgets(linha, 200, arq); //pega <inscricaoEstadual>
            //printf("%s",linha);
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(newLocadora.inscricaoEstadual,tok);

            fgets(linha, 200, arq); //pega <cnpj>
            //printf("%s",linha);
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(newLocadora.cnpj,tok);

            fgets(linha, 200, arq); //pega <endereco>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, ",</>");
            strcpy(newLocadora.endereco.rua,tok);
            tok = strtok(NULL, ",</>");
            newLocadora.endereco.numero = strtol(tok,NULL,10);
            tok = strtok(NULL, ",</>");
            strcpy(newLocadora.endereco.bairro,tok);
            tok = strtok(NULL, ",</>");
            strcpy(newLocadora.endereco.cidade,tok);
            tok = strtok(NULL, ",</>");
            strcpy(newLocadora.endereco.estado,tok);


            fgets(linha, 200, arq); //pega <telefone>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(newLocadora.telefone,tok);

            fgets(linha, 200, arq); //pega <email>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(newLocadora.email,tok);

            fgets(linha, 200, arq); //pega <nomeResponsavel>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(newLocadora.nomeResponsavel,tok);

            fgets(linha, 200, arq); //pega <telefoneResponsavel>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(newLocadora.telefoneResponsavel,tok);

            fgets(linha, 200, arq); //pega <financeiro>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, ",</>");
            newLocadora.monetario.caixa = strtof(tok,NULL);
            tok = strtok(NULL, ",</>");
            newLocadora.monetario.despesas = strtof(tok,NULL);
            tok = strtok(NULL, ",</>");
            newLocadora.monetario.contasReceber = strtof(tok,NULL);

            fgets(linha, 200, arq); //pega <user>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(newLocadora.user,tok);

            fgets(linha, 200, arq); //pega <password>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            //strcpy(newLocadora.password,tok);

            newLocadora.password = retorna_password_file(tok);

            fgets(linha, 200, arq); //pega </registro>

            printf(" %d %s %s %s %s %s %d %s %s %s %s %s %s %s %f %f %f %s %s",newLocadora.id,newLocadora.nomeFantasia,newLocadora.razaoSocial,
                   newLocadora.inscricaoEstadual,newLocadora.cnpj,newLocadora.endereco.rua,newLocadora.endereco.numero
                    ,newLocadora.endereco.bairro,newLocadora.endereco.cidade,newLocadora.endereco.estado,
                    newLocadora.telefone,newLocadora.email,newLocadora.nomeResponsavel,newLocadora.telefoneResponsavel,newLocadora.monetario.caixa,newLocadora.monetario.despesas
                    ,newLocadora.monetario.contasReceber,newLocadora.user,newLocadora.password);

        }
        lineRead++;
    }
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

void importa_Cliente(FILE *arq, cliente **dtbaseCliente, int qtdcliente) {
    int achou = 0;
    char linha[150];
    if (arq == NULL) {
        return;
    }

    int lineinit = 0;
    while ((achou == 0) && (!feof(arq))) {
        fgets(linha, 150, arq);
        if (strcmp(linha, "\t<cliente>\n") == 0) {
            achou = 1;
            break;
        }
        lineinit++;
    }

    if (achou == 0) {
        printf("Dados de Cliente nao encontrado");
        return;
    }

    char *tok;
    cliente novoCliente;

    int line = 0 ;
    while (strcmp(linha, "</cliente>\n") != 0 || (!feof(arq) || strstr(linha,"</cliente>") != NULL)){
        if (line >= lineinit) {
            fgets(linha, 150, arq);//pega <registro>
            if (strcmp(linha, "</cliente>\n") == 0 || strstr(linha,"</cliente>") != NULL) { //Verifica se a struct acabou
                break;
            }
            fgets(linha, 150, arq); //pega <id>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            novoCliente.id = strtol(tok,NULL,10);

            fgets(linha, 150, arq); //pega <nome>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(novoCliente.nome, tok);

            fgets(linha, 200, arq); //pega <endereco>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, ",</>");
            strcpy(novoCliente.endereco.rua,tok);
            tok = strtok(NULL, ",</>");
            novoCliente.endereco.numero = strtol(tok,NULL,10);
            tok = strtok(NULL, ",</>");
            strcpy(novoCliente.endereco.bairro,tok);
            tok = strtok(NULL, ",</>");
            strcpy(novoCliente.endereco.cidade,tok);
            tok = strtok(NULL, ",</>");
            strcpy(novoCliente.endereco.estado,tok);

            fgets(linha, 150, arq); //pega <cpf>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(novoCliente.cpf,tok);

            fgets(linha, 150, arq); //pega <telefone>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(novoCliente.telefone,tok);

            fgets(linha, 150, arq); //pega <email>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(novoCliente.email,tok);

            fgets(linha, 150, arq); //pega <sexo>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(novoCliente.sexo,tok);

            fgets(linha, 150, arq); //pega <est_civil>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(novoCliente.estadoCivil,tok);

            fgets(linha, 150, arq); //pega <dtNascimento>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "<>");
            strcpy(novoCliente.dataNascimento,tok);


            fgets(linha, 150, arq); //pega </registro>
            break;
        }
        line++;
    }
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

void importa_Filme(FILE *arq, filme **dtbaseFilme, int qtdfilme) {
    int achou = 0;
    char linha[150];
    if (arq == NULL) {
        return;
    }

    int lineinit = 0;
    while ((achou == 0) && (!feof(arq))) {
        fgets(linha, 150, arq);
        if (strcmp(linha, "\t<filmes>\n") == 0) {
            achou = 1;
            break;
        }
        lineinit++;
    }

    if (achou == 0) {
        printf("Dados de Filmes nao encontrado");
        return;
    }

    char *tok;
    filme novoFilme;

    int line = 0 ;
    while (strcmp(linha, "</filmes>\n") != 0 || (!feof(arq) || strstr(linha,"</filmes>") != NULL)){
        if (line >= lineinit) {
            fgets(linha, 150, arq);//pega <registro>
            if (strcmp(linha, "</filmes>\n") == 0 || strstr(linha,"</filmes>") != NULL) { //Verifica se os dados acabou
                break;
            }
            fgets(linha, 150, arq); //pega <id>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            novoFilme.codigo = strtol(tok,NULL,10);

            fgets(linha, 150, arq); //pega <descricao>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(novoFilme.nome, tok);

            fgets(linha, 150, arq); //pega <quantidade>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            novoFilme.qtd = strtol(tok,NULL,10);

            fgets(linha, 150, arq); //pega <c_categoria>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            novoFilme.c_categoria = strtol(tok,NULL,10);

            fgets(linha, 150, arq); //pega <lingua>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(novoFilme.lingua,tok);

            fgets(linha, 150, arq); //pega <qtdEmprestado>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            novoFilme.qtdEmprestado = strtol(tok,NULL,10);

            fgets(linha, 150, arq); //pega </registro>
        }
        line++;
    }
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
                    "\n\t\t</registro>"
                    ,(*dtbasecategoria)[i].codigo,
                (*dtbasecategoria)[i].descricao,
                (*dtbasecategoria)[i].vAlocacao,
                (*dtbasecategoria)[i].ativo
        );
    }
    fprintf(arq,"\n\t</categoria>\n");
}

void importa_Categoria(FILE *arq, fCategoria **dtbasecategoria, int qtdcategoria) {
    int achou = 0;
    char linha[150];
    if (arq == NULL) {
        return ;
    }

    int lineinit = 0;
    while ((achou == 0) && (!feof(arq))) {
        fgets(linha, 150, arq);
        if (strcmp(linha, "\t<categoria>\n") == 0) {
            achou = 1;
            break;
        }
        lineinit++;
    }

    if (achou == 0) {
        printf("Dados de Categoria nao encontrado");
        return;
    }

    char *tok;
    fCategoria categoria;

    int line = 0;
    while (strcmp(linha, "</categoria>\n") != 0 || (!feof(arq) || strstr(linha,"</categoria>") != NULL)){
        if (line >= lineinit) {
            fgets(linha, 150, arq);
            if (strcmp(linha, "</categoria>\n") == 0 ||
                strstr(linha, "</categoria>") != NULL) { //Verifica se a struct acabou
                printf("opa");
                break;
            }
            fgets(linha, 150, arq); //pega o codigo
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            categoria.codigo = strtol(tok, NULL, 10);

            fgets(linha, 150, arq); //pega o descricao
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            strcpy(categoria.descricao, tok);

            fgets(linha, 150, arq); //pega o valor
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            categoria.vAlocacao = strtof(tok, NULL);
            //categoria.valor_diaria = atof(tok);

            fgets(linha, 150, arq); //pega o Ativo
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            categoria.ativo = strtol(tok, NULL, 10);
            //categoria.lotacao_max = atoi(tok);

            fgets(linha, 150, arq); //pega o tabela
        }
        line++;
    }
}

void exportDadosFornecedor(FILE *arq, fornecedor **dtbasefornecedor, int qtdFornecedor){
    if (arq == NULL){
        printf("\nErro na exportacao de dadps cliente\n\n");
        exit(1);
    }

    fprintf(arq,"\t<fornecedor>");
    for (int i = 0; i < qtdFornecedor; i++)
    {
        fprintf(arq,"\n\t\t<registro>"
                    "\n\t\t\t<id>%d</id>"
                    "\n\t\t\t<nomeFantasia>%s</nomeFantasia>"
                    "\n\t\t\t<razaoSocial>%s</razaoSocial>"
                    "\n\t\t\tinscricaoEstadual%s</inscricaoEstadual>"
                    "\n\t\t\t<cnpj>%s</cnpj>"
                    "\n\t\t\t<endereco>%s, %d, %s, %s, %s </endereco>"
                    "\n\t\t\t<telefone>%s</telefone>"
                    "\n\t\t\t<email>%s</email>"
                    "\n\t\t</registro>",(*dtbasefornecedor)[i].id,
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
    fprintf(arq,"\n\t</fornecedor>\n");
}

void importa_Fornecedor(FILE *arq, fornecedor **dtbasefornecedor, int qtdFornecedor) {
    int achou = 0;
    char linha[150];
    if (arq == NULL) {
        return ;
    }

    int lineinit = 0;
    while ((achou == 0) && (!feof(arq))) {
        fgets(linha, 150, arq);
        if (strcmp(linha, "\t<fornecedor>\n") == 0) {
            achou = 1;
            break;
        }
        lineinit++;
    }

    if (achou == 0) {
        printf("Dados de Fornecedor nao encontrado");
        return;
    }

    char *tok;
    fornecedor nfornecedor;

    int line = 0;
    while (strcmp(linha, "</fornecedor>\n") != 0 || (!feof(arq) || strstr(linha,"</fornecedor>") != NULL)){

        if (line >= lineinit) {
            fgets(linha, 150, arq);
            if (strcmp(linha, "</fornecedor>\n") == 0 ||
                strstr(linha, "</fornecedor>") != NULL) { //Verifica se a struct acabou
                printf("opa");
                break;
            }
            fgets(linha, 150, arq); //pega o codigo
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            nfornecedor.id = strtol(tok, NULL, 10);

            fgets(linha, 150, arq); //pega o <nomeFantasia>
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            strcpy(nfornecedor.nomeFantasia, tok);

            fgets(linha, 150, arq); //pega o <razaoSocial>
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            strcpy(nfornecedor.razaoSocial, tok);

            fgets(linha, 150, arq); //pega o <inscricaoEstadual>
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            strcpy(nfornecedor.inscricaoEstadual, tok);
            //categoria.lotacao_max = atoi(tok);

            fgets(linha, 150, arq); //pega o <cnpj>
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            strcpy(nfornecedor.cnpj, tok);

            fgets(linha, 200, arq); //pega <endereco>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, ",</>");
            strcpy(nfornecedor.endereco.rua,tok);
            tok = strtok(NULL, ",</>");
            nfornecedor.endereco.numero = strtol(tok,NULL,10);
            tok = strtok(NULL, ",</>");
            strcpy(nfornecedor.endereco.bairro,tok);
            tok = strtok(NULL, ",</>");
            strcpy(nfornecedor.endereco.cidade,tok);
            tok = strtok(NULL, ",</>");
            strcpy(nfornecedor.endereco.estado,tok);

            fgets(linha, 150, arq); //pega <telefone>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(nfornecedor.telefone,tok);

            fgets(linha, 150, arq); //pega <email>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(nfornecedor.email,tok);

            fgets(linha, 150, arq); //pega o tabela
        }
        line++;
    }
}

void exportDadosFuncionario(FILE *arq, funcionarios **dtbasefuncionarios, int qtdfuncionarios){
    if (arq == NULL){
        printf("\nErro na exportacao de dadps cliente\n\n");
        exit(1);
    }

    fprintf(arq,"\t<funcionario>\n");
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
    fprintf(arq,"</funcionario>\n");
}

void importa_Funcionarior(FILE *arq, funcionarios **dtbasefuncionarios, int qtdfuncionarios) {
    int achou = 0;
    char linha[150];
    if (arq == NULL) {
        return ;
    }

    int lineinit = 0;
    while ((achou == 0) && (!feof(arq))) {
        fgets(linha, 150, arq);
        if (strcmp(linha, "\t<funcionario>\n") == 0) {
            achou = 1;
            break;
        }
        lineinit++;
    }

    if (achou == 0) {
        printf("Dados de Funcionario nao encontrado");
        return;
    }

    char *tok;
    funcionarios nfuncionarios;

    int line = 0;
    while (strcmp(linha, "</funcionario>\n") != 0 || (!feof(arq) || strstr(linha,"</fornecedor>") != NULL)){

        if (line >= lineinit) {
            fgets(linha, 150, arq);
            if (strcmp(linha, "</funcionario>\n") == 0 ||
                strstr(linha, "</funcionario>") != NULL) { //Verifica se a struct acabou
                printf("opa");
                break;
            }
            fgets(linha, 150, arq); //pega o codigo
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            nfuncionarios.codigo = strtol(tok, NULL, 10);

            fgets(linha, 150, arq); //pega o <nome>
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            strcpy(nfuncionarios.nome, tok);

            fgets(linha, 200, arq); //pega <endereco>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, ",</>");
            strcpy(nfuncionarios.endereco.rua,tok);
            tok = strtok(NULL, ",</>");
            nfuncionarios.endereco.numero = strtol(tok,NULL,10);
            tok = strtok(NULL, ",</>");
            strcpy(nfuncionarios.endereco.bairro,tok);
            tok = strtok(NULL, ",</>");
            strcpy(nfuncionarios.endereco.cidade,tok);
            tok = strtok(NULL, ",</>");
            strcpy(nfuncionarios.endereco.estado,tok);

            fgets(linha, 150, arq); //pega <telefone>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(nfuncionarios.telefone,tok);

            fgets(linha, 150, arq); //pega <email>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(nfuncionarios.email,tok);

            fgets(linha, 200, arq); //pega <user>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(nfuncionarios.login.user,tok);

            fgets(linha, 200, arq); //pega <password>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            //strcpy(newLocadora.password,tok);
            strcpy(nfuncionarios.login.password,tok);

            //nfuncionarios.login.password = retorna_password_file(tok);

            fgets(linha, 150, arq); //pega o tabela
        }
        line++;
    }
}
//Alterar Imports Inferior ...
void exportDadosLocacao(FILE *arq, contaCliente **dtbaseCCliente, int qtdCCliente){
    if (arq == NULL){
        printf("\nErro na exportacao de dados Locacao\n\n");
        exit(1);
    }

    fprintf(arq,"\t<locacao>");
    for (int i = 0; i < qtdCCliente; i++)
    {
        fprintf(arq,"\n\t\t<contaCliente>"
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
                        "\n\t\t\t\t<operacoe>",(*dtbaseCCliente)[i].dEmprestimo[j].ID,
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

            for (int k = 0; k < (*dtbaseCCliente)[i].dEmprestimo[j].qtdFilme - 1; k++){
                fprintf(arq,"\n\t\t\t\t\t<resgistro>"
                            "\n\t\t\t\t\t\t<id>%d</id>"
                            "\n\t\t\t\t\t\t<idFilme>%d</idFilme>"
                            "\n\t\t\t\t\t\t<nomeFilme>%s</nomeFilme>"
                            "\n\t\t\t\t\t\t<valorFilme>%.2f</valorFilme>"
                            "\n\t\t\t\t\t\t<dtemprestimo>%d/%d/%d</dtemprestimo>"
                            "\n\t\t\t\t\t\t<dtdevolucao>%d/%d/%d</dtdevolucao>"
                            "\n\t\t\t\t\t\t<dtdevolucaoReal>%d/%d/%d</dtdevolucaoReal>"
                            "\n\t\t\t\t\t\t<devolvido>%d</devolvido>"
                            "\n\t\t\t\t\t</resgistro>",(*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].ID,
                            (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].CodFilme,
                            (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].nomeFilme,
                            (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].valorFilme,
                            (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtemprestimo.dia,
                            (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtemprestimo.mes,
                            (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtemprestimo.ano,
                            (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucao.dia,
                            (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucao.mes,
                            (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucao.ano,
                            (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucaoReal.dia,
                            (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucaoReal.mes,
                            (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].dtdevolucaoReal.ano,
                            (*dtbaseCCliente)[i].dEmprestimo[j].dFilme[k].devolvido);

            }
            fprintf(arq,"\n\t\t\t\t</operacoe>\n\t\t\t</locados>");
        }
        fprintf(arq,"\n\t\t</contaCliente>");
    }
    fprintf(arq,"\n\t</locacao>\n");
}

void importa_Locacao(FILE *arq, contaCliente **dtbaseCCliente, int qtdCCliente) {
    int achou = 0;
    char linha[150];
    if (arq == NULL) {
        return ;
    }

    int lineinit = 0;
    while ((achou == 0) && (!feof(arq))) {
        fgets(linha, 150, arq);
        if (strcmp(linha, "\t<contaCliente>\n") == 0) {
            achou = 1;
            break;
        }
        lineinit++;
    }

    if (achou == 0) {
        printf("Dados de Locacao nao encontrado");
        return;
    }

    char *tok;
    contaCliente ncontaCliente;

    int line = 0;
    while (strcmp(linha, "</contaCliente>\n") != 0 || (!feof(arq) || strstr(linha,"</fornecedor>") != NULL)){

        if (line >= lineinit) {
            fgets(linha, 150, arq);
            if (strcmp(linha, "</contaCliente>\n") == 0 ||
                strstr(linha, "</contaCliente>") != NULL) { //Verifica se a struct acabou
                printf("opa");
                break;
            }
            fgets(linha, 150, arq); //pega o codigo
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            ncontaCliente.ID = strtol(tok, NULL, 10);

            fgets(linha, 150, arq); //pega o <idCliente>
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            ncontaCliente.idCliente = strtol(tok,NULL,10);

            fgets(linha, 150, arq); //pega o <nome>
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            strcpy(ncontaCliente.Nome, tok);

            fgets(linha, 150, arq); //pega o <valorDeve>
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            ncontaCliente.valorDeve = strtof(tok,NULL);
            //strcpy(ncontaCliente.valorDeve, tok);
            //categoria.lotacao_max = atoi(tok);

            fgets(linha, 150, arq); //pega o <valorPago>
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            ncontaCliente.valorPago = strtof(tok,NULL);


            fgets(linha, 150, arq); //pega <tamLocados>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            ncontaCliente.tamLocados = strtol(tok,NULL,10);

            fgets(linha, 150, arq); //pega <IDlocado>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            ncontaCliente.IDlocado = strtol(tok,NULL,10);

            //Prencher dadados de locados
            ncontaCliente.dEmprestimo = calloc(ncontaCliente.tamLocados,sizeof(operacoe));
            if (ncontaCliente.dEmprestimo == NULL){
                printf("Erro na Alocacao de Memoria");
                break;
            }

            for (int i = 0; i < ncontaCliente.tamLocados; i++){
                
            }
            fgets(linha, 150, arq); //pega locados









            fgets(linha, 150, arq); //pega o tabela
        }
        line++;
    }
}

void exportDadosEntFilme(FILE *arq, eFilme **dtbase_eFilme, int qtdeFilme){
    if (arq == NULL){
        printf("\nErro na exportacao de dadps cliente\n\n");
        exit(1);
    }

    fprintf(arq,"\t<Ent_Filme>");
    for (int i = 0; i < qtdeFilme; i++)
    {
        fprintf(arq,"\n\t\t<contaLocadora>"
                    "\n\t\t\t<id>%d</id>"
                    "\n\t\t\t<idFornecedor>%d</idFornecedor>"
                    "\n\t\t\t<nomeFornecedor>%s</nomeFornecedor>"
                    "\n\t\t\t<cnpj>%s</cnpj>"
                    "\n\t\t\t<tamOp>%d</tamOp>"
                    "\n\t\t\t<ultIDOp>%d</ultIDOp>",(*dtbase_eFilme)[i].ID,
                (*dtbase_eFilme)[i].IDFornecedor,
                (*dtbase_eFilme)[i].nomefornecedor,
                (*dtbase_eFilme)[i].cnpj,
                (*dtbase_eFilme)[i].tamOp,
                (*dtbase_eFilme)[i].ultIDOp);

        for (int j = 0; j < (*dtbase_eFilme)[i].tamOp - 1; j++)
        {
            fprintf(arq,"\n\t\t\t<operacaoEFilme>"
                        "\n\t\t\t\t<id>%d</id>"
                        "\n\t\t\t\t<frete>%.2f</frete>"
                        "\n\t\t\t\t<imposto>%.2f</imposto>"
                        "\n\t\t\t\t<tamFilm>%d</tamFilm>"
                        "\n\t\t\t\t<fretePproduto>%.2f</fretePproduto>"
                        "\n\t\t\t\t<impostoPproduto>%.2f</impostoPproduto>"
                        "\n\t\t\t\t<valorTotal>%.2f</valorTotal>"
                        "\n\t\t\t\t<tipoPagamento>%d</tipoPagamento>"
                        "\n\t\t\t\t<qtdParcelas>%d</qtdParcelas>"
                        "\n\t\t\t\t<parcelasPagas>%d</parcelasPagas>"
                        "\n\t\t\t\t<valorEntrada>%.2f</valorEntrada>"
                        "\n\t\t\t\t<valorDeve>%.2f</valorDeve>"
                        "\n\t\t\t\t<dtNota>%d/%d/%d</dtNota>"
                        "\n\t\t\t\t<dtPagamento>%d/%d/%d</dtPagamento>"
                        "\n\t\t\t\t<ultIDFilm>%d</ultIDFilm>"
                        "\n\t\t\t\t<filmeEnt>",(*dtbase_eFilme)[i].filmes[j].ID,
                    (*dtbase_eFilme)[i].filmes[j].frete,
                    (*dtbase_eFilme)[i].filmes[j].Imposto,
                    (*dtbase_eFilme)[i].filmes[j].tamFilm,
                    (*dtbase_eFilme)[i].filmes[j].fretePproduto,
                    (*dtbase_eFilme)[i].filmes[j].ImpostoPproduto,
                    (*dtbase_eFilme)[i].filmes[j].valorTotal,
                    (*dtbase_eFilme)[i].filmes[j].tipoPagamento,
                    (*dtbase_eFilme)[i].filmes[j].qtdParcelas,
                    (*dtbase_eFilme)[i].filmes[j].parcelasPagas,
                    (*dtbase_eFilme)[i].filmes[j].valorEntrada,
                    (*dtbase_eFilme)[i].filmes[j].valorDeve,
                    (*dtbase_eFilme)[i].filmes[j].dtNota.dia,
                    (*dtbase_eFilme)[i].filmes[j].dtNota.mes,
                    (*dtbase_eFilme)[i].filmes[j].dtNota.ano,
                    (*dtbase_eFilme)[i].filmes[j].dtPagamento.dia,
                    (*dtbase_eFilme)[i].filmes[j].dtPagamento.mes,
                    (*dtbase_eFilme)[i].filmes[j].dtPagamento.ano,
                    (*dtbase_eFilme)[i].filmes[j].ultIDFilm
            );

            for (int k = 0; k < (*dtbase_eFilme)[i].filmes[j].tamFilm; k++){
                fprintf(arq,"\n\t\t\t\t\t<resgistro>"
                            "\n\t\t\t\t\t\t<id>%d</id>"
                            "\n\t\t\t\t\t\t<nome>%s</nome>"
                            "\n\t\t\t\t\t\t<valorCompra>%.2f</valorCompra>"
                            "\n\t\t\t\t\t\t<qtd>%d</qtd>"
                            "\n\t\t\t\t\t</resgistro>",(*dtbase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].codigo,
                        (*dtbase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].nome,
                        (*dtbase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].valorCompra,
                        (*dtbase_eFilme)[i].filmes[j].entradaFilmesCadastro[k].qtd
                        );
            }
            fprintf(arq,"\n\t\t\t\t</filmeEnt>\n\t\t\t</operacaoEFilme>");
        }
        fprintf(arq,"\n\t\t</contaLocadora>");
    }
    fprintf(arq,"\n\t</Ent_Filme>\n");
}

void importa_EntFilme(FILE *arq, eFilme **dtbase_eFilme, int qtdeFilme) {
    int achou = 0;
    char linha[150];
    if (arq == NULL) {
        return ;
    }

    int lineinit = 0;
    while ((achou == 0) && (!feof(arq))) {
        fgets(linha, 150, arq);
        if (strcmp(linha, "\t<fornecedor>\n") == 0) {
            achou = 1;
            break;
        }
        lineinit++;
    }

    if (achou == 0) {
        printf("Dados de Fornecedor nao encontrado");
        return;
    }

    char *tok;
    fornecedor nfornecedor;

    int line = 0;
    while (strcmp(linha, "</fornecedor>\n") != 0 || (!feof(arq) || strstr(linha,"</fornecedor>") != NULL)){

        if (line >= lineinit) {
            fgets(linha, 150, arq);
            if (strcmp(linha, "</fornecedor>\n") == 0 ||
                strstr(linha, "</fornecedor>") != NULL) { //Verifica se a struct acabou
                printf("opa");
                break;
            }
            fgets(linha, 150, arq); //pega o codigo
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            nfornecedor.id = strtol(tok, NULL, 10);

            fgets(linha, 150, arq); //pega o <nomeFantasia>
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            strcpy(nfornecedor.nomeFantasia, tok);

            fgets(linha, 150, arq); //pega o <razaoSocial>
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            strcpy(nfornecedor.razaoSocial, tok);

            fgets(linha, 150, arq); //pega o <inscricaoEstadual>
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            strcpy(nfornecedor.inscricaoEstadual, tok);
            //categoria.lotacao_max = atoi(tok);

            fgets(linha, 150, arq); //pega o <cnpj>
            tok = strtok(linha, "<>");
            tok = strtok(NULL, "</>");
            strcpy(nfornecedor.cnpj, tok);

            fgets(linha, 200, arq); //pega <endereco>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, ",</>");
            strcpy(nfornecedor.endereco.rua,tok);
            tok = strtok(NULL, ",</>");
            nfornecedor.endereco.numero = strtol(tok,NULL,10);
            tok = strtok(NULL, ",</>");
            strcpy(nfornecedor.endereco.bairro,tok);
            tok = strtok(NULL, ",</>");
            strcpy(nfornecedor.endereco.cidade,tok);
            tok = strtok(NULL, ",</>");
            strcpy(nfornecedor.endereco.estado,tok);

            fgets(linha, 150, arq); //pega <telefone>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(nfornecedor.telefone,tok);

            fgets(linha, 150, arq); //pega <email>
            tok = strtok(linha, "\t<>");
            tok = strtok(NULL, "</>");
            strcpy(nfornecedor.email,tok);

            fgets(linha, 150, arq); //pega o tabela
        }
        line++;
    }
}


void exportarDados(exportcamp camposExport, char *namepath, cliente **dtbaseCliente, int qtdCliente,filme **dtbaseFilme, int qtdfilme,
                   locadora **dtbaselocadora, int qtdlocadora,fCategoria **dtbasecategoria, int qtdcategoria,
                   fornecedor **dtbasefornecedor, int qtdFornecedor,funcionarios **dtbasefuncionarios, int qtdfuncionarios,
                   contaCliente **dtbaseCCliente, int qtdCCliente,eFilme **dtbase_eFilme, int qtdeFilme){
    FILE *arq;

    arq = fopen(namepath,"w");

    if (arq == NULL){
        printf("[!] Erro na Exportacao de Dados");
        exit(1);
    }

    //fprintf(arq, "<?xml version='1.0' encoding='UTF-16'?>\n");
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

    if (camposExport.categoria == 1){
        exportDadosCategoria(arq,dtbasecategoria,qtdcategoria);
    }

    if (camposExport.fornecedor == 1){
        exportDadosFornecedor(arq,dtbasefornecedor,qtdFornecedor);
    }

    if (camposExport.funcionario == 1){
        exportDadosFuncionario(arq,dtbasefuncionarios,qtdfuncionarios);
    }

    if (camposExport.locacao_filme == 1){
        exportDadosLocacao(arq,dtbaseCCliente,qtdCCliente);
    }

    if (camposExport.compras_filme == 1){
        exportDadosEntFilme(arq,dtbase_eFilme,qtdeFilme);
    }

    fprintf(arq,"</dados>");

    fclose(arq);
    arq = NULL;
}

void importarDados(exportcamp camposImporta, char *namepath, cliente **dtbaseCliente, int qtdCliente,filme **dtbaseFilme, int qtdfilme,
                   locadora **dtbaselocadora, int qtdlocadora,fCategoria **dtbasecategoria, int qtdcategoria,
                   fornecedor **dtbasefornecedor, int qtdFornecedor,funcionarios **dtbasefuncionarios, int qtdfuncionarios,
                   contaCliente **dtbaseCCliente, int qtdCCliente,eFilme **dtbase_eFilme, int qtdeFilme){
    FILE *arq;

    arq = fopen(namepath,"r");

    if (arq == NULL){
        printf("[!] Erro na Importacao de Dados");
        exit(1);
    }

    if (camposImporta.locadora == 1){
        importa_locadora(arq,dtbaselocadora,qtdlocadora);
    }

    if (camposImporta.cliente == 1){
        importa_Cliente(arq,dtbaseCliente,qtdCliente);
    }
//
//    if (camposImporta.filme == 1){
//        exportDadosFilme(arq,dtbaseFilme,qtdfilme);
//    }
//
//    if (camposImporta.categoria == 1){
//        exportDadosCategoria(arq,dtbasecategoria,qtdcategoria);
//    }
//
//    if (camposImporta.fornecedor == 1){
//        exportDadosFornecedor(arq,dtbasefornecedor,qtdFornecedor);
//    }
//
//    if (camposImporta.funcionario == 1){
//        exportDadosFuncionario(arq,dtbasefuncionarios,qtdfuncionarios);
//    }
//
//    if (camposImporta.locacao_filme == 1){
//        exportDadosLocacao(arq,dtbaseCCliente,qtdCCliente);
//    }
//
//    if (camposImporta.compras_filme == 1){
//        exportDadosEntFilme(arq,dtbase_eFilme,qtdeFilme);
//    }

    fclose(arq);
    arq = NULL;
}


int menuImportacaoExportcao(cliente **dtbaseCliente, int qtdcliente,filme **dtbaseFilme, int qtdfilme,locadora **dtbaselocadora, int qtdlocadora,fCategoria **dtbasecategoria, int qtdcategoria,
                            fornecedor **dtbasefornecedor, int qtdFornecedor,funcionarios **dtbasefuncionarios, int qtdfuncionarios,
                            contaCliente **dtbaseCCliente, int qtdCCliente,eFilme **dtbase_eFilme, int qtdeFilme){
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

    exportcamp camposExportarImportar;
    refazexportCamp(&camposExportarImportar,0);


    if (opc == 0){ //Sair
        system("cls");
        return 1; // Sair
    }
    else if (opc == 1)
    {
        while (1){
            int t = menuImport(&camposExportarImportar);
            if (t == 0){
                break;
            }
            importarDados(camposExportarImportar,"test.xml",dtbaseCliente,qtdcliente,dtbaseFilme,qtdfilme,dtbaselocadora,qtdlocadora,
                          dtbasecategoria,qtdcategoria,dtbasefornecedor,qtdFornecedor,dtbasefuncionarios,qtdfuncionarios,dtbaseCCliente,qtdCCliente,dtbase_eFilme,qtdeFilme);
            system("cls");
            return 1; // Sair
        }
    }
    else if (opc == 2)
    {
        //EXPORTAR DADOS
        while (1){
            int t = menuexport(&camposExportarImportar);
            if (t == 0){
                break;
            }
            exportarDados(camposExportarImportar,"test.xml",dtbaseCliente,qtdcliente,dtbaseFilme,qtdfilme,dtbaselocadora,qtdlocadora,
                          dtbasecategoria,qtdcategoria,dtbasefornecedor,qtdFornecedor,dtbasefuncionarios,qtdfuncionarios,dtbaseCCliente,qtdCCliente,dtbase_eFilme,qtdeFilme);
            system("cls");
            return 1; // Sair
        }

    }
    return 0;
}