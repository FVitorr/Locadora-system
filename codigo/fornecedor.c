#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../cabecalhos/fornecedor.h"

fornecedor criarFornecedor(int id) {

    fornecedor obj;
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

int inserirFornecedor(fornecedor **dtbase, fornecedor novoFornecedor, int *qtdFornecedor, int *tamanhoFornecedor, int id) {
    if (*qtdFornecedor == *tamanhoFornecedor)
    {
        *tamanhoFornecedor = *tamanhoFornecedor + 1;
        *dtbase = (fornecedor *) realloc(*dtbase, *tamanhoFornecedor * sizeof(fornecedor));
    }
    if (*dtbase == NULL)
    {
        printf("\n  Erro na alocação de memória!");
        system("pause");
        return 0;
    }
    (*dtbase)[*tamanhoFornecedor - 1] = novoFornecedor;
    *qtdFornecedor = *qtdFornecedor + 1;
    return 1;
}

int removerFornecedor(fornecedor **dtbase, int id, int *qtdFornecedor) {
    for (int i = 0; i < *qtdFornecedor; i ++){
        if((*dtbase)[i].id == id){
            while (i < *qtdFornecedor - 1)
            {
                (*dtbase)[i] = (*dtbase)[i + 1];
                i++;
            }
            *qtdFornecedor = *qtdFornecedor - 1;
            break;
        }
    }
    return 0;
}

void listFornecedor(fornecedor **dtbase, int qtd) {
    if (qtd > 0) {
        printf("\nID \t Nome Fantasia \t Razão Social \t Inscrição Estadual \t CNPJ \t Telefone \t E-mail \t "
               " Rua \t Número \t Bairro \t Cidade \t Estado\n");
        for (int c = 0; c < qtd; c++) {
            printf("---------------------------------------------------------------------------------\n");
            printf("(%d)\t %s\t %s\t %s\t %d\t %s\t %s\t %s\t %d\t %s\t %s\t %s \n",
                   (*dtbase)[c].id,
                   (*dtbase)[c].nomeFantasia,
                   (*dtbase)[c].razaoSocial,
                   (*dtbase)[c].inscricaoEstadual,
                   (*dtbase)[c].cnpj,
                   (*dtbase)[c].telefone,
                   (*dtbase)[c].email,
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

void editarFornecedor(fornecedor **dtbase, int *qtdFornecedor, int *tamanghoFornecedor, int id)
{
    for (int i = 0; i < *qtdFornecedor; i++) {
        if ((*dtbase)[i].id == id) {
            fornecedor newEntrada = criarFornecedor(id);
            inserirFornecedor(dtbase, newEntrada, qtdFornecedor, tamanghoFornecedor, id);
            break;
        }
    }
    *qtdFornecedor = *qtdFornecedor - 1;
}

int menuFornecedor(fornecedor **bd_fornecedor, int *qtdFornecedor,int *tamanhoFornecedor,int *idControleFornecedor) {
    int escolha = INT32_MAX;

    while (escolha != 0 && escolha != 5) {
        printf("Digite a opcao referente a operacao que deseja executar\n\n");
        printf("0 - Sair \n1 - Cadastrar \n2 - Visualizar \n3 - Editar \n4 - Remover\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: {
                fornecedor newFornecedor = criarFornecedor(*idControleFornecedor);
                inserirFornecedor(bd_fornecedor, newFornecedor, qtdFornecedor, tamanhoFornecedor, *idControleFornecedor);
                idControleFornecedor += 1;
                break;
            }
            case 2: {
                listFornecedor(bd_fornecedor, *qtdFornecedor);
                break;
            }
            case 3: {
                int id = 0;
                listFornecedor(bd_fornecedor, *qtdFornecedor);
                printf("Digite o ID do Fornecedor que deseja editar.\n");
                scanf("%d", &id);
                editarFornecedor(bd_fornecedor, qtdFornecedor, tamanhoFornecedor, id);
                break;
            }
            case 4: {
                int id = 0;
                listFornecedor(bd_fornecedor, *qtdFornecedor);
                printf("Digite o ID do Cliente que deseja excluir.\n");
                scanf("%d", &id);
                removerFornecedor(bd_fornecedor, id, qtdFornecedor);
                break;
            }
            case 5: {
                printf("Voltando...\n");
                return 1;
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
    }
    return escolha;
}

