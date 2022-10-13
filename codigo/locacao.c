#include "locacao.h"
#include <stdlib.h>
#include <stdio.h>

void HeaderLocados (locados *newObjeto,int *id,cliente **dtbaseCliente,int qtdcliente){
    int idtpm;

    (*newObjeto).ID = *id;
    *id = *id + 1; //Incrementar ID

    do {
        printf("Informe ID do Cliente:");
        scanf("%d", &idtpm);

        if (verificaIdCliente(dtbaseCliente, qtdcliente, idtpm) == 1) { //Verifica se o cliente existe
            (*newObjeto).CodCliente = idtpm;
            break;
        } else {
            printf("ID invalido");
            //Permitir que clientes sejam listados
        }
    } while(1);

    obterData(&(*newObjeto).dtemprestimo);
    printf("Data do emprestimo: %d/%d/%d",(*newObjeto).dtemprestimo.dia,(*newObjeto).dtemprestimo.mes,(*newObjeto).dtemprestimo.ano);

    (*newObjeto).dtdevolucao.dia = 0;
    (*newObjeto).dtdevolucao.mes = 0;
    (*newObjeto).dtdevolucao.ano = 0;

    (*newObjeto).devolvido = 0; // 0 - Não

}
locados objetoLocados (int *id,cliente **dtbaseCliente,int qtdcliente,filme **dtbaseFilme,int qtdFilme,
                       fCategoria **dtbaseCategoria, int qtdCategoria){

    HeaderLocados()

    do {
        printf("Informe ID do Filme: ");
        scanf("%d", &idtpm);

        if (verificaIdFilme(dtbaseFilme, qtdFilme, idtpm) == 1) { //Verificar se o ID do filme Existe
            newObjeto.CodFilme = idtpm;
            //Incrementar o valor do campo emprestados
            altQtdEmprestadaFilme(dtbaseFilme,qtdFilme,newObjeto.CodFilme);
            break;
        } else {

        }
    }while (1);

    do{
        printf("Tipo do pagamento: 1- A vista \t2 - A prazo\nOPC:");
        scanf("%d",&newObjeto.tipoPagamento);
    } while (newObjeto.tipoPagamento > 2 || newObjeto.tipoPagamento < 1);

    int idCategoria = categoriaFilme(dtbaseFilme,qtdFilme, newObjeto.CodFilme);
    newObjeto.valorPago = valorCategoria(dtbaseCategoria,qtdCategoria,idCategoria);

    if (newObjeto.tipoPagamento == 1){
        //Adc a contas
    }else{
        int ent = 0,qtdParcelas;
        float valor;
        do{
            printf(">> Deseja dar uma entrada ?  1-Sim \t0-Não");
            scanf("%d",&ent);
            if (ent == 0 || ent == 1){break;}
            else{ printf(">>Opc Invalida");}
        } while (1);

        if (ent == 1){
            printf(">> Valor R$ ");
            scanf("%f",&valor);
            //Adc a contas
            //Dividir
            printf(">> Dividir de quantas Vezes [3x Valor Maximo] ? ");
            scanf("%f",&qtdParcelas);
        }
    }

    newObjeto.devolvido = 0; // 0 - Não

    return newObjeto;
}

int emprestar(filme **dtbaseFilme,int qtdFilme,cliente **dtbaseCliente,int qtdcliente,
              funcionarios **dtbaseFuncionarios, int qtdFuncionarios, int idFuncionario,int idCliente, int idFilme){
    //Verificar Funcionario
    if (verificaIdFuncionario(dtbaseFuncionarios,qtdFuncionarios,idFuncionario) == 1){
        if (verificaIdCliente(dtbaseCliente,qtdcliente,idCliente) == 1){
            if (verificaIdFilme(dtbaseFilme,qtdFilme,idFilme) == 1){

            }else{
                printf(" >>Filme não encontrado");
            }
        }else{
            printf(" >>Cliente não encontrado ou não cadastrado");
        }
    }else{
        printf(" >>Funcionario não encontrado ou não cadastrado");
    }
}

int menuLocacao(){

}