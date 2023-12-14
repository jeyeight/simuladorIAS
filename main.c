#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    char inputEsq[100];
    char inputDir[100];
    char c;

    while(!feof(fd)){
        c = fgetc(fd);
        
        while(c != ' '){
            strcat(inputEsq, &c);
            c = fgetc(fd);
            printf("%c", c);    
        }
        printf("%s", inputEsq);
        exit(1);
        
        c = fgetc(fd);

        while(c != '\n'){
            strcat(inputDir, &c);
            c = fgetc(fd);
        }

        printf("%s", inputEsq);
    }
}