#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct 
{
    char user[120];
    char *password;
}autentificacao;

typedef struct 
{
    int codigo;
    char nome[50];
    char cargo[30];
    //Endereço
    char telefone[13];
    char email[50];

    autentificacao login;
}funcionarios;

int criarFuncionario(funcionarios **dtbase, int *qtdFuncionarios,int *tamanhoFuncionarios,int atualizar,int id){
    funcionarios obj;
    int erro = 0;

    obj.codigo = id;
    printf("===============================================\n");
    (atualizar == 1) ? printf("Atualizando Funcionario\n") : printf("Adicionar novo Funcionario\n");;
    printf("===============================================\n");
    fflush (stdin);

    printf("Nome : ");
    scanf("%[^\n]s", obj.nome);

    fflush (stdin);

    printf("Cargo: ");
    scanf("%s", obj.cargo);

    // printf("===============================================");
    // printf("Inserindo endereço da locadora\n");
    // printf("===============================================\n");
    // printf("Rua: ");
    // scanf("%s", obj.endereco.rua);
    // printf("Número: ");
    // scanf("%d", &obj.endereco.numero);
    // printf("Bairro: ");
    // scanf("%s", obj.endereco.bairro);
    // printf("Cidade: ");
    // scanf("%s", obj.endereco.cidade);
    // printf("Estado: ");
    // scanf("%s", obj.endereco.estado);
    fflush (stdin);

    printf("Telefone: ");
    scanf("%[^\n]s", obj.telefone);

    fflush (stdin);

    printf("E-mail: ");
    scanf("%[^\n]s", obj.email);

    fflush (stdin);

    printf("===============================================\n");
    printf("\tAcesso\n");
    printf("===============================================\n");
    printf("Usuario: ");
    scanf("%[^\n]s", obj.login.user);

    fflush (stdin);

    printf("Senha: ");
    //scanf("%[^\n]s", obj.login.password);
    if (*qtdFuncionarios == *tamanhoFuncionarios) {
            *tamanhoFuncionarios = *tamanhoFuncionarios +  1;
            (*dtbase) = realloc((*dtbase), *tamanhoFuncionarios * sizeof(funcionarios));
    }
    if ((*dtbase) == NULL ) {
        printf("Erro de Memoria");
        erro = 1;
    }
    if (atualizar == 1){
        (*dtbase)[id] = obj;
    }else{
        (*dtbase)[*qtdFuncionarios] = obj;
    }
    *qtdFuncionarios = *qtdFuncionarios + 1;
    
    return erro;
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

void editaFuncionarios(funcionarios **dtbase,int *qtdFuncionarios,int *tamanhoFuncionarios,int id)
{
    int t;
    for (int i = 0; i < *qtdFuncionarios; i++) {
        if ((*dtbase)[i].codigo == id) {
            t = criarFuncionario(dtbase,qtdFuncionarios,tamanhoFuncionarios,1,id);
            (t == 0) ? printf(">>Sucess") : printf("Erro");
            break;
        }
    }
    *qtdFuncionarios = *qtdFuncionarios - 1;
}

int removerFuncionarios(funcionarios **dtbase, int *qtdFuncionarios, int id){
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

int menuFuncionarios(funcionarios **dtbase, int *qtdFuncionarios,int *tamanhoFuncionarios,int *id){
    int opc = 0, erro = 0, exit = 0;
    system("cls");
    //line(30,"Funcionarios\0");
    printf("\t 0 - Sair \n\t 1 - Cadastrar \n\t 2 - Cadastrar Multiplas \n");
    printf("\t 3 - Visualizar \n\t 4 - Editar \n\t 5 - Remover");
    //line(30,"-\0");

    do
    {
        if (erro == 1)
        {
            printf(">> Parametro Invalido\n");
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
        // Cadastrar um Filme
        system("cls");
        printf(">> Novo Funcionario     \tID: %d \n", *id);
        criarFuncionario(dtbase,qtdFuncionarios,tamanhoFuncionarios,0,*id);
        *id = *id + 1;
    }
    else if (opc == 2)
    {
        // Cadastrar multiplas categoria
        system("cls");
        int op = 1;
        printf(">> Multiplos Funcionario     \tID: %d \n", *id);
        while (1)
        {
            criarFuncionario(dtbase,qtdFuncionarios,tamanhoFuncionarios,0,*id);
            printf("\n >> [1 - Mais] \t [0 - Exit]: ");
            scanf("%d", &op);
            *id = *id + 1;
            if (op == 0)
            {
                break;
            }

        }
    }
    else if (opc == 3)
    {
        // Visualizar
        system("cls");
        printf(">> Funcionarios Cadastrados  \t Total: %d\n\n", *qtdFuncionarios);
        listFuncionarios(dtbase, *qtdFuncionarios);
        system("pause");
    }
    else if (opc == 4)
    {
        // editar
        system("cls");
        printf(">> Funcionarios Cadastrados  \t Total: %d\n\n", *qtdFuncionarios);
        listFuncionarios(dtbase, *qtdFuncionarios);

        int cod;
        printf("Editar (ID):");
        scanf("%d", &cod);

        editaFuncionarios(dtbase,qtdFuncionarios,tamanhoFuncionarios,cod);
    }
    else if (opc == 5)
    {
        // Remover
        system("cls");
        listFuncionarios(dtbase, *qtdFuncionarios);

        int cod;
        printf("Remover (ID):");
        scanf("%d", &cod);

        removerFuncionarios(dtbase,qtdFuncionarios,cod);

        printf("%d",*qtdFuncionarios);
        system("pause");
    }
    return exit;
}


funcionarios  *bd_funcionarios;
int qtdFuncionarios = 0,TamanhoFuncionarios = 1, idControle = 0;

int main() {
    //printf("\n%p\n",&bd_cat);
    bd_funcionarios = malloc(TamanhoFuncionarios * sizeof(funcionarios));

    while (1){
        int v;
        v = menuFuncionarios(&bd_funcionarios,&qtdFuncionarios,&TamanhoFuncionarios,&idControle);
        if (v == 1){
            break;
        }
    }
    free(bd_funcionarios);
    return 0;
}