#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

int main(){
    FILE* fd = fopen("entrada.txt", "r");
    char* m = (char*) malloc(4096 * 5 * sizeof(char));

    if (fd == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    pegarMemoria(m, fd);

    free(m);
    fclose(fd);

    return 0;
}

void pegarMemoria(char* memoria, FILE* fd){
    char inputEsq[30];
    char inputDir[30];
    char c[2];

    inputEsq[0] = '\0';
    inputDir[0] = '\0';
    c[1] = '\0';

    while(!feof(fd)){
        c[0] = fgetc(fd);
        
        while(!isspace(c[0])){
            strcat(inputEsq, c);
            c[0] = fgetc(fd);
        }
        
        c[0] = fgetc(fd);

        while(c[0] != '\n'){
            strcat(inputDir, c);
            c[0] = fgetc(fd);
        }

        inputEsq[0] = '\0';
        inputDir[0] = '\0';
    }
}