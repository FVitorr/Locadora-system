#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "fucGlobal.h"


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


/*
int replaceInt(int newValue, int *camp){
    int erro = 0;
    if (typeof(*camp) == "Integer"){
        *camp = newValue;
    }else{
        erro = 1;
    }
    return erro;
}

int replaceChar(char newValue[5], char *camp){
    int erro = 0;
    //printf("new: %s ",newValue);
    if (typeof(*camp) == "Char" || typeof(*camp) == "String"){
        strcpy( camp, newValue );
    }else{
        erro = 1;
    }
    return erro;
}
+*/
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
    int qtd_a = (max - lenChar(t)) / 2;
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

// int main(){
//     hora now;
//     data today;
//     obterData(&today);
//     obterHour(&now);
//     printf("%d:%d:%d",now.hora,now.min,now.seg);
//     printf("\t%d:%d:%d",today.dia,today.mes,today.ano);
// }