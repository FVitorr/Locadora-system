typedef struct {
    int codigo;
    char descricao[50];
    float vAlocacao;
    int ativo;
} fCategoria;

/*
 Cria um objeto de Categoria
 param: (int id, int tab = Tabulação?
 */
fCategoria objCategoria (int id,int tab);
/*
 Insere a Categoria no array Dinamico
 */
int insCategoria(fCategoria **dtbase,fCategoria newEntry,int *qtdCategoria,int *tamanhoCategoria);
/*
 Remove a Categoria no array Dinamico
 */

int remCategoria(fCategoria **dtbase, int id, int qtdCategoria);
void listCategorias(fCategoria **dtbase, int qtd);
void editaCategoria(fCategoria **dtbase,int *qtdCategoria,int *tamanhoCategoria,int id);

int menuCategoria(fCategoria **dtbase, int *qtdCategoria,int *tamanhoCategoria);