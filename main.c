#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <getopt.h>
#include "headers/types.h"
#include "headers/memoria.h" 
#include "headers/utils.h"
//#include "memoria.c"
#include "utils.c"
/*
Array com flags globais
*/
int clock = 0;
int main(int argc, char* argv[]){
    FILE* fdEntrada = NULL;
    FILE* fdSaida = NULL;
    m = (unsigned char*) malloc(4096 * 5 * sizeof(char));
    verificaArgumentos(argc, argv, &fdEntrada, &fdSaida);

    if(atoi(BR.PC) > 4096 || atoi(BR.PC) < 0){
        perror("PC não pode ter um valor fora do alcance da memória");
        exit(EXIT_FAILURE);
    };

    if (fdEntrada == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    carregarMemoria(m, fdEntrada, fdSaida);
    //BR.MBR =
    // 

    free(m);
    fclose(fdEntrada);

    return 0;
}