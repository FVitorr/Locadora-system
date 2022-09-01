#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int codigo;
    char nome[10];      // Substituir por str
    char descricao[10]; // Substituir por str
    int qtd;            // quantidade de mídias existentes na locadora
    int c_categoria;
    char lingua[10]; // Substituir por str

} filme;

filme *bd_filme; // dataBase local
int qtdFilme = 0, len_bd = 1;

// +++++++++++++++++++++++++++++++++++++++++ Subrotinas para controle dos filmes +++++++++++++++++

filme objFilme(int id) // Bloco para receber as entradas e "compartar" na struct
{
    filme p;
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

void inserirFilme(filme p) // Recebe o objeto e insere no array bd_*
{
    // Se a quantidade de filmes for igual ao tamanho alocado da lista -> espandir
    if (qtdFilme == len_bd)
    {
        len_bd += 1;
        bd_filme = realloc(bd_filme, len_bd * sizeof(filme));
    }
    // adc obj ao bd local
    bd_filme[qtdFilme] = p;
    qtdFilme++;
}
void removerFilme(filme *bd, int codigo)
{ // ponteiro global do db
    for (int i = 0; i < qtdFilme; i++)
    {
        if (bd[i].codigo == codigo)
        {
            while (i < qtdFilme - 1)
            {
                bd[i] = bd[i + 1];
                i++;
            }
            qtdFilme--;
            break;
        }
    }
}
void listFilme(filme *bd, int qtd)
{
    printf("\nID \t Nome \t Descrição \t Quant. Exemplares \t ID categoria \t Lingua\n");
    for (int c = 0; c < qtd; c++)
    {
        printf("---------------------------------------------------------------------------------\n");
        printf("(%d)\t %s\t %s\t\t\t %d\t\t %d\t\t %s\n", c, 
                                            bd[c].nome,
                                            bd[c].descricao,
                                            bd[c].qtd, 
                                            bd[c].c_categoria, 
                                            bd[c].lingua);
        // printf("\tDescricao:\t %s\n", bd[c].descricao);
        // printf("\tQnt de Exemplares:\t %d\n", bd[c].qtd);
        // printf("\tCodigo Categoria:\t %d\n", bd[c].c_categoria);
        // printf("\tLingua: \t%s\n", bd[c].lingua);
    }
    printf("\n");

}
int alterFilme(filme f, filme *bd, int codigo)
{
    for (int i = 0; i < qtdFilme; i++)
    {
        if (bd[i].codigo == codigo)
        {
            bd[i] = f;
            break;
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int menuFilme()
{
    int opc = 0, erro = 0, exit = 0;
    system("cls");
    printf("------------- Filmes -------------\n\n");
    printf("\t 0 - Sair \n\t 1 - Cadastrar \n\t 2 - Cadastrar Multiplas \n");
    printf("\t 3 - Visualizar \n\t 4 - Editar \n\t 5 - Remover\n");
    printf("--------------------------------------\n");

    do
    {
        if (erro == 1)
        {
            printf(">> Parametro Invalido\n");
        }
        printf("Opc: ");
        scanf("%d", &opc);
        erro = 1;
    } while (opc < 0 || opc > 5);

    if (opc == 0)
    {
        printf("Sair");
        exit = 1;
    }
    else if (opc == 1)
    {
        // Cadastrar um Filme
        system("cls");
        printf(">> Novo filme     ID: %d \n\n",qtdFilme);
        filme new = objFilme(qtdFilme);
        inserirFilme(new);
    }
    else if (opc == 2)
    {
        // Cadastrar multiplas categoria
        system("cls");
        int op = 1;
        while (1)
        {
            printf(">> Multiplos filme     ID: %d \n\n",qtdFilme);
            filme new = objFilme(qtdFilme);
            inserirFilme(new);
            printf("\n >> [1 - Mais] \t [0 - Exit]: ");
            scanf("%d", &op);
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
        printf(">> Filmes Cadastrados  \t Total: %d\n\n",qtdFilme);
        listFilme(bd_filme, qtdFilme);
        system("pause");
    }
    else if (opc == 4)
    {
        // editar
    }
    else if (opc == 5)
    {
        // Remover
        int cod;
        printf("Remover:");
        scanf("%d", &cod);
        //remCategoria(bd_cat, cod);
    }
    return exit;
}

int main()
{
    bd_filme = malloc(len_bd * sizeof(filme));

    while (1)
    {
        int i = menuFilme();
        if (i == 1){
            break;
        }
    }
    free(bd_filme);
    return (0);
}