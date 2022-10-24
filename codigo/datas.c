#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../cabecalhos/datas.h"

#define MIN_ANO 1
#define MAX_ANO 2500
#define DIAS_SEM 7
#define DIAS_ANO 365
#define QTD_MES 12

const int dias_mes[2][QTD_MES] = {
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

const char *nome_dia[
        DIAS_SEM + 1] = {"data invalida",
                         "sabado",
                         "domingo",
                         "segunda",
                         "terça",
                         "quarta",
                         "quinta",
                         "sexta"};

void dataAtual(data *data) {
    struct tm *data_hora_atual;
    time_t segundos;
    time(&segundos);
    data_hora_atual = localtime(&segundos);
    printf("\n>>dentro 1: %d/%d/%d\n",data->dia,data->mes,data->ano);
    data->dia = data_hora_atual->tm_mday;
    data->mes = data_hora_atual->tm_mon + 1;
    data->ano = data_hora_atual->tm_year + 1900;
    printf("\n>>dentro 2: %d/%d/%d\n",data->dia,data->mes,data->ano);
}

void formatarData(data data) {
    printf("%d/%d/%d", data.dia, data.mes, data.ano);
}

int isBissexto(int ano) {
    if ((ano % 400) == 0) return 1;
    if (((ano % 4) == 0) && ((ano % 100) != 0)) return 1;
    return 0;
}

int validarData(data data) {
    int bissexto = isBissexto(data.ano);
    if (data.ano < MIN_ANO || data.ano > MAX_ANO) {
        return 0;
    }

    if (data.mes < 1 || data.mes > QTD_MES) {
        return 0;
    }

    if (data.dia < 1 || data.dia > dias_mes[bissexto][data.mes - 1]) {
        return 0;
    }

    return 1;
}

int dataToInt(data data) {
    int tot_dias;
    int i, a, b;
    int bis = isBissexto(data.ano);
    tot_dias = 0;
    validarData(data);
    a = data.ano / 4;
    b = data.ano % 4;

    if (b) {
        tot_dias = DIAS_ANO * (data.ano - 1) + a;
    } else {
        tot_dias = DIAS_ANO * (data.ano - 1) + a - 1;
    }

    for (i = 0; i < QTD_MES; i++) {
        if (i + 1 == data.mes)break;
        tot_dias += dias_mes[bis][i];
    }

    tot_dias += data.dia;
    return tot_dias;
}

data intToData(int tot_dias) {
    int i, total, ano, mes, dia, bis;
    total = tot_dias;
    dia = 1;
    mes = 1;
    ano = 1;
    bis = 0;

    while (total > (DIAS_ANO + bis)) {
        total -= (DIAS_ANO + bis);
        ano++;
        bis = ((ano % 4) == 0);
    }

    for (i = 0; i < QTD_MES; i++) {
        if ((total - dias_mes[bis][i]) > 0) {
            total -= dias_mes[bis][i];
            mes = i + 2;
        } else {
            break;
        }
    }
    dia = total;
    data obj;
    obj.dia = dia;
    obj.mes = mes;
    obj.ano = ano;
    return obj;

}

int diaSemanaInt(data data) {
    int tot_dias;

    tot_dias = dataToInt(data);

    if (tot_dias) {
        return (tot_dias % DIAS_SEM + 1);
    }
    return 0;
}

const char* obterDiaDaSemana(data data) {
    return nome_dia[diaSemanaInt(data)];
}

int diasEntreDatas(data dataMaior, data dataMenor) {
    int tot_dias1, tot_dias2;

    tot_dias1 = dataToInt(dataMaior);
    tot_dias2 = dataToInt(dataMenor);

    if (tot_dias1 && tot_dias2) {
        return tot_dias2 - tot_dias1;
    }
    return 0;
}

data somaDataDias(data data, int dias) {
    int tot_dias;
    tot_dias = dataToInt(data);
    tot_dias += dias;
    return intToData(tot_dias);
}