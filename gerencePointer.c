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

filme *bd; // dataBase local
int qtdFilme = 0, len_bd = 1;

void adFilme(filme *bd,int codigo)
{
    bd->codigo = codigo;
    printf("Nome: ");
    scanf("%s", &bd->nome);
    printf("Descricao: ");
    scanf("%s", &bd->descricao);
    printf("Quantidade de Exemplares: ");
    scanf("%d", &bd->qtd);
    printf("Codigo Categoria: ");
    scanf("%d", &bd->c_categoria);
    printf("Lingua: ");
    scanf("%s", &bd->lingua);
}

void inserirFilme(filme p) //Recebe o objeto e insere no array bd_*
{
    // Se a quantidade de filmes for igual ao tamanho alocado da lista -> espandir
    if (qtdFilme == len_bd)
    {
        len_bd += 1;
        bd = realloc(bd, len_bd * sizeof(filme));
    }
    // adc obj ao bd local
    bd[qtdFilme] = p;
    qtdFilme++; 
}



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

void remFilme(filme *bd, int codigo){ //ponteiro global do db
    for (int i = 0; i < qtdFilme; i++){
        if (bd[i].codigo == codigo){
            while (i < qtdFilme - 1){
                bd[i] = bd[i + 1];
                i++;
            } 
            qtdFilme--;
            break;
        }
    }
}

void listFilme(filme *bd,int qtd){
    for (int c = 0; c < qtd; c++){
        printf("------------------------------------\n");
        printf("(%d)\n\tNome:\t %s\n", c,bd[c].nome);
        printf("\tDescricao:\t %s\n", bd[c].descricao);
        printf("\tQnt de Exemplares:\t %d\n", bd[c].qtd);
        printf("\tCodigo Categoria:\t %d\n", bd[c].c_categoria);
        printf("\tLingua: \t%s\n", bd[c].lingua);
    }
}
int alterFilme(filme f, filme *bd, int codigo){
    for (int i = 0; i < qtdFilme; i++)
    {
        if(bd[i].codigo == codigo)
        {
            bd[i] = f;
            break;
            return 1;
        }
        else {
            return 0;
        }
    }
 }


int main()
{
    bd = malloc(len_bd * sizeof(filme));

    filme p = objFilme(qtdFilme);
    inserirFilme(p);

    p = objFilme(qtdFilme);
    inserirFilme(p);
    
    listFilme(bd,qtdFilme);
    int codigo;

    // printf("Remover:");
    // scanf("%d", &codigo);
    // remFilme(bd,codigo);

    // listFilme(bd,qtdFilme);
    //printf("cod: %s", bd[0].nome);
    printf("Editar:");
    scanf("%d", &codigo);

    p = objFilme(qtdFilme);
    alterFilme(p,bd,codigo);

    listFilme(bd,qtdFilme);

    free(bd);
    return (0);
}