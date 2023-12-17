#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "header.h"

unsigned char opcodeLeft;
short enderecoLeft;
int posicao_memoria = 0;

int main(){
    FILE* fdEntrada = fopen("entrada.txt", "r");
    FILE* fdSaida = fopen("saida.txt", "wb");
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
    int instrucaoEsqORDir = 0;
    unsigned char opcode;
    short endereco;
    bool isExit = false;
    bool isLeft;

    inputEsq[0] = '\0';
    inputDir[0] = '\0';
    caracter[1] = '\0';

    converterNumeros(memoria, fdEntrada);

    while(!feof(fdEntrada)){
        caracter[0] = fgetc(fdEntrada);
        printf("caracter0 = %c\n", caracter[0]);
        
        while((!isspace(caracter[0]))   && (caracter[0] != EOF)){
            strcat(inputEsq, caracter);
            caracter[0] = fgetc(fdEntrada);
        }
        printf("InputEsq = %s\n", inputEsq);

        if(feof(fdEntrada)){
            isExit = true;
            printf("\nisExit entrou\n");
        }
        
        caracter[0] = fgetc(fdEntrada);

        while((caracter[0] != '\n') && (isExit == false)){
            strcat(inputDir, caracter);
            caracter[0] = fgetc(fdEntrada);
        }

        printf("InputDir = %s\n", inputDir);

        opcode = converterInstrucao(inputEsq, inputDir, &endereco);
        printf("opcode obtido = %u, e endereco = %hd\n", opcode, endereco);

        isLeft = (instrucaoEsqORDir % 2 == 0);

        escreveInstrucao(opcode, endereco, fdEntrada, isLeft, memoria);

        inputEsq[0] = '\0';
        inputDir[0] = '\0';
        instrucaoEsqORDir++;
    }
    teste_memoria(memoria);
    teste_escrever_arquivo(memoria, fdSaida);
    exit(1);
}

//Faz o reconhecimento do opcode e do endereço (caso tenha)
unsigned char converterInstrucao(char instrucaoEsq[], char instrucaoDir[], short* endereco){
    unsigned char opcode;

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
        opcode = (unsigned char)OPC_MUL;
    }else if(strcmp(instrucaoEsq, "DIV") == 0){
        opcode = (unsigned char)OPC_DIV;
    }else if(strcmp(instrucaoEsq, "LSH") == 0){
        opcode = (unsigned char)OPC_LSH;
    }else if(strcmp(instrucaoEsq, "RHS") == 0){
        opcode = (unsigned char)OPC_RSH;
    }else if(strcmp(instrucaoEsq, "EXIT") == 0){
        opcode = (unsigned char)OPC_EXIT;
    }else{
        perror("Operação não suportada");
        printf("opcode = %u", opcode);
        exit(1);
    }

    if(opcode == (unsigned char)OPC_JUMPEsq || opcode == (unsigned char)OPC_JUMPDir || opcode == (unsigned char)OPC_JUMPPEsq || opcode == (unsigned char)OPC_JUMPPDir || opcode == (unsigned char)OPC_STORDir || opcode == (unsigned char)OPC_STOREsq){
        *endereco = verificaEndereco(instrucaoDir, true);
    }else if(opcode == (unsigned char)OPC_RSH || opcode == (unsigned char)OPC_LSH || opcode == (unsigned char)OPC_EXIT || opcode == (unsigned char)OPC_LOADMQ){
        *endereco = null_address;
    }else{
        *endereco = verificaEndereco(instrucaoDir, false);
    }

    return opcode;
}

unsigned char verificaAdd(char instrucaoDir[]){
    unsigned char opcode;
    
    if(instrucaoDir[0] == 'M'){
        opcode = (char)OPC_ADD;
    }else if (instrucaoDir[0] == '|'){
        opcode = (char)OPC_ADDM;
    }else{
        perror("Operação ADD não suportada");
        exit(1);
    }
    return opcode;
};

unsigned char verificaSub(char instrucaoDir[]){
    unsigned char opcode;

    if(instrucaoDir[0] == 'M'){
        opcode = (char)OPC_SUB;
    }else if (instrucaoDir[0] == '|'){
        opcode = (char)OPC_SUBM;
    }else{
        perror("Operação ADD não suportada");
        exit(1);
    }

    return opcode;
};

unsigned char verificaJump(char instrucaoDir[]){
    unsigned char opcode;
    int contador = 0;

    while(instrucaoDir[contador] != ','){
        contador++;

    }

    contador++;

    if(instrucaoDir[contador] == '0'){
        opcode = (char)OPC_JUMPEsq;
    }
    else if(instrucaoDir[contador] == '2'){
        opcode = (char)OPC_JUMPPDir;
    }

    return opcode;
}

unsigned char verificaJumpP(char instrucaoDir[]){
    unsigned char opcode;
    int contador = 0;

    while(instrucaoDir[contador] != ','){
        contador++;
    }

    if(instrucaoDir[contador] == '0'){
        opcode = (char)OPC_JUMPPEsq;
    }

    if(instrucaoDir[contador] == '2'){
        opcode = (char)OPC_JUMPPDir;
    }
    return opcode;
}

unsigned char verificaLoad(char instrucaoDir[]){
    unsigned char opcode;
    if(instrucaoDir[0] == 'M'){
        if(instrucaoDir[1] == 'Q'){
            if(instrucaoDir[2] == ','){
                opcode = (char)OPC_LOADMQM;
            }
            else{
                opcode = (char)OPC_LOADMQ;
            }
        }
        else{
            opcode = (char)OPC_LOAD;
        }
    }else if (instrucaoDir[0] == '-'){
        if(instrucaoDir[1] == '|'){
            opcode = (char)OPC_LOADMenosModulo;
        }
        else if(instrucaoDir[1] == 'M'){
            opcode = (char)OPC_LOADMenos;
        }
    }else if(instrucaoDir[0] == '|'){
        opcode = (char)OPC_LOADModulo;
    }else{
        //perror("Operação LOAD não suportada");
        printf("erro");
        exit(1);
    }

    return opcode;
};

unsigned char verificaStor(char instrucaoDir[]){
    unsigned char opcode;
    int contador = 0;

    while((instrucaoDir[contador] != ',') && (contador <= 8)){ //se passar de 8, é apenas um STOR M(X), senão seria menor.
        contador++;
        printf("contador = %i\n", contador);
    }

    if(contador >8){
        opcode = (char)OPC_STOR; //rever isso, talvez fazer melhor
    }

    if(instrucaoDir[contador] == ','){
        if(instrucaoDir[contador+1] == '8'){
            opcode = (char)OPC_STOREsq;
        }else if(instrucaoDir[contador+1] == '2'){
            opcode = (char)OPC_STORDir;
        }
    }

    return opcode;
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

void converterNumeros(unsigned char* memoria, FILE* fdEntrada){
    long long int numero;
    long long int temp;
    long long int cheio = 255;
    long long int negativo = 128;
    int contador = 0;
    char numeroString[tamanho_max_num];
    char numero_sem_negativo[tamanho_max_num];
    bool isNegative = false;

    while(contador < quantidade_dados){
        fgets(numeroString, tamanho_max_num, fdEntrada);
        isNegative = false;
        if(numeroString[0] == '-'){
            isNegative = true;
            for (int i = 1; i < strlen(numeroString);i++){    
                numero_sem_negativo[i-1] = numeroString[i];
            }
            numero = atoll(numero_sem_negativo);    
        }else{
            numero = atoll(numeroString);
        }

        for(int i = 4;i>=0; i--){
            temp = (numero >> (8*i)) & cheio; 
            if(isNegative && i == 4){
                temp = temp | negativo; 
            }
            printf("Escrevendo %lli, na posicao_memoria %i\n", temp, posicao_memoria);
            memoria[posicao_memoria] = temp;
            posicao_memoria++;
        }
        contador++;
    }
}

void escreveInstrucao(unsigned char opcode, short endereco, FILE* fdEntrada, bool isLeft, unsigned char* memoria){
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

        for(int i = 4;i>=0; i--){
            temp = (linhaDeInstrucao >> (8*i)) & 0xFF; 
            memoria[posicao_memoria] = temp;
            posicao_memoria++;
        }
    }

    
};

void teste_memoria(unsigned char* memoria){
    for(int i = 0; i < 20; i++){
        printf("%u \n", memoria[i]);
    }
}


void teste_escrever_arquivo(unsigned char* memoria, FILE* fdSaida){
    int posicao_final = posicao_memoria;
    bool isNegative;
    int numeros = 0;
    long long int linha = 0;
    char byte_atual = 0;
    while(byte_atual < posicao_memoria){ //sla se tá certo isso, mas quando deixei <= ele printou a mais.
        isNegative = false;
        linha |= memoria[byte_atual];
        if((linha >= 128) && (byte_atual/5 <= quantidade_dados + 1)){
            linha -= 128;
            isNegative = true;

        }
        printf("linha = %lli\n", linha);
        linha <<= 8;
        printf("linha = %lli\n", linha);
        byte_atual++;
        linha |= memoria[byte_atual];
        printf("linha = %lli\n", linha);
        linha <<= 8;
        printf("linha = %lli\n", linha);
        byte_atual++;
        linha |= memoria[byte_atual];
        printf("linha = %lli\n", linha);
        linha <<= 8;
        printf("linha = %lli\n", linha);
        byte_atual++;
        linha |= memoria[byte_atual];
        printf("linha = %lli\n", linha);
        linha <<= 8;
        printf("linha = %lli\n", linha);
        byte_atual++;
        linha |= memoria[byte_atual];
        printf("linha = %lli\n", linha);
        byte_atual++;
        if(isNegative){
            fprintf(fdSaida, "-%lli\n", linha);
        }else{
            fprintf(fdSaida, "%lli\n", linha);
        }
        printf("Próximo número!"); //escrever '\n'? não sei se precisa.
        linha = 0;
        
    }
}