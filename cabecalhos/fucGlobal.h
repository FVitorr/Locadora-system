#include "datas.h"

typedef struct
{
    int hora;
    int min;
    int seg;
}hora;

void limpaString(char *string,int lenString);

char *formatstring(int lenMax,int lenString,const char *string);

typedef struct {
    int codigo;
    char nome[120];
    char descricao[120];
    int qtd;            // quantidade de mídias existentes na locadora
    int c_categoria;
    char lingua[120];
    int qtdEmprestado;

    // Parte da struct preenchida na parte de entrada de Filmes
    float valorCompra;
} filme;

typedef struct {
    int tipo_configuracao;
    char user[120];
    char password[17];
}config;

int replaceInt(int newValue, int *camp);

int replaceChar(char newValue[5], char *camp);

int replacefloat(float newValue, float *camp);

void addTab(char *str);

int lenChar(char *n);

void line(int max, char *t);

void abortOp(void);

void sucess(void);

char  *obterPassword(int max);

char *retorna_password_file (char password[16]);

char *string_to_pointer (char entry[120]);

/*
   Função para converter char em Int
   retorna o numero inteiro ou -1 se a operação falhar
*/

int ctoi ( char ch );

/*
https://dicasdeprogramacao.com.br/algoritmo-para-validar-cpf/#:~:text=Regra%20para%20validar%20CPF&text=O%20CPF%20%C3%A9%20formado%20por,do%20sinal%20%22%2D%22)

Função para validar CPF

Entrada: *cpf

Saida: 0 - Cpf Valido
       1 - Cpf Invalido
*/

int validaCPF(char *cpf);

/*Função parar validar CNPJ
http://www.fidelis.work/chega-de-gambeta-como-validar-cnpj-e-cpf-corretamente/
Entrada: *CNPJ
Saida: 0 - CNPJ Valido
       1 - CNPJ Invalido

*/
int validaCNPJ(char *CNPJ);

/*Cria o arquivo caso não exista.
 * \tParametros: Nome do Arquivo , tipo_configuracao 1 txt;
 * \tRetorno: Inteiro 0 - Sucesso.  1 - Erro.
 * */
int creatFile(char nameFile[30],int tipo_configuracao);

/*Substitui o caracter \n por \0 na string
* \tParametros: "String";
*/

void limpa_final_string(char *c);

/*
 * Verifica se os arquivos ja existem caso não cria;
 * tipo_configuracao : 1 - TXT
 *                     0 - BIN
 */

int verifica_arquivos(int tipo_config,char *nameFile);

int tipo_configuracao(config *set);

int verifica_log(config *set,int *tipo_config);

void refazLog(config *set);

void remover_espaco(char *c);

int confirm_remover(int cod);

void info_cancela(void);

void systemPause();