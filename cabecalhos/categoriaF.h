
//#include "../cabecalhos/fucGlobal.h"
typedef struct {
   int codigo;
   char descricao[120];
   float vAlocacao;
   int ativo;
} fCategoria;

/*
 Cria um objeto de Categoria
 param: (int id, int tab = Tabulação?
 */
fCategoria objCategoria (int *id,int tab);
/*
 Insere a Categoria no array Dinamico
 */
int insCategoria(fCategoria **dtbase,fCategoria newEntry,int *qtdCategoria,int *tamanhoCategoria, int tipo_config);
/*
 Remove a Categoria no array Dinamico
 */

int remCategoria(fCategoria **dtbase, int id, int *qtdCategoria,int *tamanhoCategoria,int tipo_config);

void listCategorias(fCategoria **dtbase, int qtd);

int editaCategoria(fCategoria **dtbase,int *qtdCategoria,int *tamanhoCategoria,int id,int tipo_config);

int locID(fCategoria **dtbase,int qtd_Categoria, int ID) ;
/*Retorna o Valor pago na Categoria de acordo com o ID informado*/
float valorCategoria(fCategoria **dtbase,int qtd_Categoria, int ID);

int menuCategoria(fCategoria **dtbase, int *qtdCategoria,int *tamanhoCategoria,int *idCategoria, int tipo_config);

int saveCategoria(fCategoria objeto,int tipo_config);

int carregarDados_Categoria(fCategoria **dtBase, int *qtdCategoria, int *tamanhoCategoria, int *id,int tipo_config);

int refazDados_Categoria(fCategoria **dtbase, int *qtdCategoria, int *tamanhoCategoria, int tipo_config);

//int verifica_IDCategoria(fCategoria **dtbase,int qtd_Locadora,int id);