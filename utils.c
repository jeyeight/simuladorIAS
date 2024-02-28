#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <getopt.h>
#include "headers/types.h"
#include "headers/utils.h"

void zerarString(char string[], int tamanho){
    for(int i = 0; i < tamanho; i++){
        string[i] = '\0';
    }
}

void verificaArgumentos(int argc, char* argv[], FILE** fdEntrada, FILE** fdSaida){
    int opt;
    char *nomeArquivoEntrada = NULL;

    while ((opt = getopt(argc, argv, "p:i:")) != -1) {
        switch (opt) {
            case 'p':
                nomeArquivoEntrada = optarg;
                break;
            case 'i':
                strcpy(BR.PC, optarg);
                break;
            default:
                fprintf(stderr, "Uso: %s -p nomedoarquivodeentrada.ias -i PC\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if (nomeArquivoEntrada == NULL) {
        fprintf(stderr, "É necessário fornecer os argumentos -p e -i\n");
        exit(EXIT_FAILURE);
    }

    if (nomeArquivoEntrada[0] == '<' && nomeArquivoEntrada[strlen(nomeArquivoEntrada) - 1] == '>') {
        nomeArquivoEntrada++;
        nomeArquivoEntrada[strlen(nomeArquivoEntrada) - 1] = '\0';
    }

    *fdEntrada = fopen(nomeArquivoEntrada, "r");
    if (*fdEntrada == NULL) {
        perror("Erro ao abrir arquivo de entrada");
        exit(EXIT_FAILURE);
    }

    *fdSaida = fopen("saida.ias.m", "wb"); 
    if(*fdSaida == NULL) {
        perror("Erro ao abrir arquivo de saída");
        exit(EXIT_FAILURE);
    }
}

void incrementarPC(int* PC){
    *PC++;
} 

// bool isNegative(unsigned char* memoria, int number){
//     long long int linha = 0;

//     linha |= memoria[byte_atual];

//     if((linha >= 128) && (contadorNumeros < quantidade_dados)){
//             linha -= 128;
//             return = true;
//     }else{
//         return false;
//     }
// }