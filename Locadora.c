#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    char rua[10];
    int numero;
    char bairro[10];
    char cidade[10];
    char estado[2];

} endereco;

typedef struct
{
    int id;
    char nomeFantasia[10];
    char razaoSocial[10];
    char inscricaoEstadual[10];
    int cnpj;
    endereco endereco;
    char telefone[10];
    char email[10];
    char nomeResponsavel[10];
    char telefoneResponsavel[10];
} locadora;

locadora *dados;
int qtd = 0, tamanho = 1;

locadora criarLocadora(int atualizar){
    locadora obj;

    obj.id = 1;
    printf("===============================================\n");
    (atualizar == 1) ? printf("Atualizando locadora\n") : printf("Criando uma nova locadora\n");;
    printf("===============================================\n");
    printf("Nome Fantasia: ");
    scanf("%s", &obj.nomeFantasia);
    printf("Razão Social: ");
    scanf("%s", &obj.razaoSocial);
    printf("Inscrição Estadual: ");
    scanf("%s", &obj.inscricaoEstadual);
    printf("CNPJ: ");
    scanf("%d", &obj.cnpj);
    printf("Telefone: ");
    scanf("%s", &obj.telefone);
    printf("E-mail: ");
    scanf("%s", &obj.email);
    printf("Nome do Responsável: ");
    scanf("%s", &obj.nomeResponsavel);
    printf("Telefone do Responsável: ");
    scanf("%s", &obj.telefoneResponsavel);
    printf("===============================================");
    printf("Inserindo endereço da locadora\n");
    printf("===============================================\n");
    printf("Rua: ");
    scanf("%s", &obj.endereco.rua);
    printf("Número: ");
    scanf("%d", &obj.endereco.numero);
    printf("Bairro: ");
    scanf("%s", &obj.endereco.bairro);
    printf("Cidade: ");
    scanf("%s", &obj.endereco.cidade);
    printf("Estado: ");
    scanf("%s", &obj.endereco.estado);

    if (atualizar == 1) {
        if (qtd == tamanho) {
            tamanho += 1;
            dados = realloc(dados, tamanho * sizeof(locadora));
        }
        dados[qtd] = obj;
        qtd++;
    }
    return obj;
}

void imprimirLocadora(locadora obj){
    printf("\nIdentificador da Locadora: %d", obj.id);
    printf("\nNome Fantasia: %s", obj.nomeFantasia);
    printf("\nRazão Social: %s", obj.razaoSocial);
    printf("\nInscrição Estadual: %s", obj.inscricaoEstadual);
    printf("\nCNPJ: %d", obj.cnpj);
    printf("\nTelefone: %s", obj.telefone);
    printf("\nE-mail: %s", obj.email);
    printf("\nNome do Responsável: %s", obj.nomeResponsavel);
    printf("\nTelefone do Responsável: %s", obj.telefoneResponsavel);
    printf("\nEndereço: Rua %s, %d, Bairro %s, %s - %s,",
           obj.endereco.rua, obj.endereco.numero, obj.endereco.bairro, obj.endereco.cidade, obj.endereco.estado);
}

void imprimirLocadoraList(){
    for (int i = 0; i < qtd; ++i) {
        imprimirLocadora(dados[i]);
    }
}

void removerLocadora(int id){
    for (int i = 0; i < qtd; i++){
        if (dados[i].id == id){
            while (i < qtd - 1){
                dados[i] = dados[i + 1];
                i++;
            }
            qtd--;
            break;
        }
    }
}

void atualizarLocadora(int id){
    for (int i = 0; i < qtd; i++){
        if (dados[i].id == id){
            dados[i] = criarLocadora(1);
        }
    }
}