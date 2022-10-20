#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <io.h>
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

int inserirCliente(cliente **dtbase, cliente novoCliente, int *qtdCliente, int *tamanhoCliente) {
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

int removerCliente(cliente **dtbase, int id, int *qtdCliente, int tipo_config) {
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
    refazDadosCliente(dtbase, qtdCliente, tipo_config);
    return 0;
}

void listCliente(cliente **dtbase, int qtd) {
    if (qtd > 0) {
        for (int c = 0; c < qtd; c++) {
            printf("---------------------------------------------------------------------------------\n");
            printf("(%d)\nNome: %s\nCPF %s\nTelefone %s\nE-mail %s\nSexo %s\nEstado civil %s"
                   "\nData de Nascimento %s \nRua %s ,%d Bairo: %s \tCidade: %s - %s",
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

void editaCliente(cliente **dtbase, int qtdCliente, int *tamanhoCliente, int id, int tipo_config)
{
    for (int i = 0; i < qtdCliente; i++) {
        if ((*dtbase)[i].id == id) {
            cliente newEntrada = criarCliente(&id);
            (*dtbase)[i] = newEntrada;
            break;
        }
    }
    refazDadosCliente(dtbase, tamanhoCliente, tipo_config);
}

int menuClientes(cliente **bd_cliente, int *qtdCliente, int *tamanhoCliente, int *idControleCliente, int tipo_config){
    int escolha = INT32_MAX;

    while (escolha != 0) {
        printf("Digite a opcao referente a operacao que deseja executar\n\n");
        printf("0 - Sair \n1 - Cadastrar \n2 - Visualizar \n3 - Editar \n4 - Remover\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: {
                cliente newCliente = criarCliente((idControleCliente));
                inserirCliente(bd_cliente, newCliente, qtdCliente, tamanhoCliente);
                saveCliente(newCliente, tipo_config);
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
                editaCliente(bd_cliente, *qtdCliente, tamanhoCliente, id, tipo_config);
                break;
            }
            case 4: {
                int id = 0;
                listCliente(bd_cliente, *qtdCliente);
                printf("Digite o ID do Cliente que deseja excluir.\n");
                scanf("%d", &id);
                removerCliente(bd_cliente, id, qtdCliente, tipo_config);
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

int saveCliente(cliente objeto, int tipo_config){
    FILE *clientesF = NULL;

    if (tipo_config == 1){//Arquivo TXT

        if (verifica_arquivos(tipo_config,"cpyBdCliente.txt\0") == 1){
            clientesF = fopen("cpyBdCliente.txt", "a");
        } else{
            clientesF = fopen("cpyBdCliente.txt", "w");
        }

        if (clientesF == NULL){ // Se a abertura falhar
            return 1;
        }

        fprintf(clientesF, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n"
                          "%s\n%d\n%s\n%s\n%s\n",
                objeto.id,
                objeto.nome,
                objeto.cpf,
                objeto.telefone,
                objeto.email,
                objeto.sexo,
                objeto.estadoCivil,
                objeto.dataNascimento,
                objeto.endereco.rua,
                objeto.endereco.numero,
                objeto.endereco.bairro,
                objeto.endereco.cidade,
                objeto.endereco.estado
                );

    }else if (tipo_config == 0){ //Arquivo BINARIO
        if (verifica_arquivos(tipo_config,"cpyBdCliente.bin\0") == 1){
            clientesF = fopen("cpyBdCliente.bin", "ab");
        } else{
            clientesF = fopen("cpyBdCliente.bin", "wb");
        }

        if (clientesF == NULL){ // Se a abertura falhar
            printf("\nArquivo não encontrado ou erro na criação: 'cpyBdCliente.bin'");
            return 1;
        }
        fwrite(&objeto, sizeof(cliente), 1,clientesF);
    }
    fclose(clientesF);
    clientesF = NULL;
    return 0;
}

int verificaIdCliente(cliente **dtbase, int qtdClientes, int id) {
    for (int i = 0; i < qtdClientes; i++) {
        if ((*dtbase)[i].id == id) {
            return 1;
        }
    }
    return 0;
}

char *nomeCliente(cliente **dtbase,int qtd_Cliente, int ID){
    for (int i = 0; i < qtd_Cliente; i++)
    {
        if ((*dtbase)[i].id == ID) {
            return (*dtbase)[i].nome;
        }
    }
    return NULL;
}


int carregarDadosClientes(cliente **dtBase, int *qtdClientes, int *tamanhoCliente, int *id, int tipo_config) {
    FILE *p = NULL;
    cliente new;
    int t = 0;
    if (tipo_config == 1){ //Arquivo TXT
        p = fopen("cpyBdCliente.txt", "r");

        if (p == NULL){
            printf("\nErro na Leitura 'cpyBdCliente.txt' \n");
            return 1;
        }

        while (!feof(p)){
            if (!filelength(fileno(p))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fscanf(p, "%d\n", &new.id);

            fgets(new.nome, 120, p);
            limpa_final_string(new.nome);

            fgets(new.cpf, 20, p);
            limpa_final_string(new.cpf);

            fgets(new.telefone, 120, p);
            limpa_final_string(new.telefone);


            fgets(new.email, 120, p);
            limpa_final_string(new.email);

            fgets(new.sexo, 15, p);
            limpa_final_string(new.sexo);

            fgets(new.estadoCivil, 15, p);
            limpa_final_string(new.estadoCivil);

            fgets(new.dataNascimento, 12, p);
            limpa_final_string(new.dataNascimento);

            fgets(new.endereco.rua, 50, p);
            limpa_final_string(new.endereco.rua);

            fscanf(p, "%d\n", &new.endereco.numero);

            fgets(new.endereco.bairro, 50, p);
            limpa_final_string(new.endereco.bairro);

            fgets(new.endereco.cidade, 50, p);
            limpa_final_string(new.endereco.cidade);

            fgets(new.endereco.estado, 3, p);
            limpa_final_string(new.endereco.estado);

            if (verificaIdCliente(dtBase, *qtdClientes, new.id) == 0){
                t = inserirCliente(dtBase, new, qtdClientes, tamanhoCliente);
                if (*id <= new.id) {
                    *id = new.id + 1;
                }
            }

            if (t == 0){
                printf("\nAcao Interrompida");
                break;
            }
        }
    }
    else  if (tipo_config == 0){ //Arquivo BIN
        p = fopen("cpyBdCliente.bin", "rb");
        if (p == NULL){
            printf("Arquivo não Encontrado: 'cpyBdCliente.bin'");
            return 1;
        }
        while (!feof(p)){
            if (!filelength(fileno(p))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fread(&new,sizeof(cliente),1,p);
            printf("%s %s %s %s %s %s %s %s %s %s %s", new.nome, new.cpf, new.telefone, new.email, new.sexo,
                   new.estadoCivil, new.dataNascimento, new.endereco.rua, new.endereco.bairro, new.endereco.cidade, new.endereco.estado);
            if (verificaIdCliente(dtBase, *qtdClientes, new.id) == 0){
                t = inserirCliente(dtBase, new, qtdClientes, tamanhoCliente);
                if (*id <= new.id) {
                    *id = new.id + 1;
                }
            }

            if (t == 0){
                printf("\nAcao Interrompida");
                break;
            }
        }
    }
    fclose(p);
    p = NULL;
    return 0;
}


int refazDadosCliente(cliente **dtbase, int *tamanhoCliente, int tipo_config){

    FILE *p;
    if (tipo_config== 1){
        p = fopen("cpyBdCliente.txt", "w");
        fclose(p);
        p = NULL;
        for (int i = 0; i < *tamanhoCliente; i++){
            saveCliente((*dtbase)[i],1);
        }
    }else if (tipo_config == 0){
        p = fopen("cpyBdCliente.bin", "wb");
        fclose(p);
        for (int i = 0; i < *tamanhoCliente; i++){
            saveCliente((*dtbase)[i],0);
        }
    }
    return 0;
}
