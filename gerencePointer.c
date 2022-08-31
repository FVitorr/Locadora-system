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

void atChar_fil(filme *bd,int codigo, char *campo[30]){
    switch (codigo)
    {
    case 0:
        printf("%s",bd.nome);
        break;
    case 1:
        /* code */
        break;
    case 4:
        /* code */
        break;
    
    default:
        break;
    }
    printf("")
}

void AlterValFilme(filme *bd,int codigo){
    int des;
    char entry[30];
    for (int i = 0; i < qtdFilme; i++){
        if (bd[i].codigo == codigo){
            printf("Paramentros: \n 0 - Nome \n 1 - Descricao \n 2 - Qtd \n 3 - Codigo Categoria \n 4 - Lingua ");
            do {
                scanf("%d",&des);
            } while (des < 0 && des > 4);
            printf("Novo Valor: ");
            scanf("%s",entry);
            //alter_(&bd[i],codigo,);
            break;
        } 
    }
}

int main()
{
    bd = malloc(len_bd * sizeof(filme));
    adFilme(&bd[qtdFilme],qtdFilme);
    qtdFilme++;
    adFilme(&bd[qtdFilme],qtdFilme);
    qtdFilme++;
    
    int codigo;
    listFilme(bd,qtdFilme);

    printf("Remover:");
    scanf("%d", &codigo);
    remFilme(bd,codigo);

    listFilme(bd,qtdFilme);
    //printf("cod: %s", bd[0].nome);

    free(bd);
    return (0);
}