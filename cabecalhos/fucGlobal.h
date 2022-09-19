typedef struct
{
    int hora;
    int min;
    int seg;
}hora;

typedef struct{
    int dia;
    int mes;
    int ano;
}data;

typedef struct
{
    int codigo;
    char nome[120];      // Substituir por str
    char descricao[120]; // Substituir por str
    int qtd;            // quantidade de mídias existentes na locadora
    int c_categoria;
    char lingua[120]; // Substituir por str

} filme;


void obterHour(hora *n);

void obterData(data *n);

int replaceInt(int newValue, int *camp);

int replaceChar(char newValue[5], char *camp);

void addTab(char *str);

int lenChar(char *n);

void line(int max, char *t);

void abortOp(void);

void sucess(void);

char  *obterPassword(int max);

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