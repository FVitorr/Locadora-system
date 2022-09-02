#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int codigo;
    char descricao[30];
    float vAlocacao;
} fCategoria;

fCategoria *bd_cat;
int qtdCat = 0, len_cat = 1;

fCategoria objCategoria (int id){
    fCategoria obj;

    obj.codigo = id;
    printf("Descrição Categoria: ");
    scanf("%s", &obj.descricao);
    printf("Valor Locação: ");
    scanf("%f", &obj.vAlocacao);
    return obj;
}

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
    system("cls");
    printf("\n ID \tDescrição Categoria \t Valor Locação\n");
    for (int c = 0; c < qtd; c++){
        printf("----------------------------------------------------\n");
        printf("(%d)\t%15s\t\t %.2f\n",bd[c].codigo,bd[c].descricao);
    }
    printf("\n");
    system("pause");
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


int menuCategoria(){
        int opc = 0, erro = 0, exit = 0;
        system("cls");
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
            system("cls");
            printf(">> Exit");
            exit = 1;
            system("pause");
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
            //Visualizar 
            listCategoria(bd_cat,qtdCat);
        }else if (opc == 4){
            // editar
        }else if (opc == 5){
            // Remover
            int cod;
            printf("Remover:");
            scanf("%d", &cod);
            remCategoria(bd_cat,cod);
        }
        return exit;
}


int main()
{
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

    while (1)
    {
        int i = menuCategoria();
        if (i == 1){
            break;
        }
    }

    free(bd_cat);
    return (0);
}