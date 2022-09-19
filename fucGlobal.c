#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
// Comentei pq essa biblioteca não existe no linux
#include <conio.h>
#include "cabecalhos/fucGlobal.h"


//Macro typeof(var) retorna o tipo do dado

// ****************** Estruturas de Tempo *******************//

// http://linguagemc.com.br/exibindo-data-e-hora-com-time-h/
// Referente ao sinstema
//ponteiro para struct que armazena data e hora

// struct tm {
// int tm_sec; //representa os segundos de 0 a 59
// int tm_min; //representa os minutos de 0 a 59
// int tm_hour; //representa as horas de 0 a 24
// int tm_mday: //dia do mês de 1 a 31
// int tm_mon; //representa os meses do ano de 0 a 11
// int tm_year; //representa o ano a partir de 1900
// int tm_wday; //dia da semana de 0 (domingo) até 6 (sábado)
// int tm_yday; // dia do ano de 1 a 365
// int tm_isdst; //indica horário de verão se for diferente de zero
// };



void obterHour(hora *n){
    struct tm * DATAHORA_ATUAL;
    time_t segundos;
        //obtendo o tempo em segundos  
    time(&segundos); 
    DATAHORA_ATUAL = localtime(&segundos); 

    n->hora = DATAHORA_ATUAL->tm_hour;
    n->min = DATAHORA_ATUAL->tm_min;
    n->seg = DATAHORA_ATUAL->tm_sec;
}
void obterData(data *n){
    struct tm * DATAHORA_ATUAL;
    time_t segundos;
        //obtendo o tempo em segundos  
    time(&segundos); 
    DATAHORA_ATUAL = localtime(&segundos); 

    n->dia = DATAHORA_ATUAL->tm_mday;
    n->mes = DATAHORA_ATUAL->tm_mon + 1;
    n->ano = DATAHORA_ATUAL->tm_year + 1900;
}

/* +++++++++++++++++ Gerenciamento de Endereço +++++++++++++++++ */

void addTab(char *str){
    int i;
    char temp[35];
    //printf("%s",str);
    temp[0] = '\t';
    for (i = 0; i < 35; i++){
        temp[i+1] = str[i];
        if (str[i] == '\0'){
            break;
        }
    }
    temp[i+1] = '\0';
    strcpy(str,temp);
}

int lenChar(char *n){
    int i = 0;
    while (n[i] != '\0')
    {
        i++;
    }
    return i;
}

void line(int max, char *t){
    int qtd_a = (max - strlen(t)) / 2;
    int par = qtd_a % 2 == 0 ? 0 : 1;
    char a = 205;
    printf("\n");

    for (int i = 0; i < max;)
    {
        printf("%c", a);
        if (i == qtd_a + par)
        {
            if (lenChar(t) > 1){
                printf(" %s ", t);
            }else{
                printf("%c%c%c",a,a,a);
            }
            i = i + lenChar(t);
        }else{
            i++;
        }
    }
    printf("\n");
}

void abortOp(void){
    printf("\n\t[ERRO404] Operação Abortada:\n");
}

void sucess(void){
    printf("\n\t>> Sucess");
    system("pause");
}


// Comentei pq essa biblioteca não existe no linux
char  *obterPassword(int max){
    char *senha = (char *)malloc(sizeof(char) * max + 1);
    int i = 0;

    char ch = getch();
    while (ch != 13 && i < max) {
        senha[i] = ch;
        putchar(36);
        ch = getch();
        i++;
    }
    senha[i] = '\0';
    return senha;
}

/*
   Função para converter char em Int
   retorna o numero inteiro ou -1 se a operação falhar
*/

int ctoi ( char ch ) {
    return (int) (ch > 47 && ch < 58) ? ch - 48 : -1;
}

/*
https://dicasdeprogramacao.com.br/algoritmo-para-validar-cpf/#:~:text=Regra%20para%20validar%20CPF&text=O%20CPF%20%C3%A9%20formado%20por,do%20sinal%20%22%2D%22)

Função para validar CPF

Entrada: *cpf

Saida: 0 - Cpf Valido
       1 - Cpf Invalido
*/

int validaCPF(char *cpf){
    int erro = 0;
    int key_ = 10,result = 0,num;
    if (strlen(cpf) == 11){ //Se não tiver 11 digitos CPF invalido
        // Verificar se os digitos não são entradas sucessivas de mesmo digito e
        //se podem ser convertido para int
        int qtd = 0;
        for (int i = 0; i < 11; i++){
            if ((num = ctoi(cpf[i])) == -1) return 1;
            for (int j = i + 1; j < 11; j++){
                if (num == ctoi(cpf[j]) && ctoi(cpf[j]) != -1){
                    qtd++;
                }
            }
            if (qtd == 10){
                return 1;
            }
        }
        //Bloco para testar primerio digito
        for (int i = 0; i < 9; i++){
            result += ctoi(cpf[i]) * key_ ;
            key_--;
        }
        //Verificar primeiro digito se valido entrar no if e verificar o proximo digito
        if (ctoi(cpf[9]) == (result * 10) % 11){
            // verificar o proximo digito
            key_ = 11;
            result = 0;
            for (int i = 0; i < 10; i++){
                result += ctoi(cpf[i]) * key_ ;
                key_--;
            }
            if (ctoi(cpf[10]) == (result * 10) % 11){
                return 0;
            }
        }
    }
    return 1;
}

/*Função parar validar CNPJ

Entrada: *CNPJ
Saida: 0 - CNPJ Valido
       1 - CNPJ Invalido

*/
int validaCNPJ(char *CNPJ){
    int soma,dig;
    //Primeiro Digito Verificador
    //Obter Soma
    if (strlen(CNPJ) == 14){
        soma =((ctoi(CNPJ[0])* 5) +
               (ctoi(CNPJ[1])* 4) +
               (ctoi(CNPJ[2]) * 3) +
               (ctoi(CNPJ[3]) * 2) +
               (ctoi(CNPJ[4]) * 9) +
               (ctoi(CNPJ[5]) * 8) +
               (ctoi(CNPJ[6]) * 7) +
               (ctoi(CNPJ[7]) * 6) +
               (ctoi(CNPJ[8]) * 5) +
               (ctoi(CNPJ[9]) * 4) +
               (ctoi(CNPJ[10]) * 3) +
               (ctoi(CNPJ[11]) * 2));
        //Verificar se o primeiro digito verificador é valido
        if ((dig = 11 - (soma % 11)) == ctoi(CNPJ[12])){ //Subtrair base 11 do resto da divisão por 11
            soma =((ctoi(CNPJ[0])* 6) +
                   (ctoi(CNPJ[1])* 5 )+
                   (ctoi(CNPJ[2]) * 4) +
                   (ctoi(CNPJ[3]) * 3) +
                   (ctoi(CNPJ[4]) * 2) +
                   (ctoi(CNPJ[5]) * 9) +
                   (ctoi(CNPJ[6]) * 8) +
                   (ctoi(CNPJ[7]) * 7) +
                   (ctoi(CNPJ[8]) * 6) +
                   (ctoi(CNPJ[9]) * 5) +
                   (ctoi(CNPJ[10]) * 4) +
                   (ctoi(CNPJ[11]) * 3) +
                   (ctoi(CNPJ[12]) * 2));
            if ((dig = 11 - (soma % 11)) == ctoi(CNPJ[13])){
                return 0;
            }else{
                return 1;
            }
        }
    }
    return 1;
}


