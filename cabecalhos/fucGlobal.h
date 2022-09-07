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

void obterHour(hora *n);
void obterData(data *n);

typedef struct
{
    char rua[10];
    int numero;
    char bairro[10];
    char cidade[10];
    char estado[2];

} endereco;

int replaceInt(int newValue, int *camp);
int replaceChar(char newValue[5], char *camp);

void addTab(char *str);
int lenChar(char *n);
void line(int max, char *t);

typedef struct
{
    int codigo;
    char nome[10];      // Substituir por str
    char descricao[10]; // Substituir por str
    int qtd;            // quantidade de m�dias existentes na locadora
    int c_categoria;
    char lingua[10]; // Substituir por str

} filme;