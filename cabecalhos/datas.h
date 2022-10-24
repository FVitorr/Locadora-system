#ifndef LOCADORA_SYSTEM_DATAS_H
#define LOCADORA_SYSTEM_DATAS_H

typedef struct {
    int dia;
    int mes;
    int ano;
} data;

void dataAtual(data data);
void formatarData(data data);
int isBissexto(int ano);
int validarData(data data);
int dataToInt(data data);
data intToData(int tot_dias);
int diaSemanaInt(data data);
const char* obterDiaDaSemana(data data);
int diasEntreDatas(data dataMaior, data dataMenor);
data somaDataDias(data data, int dias);

#endif //LOCADORA_SYSTEM_DATAS_H
