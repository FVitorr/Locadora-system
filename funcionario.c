#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
    int id;
    char nome[20];
    char cargo[20];
    // Precisa da função endereço
    char telefone [12];
    char email [12];
}funcionario;
