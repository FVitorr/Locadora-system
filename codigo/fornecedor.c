#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <stdint.h>
#include "../cabecalhos/fucGlobal.h"
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

    setbuf(stdin,NULL);
    printf("CNPJ: ");
    scanf("%[^\n]s", obj.cnpj);

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

int inserirFornecedor(fornecedor **dtbase, fornecedor novoFornecedor, int *qtdFornecedor, int *tamanhoFornecedor) {
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

int removerFornecedor(fornecedor **dtbase, int id, int *qtdFornecedor, int tipo_config) {
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
    refazDadosFornecedor(dtbase, qtdFornecedor, tipo_config);
    return 0;
}

int posArrayFornecedor(fornecedor **dtbase,int qtd_Locadora,int id){
    for (int i = 0; i < qtd_Locadora; i++){
        if ((*dtbase)[i].id == id){
            return i;
        }
    }
    return -1;
}


void listFornecedor(fornecedor **dtbase, int qtd) {
    if (qtd > 0) {
//        printf("\nID \t Nome Fantasia \t Razão Social \t Inscrição Estadual \t CNPJ \t Telefone \t E-mail \t "
//               " Rua \t Número \t Bairro \t Cidade \t Estado\n");
        for (int c = 0; c < qtd; c++) {
            printf("---------------------------------------------------------------------------------\n");
            printf("(ID : %d)\n Nome Fantasia: %s\n Razão Social: %s\n Inscrição Estadual: %s\n CNPJ: %s\n Telefone: %s\n E-mail: %s \n Endereco: %s, %d, %s, %s-%s \n",
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
    printf("\n\n");
}

void editarFornecedor(fornecedor **dtbase, int qtdFornecedor, int id, int tipo_config)
{
    for (int i = 0; i < qtdFornecedor; i++) {
        if ((*dtbase)[i].id == id) {
            fornecedor newEntrada = criarFornecedor(id);
            (*dtbase)[i] = newEntrada;
            break;
        }
    }
    refazDadosFornecedor(dtbase, qtdFornecedor, tipo_config);
}

int menuFornecedor(fornecedor **bd_fornecedor, int *qtdFornecedor,int *tamanhoFornecedor,int *idControleFornecedor, int tipo_config) {
    int escolha = INT32_MAX;
    char temEscolha[4];

    while (1) {
        system("cls");
        setbuf(stdin,NULL);
        lineBox(70,"MENU FORNECEDOR\0",1);
        printf("\tDigite a opcao referente a operacao que deseja executar\n\n");
        printf("\t0 - Sair \n\t1 - Cadastrar \n\t2 - Visualizar \n\t3 - Editar \n\t4 - Remover\n");
        lineBox(70,"-\0",0);

        //Tratamento de entrada
        printf(">>");
        scanf("%s", temEscolha); //Permite a entrada de qualquer caracter
        setbuf(stdin,NULL);

        escolha = strtol(temEscolha,NULL,10); //Procura na entrada um numero na base 10

        switch (escolha) {
            case 1: {
                int IDFornecedor = retornarUltimoID_Fornecedor(bd_fornecedor, *qtdFornecedor);
                fornecedor newFornecedor = criarFornecedor(IDFornecedor);
                inserirFornecedor(bd_fornecedor, newFornecedor, qtdFornecedor, tamanhoFornecedor);
                saveFornecedor(newFornecedor, tipo_config);
                break;
            }
            case 2: {
                listFornecedor(bd_fornecedor, *qtdFornecedor);
                system("pause");
                break;
            }
            case 3: {
                int id = 0;
                listFornecedor(bd_fornecedor, *qtdFornecedor);
                printf("\n\tDigite o ID do Fornecedor que deseja editar (0- Sair)\n>>");
                scanf("%d", &id);
                if (id == 0){
                    break;
                }
                editarFornecedor(bd_fornecedor, *qtdFornecedor, tamanhoFornecedor, id, tipo_config);
                break;
            }
            case 4: {
                int id = 0;
                listFornecedor(bd_fornecedor, *qtdFornecedor);
                printf("\n\tDigite o ID do Fornecedor que deseja excluir (0- Sair)\n>>");
                scanf("%d", &id);
                if (id == 0){
                    break;
                }
                removerFornecedor(bd_fornecedor, id, qtdFornecedor, tipo_config);
                break;
            }
            case 0: {
                system("cls");
                return 1;
            }
            default: {
                printf("Esta não é uma opção válida, favor selecionar novamente.\n");
                break;
            }
        }
    }
}


int saveFornecedor(fornecedor objeto, int tipo_config){
    FILE *fonecedoresF = NULL;

    if (tipo_config == 1){//Arquivo TXT
        if (verifica_arquivos(tipo_config,"cpyBdFornecedor.txt\0") == 1){
            fonecedoresF = fopen("cpyBdFornecedor.txt", "ab");
        } else{
            fonecedoresF = fopen("cpyBdFornecedor.txt", "wb");
        }

        if (fonecedoresF == NULL){ // Se a abertura falhar
            return 1;
        }

        fprintf(fonecedoresF, "%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%s\n%s\n%s\n",
                objeto.id,
                objeto.nomeFantasia,
                objeto.razaoSocial,
                objeto.inscricaoEstadual,
                objeto.cnpj,
                objeto.telefone,
                objeto.email,
                objeto.endereco.rua,
                objeto.endereco.numero,
                objeto.endereco.bairro,
                objeto.endereco.cidade,
                objeto.endereco.estado
        );

    }else if (tipo_config == 0){ //Arquivo BINARIO
        if (verifica_arquivos(tipo_config,"cpyBdFornecedor.bin\0") == 1){
            fonecedoresF = fopen("cpyBdFornecedor.bin", "ab");
        } else{
            fonecedoresF = fopen("cpyBdFornecedor.bin", "wb");
        }
        if (fonecedoresF == NULL){ // Se a abertura falhar
            return 1;
        }
        fwrite(&objeto, sizeof(fornecedor), 1, fonecedoresF);
    }
    fclose(fonecedoresF);
    return 0;
}

char *nomeFornecedor(fornecedor **dtbase, int qtd, int id){
    for (int i =0 ; i < qtd; i++){
        if ((*dtbase)[i].id == id){
            return (*dtbase)[i].nomeFantasia;
        }
    }
    return NULL;
}


int retornarUltimoID_Fornecedor(fornecedor **dtBase, int qtdFornecedor){
    int id,tId = 0;
    id = (qtdFornecedor > 0) ? (*dtBase)[0].id : 1;
    for (int i = 0; i < qtdFornecedor; i++){
        if ((*dtBase)[i].id <= id){
            id = (*dtBase)[i].id + 1;
        }
    }
    return id;
}
int verificaIdFornecedor(fornecedor **dtbase, int qtdFornecedor, int id) {
    for (int i = 0; i < qtdFornecedor; i++) {
        if ((*dtbase)[i].id == id) {
            return 1;
        }
    }
    return 0;
}

int carregarDadosFornecedores(fornecedor **dtBase, int *qtdFornecedor, int *tamanhoFornecedor, int *id, int tipo_config) {
    FILE *p = NULL;
    fornecedor new;
    int t = 0;
    if (tipo_config == 1){ //Arquivo TXT
        p = fopen("cpyBdFornecedor.txt", "r");

        if (p == NULL){
            printf("\nErro na Leitura 'cpyBdFornecedor.txt' \n");
            return 1;
        }

        while (!feof(p)){
            if (!filelength(fileno(p))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fscanf(p, "%d\n", &new.id);

            fgets(new.nomeFantasia, 100, p);
            limpa_final_string(new.nomeFantasia);

            fgets(new.razaoSocial, 100, p);
            limpa_final_string(new.razaoSocial);

            fgets(new.inscricaoEstadual, 30, p);
            limpa_final_string(new.inscricaoEstadual);

            fgets(new.cnpj,16,p);
            limpa_final_string(new.cnpj);
            //fscanf(p, "%d\n", &new.cnpj);

            fgets(new.telefone, 15, p);
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

            fgets(new.endereco.estado, 3, p);
            limpa_final_string(new.endereco.estado);

            if (verificaIdFornecedor(dtBase, *qtdFornecedor, new.id) == 0){
                t = inserirFornecedor(dtBase, new, qtdFornecedor, tamanhoFornecedor);
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
        p = fopen("cpyBdFornecedor.bin", "rb");
        if (p == NULL){
            printf("\nErro na Leitura 'cpyBdFornecedor.bin' \n");
            return 1;
        }
        while (!feof(p)){
            if (!filelength(fileno(p))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fread(&new,sizeof(fornecedor),1,p);
            printf("%s %s %s %s %s %s %s %s %s", new.nomeFantasia, new.razaoSocial, new.inscricaoEstadual, new.telefone, new.email, new.endereco.rua, new.endereco.bairro, new.endereco.cidade, new.endereco.estado);
            if (verificaIdFornecedor(dtBase, *qtdFornecedor, new.id) == 0){
                t = inserirFornecedor(dtBase, new, qtdFornecedor, tamanhoFornecedor);
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
    return 0;
}


int refazDadosFornecedor(fornecedor **dtbase, int *tamanhoFornecedor, int tipo_config){

    FILE *p;
    if (tipo_config== 1){
        p = fopen("cpyBdFornecedor.txt", "w");
        fclose(p);
        p = NULL;
        for (int i = 0; i < *tamanhoFornecedor; i++){
            saveFornecedor((*dtbase)[i],1);
        }
    }else if (tipo_config == 0){
        p = fopen("cpyBdFornecedor.bin", "wb");
        fclose(p);
        for (int i = 0; i < *tamanhoFornecedor; i++){
            saveFornecedor((*dtbase)[i],0);
        }
    }
    return 0;
}


