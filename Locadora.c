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

locadora criarLocadora();
void imprimirLocadora(locadora obj);
void imprimirLocadoraList(locadora obj[]);

int main(){

    locadora locadoraCriada = criarLocadora();
    imprimirLocadora(locadoraCriada);
    return 0;

}

locadora criarLocadora(){
    locadora obj;

    obj.id = 1;
    printf("===============================================\n");
    printf("Criando nova locadora\n");
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
    return obj;
}

void imprimirLocadora(locadora obj){
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

void imprimirLocadoraList(locadora obj[]){
    obj
}