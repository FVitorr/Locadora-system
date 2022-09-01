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

typedef struct{
    int codigo;
    char descricao[30];
    float vAlocacao;
} fCategoria;

filme *bd; // dataBase local
int qtdFilme = 0, len_bd = 1;

fCategoria *bd_cat;
int qtdCat = 0, len_cat = 1;

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

fCategoria objCategoria (int id){
    fCategoria obj;

    obj.codigo = id;
    printf("Descrição Categoria: ");
    scanf("%s", &obj.descricao);
    printf("Valor Locação: ");
    scanf("%f", &obj.vAlocacao);
    return obj;
}

// +++++++++++++++++++++++++++++++++++++++++ Subrotinas para controle dos filmes +++++++++++++++++
// void adFilme(filme *bd,int codigo)
// {
//     bd->codigo = codigo;
//     printf("Nome: ");
//     scanf("%s", &bd->nome);
//     printf("Descricao: ");
//     scanf("%s", &bd->descricao);
//     printf("Quantidade de Exemplares: ");
//     scanf("%d", &bd->qtd);
//     printf("Codigo Categoria: ");
//     scanf("%d", &bd->c_categoria);
//     printf("Lingua: ");
//     scanf("%s", &bd->lingua);
// }
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

// ++++++++++++++++++++++++++++++ Subrotinas para controle das Categorias filmes +++++++++++++++++
void insCategoria(fCategoria p)
{
    // Se a quantidade de categorias for igual ao tamanho alocado da lista -> espandir
    if (qtdCat == len_cat)
    {
        len_cat += 1;
        bd_cat = realloc(bd_cat, len_cat * sizeof(fCategoria));
    }
    // adc obj ao bd local
    bd_cat[qtdCat] = p;
    qtdCat++; 
}
void remCategoria(fCategoria *bd, int codigo){
    for (int i = 0; i < qtdCat; i++){
        if (bd[i].codigo == codigo){
            while (i < qtdCat - 1){
                bd[i] = bd[i + 1];
                i++;
            } 
            qtdCat--;
            break;
        }
    }
}
void listCategoria(fCategoria *bd,int qtd){
    for (int c = 0; c < qtd; c++){
        printf("--------------------------------------\n");
        printf("(%d)\n\tDescrição Categoria:\t %s\n", bd[c].codigo,bd[c].descricao);
        printf("\tValor Locação:\t %.2f\n", bd[c].vAlocacao);
        printf("--------------------------------------\n");
    }
}
int alteraCat(fCategoria f, fCategoria *bd, int codigo){
    int proc = 0;
    for (int i = 0; i < qtdCat; i++)
    {
        if(bd[i].codigo == codigo)
        {   
            bd[i] = f;
            proc = 1;
            break;
        }else{
            proc = 0;
        }
    }
    return proc;
 }

void menuCategoria(){
        int opc = 0, erro = 0;
        printf("------------- Categorias -------------\n\n");
        printf("\t 0 - Sair \n\t 1 - Cadastrar \n\t 2 - Cadastrar Multiplas \n");
        printf("\t 3 - Visualizar \n\t 4 - Editar \n\t 5 - Remover\n");
        printf("--------------------------------------\n");

        do
        {   
            if (erro == 1){
                printf(">> Parametro Invalido\n");
            }
            printf("Opc: ");
            scanf ("%d",&opc);
            erro = 1;
        } while (opc < 0 || opc > 5);

        if (opc == 0){
            printf("Sair");
        }else if (opc == 1){
            //Cadastrar uma categoria
            fCategoria new = objCategoria(qtdCat);
            insCategoria(new);
        }else if (opc == 2){
            //Cadastrar multiplas categoria
            int qtd_ = 1;
            while (1)
            {
                fCategoria new = objCategoria(qtdCat);
                insCategoria(new);
                printf("[1 - Mais] \t [0 - Exit]: ");
                scanf("%d",&qtd_);
                if (qtd_ == 0){
                    break;
                }
            }
            
        }else if (opc == 3){

        }else if (opc == 4){

        }else if (opc == 5){
            
        }
}

int main()
{
    bd = malloc(len_bd * sizeof(filme));
    bd_cat = malloc(len_cat * sizeof(fCategoria));

    // filme p = objFilme(qtdFilme);
    // inserirFilme(p);

    // p = objFilme(qtdFilme);
    // inserirFilme(p);
    
    // listFilme(bd,qtdFilme);
    // int codigo;

    // printf("Remover:");
    // scanf("%d", &codigo);
    // remFilme(bd,codigo);

    // listFilme(bd,qtdFilme);
    //printf("cod: %s", bd[0].nome);
    // printf("Editar:");
    // scanf("%d", &codigo);

    // p = objFilme(qtdFilme);
    // alterFilme(p,bd,codigo);
    // listFilme(bd,qtdFilme);

    // fCategoria new = objCategoria(qtdCat);
    // insCategoria(new);
    // new = objCategoria(qtdCat);
    // insCategoria(new);
    // listCategoria(bd_cat,qtdCat);

    // int codigo;
    // printf("%d\n",qtdCat);

    // printf("Editar:");
    // scanf("%d", &codigo);
    // new = objCategoria(codigo);
    // int v;
    // v = alteraCat(new,bd_cat,codigo);
    // listCategoria(bd_cat,qtdCat);
    // printf("%d",v);

    menuCategoria();
    free(bd);
    free(bd_cat);
    return (0);
}