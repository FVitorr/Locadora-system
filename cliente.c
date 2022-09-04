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
    char nome[10];
    endereco endereco;
    int cpf;
    char telefone[10];
    char email[10];
    char sexo[1];
    char estadoCivil[10];
    char dataNascimento[10];
} cliente;

cliente *dados;
int qtd = 0, tamanho = 1;

cliente criarcliente(int atualizar){
    cliente obj;

    obj.id = 1;
    printf("===============================================\n");
    (atualizar == 1) ? printf("Atualizando o cliente\n") : printf("Criando um novo cliente\n");
    printf("===============================================\n");
    printf("Nome: ");
    scanf("%s", &obj.nome);
    printf("CPF: ");
    scanf("%d", &obj.cpf);
    printf("Telefone: ");
    scanf("%s", &obj.telefone);
    printf("E-mail: ");
    scanf("%s", &obj.email);
    printf("Sexo (M para MASCULINO e F para FEMININO): ");
    scanf("%s", &obj.sexo);
    printf("Estado civil: ");
    scanf("%s", &obj.estadoCivil);
    printf("Data de Nascimento (Utilize o seguinte formato 11/11/1111): ");
    scanf("%s", &obj.dataNascimento);
    printf("===============================================");
    printf("Inserindo endereço do cliente\n");
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
            dados = realloc(dados, tamanho * sizeof(cliente));
        }
        dados[qtd] = obj;
        qtd++;
    }
    return obj;
}

void imprimircliente(cliente obj){
    printf("\nIdentificador do cliente: %d", obj.id);
    printf("\nNome: %s", obj.nome);
    printf("\nEndereço: Rua %s, %d, Bairro %s, %s - %s,",
           obj.endereco.rua, obj.endereco.numero, obj.endereco.bairro, obj.endereco.cidade, obj.endereco.estado);
    printf("\nCPF: %d", obj.cpf);
    printf("\nTelefone: %s", obj.telefone);
    printf("\nE-mail: %s", obj.email);
    printf("\nSexo: %s", (obj.sexo[0] == 'F') ? "Feminino" : "Masculino");
    printf("\nEstado civil: %s", obj.estadoCivil);
    printf("\nData de nascimento: %s", obj.dataNascimento);
}

void imprimirclienteList(){
    for (int i = 0; i < qtd; ++i) {
        imprimircliente(dados[i]);
    }
}

void removercliente(int id){
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

void atualizarcliente(int id){
    for (int i = 0; i < qtd; i++){
        if (dados[i].id == id){
            dados[i] = criarcliente(1);
        }
    }
}
