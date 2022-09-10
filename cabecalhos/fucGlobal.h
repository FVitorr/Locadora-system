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