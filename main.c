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

    long long int duas_instrucoes = 0;
    int posicon = 2500;
    duas_instrucoes |= m[posicon];
    BR.MBR[0] = m[posicon];
    duas_instrucoes <<= 8;
    
    posicon++;
    duas_instrucoes |= m[posicon];
    BR.MBR[1] = m[posicon];
    duas_instrucoes <<= 8;
    posicon++;
    duas_instrucoes |= m[posicon];
    BR.MBR[2] = m[posicon];
    duas_instrucoes <<= 8;
    posicon++;
    duas_instrucoes |= m[posicon];
    BR.MBR[3] = m[posicon];
    duas_instrucoes <<= 8;
    posicon++;
    duas_instrucoes |= m[posicon];
    BR.MBR[4] = m[posicon];
    posicon++;
    printf("as duas instrucoes sao o valor - %lld\n", duas_instrucoes);
    //printBits(duas_instrucoes);
    //sprintf(BR.MBR, "%ld", duas_instrucoes);
    //printf("%s - MBR\n", BR.MBR);

    // printBitsChar(BR.MBR[0]);
    // printBitsChar(BR.MBR[1]);
    // printBitsChar(BR.MBR[2]);
    // printBitsChar(BR.MBR[3]);
    // printBitsChar(BR.MBR[4]);

    //pipeline()

    decodificacao(true);    
    decodificacao(false);

    printf("AC depois = %s", BR.AC);

    free(m);
    fclose(fdEntrada);

    return 0;
}