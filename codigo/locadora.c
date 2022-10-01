#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

    setbuf(stdin,NULL);

    printf("Senha: ");
    obj.password = obterPassword(16);

    return obj;
}

int inserirLocadora(locadora **dtbase, locadora novaLocadora, int *qtdLocadora, int *tamanhoLocadora, int tipo_config) {
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

int removerLocadora(locadora **dtbase, int id, int *qtdLocadora, int *tamanhoLocadora, int tipo_config){
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
    refazDados_Locadora(dtbase,qtdLocadora,tamanhoLocadora,tipo_config);
    return 0;
}

void listLocadora(locadora **dtbase, int qtd){
    if (qtd > 0) {
        printf("\nID \t Nome Fantasia \t Razão Social \t Inscrição Estadual \t CNPJ \t Telefone \t E-mail \t "
               "Nome do Responsável \t Telefone do Responsável \t Rua \t Número \t Bairro \t Cidade \t Estado\n");
        for (int c = 0; c < qtd; c++) {
            printf("---------------------------------------------------------------------------------\n");
            printf("(%d)\t %s\t %s\t %s\t %s\t %s\t %s\t %s\t %s\t %s\t %d\t %s\t %s\t %s \n",
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
            locadora newEntrada = criarLocadora(&id);
            (*dtbase)[i] = newEntrada;
            break;
        }
    }
    *qtdLocadora = *qtdLocadora - 1;
}

int menuLocadora(locadora **dtbase, int *qtdLocadora,int *tamanhoLocadora,int *id, int tipo_config){
    int erro = 0, exit = 0, opc = 0;
    system("cls");
    line(30,"Locadora\0");
    printf("\t 0 - Sair \t 1 - Cadastrar \n");
    printf("\t 2 - Visualizar \t 3 - Editar \n\t 4 - Remover");
    line(30,"-\0");

    do
    {
        if (erro == 1)
        {
            printf(">> Parametro Invalido\n");
            printf("dsa");
        }
        printf("\n>> Opc: ");
        scanf("%d", &opc);
        erro = 1;
    } while (opc < 0 || opc > 5);

    if (opc == 0)
    {
        printf(">> Exit");
        exit = 1;
    }
    else if (opc == 1)
    {
        // Cadastrar uma Locadora
        system("cls");
        printf(">> Nova Locadora     \tID: %d \n", *id);
        locadora newLocadora = criarLocadora(id);
        inserirLocadora(dtbase,newLocadora,qtdLocadora,tamanhoLocadora, tipo_config);
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
        printf("Editar (ID):");
        scanf("%d", &cod);

        editaLocadora(dtbase,qtdLocadora,tamanhoLocadora,cod);
    }
    else if (opc == 4)
    {
        // Remover
        system("cls");
        listLocadora(dtbase, *qtdLocadora);

        int cod;
        printf("Remover (ID):");
        scanf("%d", &cod);

        removerLocadora(dtbase,cod,qtdLocadora,tamanhoLocadora,tipo_config);
    }
    return exit;
}

int saveLocadora(locadora objeto,int tipo_config){
    FILE *locadora;

    if (tipo_config == 1){//Arquivo TXT
        locadora = fopen("cpyBdLocadora.txt", "a");

        if (locadora == NULL){ // Se a abertura falhar
            return 1;
        }

        fprintf(locadora,"%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%s\n%s\n%s\n",
                objeto.id,
                objeto.nomeFantasia,
                objeto.razaoSocial,
                objeto.inscricaoEstadual,
                objeto.cnpj,
                objeto.telefone,
                objeto.email,
                objeto.nomeResponsavel,
                objeto.telefoneResponsavel,
                objeto.endereco.rua,
                objeto.endereco.numero,
                objeto.endereco.bairro,
                objeto.endereco.cidade,
                objeto.endereco.estado);

    }
    if (tipo_config == 0){ //Arquivo BINARIO
        locadora = fopen("cpyBdLocadora.bin", "ab");
        if (locadora == NULL){ // Se a abertura falhar
            return 1;
        }
        fwrite(&objeto, sizeof(filme), 1,locadora);
    }
    fclose(locadora);
    return 0;
}

int carregarDados_Locadora(locadora **dtBase, int *qtdLocadora, int *tamanhoLocadora, int *id,int tipo_config) {
    printf(">> Carregando Dados de Locadora ...\n");
    FILE *p;
    locadora new;
    int t = 0;
    if (tipo_config == 1){ //Arquivo TXT
        p = fopen("cpyBdLocadora.txt", "r");

        if (p == NULL){
            printf("\nErro na Leitura 'cpyBdLocadora.txt' \n");
            system("Pause");
            return 1;
        }

        while (!feof(p)){
//            if (!filelength(fileno(p))){  /* teste para saber se o tamanho do arquivo é zero */
//                break;
//            }


            fscanf(p, "%d\n", &new.id);

            fgets(new.nomeFantasia, 50, p);
            limpa_final_string(new.nomeFantasia);

            fgets(new.razaoSocial, 50, p);
            limpa_final_string(new.razaoSocial);

            fgets(new.inscricaoEstadual,30, p);
            limpa_final_string(new.razaoSocial);

            fgets(new.cnpj, 15, p);
            limpa_final_string(new.cnpj);

            fgets(new.endereco.rua, 50, p);
            limpa_final_string(new.endereco.rua);

            fscanf(p, "%d\n", &new.endereco.numero);

            fgets(new.endereco.bairro, 10, p);
            limpa_final_string(new.endereco.bairro);

            fgets(new.endereco.cidade, 10, p);
            limpa_final_string(new.endereco.cidade);

            fgets(new.endereco.estado, 3, p);
            limpa_final_string(new.endereco.estado);

            t = inserirLocadora(dtBase,new,qtdLocadora,tamanhoLocadora,tipo_config);
            if (*id <= new.id) {
                *id = new.id + 1;
            }

            if (t == 0){
                printf("\nAcao Interrompida");
                fclose(p);
                break;
            }
        fclose(p);
        printf("Okay");
        }
    }
    else  if (tipo_config == 0){ //Arquivo BIN
        p = fopen("cpyBdFilme.bin", "rb");
        while (!feof(p)){
            if (!filelength(fileno(p))){  /* teste para saber se o tamanho do arquivo é zero */
                break;
            }
            fread(&new,sizeof(locadora),1,p);
            t = inserirLocadora(dtBase,new,qtdLocadora,tamanhoLocadora,tipo_config);
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
int refazDados_Locadora(locadora **dtbase, int *qtdLocadora, int *tamanhoLocadora, int tipo_configuracao){

    FILE *p;
    if (tipo_configuracao == 1){
        p = fopen("cpyBdFilme.txt", "w");
        fclose(p);
        p = NULL;
        for (int i = 0; i < *tamanhoLocadora; i++){
            saveLocadora((*dtbase)[i],1);
        }
    }else if (tipo_configuracao == 0){
        p = fopen("cpyBdFilme.bin", "wb");
        fclose(p);
        for (int i = 0; i < *tamanhoLocadora; i++){
            saveLocadora((*dtbase)[i],0);
        }
    }
    return 0;
}

int set_configuracao_Locadora(locadora **dtbase,char *user,char *password,int *qtdLocadora,int *tamanhoLocadora, int *id){
    locadora new = criarLocadora(id);
    inserirLocadora(dtbase,new,qtdLocadora,tamanhoLocadora,*id);

    strcpy(user,new.user);
    new.password = password;

    //SALVAR NO ARQUIVO DE LOCADORAS
}

//locadora *bd_locadora;
//int qtdLocadora = 0, tamanhoLocadora = 1, idControleLocadora = 0;
//
//int main(){
//    bd_locadora = malloc(tamanhoLocadora * sizeof(locadora));
//    while (1)
//    {
//        int t = menuLocadora(&bd_locadora,&qtdLocadora,&tamanhoLocadora,&idControleLocadora);
//        if (t == 1){
//            break;
//        }
//    }
//    free(bd_locadora);
//    return 0;
//}