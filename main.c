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
    char opcode;
    char endereco;
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

        converterInstrucao(inputEsq, inputDir, opcode, endereco);

        inputEsq[0] = '\0';
        inputDir[0] = '\0';
    }
}

void converterInstrucao(char* instrucaoEsq, char* instrucaoDir, char* opcode, char*  endereco){
    if(strcmp(instrucaoEsq, "LOAD") == 0){
        opcode = verificaLoad(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "STOR") == 0){
        //opcode = verificaStor(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "JUMP") == 0){
        opcode = verificaJump(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "JUMP+") == 0){
        opcode = verificaJumpP(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "ADD") == 0){
        opcode = verificaAdd(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "SUB") == 0){
        opcode = verificaSub(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "MUL") == 0){
        opcode = OPC_MUL;
    }else if(strcmp(instrucaoEsq, "DIV") == 0){
        opcode = OPC_DIV;
    }else if(strcmp(instrucaoEsq, "LSH") == 0){
        opcode = OPC_LSH;
    }else if(strcmp(instrucaoEsq, "RHS") == 0){
        opcode = OPC_RSH;
    }else if(strcmp(instrucaoEsq, "EXIT") == 0){
        opcode = OPC_EXIT;
    }else{
        perror("Operação não suportada");
        exit(1);
    }
}

char verificaAdd(char* instrucaoDir){
    char retorno;
    
    if(instrucaoDir[0] == 'M'){
        retorno = OPC_ADD;
    }else if (instrucaoDir[0] == '|'){
        retorno = OPC_ADDM;
    }else{
        perror("Operação ADD não suportada");
        exit(1);
    }
    return retorno;
};
char verificaSub(char* instrucaoDir){
    char retorno;

    if(instrucaoDir[0] == 'M'){
        retorno = OPC_SUB;
    }else if (instrucaoDir[0] == '|'){
        retorno = OPC_SUBM;
    }else{
        perror("Operação ADD não suportada");
        exit(1);
    }
    return retorno;
};

char verificaJump(char* instrucaoDir){
    char retorno;
    int contador = 0;

    while(instrucaoDir[contador] != ','){
        contador++;
        printf("TESTE: Elemento está na posicao %i\n", contador);

    }

    printf("achei\n");
    printf("Elemento está na posicao %i\n", contador);

    contador++;

    printf("instrucaoDir[contador] = %c", instrucaoDir[contador]);
    if(instrucaoDir[contador] == '0'){

        retorno = OPC_JUMPEsq;
        printf("retorno 13");
    }
    else if(instrucaoDir[contador] == '2'){
        retorno = OPC_JUMPPDir;
        printf("retorno 14");
    }

    return retorno;
}

char verificaJumpP(char* instrucaoDir){
    char retorno;
    int contador = 0;

    while(instrucaoDir[contador] != ','){
        contador++;
    }

    if(instrucaoDir[contador] == '0'){
        retorno = OPC_JUMPPEsq;
        printf("JUMPPESQ");
    }

    if(instrucaoDir[contador] == '2'){
        retorno = OPC_JUMPPDir;
        printf("JUMPPESQ");
    }
    return retorno;
}

char verificaLoad(char* instrucaoDir){
    char retorno;

    if(instrucaoDir[0] == 'M'){
        if(instrucaoDir[1] == 'Q'){
            if(instrucaoDir[2] == ','){
                retorno = OPC_LOADMQM;
                printf("retorno 9");
            }
            else{
                retorno = OPC_LOADMQ;
                printf("retorno 10");
            }
        }
        else{
            retorno = OPC_LOAD;
            printf("retorno 1");
        }
    }else if (instrucaoDir[0] == '-'){
        if(instrucaoDir[1] == '|'){
            retorno = OPC_LOADMenosModulo;
            printf("retorno 4");
        }
        else if(instrucaoDir[1] == 'M'){
            retorno = OPC_LOADMenos;
            printf("retorno 2");

        }
    }else if(instrucaoDir[0] == '|'){
        retorno = OPC_LOADModulo;
        printf("retorno 3");

    }else{
        //perror("Operação LOAD não suportada");
        printf("erro");
        exit(1);
    }
    return retorno;
};