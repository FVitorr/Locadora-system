#include "filmes.h"
#include "cliente.h"
#include "funcionarios.h"
typedef struct{
    int CodFilme;
    float valorPago;
    int tipoPagamento; // 1 - A vista  2 - A prazo
    int qtdParcelas;
}dLocadosFilme;

typedef struct {
    int ID;
    int CodCliente; //Não Altera
    data dtemprestimo; //Não Altera
    data dtdevolucao; //Não Altera
    dLocadosFilme dFilme;
    int devolvido; // 0-Sim 1-Não //Não Altera
}locados;




int emprestar(filme **dtbaseFilme,int qtdFilme,cliente **dtbaseCliente,int qtdcliente,
              funcionarios **dtbaseFuncionarios, int qtdFuncionarios, int idFuncionario,int idCliente, int idFilme);