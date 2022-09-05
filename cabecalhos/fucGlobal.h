#define typeof(var);

typedef struct hora;

typedef struct data;

void obterHour(hora *n);
void obterData(data *n);

typedef struct endereco;

int replaceInt(int newValue, int *camp);
int replaceChar(char newValue[5], char *camp);

void addT(char *str);
int lenChar(char *n);
void line(int max, char *t);
