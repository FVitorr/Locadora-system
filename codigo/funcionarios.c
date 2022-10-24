#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <io.h>
#include "../cabecalhos/funcionarios.h"
#include "../cabecalhos/fucGlobal.h"

funcionarios criarFuncionario(int *idFuncionario) {
    funcionarios obj;

    obj.codigo = *idFuncionario;

    *idFuncionario = *idFuncionario + 1;

    setbuf(stdin, NULL);

    printf("Nome : ");
    scanf("%[^\n]s", obj.nome);

    setbuf(stdin, NULL);

    printf("Cargo: ");
    scanf("%[^\n]s", obj.cargo);

    setbuf(stdin, NULL);

    line(20, "Endereço Funcionario\n");
    printf("Rua: ");
    scanf("%[^\n]s", obj.endereco.rua);


    printf("Número: ");
    scanf("%d", &obj.endereco.numero);

    setbuf(stdin, NULL);

    printf("Bairro: ");
    scanf("%[^\n]s", obj.endereco.bairro);

    setbuf(stdin, NULL);

    printf("Cidade: ");
    scanf("%[^\n]s", obj.endereco.cidade);

    setbuf(stdin, NULL);

    printf("Estado: ");
    scanf("%[^\n]s", obj.endereco.estado);

    setbuf(stdin, NULL);

    printf("Telefone: ");
    scanf("%[^\n]s", obj.telefone);

    setbuf(stdin, NULL);

    printf("E-mail: ");
    scanf("%[^\n]s", obj.email);

    setbuf(stdin, NULL);

    printf("===============================================\n");
    printf("\tAcesso\n");
    printf("===============================================\n");
    printf("Usuario: ");
    scanf("%[^\n]s", obj.login.user);

    setbuf(stdin, NULL);

    printf("Senha: ");
    obj.login.password = obterPassword(16);
    return obj;
}

int
inserirFuncionario(funcionarios **dtbase, funcionarios novoFuncionario, int *qtdFuncionario, int *tamanhoFuncionario) {
    if (*qtdFuncionario == *tamanhoFuncionario) {
        *tamanhoFuncionario = *tamanhoFuncionario + 1;
        *dtbase = (funcionarios *) realloc(*dtbase, *tamanhoFuncionario * sizeof(funcionarios));
    }
    if (*dtbase == NULL) {
        printf("\n  Erro na alocação de memória!");
        system("pause");
        exit(1);
    }
    (*dtbase)[*tamanhoFuncionario - 1] = novoFuncionario;
    *qtdFuncionario = *qtdFuncionario + 1;
    return 1;
}

void listFuncionarios(funcionarios **dtbase, int qtd) {
    if (qtd > 0) {
        //printf("\n ID \t Nome \t\t Cargo \t Telefone \t Email \t\t\t User \t Password\n");
        for (int c = 0; c < qtd; c++) {
            printf("---------------------------------------------------------------------------------\n");
            printf("(%d) Nome : %s\nCargo: %s \n\nRua: %s \nNumero: %d\nBairro: %s\nCidade: %s\nEstado: %s\nTelefone: %s\nEmail: %s"
                   "\nUser: %s \n Password: %s",
                   (*dtbase)[c].codigo,
                   (*dtbase)[c].nome,
                   (*dtbase)[c].cargo,
                   (*dtbase)[c].endereco.rua,
                   (*dtbase)[c].endereco.numero,
                   (*dtbase)[c].endereco.bairro,
                   (*dtbase)[c].endereco.cidade,
                   (*dtbase)[c].endereco.estado,
                   (*dtbase)[c].telefone,
                   (*dtbase)[c].email,
                   (*dtbase)[c].login.user,
                   (*dtbase)[c].login.password);
        }
    } else {
        printf("\n\t>> Nada para mostrar aqui");
    }
    printf("\n");
}

void editaFuncionarios(funcionarios **dtbase, int qtdFuncionarios, int *tamanhoFuncionarios, int id, int tipo_config) {
    for (int i = 0; i < qtdFuncionarios; i++) {
        if ((*dtbase)[i].codigo == id) {
            funcionarios newEntrada = criarFuncionario(&id);
            (*dtbase)[i] = newEntrada;
            break;
        }
    }
    refazDadosFuncionario(dtbase, tamanhoFuncionarios, tipo_config);
}

int removerFuncionarios(funcionarios **dtbase, int *qtdFuncionarios, int id, int tipo_config) {
    for (int i = 0; i < *qtdFuncionarios; i++) {
        if ((*dtbase)[i].codigo == id) {
            while (i < *qtdFuncionarios - 1) {
                (*dtbase)[i] = (*dtbase)[i + 1];
                i++;
            }
            *qtdFuncionarios = *qtdFuncionarios - 1;
            break;
        }
    }
    refazDadosFuncionario(dtbase, qtdFuncionarios, tipo_config);
    return 0;
}

int menuFuncionarios(funcionarios **dtbase, int *qtdFuncionarios, int *tamanhoFuncionarios, int *idControleCliente,
                     int tipo_config) {
    int escolha = INT32_MAX;

    system("cls");

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
                printf("Digite o ID do Funcionario que deseja editar.\nOpc:");
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
    FILE *funcionarioF = NULL;

    if (tipo_config == 1) {//Arquivo TXT
        //Se o arquivo não existir, tentar criar.
        if (verifica_arquivos(tipo_config,"cpyBdFuncionario.txt\0") == 1){
            funcionarioF = fopen("cpyBdFuncionario.txt", "a");
        } else{
            funcionarioF = fopen("cpyBdFuncionario.txt", "w");
        }


        if (funcionarioF == NULL) { // Se a abertura falhar
            return 1;
        }

        fprintf(funcionarioF, "%d\n%s\n%s\n%s\n%s\n%s\n%d\n%s\n%s\n%s\n%s\n%s\n",
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

    } else if (tipo_config == 0) { //Arquivo BINARIO
        if (verifica_arquivos(tipo_config,"cpyBdFuncionario.bin\0") == 1){
            funcionarioF = fopen("cpyBdFuncionario.bin", "ab");
        } else{
            funcionarioF = fopen("cpyBdFuncionario.bin", "wb");
        }
        if (funcionarioF == NULL) { // Se a abertura falhar
            return 1;
        }
        fwrite(&objeto, sizeof(funcionarios), 1, funcionarioF);
    }
    fclose(funcionarioF);
    funcionarioF = NULL;
    return 0;
}

int verificaIdFuncionario(funcionarios **dtbase, int qtdFuncionarios, int id) {
    for (int i = 0; i < qtdFuncionarios; i++) {
        if ((*dtbase)[i].codigo == id) {
            return 1;
        }
    }
    return 0;
}

char *nomefuncionario(funcionarios **dtbase, int qtdFuncionarios,int id){
    for (int i = 0 ; i < qtdFuncionarios; i++){
        if((*dtbase)[i].codigo == id){
            //printf("%s",(*dtbase)[i].nome);
            return (*dtbase)[i].nome;
        }
    }
    return NULL;
}



int autentificacaoSystem(adm *set, funcionarios **dtBase,int qtdFuncionarios){
    while (1) {
        if (qtdFuncionarios == 0){
            break;
            //Primeiro Acesso ou Funcionarios não existe funcionarios
        }
        system("cls");
        char user[120], *password;
        line(100, "Login\0");

        printf("Usuario: ");

        scanf("%[^\n]s", user);
        limpa_final_string(user);
        remover_espaco(user);

        setbuf(stdin, NULL);

        printf("\n[!]Nao e possivel apagar os caracteres informados na Senha\n\n Senha: ");

        password = obterPassword(16);
        //Criar Opção para recuperar senha
        for (int i = 0; i < qtdFuncionarios; i++) {
            if (strcmp((*dtBase)[i].login.user, user) == 0 || strcmp(set->user, user) == 0) {
                if (strcmp((*dtBase)[i].login.password, password) == 0 || strcmp(set->password, password) == 0) {
                    printf("\n>> Sucess\n");
                    system("Pause");
                    if (strcmp(set->password, password) == 0 && strcmp(set->user, user) == 0){
                        //Informa que o ADM esta Logado.
                        return 0;
                    }else{
                        //Informa qual funcionario esta Logado.
                        return (*dtBase)[i].codigo;
                    }
                } else {
                    printf("\n[Erro 401] Senha errada.\n");
                    system("Pause");
                }

            } else {
                printf("\n[Erro 401] Usuario nao Encontrado.\n");
                system("Pause");
            }
        }
    }
}





int carregarDadosFuncionarios(funcionarios **dtBase, int *qtdFuncionarios, int *tamanhoFuncionarios, int *id, int tipo_config) {
    FILE *p = NULL;
    funcionarios new;
    char password[16];
    int t = 0;
    if (tipo_config == 1){ //Arquivo TXT
        p = fopen("cpyBdFuncionario.txt", "r");

        if (p == NULL){
            printf("\nErro na Leitura 'cpyBdFuncionario.txt' \n");
            return 1;
        }

        while (!feof(p)){
            if (!filelength(fileno(p))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fscanf(p, "%d\n", &new.codigo);

            fgets(new.nome, 120, p);
            limpa_final_string(new.nome);

            fgets(new.cargo, 50, p);
            limpa_final_string(new.cargo);

            fgets(new.telefone, 17, p);
            limpa_final_string(new.telefone);

            fgets(new.email, 50, p);
            limpa_final_string(new.email);

            fgets(new.endereco.rua, 50, p);
            limpa_final_string(new.endereco.rua);

            fscanf(p, "%d\n", &new.endereco.numero);

            fgets(new.endereco.bairro, 50, p);
            limpa_final_string(new.endereco.bairro);

            fgets(new.endereco.cidade, 50, p);
            limpa_final_string(new.endereco.cidade);

            fgets(new.endereco.estado, 4, p);
            limpa_final_string(new.endereco.estado);


            fgets(new.login.user, 50, p);
            limpa_final_string(new.login.user);

            fgets(password, 16, p);
            new.login.password = retorna_password_file(password);


            if (verificaIdFuncionario(dtBase, *qtdFuncionarios, new.codigo) == 0){
                t = inserirFuncionario(dtBase, new, qtdFuncionarios, tamanhoFuncionarios);
                if (*id <= new.codigo) {
                    *id = new.codigo + 1;
                }
            }

            if (t == 0){
                printf("\nAcao Interrompida");
                break;
            }
        }
    }
    else  if (tipo_config == 0){ //Arquivo BIN
        p = fopen("cpyBdFuncionario.bin", "rb");
        if (p == NULL){
            printf("\nErro na Leitura 'cpyBdFuncionario.bin' \n");
            return 1;
        }
        while (!feof(p)){
            if (!filelength(fileno(p))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fread(&new,sizeof(funcionarios),1,p);
            printf("%s %s %s %s %s %s %s %s %s %s", new.nome, new.cargo, new.endereco.rua, new.endereco.bairro,
                   new.endereco.cidade, new.endereco.estado, new.telefone, new.email, new.login.user, new.login.password);
            if (verificaIdFuncionario(dtBase, *qtdFuncionarios, new.codigo) == 0){
                t = inserirFuncionario(dtBase, new, qtdFuncionarios, tamanhoFuncionarios);
                if (*id <= new.codigo) {
                    *id = new.codigo + 1;
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


int refazDadosFuncionario(funcionarios **dtbase, int *tamanhoFuncionario, int tipo_config){

    FILE *p;
    if (tipo_config== 1){
        p = fopen("cpyBdFuncionario.txt", "w");
        fclose(p);
        p = NULL;
        for (int i = 0; i < *tamanhoFuncionario; i++){
            saveFuncionario((*dtbase)[i],1);
        }
    }else if (tipo_config == 0){
        p = fopen("cpyBdFuncionario.bin", "wb");
        fclose(p);
        for (int i = 0; i < *tamanhoFuncionario; i++){
            saveFuncionario((*dtbase)[i],0);
        }
    }
    return 0;
}


