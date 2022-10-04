#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../cabecalhos/funcionarios.h"
#include "../cabecalhos/fucGlobal.h"

funcionarios criarFuncionario(int *idFuncionario){
    funcionarios obj;

    obj.codigo = *idFuncionario;

    setbuf(stdin,NULL);

    printf("Nome : ");
    scanf("%[^\n]s", obj.nome);

    setbuf(stdin,NULL);

    printf("Cargo: ");
    scanf("%s", obj.cargo);

    setbuf(stdin,NULL);

    line(20,"Endereço Funcionario\n");
    printf("Rua: ");
    scanf("%s", obj.endereco.rua);

    setbuf(stdin,NULL);

    printf("Número: ");
    scanf("%d", &obj.endereco.numero);

    setbuf(stdin,NULL);

    printf("Bairro: ");
    scanf("%s", obj.endereco.bairro);

    setbuf(stdin,NULL);

    printf("Cidade: ");
    scanf("%s", obj.endereco.cidade);

    setbuf(stdin,NULL);

    printf("Estado: ");
    scanf("%s", obj.endereco.estado);

    setbuf(stdin,NULL);

    printf("Telefone: ");
    scanf("%[^\n]s", obj.telefone);

    setbuf(stdin,NULL);

    printf("E-mail: ");
    scanf("%[^\n]s", obj.email);

    setbuf(stdin,NULL);

    printf("===============================================\n");
    printf("\tAcesso\n");
    printf("===============================================\n");
    printf("Usuario: ");
    scanf("%[^\n]s", obj.login.user);

    setbuf(stdin,NULL);

    printf("Senha: ");
    obj.login.password = obterPassword(16);
    return obj;
}

int inserirFuncionario(funcionarios **dtbase, funcionarios novoFuncionario, int *qtdFuncionario, int *tamanhoFuncionario) {
    if (*qtdFuncionario == *tamanhoFuncionario)
    {
        *tamanhoFuncionario = *tamanhoFuncionario + 1;
        *dtbase = (funcionarios *) realloc(*dtbase, *tamanhoFuncionario * sizeof(funcionarios));
    }
    if (*dtbase == NULL)
    {
        printf("\n  Erro na alocação de memória!");
        system("pause");
        exit(1);
    }
    (*dtbase)[*tamanhoFuncionario - 1] = novoFuncionario;
    *qtdFuncionario = *qtdFuncionario + 1;
    return 1;
}

void listFuncionarios(funcionarios **dtbase, int qtd){
    if (qtd > 0) {
        printf("\n ID \t Nome \t\t Cargo \t Telefone \t Email \t\t\t User \t Password\n");
        for (int c = 0; c < qtd; c++) {
            printf("---------------------------------------------------------------------------------\n");
            printf("(%d)\t %s\t\t %s\t %s\t\t %s\t\t\t %s \t\t %s\n", (*dtbase)[c].codigo,
                   (*dtbase)[c].nome,
                   (*dtbase)[c].cargo,
                   (*dtbase)[c].telefone,
                   (*dtbase)[c].email,
                   (*dtbase)[c].login.user,
                   (*dtbase)[c].login.password );
        }
    }
    else{
        printf("\n\t>> Nada para mostrar aqui");
    }
    printf("\n");
}

void editaFuncionarios(funcionarios **dtbase, int qtdFuncionarios,int *tamanhoFuncionarios,int id, int tipo_config)
{
    for (int i = 0; i < qtdFuncionarios; i++) {
        if ((*dtbase)[i].codigo == id) {
            funcionarios newEntrada = criarFuncionario(&id);
            (*dtbase)[i] = newEntrada;
            break;
        }
    }
//    refazDadosCliente(dtbase, tamanhoFuncionarios, tipo_config);
}

int removerFuncionarios(funcionarios **dtbase, int *qtdFuncionarios, int id, int tipo_config){
    for (int i = 0; i < *qtdFuncionarios; i ++){
        if((*dtbase)[i].codigo == id){
            while (i < *qtdFuncionarios - 1)
            {
                (*dtbase)[i] = (*dtbase)[i + 1];
                i++;
            }
            *qtdFuncionarios = *qtdFuncionarios - 1;
            break;
        }
    }
    return 0;
}

int menuFuncionarios(funcionarios **dtbase, int *qtdFuncionarios,int *tamanhoFuncionarios,int *idControleCliente, int tipo_config){
    int escolha = INT32_MAX;

    while (escolha != 0) {
        printf("Digite a opcao referente a operacao que deseja executar\n\n");
        printf("0 - Sair \n1 - Cadastrar \n2 - Visualizar \n3 - Editar \n4 - Remover\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: {
                funcionarios newFuncionario = criarFuncionario((idControleCliente));
                inserirFuncionario(dtbase, newFuncionario, qtdFuncionarios, tamanhoFuncionarios);
                saveFuncionario(newFuncionario, tipo_config);
                break;
            }
            case 2: {
                listFuncionarios(dtbase, *qtdFuncionarios);
                break;
            }
            case 3: {
                int id = 0;
                listFuncionarios(dtbase, *qtdFuncionarios);
                printf("Digite o ID do Funcionario que deseja editar.\n");
                scanf("%d", &id);
                editaFuncionarios(dtbase, *qtdFuncionarios, tamanhoFuncionarios, id, tipo_config);
                break;
            }
            case 4: {
                int id = 0;
                listFuncionarios(dtbase, *qtdFuncionarios);
                printf("Digite o ID do Funcionario que deseja excluir.\n");
                scanf("%d", &id);
                removerFuncionarios(dtbase, qtdFuncionarios, id, tipo_config);
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
    }
    return escolha;
}

int saveFuncionario(funcionarios objeto, int tipo_config) {
    FILE *fileFuncionario;
    
    if (tipo_config == 1){//Arquivo TXT
    fileFuncionario = fopen("cpyBdFuncionario.txt", "a");
    
    if (fileFuncionario == NULL){ // Se a abertura falhar
    return 1;
    }
    
    fprintf(fileFuncionario, "%d\n%s\n%s\n%s\n%s\n"
    "%s\n%d\n%s\n%s\n%s\n%s\n%s\n",
            objeto.codigo,
            objeto.nome,
            objeto.cargo,
            objeto.telefone,
            objeto.email,
            objeto.endereco.rua,
            objeto.endereco.numero,
            objeto.endereco.bairro,
            objeto.endereco.cidade,
            objeto.endereco.estado,
            objeto.login.user,
            objeto.login.password
    );
    
    }else if (tipo_config == 0){ //Arquivo BINARIO
    fileFuncionario = fopen("cpyBdFuncionario.bin", "ab");
    if (fileFuncionario == NULL){ // Se a abertura falhar
    return 1;
    }
    fwrite(&objeto, sizeof(funcionarios), 1, fileFuncionario);
    }
    fclose(fileFuncionario);
    return 0;
}