#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
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
    bool isExit = false;

    inputEsq[0] = '\0';
    inputDir[0] = '\0';
    c[1] = '\0';

    while(!feof(fd)){
        c[0] = fgetc(fd);
        
        while((!isspace(c[0]))   && (c[0] != EOF)){
            strcat(inputEsq, c);
            c[0] = fgetc(fd);
        }

        if(feof(fd)){
            isExit = true;
        }
        
        c[0] = fgetc(fd);

        while((c[0] != '\n') && (isExit == false)){
            strcat(inputDir, c);
            c[0] = fgetc(fd);
        }

        inputEsq[0] = '\0';
        inputDir[0] = '\0';
    }
}

int converterInstrucao(char* instrucaoEsq, char* instrucaoDir){
    int retorno = 0;

    if(strcmp(instrucaoEsq, "LOAD")){
        verificaLoad(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "STOR")){
        verificaStor(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "JUMP")){
        verificaJump(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "JUMP+")){
        verificaJumpPlus(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "ADD")){
        verificaAdd(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "SUB")){
        verificaSub(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "MUL")){
        verificaLoad(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "DIV")){
        verificaDiv(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "LSH")){

    }else if(strcmp(instrucaoEsq, "RHS")){

    }else if(strcmp(instrucaoEsq, "EXIT")){

    }else{
        perror("Operação não suportada");
        exit(1);
    }

    return retorno;
}