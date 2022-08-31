#include <stdlib.h>
#include <stdio.h>


/*Lembrar:
    Variaveis globais:
    *bd_ = Array dinamico que armazena em tempo de exercusão os filmes cadastrados
    int qtdFilmes = 0,  Variavel que controla em t. exercusão a qtd de filme cadastrado
    tamFilmes = 2; Variavel que controla o tamanho primitivo do *bd, usado para controle de Alocação
*/

typedef struct
{
    int codigo;
    char nome[10];  // Substituir por str
    char descricao[10]; // Substituir por str
    int qtd; // quantidade de mídias existentes na locadora
    int c_categoria;
    char lingua[10]; // Substituir por str

} n_filme;

n_filme *bd_; // dataBase local

n_filme objFilme(int id) // Bloco para receber as entradas e "compartar" na struct
{
    n_filme p;
    p.codigo = id;
    printf("Nome: ");
    scanf("%s", &p.nome);
    printf("Descricao: ");
    scanf("%s", &p.descricao);
    printf("Quantidade de Exemplares: ");
    scanf("%d", &p.qtd);
    printf("Codigo Categoria: ");
    scanf("%d", &p.c_categoria); //Possivelmente este campo precisa ser comparado ...
    printf("Lingua: ");
    scanf("%s", &p.lingua);
    return p;
}
// Adc filmes via ponteiro
// void addMovie(n_filme *bd){
//     printf("Nome: ");
//     scanf("%s",&bd->nome);
//     printf("Descricao: ");
//     scanf("%s",&bd->descricao);
//     printf("Quantidade de Exemplares: ");
//     scanf("%d",&bd->qtd);
//     printf("Codigo Categoria: ");
//     scanf("%d",&bd->c_categoria);
//     printf("Lingua: ");
//     scanf("%s",&bd->lingua);
// }
int qtdFilmes = 0, tamFilmes = 2;
void inserirFilme(n_filme p) //Recebe o objeto e insere no array bd_*
{
    // Se a quantidade de filmes for igual ao tamanho alocado da lista -> espandir
    if (qtdFilmes == tamFilmes)
    {
        tamFilmes *= 1.5;
        bd_ = realloc(bd_, tamFilmes * sizeof(n_filme));
    }
    // adc obj ao bd local
    bd_[qtdFilmes] = p;
    qtdFilmes++; 
}

void listarFilmes() // precisa criar um filtro
{
    printf("\nListando %d - Filmes cadastrados\n", qtdFilmes);
    for (int c = 0; c < qtdFilmes; c++)
    {
        printf("-----------------------------------\n");
        printf("(%d)\n", c + 1);
        printf("Nome  = %s\n", bd_[c].nome);
        printf("Descricao = %s\n", bd_[c].descricao);
        printf("Quantidade de Exemplares: %d\n", bd_[c].qtd);
        printf("Codigo Categoria: %d\n", bd_[c].c_categoria);
        printf("Lingua: %s\n", bd_[c].lingua);
    }
}
void removerFilme(int codigo)
{
    for (int i = 0; i < qtdFilmes; i++)
    {
        if ((bd_[i].codigo - codigo) == 0)
        {
            // A operação de remover sobrescreve o conteudo de bd_ menos a posição desejada
            while (i < qtdFilmes - 1)
            {
                bd_[i] = bd_[i + 1];
                i++;
            }
            qtdFilmes--;
            break;
        }
    }
}

void alterarfilme(int codigo)
{
    n_filme p;
    p = objFilme(codigo);
    for (int i = 0; i < qtdFilmes; i++)
    {
        if(bd_[i].codigo == codigo)
        {
            bd_[i] = p;
            break;
        }
    }
}


int main()
{
    // Adicionar Filme
    bd_ = malloc(tamFilmes * sizeof(n_filme));
    n_filme p;
    for (int j = 0; j < 2; j++)
    {
        p = objFilme(qtdFilmes);
        inserirFilme(p);
    }

    listarFilmes();
    printf("\n");
    int key_filme;

    printf("Digite o Codigo do Filme que deseja editar: ");
    scanf("%d", &key_filme);
    alterarfilme(key_filme);

    listarFilmes();
    printf("\n");

    printf("Digite o Codigo do Filme que deseja remover: ");
    scanf("%d", &key_filme);

    removerFilme(key_filme);

    listarFilmes();
    printf("\n");

    free(bd_);
    return (0);
}