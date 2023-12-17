#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "header.h"

int main(){
    FILE* fdEntrada = fopen("entrada.txt", "r");
    FILE* fdSaida = fopen("saida.txt", "w");
    unsigned char* m = (unsigned char*) malloc(4096 * 5 * sizeof(char));

    if (fdEntrada == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    carregarMemoria(m, fdEntrada, fdSaida);

    free(m);
    fclose(fdEntrada);

    return 0;
}

void carregarMemoria(unsigned char* memoria, FILE* fdEntrada, FILE* fdSaida){
    char inputEsq[30];
    char inputDir[30];
    char caracter[2];
    char opcode;
    short endereco;
    bool isExit = false;

    inputEsq[0] = '\0';
    inputDir[0] = '\0';
    caracter[1] = '\0';

    converterNumeros(memoria, fdEntrada, fdSaida);
    exit(1);

    while(!feof(fdEntrada)){
        caracter[0] = fgetc(fdEntrada);
        
        while((!isspace(caracter[0]))   && (caracter[0] != EOF)){
            strcat(inputEsq, caracter);
            caracter[0] = fgetc(fdEntrada);
        }

        if(feof(fdEntrada)){
            isExit = true;
        }
        
        caracter[0] = fgetc(fdEntrada);

        while((caracter[0] != '\n') && (isExit == false)){
            strcat(inputDir, caracter);
            caracter[0] = fgetc(fdEntrada);
        }

        opcode = converterInstrucao(inputEsq, inputDir, &endereco);

        inputEsq[0] = '\0';
        inputDir[0] = '\0';
    }
}

//Faz o reconhecimento do opcode e do endereço (caso tenha)
char converterInstrucao(char instrucaoEsq[], char instrucaoDir[], short* endereco){
    char opcode;

    if(strcmp(instrucaoEsq, "LOAD") == 0){
        opcode = verificaLoad(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "STOR") == 0){
        opcode = verificaStor(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "JUMP") == 0){
        opcode = verificaJump(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "JUMP+") == 0){
        opcode = verificaJumpP(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "ADD") == 0){
        opcode = verificaAdd(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "SUB") == 0){
        opcode = verificaSub(instrucaoDir);
    }else if(strcmp(instrucaoEsq, "MUL") == 0){
        opcode = (char)OPC_MUL;
    }else if(strcmp(instrucaoEsq, "DIV") == 0){
        opcode = (char)OPC_DIV;
    }else if(strcmp(instrucaoEsq, "LSH") == 0){
        opcode = (char)OPC_LSH;
    }else if(strcmp(instrucaoEsq, "RHS") == 0){
        opcode = (char)OPC_RSH;
    }else if(strcmp(instrucaoEsq, "EXIT") == 0){
        opcode = (char)OPC_EXIT;
    }else{
        perror("Operação não suportada");
        exit(1);
    }

    if(opcode == (char)OPC_JUMPEsq || opcode == (char)OPC_JUMPDir || opcode == (char)OPC_JUMPPEsq || opcode == (char)OPC_JUMPPDir || opcode == (char)OPC_STORDir || opcode == (char)OPC_STOREsq){
        *endereco = verificaEndereco(instrucaoDir, true);
    }else if(opcode == (char)OPC_RSH || opcode == (char)OPC_LSH || opcode == (char)OPC_EXIT || opcode == (char)OPC_LOADMQ){
        *endereco = null_address;
    }else{
        *endereco = verificaEndereco(instrucaoDir, false);
    }

    return opcode;
}

char verificaAdd(char instrucaoDir[]){
    char retorno;
    
    if(instrucaoDir[0] == 'M'){
        retorno = (char)OPC_ADD;
    }else if (instrucaoDir[0] == '|'){
        retorno = (char)OPC_ADDM;
    }else{
        perror("Operação ADD não suportada");
        exit(1);
    }
    return retorno;
};

char verificaSub(char instrucaoDir[]){
    char retorno;

    if(instrucaoDir[0] == 'M'){
        retorno = (char)OPC_SUB;
    }else if (instrucaoDir[0] == '|'){
        retorno = (char)OPC_SUBM;
    }else{
        perror("Operação ADD não suportada");
        exit(1);
    }

    return retorno;
};

char verificaJump(char instrucaoDir[]){
    char retorno;
    int contador = 0;

    while(instrucaoDir[contador] != ','){
        contador++;

    }

    contador++;

    if(instrucaoDir[contador] == '0'){

        retorno = (char)OPC_JUMPEsq;
    }
    else if(instrucaoDir[contador] == '2'){
        retorno = (char)OPC_JUMPPDir;
    }

    return retorno;
}

char verificaJumpP(char instrucaoDir[]){
    char retorno;
    int contador = 0;

    while(instrucaoDir[contador] != ','){
        contador++;
    }

    if(instrucaoDir[contador] == '0'){
        retorno = (char)OPC_JUMPPEsq;
    }

    if(instrucaoDir[contador] == '2'){
        retorno = (char)OPC_JUMPPDir;
    }
    return retorno;
}

char verificaLoad(char instrucaoDir[]){
    char retorno;
    if(instrucaoDir[0] == 'M'){
        if(instrucaoDir[1] == 'Q'){
            if(instrucaoDir[2] == ','){
                retorno = (char)OPC_LOADMQM;
            }
            else{
                retorno = (char)OPC_LOADMQ;
            }
        }
        else{
            retorno = (char)OPC_LOAD;
        }
    }else if (instrucaoDir[0] == '-'){
        if(instrucaoDir[1] == '|'){
            retorno = (char)OPC_LOADMenosModulo;
        }
        else if(instrucaoDir[1] == 'M'){
            retorno = (char)OPC_LOADMenos;
        }
    }else if(instrucaoDir[0] == '|'){
        retorno = (char)OPC_LOADModulo;
    }else{
        //perror("Operação LOAD não suportada");
        printf("erro");
        exit(1);
    }

    return retorno;
};

char verificaStor(char instrucaoDir[]){
    char retorno;
    int contador = 0;

    while(instrucaoDir[contador] != ','){
        contador++;
    }

    if(instrucaoDir[contador] == ','){
        if(instrucaoDir[contador+1] == '8'){
            retorno = (char)OPC_STOREsq;
        }else if(instrucaoDir[contador+1] == '2'){
            retorno = (char)OPC_STORDir;
        }
    }else if(instrucaoDir[contador] == ')'){
        retorno = (char)OPC_STOR;
    }

    return retorno;
};

short  verificaEndereco(char instrucaoDir[], bool isLeftRight){
    int contador = 0;
    char enderecoTemp[4];
    short endereco = 0; 
    int pos = 0;
    char limitadorDireito = isLeftRight ? ',' : ')';

    while(instrucaoDir[contador] != '(') {
        contador++;
    }
    contador++;
    while(instrucaoDir[contador] != limitadorDireito){
        enderecoTemp[pos] = instrucaoDir[contador];
        pos++;
        contador++;
    }
    
    endereco = (short)atoi(enderecoTemp);
    
    return endereco;
}

void converterNumeros(unsigned char* memoria, FILE* fdEntrada, FILE* fdSaida){
    long long int numero;
    long long int temp;
    long long int cheio = 255;
    int contador = 0;
    int posicao_memoria = 0;
    char numeroString[tamanho_max_num];

    while(contador < 7){
        fgets(numeroString, tamanho_max_num, fdEntrada);
        numero = atoll(numeroString);

        printf("Indo da direita para a esquerda...\n");
        for(int i = 4;i>=0; i--){
            temp = (numero >> (8*i)) & cheio; 
            memoria[posicao_memoria] = temp;

            printf("m[%i] = %lld\n",posicao_memoria, memoria[posicao_memoria]);
            posicao_memoria++;
        }
        contador++;
    }
}