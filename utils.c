#include <stdio.h>
#include "utils.h"

void zerarString(char string[], int tamanho){
    for(int i = 0; i < tamanho; i++){
        string[i] = '\0';
    }
}

void verificaArgumentos(int argc, char* argv[], FILE** fdEntrada, FILE** fdSaida) {
    int opt;
    char *nomeArquivoEntrada = NULL;
    char *nomeArquivoSaida = NULL;

    while ((opt = getopt(argc, argv, "p:m:")) != -1) {
        switch (opt) {
            case 'p':
                nomeArquivoEntrada = optarg;
                break;
            case 'm':
                nomeArquivoSaida = optarg;
                break;
            default:
                fprintf(stderr, "Uso: %s -p <nomedoarquivodeentrada.ias> -m <nomedoarquivodesaida.ias.m>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if (nomeArquivoEntrada == NULL || nomeArquivoSaida == NULL) {
        fprintf(stderr, "É necessário fornecer os argumentos -p e -m\n");
        exit(EXIT_FAILURE);
    }

    if (nomeArquivoEntrada[0] == '<' && nomeArquivoEntrada[strlen(nomeArquivoEntrada) - 1] == '>') {
        nomeArquivoEntrada++;
        nomeArquivoEntrada[strlen(nomeArquivoEntrada) - 1] = '\0';
    }

    if (nomeArquivoSaida[0] == '<' && nomeArquivoSaida[strlen(nomeArquivoSaida) - 1] == '>') {
        nomeArquivoSaida++;
        nomeArquivoSaida[strlen(nomeArquivoSaida) - 1] = '\0';
    }

    *fdEntrada = fopen(nomeArquivoEntrada, "r");
    if (*fdEntrada == NULL) {
        perror("Erro ao abrir arquivo de entrada");
        exit(EXIT_FAILURE);
    }

    *fdSaida = fopen(nomeArquivoSaida, "wb"); 
    if (*fdSaida == NULL) {
        perror("Erro ao abrir arquivo de saída");
        exit(EXIT_FAILURE);
    }
}