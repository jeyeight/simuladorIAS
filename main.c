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
    clock = 0;
    flags = 0;
    FILE* fdEntrada = NULL;
    FILE* fdSaida = NULL;
    m = (unsigned char*) malloc(4096 * 5 * sizeof(char));
    verificaArgumentos(argc, argv, &fdEntrada, &fdSaida);

    if(atoi((char*)BR.PC) > 4096 || atoi((char*)BR.PC) < 0){
        perror("PC não pode ter um valor fora do alcance da memória");
        exit(EXIT_FAILURE);
    };

    if (fdEntrada == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    verificaPesos(fdEntrada);

    carregarMemoria(m, fdEntrada, fdSaida);

    int num1 = 1;
    sprintf(BR.AC, "%i", num1);
    
    printf("AC antes = %s", BR.AC);
    executaULA(ADD, 1, atoi(BR.AC));

    printf("AC depois = %s", BR.AC);

    free(m);
    fclose(fdEntrada);

    return 0;
}