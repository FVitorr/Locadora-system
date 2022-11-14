#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "cabecalhos/fucGlobal.h"

/* +++++++++++++++++ Gerenciamento de Endereço +++++++++++++++++ */

void addTab(char *str){
    int i;
    char temp[35];
    printf("%s",str);
    temp[0] = (char)9;
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
    int qtd_a = (max - (int)strlen(t)) / 2;
    int par = qtd_a % 2 == 0 ? 0 : 1;
    char a = (char)205;
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
    printf("\n\t[!] Operação Abortada:\n");
}

void info_cancela(void){
    printf("\n\t>>Operação Cancelada\n");
    system("Pause");
}

void stringLower(char *string){
    int i = 0;
    while (string[i] != '\0' || i == strlen(string)){
        string[i] = (char)tolower(string[i]);
        i++;
    }
}

void removeSpace(char *string){
    int i = 0;
    while (string[i] != '\0' || i == strlen(string)){
        if (string[i] == ' '){
            for (int j = i + 1;string[j] != '\0';j++){
                string[i] = string[j];
            }
        }
        i++;
    }
}

int confirm_remover(int cod){
    int op;
    printf("Tem certeza que deseja remover (ID): %d \n 1- SIM \t 0-Não", cod);
    scanf("%d", &op);
    if (op == 1) {
        return 1;
    }else{
        return 0;
    }
}

void sucess(void){
    printf("\n\t>> Sucess\n");
    system("pause");
}


// Comentei pq essa biblioteca não existe no linux
char  *obterPassword(int max){
    char *senha = (char *)malloc(sizeof(char) * max + 1);
    int i = 0;

    char ch = (char)getch();
    while (ch != (char)13 && i < max) {
        senha[i] = ch;
        putchar(36);
        ch = (char)getch();
        i++;
    }
    senha[i] = '\0';
    return senha;
}

char *retorna_password_file (char password_e[16]){
    int i = 0;
    char *password = (char *)malloc(sizeof(char) * 16);
    while (password_e[i] != '#' && i < 16 && password_e[i] != '\n'){
        password[i] = password_e[i];
        i++;
    }
    password[i] = '\0';
    return password;
}
/*
 * Algumas Struct
 */

char *string_to_pointer (char entry[120]){
    int i = 0;
    char *string = (char *)malloc(sizeof(char) * 120);
    while (entry[i] != '\n' && i < 120 && entry[i] != '\0'){
        string[i] = entry[i];
        i++;
    }
    string[i] = '\0';
    return string;
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

/*
    Substitui o caracter \n por \0 na string
*/

void limpa_final_string(char *c) {
    int i;
    for (i = 0; i < strlen(c); i++){
        if (c[i] == '\n') {
            c[i] = '\0';
            break;
        }
    }
}

void remover_espaco(char *c){
    for(int i = 0; i < strlen(c); i++){
        if(c[i]==' '){
            c[i]=c[i+1];
        }
    }
}


void limpa_extensao(char *c) {
    int i;
    for (i = 0; i < strlen(c); i++){
        if (c[i] == '.') {
            c[i] = '\0';
            break;
        }
    }
}

int verifica_arquivos(int tipo_config,char *nameFile){
    FILE *p;

    //strcat(nameFile,".txt\0");

    if (tipo_config == 1){
        p = fopen(nameFile,"r");
        if (p != NULL){ //Arquivo existe
            fclose(p);
            p = NULL;
            //printf("Existe Arquivo %s",nameFile);
            return 1;
        }
        fclose(p);
        p = NULL;
        return 0;
    }else {
        p = fopen(nameFile,"rb");
        if (p != NULL){ //Arquivo existe
            fclose(p);
            p = NULL;
            //printf("Existe Arquivo %s",nameFile);
            return 1;
        }
        fclose(p);
        p = NULL;
        return 0;
    }
}


int tipo_configuracao(config *set) {
    FILE *log = NULL;
    log = fopen("log.bin","wb");

    char entry;
    while (1){
        line(100, "Configuracoes de Sistema\0");
        printf(" >> Salvar dados em qual Extensao: \t0 - BIN \t1 - TXT ");
        line(100, "=\0");
        scanf("%c", &entry);
        if ((ctoi(entry)) == 0 || (ctoi(entry)) == 1) {
            break;
        }
        system("cls");
        printf(">>Parametro Invalido");
    }
    set->tipo_configuracao = ctoi(entry);
    fwrite(set, sizeof(config), 1,log);
    return (ctoi(entry));
}

void refazLog(config *set){
    FILE *log = NULL;
    log = fopen("log.bin","wb");
    fwrite(set, sizeof(config), 1,log);
    fclose(log);
}

int verifica_log(config *set,int *tipo_config){
    //Arquivo log.bin armazenas informaçoes do sistema
    config setTpm;

    FILE *log;
    log = fopen("log.bin","rb");
    line(100,"Bem Vindo\0");
    if (log == NULL){
        printf("\nPrecisamos de algumas infomacoes para inicializar o Sistema\n");
        *tipo_config = tipo_configuracao(set);
        return 1; // Primeira Execussão do programa
    }else{
        do{
            fread(&setTpm,sizeof(config),1,log);
        }while (!feof(log));

        set->tipo_configuracao = setTpm.tipo_configuracao;
        strcpy(set->user,setTpm.user);
        strcpy(set->password,setTpm.password);
        *tipo_config = set->tipo_configuracao;

        //system("pause");
    }
    return 0;
}

int replaceInt(int newValue, int *camp){
    *camp = newValue;
}

int replacefloat(float newValue, float *camp){
    *camp = newValue;
}

void limpaString(char *string,int lenString){
    for (int i = 0; i < lenString; i++){
        string[i] = '\0';
    }
}

char *formatstring(int lenMax,int lenString,const char *string){
    char space = 32;
    int lenAntes = (lenMax - lenString - 1) / 2;
    char *string1 = malloc(lenMax * sizeof (char));
    int  i = 0 ;
    while (i <= lenMax){
        if (i < lenAntes){
            string1[i] = space;
            i++;
        }else if (i == lenAntes){
            for (int j = 0; j < lenString; j++){
                string1[i] = string[j];
                i++;
            }
        }else if (i > lenAntes){
            string1[i] = space;
            i++;
        }
    }
    string1[lenMax] = '\0';
    return string1;
}


void systemPause(){
    char a;
    printf("\nPrecione uma Tecla para continuar...");
    scanf("%c",a);
}