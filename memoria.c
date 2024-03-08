#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <getopt.h>
#include "headers/types.h"
#include "headers/utils.h"
#include "headers/memoria.h" 
//Arquivo responsável por fazer a tradução do arquivo de entrada e carregar a memória da máquina 
void carregarMemoria(unsigned char* memoria, FILE* fdEntrada, FILE* fdSaida){
    char inputEsq[30];
    char inputDir[30];
    char caracter[2];
    int inputEsqORDir = 0;
    opc opcode;
    short endereco;
    bool isExit = false;
    bool isLeft;
    bool isLshORRsh = false;

    inputEsq[0] = '\0';
    inputDir[0] = '\0';
    caracter[1] = '\0';

    converterNumeros(memoria, fdEntrada);

    while(!feof(fdEntrada)){
        caracter[0] = fgetc(fdEntrada);
        
        while((!isspace(caracter[0])) && (caracter[0] != EOF) && (caracter[0] != '\n')){
            strcat(inputEsq, caracter);
            caracter[0] = fgetc(fdEntrada);
        }
        
        if((strcmp(inputEsq, "LSH") == 0) || (strcmp(inputEsq, "RSH") == 0) || (strcmp(inputEsq, "EXIT") == 0)){
            inputDir[0] = '\0';
            isLshORRsh = true;
        }

        if(feof(fdEntrada)) isExit = true;
        
        if(!isLshORRsh && !isExit){
            caracter[0] = fgetc(fdEntrada);
            while((caracter[0] != '\n') && (isExit == false) && (caracter[0] != -1)){
                strcat(inputDir, caracter);
                caracter[0] = fgetc(fdEntrada);
            }
        };

        if(feof(fdEntrada)) isExit = true;

        isLshORRsh = false;

        opcode = converterInstrucao(inputEsq, inputDir, &endereco);

        isLeft = (inputEsqORDir % 2 == 0);

        escreveInstrucao(opcode, endereco, isLeft, isExit, memoria);


        inputEsq[0] = '\0';
        inputDir[0] = '\0';
        inputEsqORDir++;
    }
    escreverArquivo(memoria, fdSaida);
}

opc converterInstrucao(char inputEsq[], char inputDir[], short* endereco){
    opc opcode;

    if(strcmp(inputEsq, "LOAD") == 0){
        opcode = verificaLoad(inputDir);
    }else if(strcmp(inputEsq, "LOAD-") == 0){
        opcode = verificaLoadMenos(inputDir);
    }else if(strcmp(inputEsq, "STOR") == 0){
        opcode = verificaStor(inputDir);
    }else if(strcmp(inputEsq, "JUMP") == 0){
        opcode = verificaJump(inputDir);
    }else if(strcmp(inputEsq, "JUMP+") == 0) {
        opcode = verificaJumpP(inputDir);
    }else if(strcmp(inputEsq, "ADD") == 0){
        opcode = verificaAdd(inputDir);
    }else if(strcmp(inputEsq, "SUB") == 0){
        opcode = verificaSub(inputDir);
    }else if(strcmp(inputEsq, "MUL") == 0){
        opcode = (opc)OPC_MUL;
    }else if(strcmp(inputEsq, "DIV") == 0){
        opcode = (opc)OPC_DIV;
    }else if(strcmp(inputEsq, "LSH") == 0){
        opcode = (opc)OPC_LSH;
    }else if(strcmp(inputEsq, "RSH") == 0){
        opcode = (opc)OPC_RSH;
    }else if(strcmp(inputEsq, "EXIT") == 0){
        opcode = (opc)OPC_EXIT;
    }else{
        perror("Operação não suportada");
        exit(1);
    }

    *endereco = determinarEndereco(opcode, inputDir);

    return opcode;
}

opc verificaAdd(char inputDir[]){
    opc opcode;
    
    if(inputDir[0] == 'M'){
        opcode = (opc)OPC_ADD;
    }else if (inputDir[0] == '|'){
        opcode = (opc)OPC_ADDM;
    }else{
        perror("Operação ADD não suportada");
        exit(1);
    }
    return opcode;
};

opc verificaSub(char inputDir[]){
    opc opcode;

    if(inputDir[0] == 'M'){
        opcode = (opc)OPC_SUB;
    }else if (inputDir[0] == '|'){
        opcode = (opc)OPC_SUBM;
    }else{
        perror("Operação SUB não suportada");
        exit(1);
    }

    return opcode;
};

opc verificaJump(char inputDir[]){
    opc opcode;
    int contador = 0;

    while(inputDir[contador] != ','){
        contador++;
    }

    contador++;

    if(inputDir[contador] == '0'){
        opcode = (opc)OPC_JUMPEsq;
    }else if(inputDir[contador] == '2'){
        opcode = (opc)OPC_JUMPDir;
    }else{
        perror("Operação JUMP não suportada");
        exit(1);
    }

    return opcode;
}
opc verificaJumpP(char inputDir[]){
    opc opcode;
    int contador = 0;

    while(inputDir[contador] != ','){
        contador++;
    }

    if(inputDir[contador + 1] == '0'){
        opcode = (opc)OPC_JUMPPEsq;
    }else if(inputDir[contador + 1] == '2'){
        opcode = (opc)OPC_JUMPPDir;
    }else{
        perror("Operação JUMPP não suportada");
        exit(1);
    }
    return opcode;
}

opc verificaLoad(char inputDir[]){
    opc opcode;
    if(inputDir[0] == 'M'){
        if(inputDir[1] == 'Q'){
            if(inputDir[2] == ','){
                opcode = (opc)OPC_LOADMQM;
            }else{
                opcode = (opc)OPC_LOADMQ;
            }
        }
        else{
            opcode = (opc)OPC_LOAD;
        }
    }else if(inputDir[0] == '|'){
        opcode = (opc)OPC_LOADModulo;
    }else{
        printf("Operação LOAD não suportada");
        exit(1);
    }

    return opcode;
};

opc verificaStor(char inputDir[]){
    opc opcode;
    int contador = 0;

    while((inputDir[contador] != ',') && (contador <= 8)){ 
        contador++;
    }

    if(contador >8){
        opcode = (opc)OPC_STOR; 
    }else{
        if(inputDir[contador] == ','){
            if(inputDir[contador+1] == '8'){
                opcode = (opc)OPC_STOREsq;
            }else if(inputDir[contador+1] == '2'){
                opcode = (opc)OPC_STORDir;
            }else{
                perror("Operação STOR não suportada");
                exit(1);
            }
        }
    }
    return opcode;
};

opc verificaLoadMenos(char inputDir[]){
    opc opcode;
    if(inputDir[0] == '|'){
        opcode = (opc)OPC_LOADMenosModulo;
    }else if(inputDir[0] == 'M'){
        opcode = (opc)OPC_LOADMenos;
    }else{
        perror("Operação LOAD- não suportada");
        exit(1);
    }
    return opcode;
}

short verificaEndereco(char inputDir[], bool isLeftRight){
    int contador = 0;
    char enderecoTemp[5];
    short endereco = 0; 
    int pos = 0;
    char limitadorDireito = isLeftRight ? ',' : ')';
    
    zerarString(enderecoTemp, 5);

    while(inputDir[contador] != '(') {
        contador++;
    }

    while(inputDir[contador + 1] != limitadorDireito){
        enderecoTemp[pos] = inputDir[contador + 1];
        pos++;
        contador++;
    }
    endereco = (short)atoi(enderecoTemp);
    return endereco;
}

void converterNumeros(unsigned char* memoria, FILE* fdEntrada){
    long long int numero;
    long long int temp;
    long long int cheio = tam_max_byte;
    long long int negativo = negativo_byte;
    int contador = 0;
    char numeroString[tamanho_max_num];
    char numero_sem_negativo[tamanho_max_num];
    bool isNegative = false;
    bool isAlpha = false;

    while(contador < quantidade_dados && !isAlpha){
        fgets(numeroString, tamanho_max_num, fdEntrada);
        isNegative = false;
        if(numeroString[0] == '-'){
            isNegative = true;
            for (int i = 1; i < (int)strlen(numeroString);i++){    
                numero_sem_negativo[i-1] = numeroString[i];
            }
            numero = atoll(numero_sem_negativo);    
        }else{
            numero = atoll(numeroString);
        }

        if(isalpha(numeroString[0])){
            isAlpha = true;
            fseek(fdEntrada,-strlen(numeroString) , SEEK_CUR);
            preencherZero(memoria);
        } 
        
        if(!isAlpha){
            for(int i = 4;i>=0; i--){
                temp = (numero >> (8*i)) & cheio; 
                if(isNegative && i == 4){
                    temp = temp | negativo; 
                }
                memoria[posicao_memoria] = temp;
                posicao_memoria++;
            }
            contador++;
        }
    }
}

void escreveInstrucao(opc opcode, short endereco, bool isLeft, bool isExit, unsigned char* memoria){
    long long int linhaDeInstrucao = 0;
    long long int temp;

    if(isLeft){
        opcodeLeft = opcode;
        enderecoLeft = endereco;
    }else{
        linhaDeInstrucao |= opcodeLeft;
        linhaDeInstrucao <<= 12;
        linhaDeInstrucao |= enderecoLeft;
        linhaDeInstrucao <<= 8;
        linhaDeInstrucao |= opcode;
        linhaDeInstrucao <<= 12;
        linhaDeInstrucao |= endereco;

        for(int i = 4;i >= 0; i--){
            temp = (linhaDeInstrucao >> (8*i)) & tam_max_byte; 
            memoria[posicao_memoria] = temp;
            posicao_memoria++;
        }
    }

    if(isLeft && isExit){
        linhaDeInstrucao |= opcodeLeft;
        linhaDeInstrucao <<= 12;
        linhaDeInstrucao |= enderecoLeft;
        linhaDeInstrucao <<= 20;

        for(int i = 4;i >= 0; i--){
            temp = (linhaDeInstrucao >> (8*i)) & tam_max_byte; 
            memoria[posicao_memoria] = temp;
            posicao_memoria++;
        }
    }
};

void escreverArquivo(unsigned char* memoria, FILE* fdSaida){
    int contadorNumeros = 0;
    long long int linha = 0;
    int byte_atual = 0;
    while(byte_atual < (size_memory * 5)){ 
        linha |= memoria[byte_atual];
        if(contadorNumeros < quantidade_dados) contadorNumeros++;
        linha <<= 8;
        byte_atual++;
        linha |= memoria[byte_atual];
        linha <<= 8;
        byte_atual++;
        linha |= memoria[byte_atual];
        linha <<= 8;
        byte_atual++;
        linha |= memoria[byte_atual];
        linha <<= 8;
        byte_atual++;
        linha |= memoria[byte_atual];
        byte_atual++;
        fprintf(fdSaida, "%lli\n", linha);
        linha = 0;
    }
}

short determinarEndereco(opc opcode, char inputDir[]){
    if(opcode == (opc)OPC_JUMPEsq || opcode == (opc)OPC_JUMPDir || opcode == (opc)OPC_JUMPPEsq || opcode == (opc)OPC_JUMPPDir || opcode == (opc)OPC_STORDir || opcode == (opc)OPC_STOREsq){
        return verificaEndereco(inputDir, true);
    }else if(opcode == (opc)OPC_RSH || opcode == (opc)OPC_LSH || opcode == (opc)OPC_EXIT || opcode == (opc)OPC_LOADMQ){
        return null_address;
    }else{
        return verificaEndereco(inputDir, false);
    }
}

void preencherZero(unsigned char* memoria){
    for(int i = posicao_memoria; i < fim_entrada_dados; i++){
        memoria[i] = 0;
    }
    posicao_memoria = fim_entrada_dados;
}

void transferirRR(Registrador destino, Registrador origem){
    for(int i = 0; i < 5; i++){
        destino[i] = origem[i];
    }
}
void transferirMR(Registrador destino, Memoria m, int PosicaoInicialMemoria){
    for(int i = 0; i < 5; i++){
        destino[i] = m[PosicaoInicialMemoria];
        PosicaoInicialMemoria++;
    }
}
void transferirRM(Registrador origem, Memoria destino, int PosicaoMemoria){
    for(int i = 0; i < 5; i++){
        destino[PosicaoMemoria] = origem[i];
        PosicaoMemoria++;
    }
}
void transferirMM(Memoria m, int PosicaoMemoriaSrc, int PosicaoMemoriaDest){
    for(int i = 0; i < 5; i++){
        m[PosicaoMemoriaDest] = m[PosicaoMemoriaSrc];
        PosicaoMemoriaSrc++;
        PosicaoMemoriaDest++;
    }
}