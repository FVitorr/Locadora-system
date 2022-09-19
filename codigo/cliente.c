#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "../cabecalhos/cliente.h"
#include "../cabecalhos/fucGlobal.h"

cliente criarCliente(int id){
    cliente obj;
    obj.id = id;

    setbuf(stdin,NULL);
    printf("Nome: ");
    scanf("%[^\n]s", obj.nome);

    setbuf(stdin,NULL);
    printf("CPF: ");
    scanf("%d", &obj.cpf);

    setbuf(stdin,NULL);
    printf("Telefone: ");
    scanf("%[^\n]s", obj.telefone);

    setbuf(stdin,NULL);
    printf("E-mail: ");
    scanf("%[^\n]s", obj.email);

    setbuf(stdin,NULL);
    printf("Sexo: ");
    scanf("%[^\n]s", obj.sexo);

    setbuf(stdin,NULL);
    printf("Estado civil: ");
    scanf("%[^\n]s", obj.estadoCivil);

    setbuf(stdin,NULL);
    printf("Data de Nascimento (Utilize o seguinte formato 11/11/1111): ");
    scanf("%[^\n]s", obj.dataNascimento);

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

int inserirCliente(cliente **dtbase, cliente novoCliente, int *qtdCliente, int *tamanhoCliente, int id) {
    if (*qtdCliente == *tamanhoCliente)
    {
        *tamanhoCliente = *tamanhoCliente + 1;
        *dtbase = (cliente *) realloc(*dtbase, *tamanhoCliente * sizeof(cliente));
    }
    if (*dtbase == NULL)
    {
        printf("\n  Erro na alocação de memória!");
        system("pause");
        return 0;
    }
    (*dtbase)[id] = novoCliente;
    *qtdCliente = *qtdCliente + 1;
    return 1;
}

int removerCliente(cliente **dtbase, int id, int *qtdCliente) {
    for (int i = 0; i < *qtdCliente; i ++){
        if((*dtbase)[i].id == id){
            while (i < *qtdCliente - 1)
            {
                (*dtbase)[i] = (*dtbase)[i + 1];
                i++;
            }
            *qtdCliente = *qtdCliente - 1;
            break;
        }
    }
    return 0;
}

void listCliente(cliente **dtbase, int qtd) {
    if (qtd > 0) {
        printf("\nID \t Nome \t CPF \t Telefone \t E-mail \t Sexo \t Estado civil \t "
               "Data de Nascimento \t Rua \t Número \t Bairro \t Cidade \t Estado\n");
        for (int c = 0; c < qtd; c++) {
            printf("---------------------------------------------------------------------------------\n");
            printf("(%d)\t %s\t %d\t %s\t %s\t %s\t %s\t %s\t %s\t %d\t %s\t %s\t %s \n",
                   (*dtbase)[c].id,
                   (*dtbase)[c].nome,
                   (*dtbase)[c].cpf,
                   (*dtbase)[c].telefone,
                   (*dtbase)[c].email,
                   (*dtbase)[c].sexo,
                   (*dtbase)[c].estadoCivil,
                   (*dtbase)[c].dataNascimento,
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

void editaCliente(cliente **dtbase, int *qtdCliente, int *tamanhoCliente, int id)
{
    for (int i = 0; i < *qtdCliente; i++) {
        if ((*dtbase)[i].id == id) {
            cliente newEntrada = criarCliente(id);
            inserirCliente(dtbase, newEntrada, qtdCliente, tamanhoCliente, id);
            break;
        }
    }
    *qtdCliente = *qtdCliente - 1;
}