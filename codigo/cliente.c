#include <stdlib.h>
#include <stdio.h>
#include "../cabecalhos/cliente.h"

int qtdCliente = 0, tamanhoCliente = 1;

cliente criarCliente(cliente *dados, int atualizar){
    cliente obj;

    obj.id = 1;
    printf("===============================================\n");
    (atualizar == 1) ? printf("Atualizando o cliente\n") : printf("Criando um novo cliente\n");
    printf("===============================================\n");
    printf("Nome: ");
    scanf("%s", obj.nome);
    printf("CPF: ");
    scanf("%d", &obj.cpf);
    printf("Telefone: ");
    scanf("%s", obj.telefone);
    printf("E-mail: ");
    scanf("%s", obj.email);
    printf("Sexo (M para MASCULINO e F para FEMININO): ");
    scanf("%s", obj.sexo);
    printf("Estado civil: ");
    scanf("%s", obj.estadoCivil);
    printf("Data de Nascimento (Utilize o seguinte formato 11/11/1111): ");
    scanf("%s", obj.dataNascimento);
    printf("===============================================");
    printf("Inserindo endereço do cliente\n");
    printf("===============================================\n");
    printf("Rua: ");
    scanf("%s", obj.endereco.rua);
    printf("Número: ");
    scanf("%d", &obj.endereco.numero);
    printf("Bairro: ");
    scanf("%s", obj.endereco.bairro);
    printf("Cidade: ");
    scanf("%s", obj.endereco.cidade);
    printf("Estado: ");
    scanf("%s", obj.endereco.estado);

    if (atualizar == 1) {
        if (qtdCliente == tamanhoCliente) {
            tamanhoCliente += 1;
            dados = realloc(dados, tamanhoCliente * sizeof(cliente));
        }
        dados[qtdCliente] = obj;
        qtdCliente++;
    }
    return obj;
}

void imprimirCliente(cliente obj){
    printf("\nIdentificador do cliente: %d", obj.id);
    printf("\nNome: %s", obj.nome);
    printf("\nEndereço: Rua %s, %d, Bairro %s, %s - %s,",
           obj.endereco.rua, obj.endereco.numero, obj.endereco.bairro, obj.endereco.cidade, obj.endereco.estado);
    printf("\nCPF: %d", obj.cpf);
    printf("\nTelefone: %s", obj.telefone);
    printf("\nE-mail: %s", obj.email);
    printf("\nSexo: %s", (obj.sexo[0] == 'F') ? "Feminino" : "Masculino");
    printf("\nEstado civil: %s", obj.estadoCivil);
    printf("\nData de nascimento: %s", obj.dataNascimento);
}

void imprimirClienteList(cliente *dados){
    for (int i = 0; i < qtdCliente; ++i) {
        imprimirCliente(dados[i]);
    }
}

void removerCliente(cliente *dados, int id){
    for (int i = 0; i < qtdCliente; i++){
        if (dados[i].id == id){
            while (i < qtdCliente - 1){
                dados[i] = dados[i + 1];
                i++;
            }
            qtdCliente--;
            break;
        }
    }
}

void atualizarCliente(cliente *dados, int id){
    for (int i = 0; i < qtdCliente; i++){
        if (dados[i].id == id){
            dados[i] = criarCliente(dados, 1);
        }
    }
}
