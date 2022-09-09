#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "../cabecalhos/locadora.h"

locadora criarLocadora(int id) {

    locadora obj;
    obj.id = id;

    setbuf(stdin,NULL);
    printf("Nome Fantasia: ");
    scanf("%[^\n]s", obj.nomeFantasia);

    setbuf(stdin,NULL);
    printf("Razão Social: ");
    scanf("%[^\n]s", obj.razaoSocial);

    setbuf(stdin,NULL);
    printf("Inscrição Estadual: ");
    scanf("%[^\n]s", obj.inscricaoEstadual);

    printf("CNPJ: ");
    scanf("%d", &obj.cnpj);

    setbuf(stdin,NULL);
    printf("Telefone: ");
    scanf("%[^\n]s", obj.telefone);

    setbuf(stdin,NULL);
    printf("E-mail: ");
    scanf("%[^\n]s", obj.email);

    setbuf(stdin,NULL);
    printf("Nome do Responsável: ");
    scanf("%[^\n]s", obj.nomeResponsavel);

    setbuf(stdin,NULL);
    printf("Telefone do Responsável: ");
    scanf("%[^\n]s", obj.telefoneResponsavel);


    setbuf(stdin,NULL);
    printf("Rua: ");
    scanf("%[^\n]s", obj.endereco.rua);

    printf("Número: ");
    scanf("%d", &obj.endereco.numero);

    setbuf(stdin,NULL);
    printf("Bairro: ");
    scanf("%[^\n]s", obj.endereco.bairro);

    setbuf(stdin,NULL);
    printf("Cidade: ");
    scanf("%[^\n]s", obj.endereco.cidade);

    setbuf(stdin,NULL);
    printf("Estado: ");
    scanf("%[^\n]s", obj.endereco.estado);
    return obj;
}

int inserirLocadora(locadora **dtbase, locadora novaLocadora, int *qtdLocadora, int *tamanhoLocadora, int id) {
    if (*qtdLocadora == *tamanhoLocadora)
    {
        *tamanhoLocadora = *tamanhoLocadora + 1;
        *dtbase = (locadora *) realloc(*dtbase, *tamanhoLocadora * sizeof(locadora));
    }
    if (*dtbase == NULL)
    {
        printf("\n  Erro na alocação de memória!");
        system("pause");
        return 0;
    }
    (*dtbase)[id] = novaLocadora;
    *qtdLocadora = *qtdLocadora + 1;
    return 1;
}

int removerLocadora(locadora **dtbase, int id, int *qtdLocadora){
    for (int i = 0; i < *qtdLocadora; i ++){
        if((*dtbase)[i].id == id){
            while (i < *qtdLocadora - 1)
            {
                (*dtbase)[i] = (*dtbase)[i + 1];
                i++;
            }
            *qtdLocadora = *qtdLocadora - 1;
            break;
        }
    }
    return 0;
}

void listLocadora(locadora **dtbase, int qtd){
    if (qtd > 0) {
        printf("\nID \t Nome Fantasia \t Razão Social \t Inscrição Estadual \t CNPJ \t Telefone \t E-mail \t "
               "Nome do Responsável \t Telefone do Responsável \t Rua \t Número \t Bairro \t Cidade \t Estado\n");
        for (int c = 0; c < qtd; c++) {
            printf("---------------------------------------------------------------------------------\n");
            printf("(%d)\t %s\t %s\t %s\t %d\t %s\t %s\t %s\t %s\t %s\t %d\t %s\t %s\t %s \n",
                   (*dtbase)[c].id,
                   (*dtbase)[c].nomeFantasia,
                   (*dtbase)[c].razaoSocial,
                   (*dtbase)[c].inscricaoEstadual,
                   (*dtbase)[c].cnpj,
                   (*dtbase)[c].telefone,
                   (*dtbase)[c].email,
                   (*dtbase)[c].nomeResponsavel,
                   (*dtbase)[c].telefoneResponsavel,
                   (*dtbase)[c].endereco.rua,
                   (*dtbase)[c].endereco.numero,
                   (*dtbase)[c].endereco.bairro,
                   (*dtbase)[c].endereco.cidade,
                   (*dtbase)[c].endereco.estado);
        }
    }
    else{
        printf("\n\t>> Nada para mostrar aqui");
    }
    printf("\n");
}

void editaLocadora(locadora **dtbase, int *qtdLocadora, int *tamanhoLocadora, int id)
{
    for (int i = 0; i < *qtdLocadora; i++) {
        if ((*dtbase)[i].id == id) {
            locadora newEntrada = criarLocadora(id);
            inserirLocadora(dtbase, newEntrada, qtdLocadora, tamanhoLocadora, id);
            break;
        }
    }
    *qtdLocadora = *qtdLocadora - 1;
}