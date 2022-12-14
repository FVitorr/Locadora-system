#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include "../cabecalhos/locadora.h"
#include "../cabecalhos/fucGlobal.h"

locadora criarLocadora(int *id) {

    locadora obj;
    obj.id = *id;

    *id = *id + 1;

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
    scanf("%s", obj.cnpj);

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

    setbuf(stdin,NULL);
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

    setbuf(stdin,NULL);
    line(100,"Autentificacao de Administrador\0");
    printf("Usuario: ");
    scanf("%[^\n]s", obj.user);
    limpa_final_string(obj.user);
    removeSpace(obj.user);

    setbuf(stdin,NULL);

    printf("Tamanho Maximo: 15\n");
    printf("Senha: ");
    obj.password = obterPassword(16);

    setbuf(stdin,NULL);
    printf("\nMulta por Atraso: ");
    scanf("%f", &obj.monetario.multaLocadora);

    obj.monetario.caixa = 0;
    obj.monetario.despesas = 0;
    obj.monetario.contasReceber = 0;

    return obj;
}

int inserirLocadora(locadora **dtbase, locadora novaLocadora, int *qtdLocadora, int *tamanhoLocadora) {
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
    (*dtbase)[*tamanhoLocadora - 1] = novaLocadora;
    *qtdLocadora = *qtdLocadora + 1;
    //saveLocadora(novaLocadora,tipo_config);
    return 1;
}

int removerLocadora(locadora **dtbase, int id, int *qtdLocadora, int tipo_config){
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
    refazDados_Locadora(dtbase,*qtdLocadora,tipo_config);
    return 0;
}

void listLocadora(locadora **dtbase, int qtd){
    if (qtd > 0) {
    //printf("\nID  Nome Fantasia  Razão Social  Inscrição Estadual  CNPJ \t Telefone \t E-mail \t "
    //           "Nome do Responsável \t Telefone do Responsável \t Rua \t Número \t Bairro \t Cidade \t Estado\n");
        for (int c = 0; c < qtd; c++) {
            printf("---------------------------------------------------------------------------------\n");
            printf("ID: (%d)\nNome Fantasia: %s\nRazão Social: %s \nInscrição Estadual: %s\nCNPJ: %s\nTelefone: %s\nE-mail: %s\nNome do Responsável: %s\nTelefone do Responsável: %s\nRua: %s\nNumero: %d\nBairro: %s\nCidade: %s\nEstado: %s \n",
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
            //printf("\n\nUser: %s\nPassword:  %s",(*dtbase)[c].user,(*dtbase)[c].password);
        }
    }
    else{
        printf("\n\t>> Nada para mostrar aqui");
    }
    printf("\n");
}

void editaLocadora(locadora **dtbase, int qtdLocadora, int id, int tipo_config)
{
    for (int i = 0; i < qtdLocadora; i++) {
        if ((*dtbase)[i].id == id) {
            locadora newEntrada = criarLocadora(&id);
            (*dtbase)[i] = newEntrada;
            break;
        }
    }
    refazDados_Locadora(dtbase,qtdLocadora,tipo_config);
}

int menuLocadora(locadora **dtbase, int *qtdLocadora,int *tamanhoLocadora,int *id, int tipo_config){
    int erro = 0, opc;
    char temEscolha[4];

    system("cls");
    setbuf(stdin,NULL);
    lineBox(70,"MENU LOCADORA\0",1);
    printf("\tDigite a opcao referente a operacao que deseja executar\n\n");
    printf("\t0 - Sair \n\t1 - Cadastrar \n\t2 - Visualizar \n\t3 - Editar \n\t4 - Remover\n");
    lineBox(70,"-\0",0);



    do
    {
        if (erro == 1)
        {
            printf(">> Parametro Invalido\n");
            printf("dsa");
        }
        //Tratamento de entrada
        printf(">>");
        scanf("%s", temEscolha); //Permite a entrada de qualquer caracter
        setbuf(stdin,NULL);

        opc = strtol(temEscolha,NULL,10); //Procura na entrada um numero na base 10
        erro = 1;
    } while (opc < 0 || opc > 5);

    if (opc == 0)
    {
        system("cls");
        return 1;
    }
    else if (opc == 1)
    {
        // Cadastrar uma Locadora
        system("cls");
        printf(">> Nova Locadora     \tID: %d \n", *id);
        locadora newLocadora = criarLocadora(id);
        inserirLocadora(dtbase,newLocadora,qtdLocadora,tamanhoLocadora);
        saveLocadora(newLocadora,tipo_config);
    }
    else if (opc == 2)
    {
        // Visualizar
        system("cls");
        printf(">> Locadora Cadastrada  \t Total: %d\n\n", *qtdLocadora);
        listLocadora(dtbase, *qtdLocadora);
        system("pause");
    }
    else if (opc == 3)
    {
        // editar
        system("cls");
        printf(">> Locadora Cadastrada  \t Total: %d\n\n", *qtdLocadora);
        listLocadora(dtbase, *qtdLocadora);

        int cod;
        printf("Informe o ID que deseja Editar (0- Sair):");
        scanf("%d", &cod);

        if (cod == 0){
            return -1;
        }
        editaLocadora(dtbase,*qtdLocadora,cod,tipo_config);
    }
    else if (opc == 4)
    {
        // Remover
        system("cls");
        listLocadora(dtbase, *qtdLocadora);

        int cod;
        printf("Informe o ID que deseja Excluir (0- Sair):");
        scanf("%d", &cod);

        if (cod == 0){
            return -1;
        }

        if (confirm_remover(cod) == 1) {
            removerLocadora(dtbase,cod,qtdLocadora,tipo_config);
            sucess();
        }else{
            info_cancela();
        }
    }
    return 0;
}

int saveLocadora(locadora objeto,int tipo_config){
    FILE *locadoraF = NULL;

    if (tipo_config == 1){//Arquivo TXT
        //Se o arquivo não existir, tentar criar.
        if (verifica_arquivos(tipo_config,"cpyBdLocadora.txt\0") == 1){
            locadoraF = fopen("cpyBdLocadora.txt", "a");
        } else{
            locadoraF = fopen("cpyBdLocadora.txt", "w");
        }

        if (locadoraF == NULL){ // Se a abertura falhar
            return 1;
        }

        fprintf(locadoraF,"%d\n%s\n%s\n%s\n%s\n%s\n%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%f\n%f\n%f\n%f\n%s\n%s\n",
                objeto.id,
                objeto.nomeFantasia,
                objeto.razaoSocial,
                objeto.inscricaoEstadual,
                objeto.cnpj,
                objeto.endereco.rua,
                objeto.endereco.numero,
                objeto.endereco.bairro,
                objeto.endereco.cidade,
                objeto.endereco.estado,
                objeto.telefone,
                objeto.email,
                objeto.nomeResponsavel,
                objeto.telefoneResponsavel,

                objeto.monetario.caixa,
                objeto.monetario.despesas,
                objeto.monetario.contasReceber,
                objeto.monetario.multaLocadora,

                objeto.user,
                objeto.password
);

    }
    if (tipo_config == 0){ //Arquivo BINARIO
        //Se o arquivo não existir, tentar criar.
        if (verifica_arquivos(tipo_config,"cpyBdLocadora.bin\0") == 1){
            locadoraF = fopen("cpyBdLocadora.bin", "ab");
        } else{
            locadoraF = fopen("cpyBdLocadora.bin", "wb");
        }
        if (locadoraF == NULL){ // Se a abertura falhar
            return 1;
        }
        fwrite(&objeto, sizeof(filme), 1,locadoraF);
    }
    fclose(locadoraF);
    locadoraF = NULL;
    return 0;
}
int verifica_IDLocadora(locadora **dtbase,int qtd_Locadora,int id) {
    for (int i = 0; i < qtd_Locadora; i++) {
        if ((*dtbase)[i].id == id) {
            return 1;
        }
    }
    return 0;
}

int carregarDados_Locadora(locadora **dtBase, int *qtdLocadora, int *tamanhoLocadora, int *id,int tipo_config) {
    locadora new;
    int t = 0;
    char password[16];
    if (tipo_config == 1){ //Arquivo TXT
        FILE *arquivo = NULL;
        arquivo = fopen("cpyBdLocadora.txt", "r");

        if (arquivo == NULL){
            printf("\nErro na Leitura 'cpyBdLocadora.txt' \n");
            return 1;
        }

        while(!feof(arquivo)){
            if (!filelength(fileno(arquivo))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }

            fscanf(arquivo, "%d\n", &new.id);

            fgets(new.nomeFantasia, 120, arquivo);
            limpa_final_string(new.nomeFantasia);

            fgets(new.razaoSocial, 50, arquivo);
            limpa_final_string(new.razaoSocial);

            fgets(new.inscricaoEstadual,30, arquivo);
            limpa_final_string(new.inscricaoEstadual);

            fgets(new.cnpj, 15, arquivo);
            limpa_final_string(new.cnpj);

            fgets(new.endereco.rua, 50, arquivo);
            limpa_final_string(new.endereco.rua);

            fscanf(arquivo, "%d\n", &new.endereco.numero);

            fgets(new.endereco.bairro, 50, arquivo);
            limpa_final_string(new.endereco.bairro);

            fgets(new.endereco.cidade, 50, arquivo);
            limpa_final_string(new.endereco.cidade);

            fgets(new.endereco.estado, 50, arquivo);
            limpa_final_string(new.endereco.estado);

            fgets(new.telefone, 15, arquivo);
            limpa_final_string(new.telefone);

            fgets(new.email, 50, arquivo);
            limpa_final_string(new.email);

            fgets(new.nomeResponsavel, 50, arquivo);
            limpa_final_string(new.nomeResponsavel);

            fgets(new.telefoneResponsavel, 15, arquivo);
            limpa_final_string(new.telefoneResponsavel);

            fscanf(arquivo, "%f\n", &new.monetario.caixa);
            fscanf(arquivo, "%f\n", &new.monetario.despesas);
            fscanf(arquivo, "%f\n", &new.monetario.contasReceber);
            fscanf(arquivo, "%f\n", &new.monetario.multaLocadora);

            fgets(new.user, 30, arquivo);
            limpa_final_string(new.user);

            fgets(password, 16, arquivo);

            new.password = retorna_password_file(password);
            //printf("New.PassWord: %s",new.password);

            if (verifica_IDLocadora(dtBase,*qtdLocadora,new.id) == 0){
                t = inserirLocadora(dtBase,new,qtdLocadora,tamanhoLocadora);
                if (*id <= new.id) {
                    *id = new.id + 1;
                }
            }

            if (t == 0){
                printf("\nAcao Interrompida");
                break;
            }
        }
        fclose(arquivo);
    }
    else  if (tipo_config == 0){ //Arquivo BIN
        FILE *p;
        p = fopen("cpyBdLocadora.bin", "rb");
        if (p == NULL){
            printf("\nErro na Leitura 'cpyBdLocadora.bin' \n");
            return 1;
        }
        while (!feof(p)){
            if (!filelength(fileno(p))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fread(&new,sizeof(locadora),1,p);
            t = inserirLocadora(dtBase,new,qtdLocadora,tamanhoLocadora);
            if (*id <= new.id) {
                    *id = new.id + 1;
            }

            if (t == 0){
                printf("\nAcao Interrompida");
                break;
            }
        }
        fclose(p);
    }
    return 0;
}
int refazDados_Locadora(locadora **dtbase, int qtdLocadora, int tipo_configuracao){

    FILE *p;
    if (tipo_configuracao == 1){
        p = fopen("cpyBdLocadora.txt", "w");
        fclose(p);
        for (int i = 0; i < qtdLocadora; i++){
            saveLocadora((*dtbase)[i],1);
        }
    }else if (tipo_configuracao == 0){
        p = fopen("cpyBdLocadora.bin", "wb");
        fclose(p);
        for (int i = 0; i < qtdLocadora; i++){
            saveLocadora((*dtbase)[i],0);
        }
    }
    return 0;
}


