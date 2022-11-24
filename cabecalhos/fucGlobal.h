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
    //char descricao[120];
    int qtd;            // quantidade de mídias existentes na locadora
    int c_categoria;
    char lingua[120];
    int qtdEmprestado;

    // Parte da struct preenchida na parte de entrada de Filmes
    int IDDTbaseFIlme;
    float valorCompra;
} filme;

typedef struct {
    int tipo_configuracao;
    char user[120];
    char password[17];
}config;

int replaceInt(int newValue, int *camp);

int replacefloat(float newValue, float *camp);

void line(int max, char *t);

void abortOp(void);

void sucess(void);

char  *obterPassword(int max);

char *retorna_password_file (const char password_e[16]);

//-------------------------------- Tratamento de Strings --------------------------------- //
int replaceChar(char newValue[5], char *camp);

void resetstring(char *string);

void removeSpace(char *string);

//int lenChar(char *n);

char *string_to_pointer (const char entry[120]);

void stringLower(char *string);


/*Substitui o caracter \n por \0 na string
* \tParametros: "String";
*/

void limpa_final_string(char *c);

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




/*
 * Verifica se os arquivos ja existem caso não cria;
 * tipo_configuracao : 1 - TXT
 *                     0 - BIN
 */

void lineBox(int len_max, char *t, int direcao);

int verifica_arquivos(int tipo_config,char *nameFile);

int tipo_configuracao(config *set);

int verifica_log(config *set,int *tipo_config);

void refazLog(config *set);


int confirm_remover(int cod);

int menuConfiguracao(config *set,int *tipoConfig);

void info_cancela(void);

void systemPause();