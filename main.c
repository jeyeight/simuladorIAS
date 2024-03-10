#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "headers/types.h"
#include "headers/utils.h"
#include "headers/memoria.h"
#include "headers/processador.h"
#include "headers/barramento.h"
#include "headers/flags.h"
#include "headers/uc.h"

short enderecoLeft;
int posicao_memoria = 0;
int Pesos[23];
B_D b_d;
D_BO d_bo;
BO_EX bo_ex;
EX_ER ex_er;
BarramentoDados BD;
BarramentoEndereco BE;
opc opcodeLeft;
banco_de_registradores BR;
UnidadeLogicaAritmetica ULA;
Memoria m;
ClockDoSistema cpu_clk;
const char *nomesOperacoes[] = {
    "ADD",
    "ADD|",
    "SUB", 
    "SUB|",
    "MUL",
    "DIV",
    "LSH",
    "RSH",
    "STOR",
    "STORM",
    "STORM",
    "LOADM",
    "LOADMM",
    "LOAD",
    "LOAD-M",
    "LOAD|M", 
    "LOAD-|M",
    "JUMP",
    "JUMP",
    "JUMP+",
    "JUMP+",
    "EXIT"
};

int main(int argc, char* argv[]){
    FILE* fdEntrada = NULL;
    FILE* fdSaida = NULL;
    m = (unsigned char*) malloc(4096 * 5 * sizeof(char));
    printf("to aq");

    verificaArgumentos(argc, argv, &fdEntrada, &fdSaida);
    printf("to aq2");


    if(registradorParaInteiro(BR.PC, false, -1) > 4096 || registradorParaInteiro(BR.PC, false, -1) < 0){
        perror("PC não pode ter um valor fora do alcance da memória");
        exit(EXIT_FAILURE);
    };
    printf("to aq3");


    if(fdEntrada == NULL){
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    verificaPesos(fdEntrada);

    carregarMemoria(m, fdEntrada, fdSaida);
    //Clocks, Pipeline, PC e UC
    set_flag_pipe(true);
    verificaAcao();
    exit(1);
    

    free(m);
    fclose(fdEntrada);

    return 0;
}