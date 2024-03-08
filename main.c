#include <stdio.h>
#include <stdlib.h>
#include "headers/types.h"
#include "memoria.c"
#include "processador.c"
#include "barramento.c"
#include "flags.c"
#include "utils.c"

/*
Array com flags globais
*/
int main(int argc, char* argv[]){
    FILE* fdEntrada = NULL;
    FILE* fdSaida = NULL;
    m = (unsigned char*) malloc(4096 * 5 * sizeof(char));
    verificaArgumentos(argc, argv, &fdEntrada, &fdSaida);

    if(registradorParaInteiro(BR.PC, false, -1) > 4096 || registradorParaInteiro(BR.PC, false, -1) < 0){
        perror("PC não pode ter um valor fora do alcance da memória");
        exit(EXIT_FAILURE);
    };

    if(fdEntrada == NULL){
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    verificaPesos(fdEntrada);

    carregarMemoria(m, fdEntrada, fdSaida);
    //Clocks, Pipeline, PC e UC
    pipeline();

    free(m);
    fclose(fdEntrada);

    return 0;
}