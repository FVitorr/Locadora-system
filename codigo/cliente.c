#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../cabecalhos/cliente.h"
#include "../cabecalhos/fucGlobal.h"

cliente criarCliente(int *idCliente){
    cliente obj;
    obj.id = *idCliente;

    *idCliente = *idCliente + 1;

    setbuf(stdin,NULL);
    printf("Nome: ");
    scanf("%[^\n]s", obj.nome);

    int CpfIsTrue = 0;
    do {
        if(CpfIsTrue == 1){
            printf(" \n>> Cpf Invalido. Tente Novamente.\n");
        }
        setbuf(stdin,NULL);
        printf("CPF: ");
        scanf("%[^\n]s", obj.cpf);
        CpfIsTrue = 1;
    }
    while (validaCPF(obj.cpf) == 1);

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

int inserirCliente(cliente **dtbase, cliente novoCliente, int *qtdCliente, int *tamanhoCliente, int tipo_config) {
    if (*qtdCliente == *tamanhoCliente)
    {
        *tamanhoCliente = *tamanhoCliente + 1;
        *dtbase = (cliente *) realloc(*dtbase, *tamanhoCliente * sizeof(cliente));
    }
    if (*dtbase == NULL)
    {
        printf("\n  Erro na alocação de memória!");
        system("pause");
        exit(1);
    }
    (*dtbase)[*tamanhoCliente - 1] = novoCliente;
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
            printf("(%d)\t %s\t %s\t %s\t %s\t %s\t %s\t %s\t %s\t %d\t %s\t %s\t %s \n",
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

void editaCliente(cliente **dtbase, int qtd_Cliente, int *tamanhoCliente, int id)
{
    for (int i = 0; i < qtd_Cliente; i++) {
        if ((*dtbase)[i].id == id) {
            cliente newEntrada = criarCliente(&id);
            (*dtbase)[i] = newEntrada;
            break;
        }
    }
}

int sairOuContinuar() {
    int escolhaSair = INT32_MAX;
    printf("Para realizar outra ação digite 1, para sair digite 0.\n");
    scanf("%d", &escolhaSair);
    if (escolhaSair != 1) {
        escolhaSair = 5;
    }
    return escolhaSair;
}

int menuClientes(cliente **bd_cliente, int *qtdCliente, int *tamanhoCliente, int *idControleCliente){
    int escolha = INT32_MAX;

    while (escolha != 0) {
        printf("Digite a opcao referente a operacao que deseja executar\n\n");
        printf("0 - Sair \n1 - Cadastrar \n2 - Visualizar \n3 - Editar \n4 - Remover\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: {
                cliente newCliente = criarCliente((idControleCliente));
                inserirCliente(bd_cliente, newCliente, qtdCliente, tamanhoCliente, *idControleCliente);
                idControleCliente += 1;
                break;
            }
            case 2: {
                listCliente(bd_cliente, *qtdCliente);
                break;
            }
            case 3: {
                int id = 0;
                listCliente(bd_cliente, *qtdCliente);
                printf("Digite o ID do Cliente que deseja editar.\n");
                scanf("%d", &id);
                editaCliente(bd_cliente, *qtdCliente, tamanhoCliente, id);
                break;
            }
            case 4: {
                int id = 0;
                listCliente(bd_cliente, *qtdCliente);
                printf("Digite o ID do Cliente que deseja excluir.\n");
                scanf("%d", &id);
                removerCliente(bd_cliente, id, qtdCliente);
                break;
            }
            case 0: {
                printf("Saindo...\n");
                return 1;
            }
            default: {
                printf("Esta não é uma opção válida, favor selecionar novamente.\n");
                break;
            }
        }
        if (escolha != 0 && escolha != 5) {
            escolha = sairOuContinuar();
        }
    }
    return escolha;
}