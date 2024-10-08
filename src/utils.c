#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include "../headers/types.h"
#include "../headers/utils.h"

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
                long long int optnovo = atoi(optarg);
                inteiroParaRegistrador(optnovo, BR.PC);
                break;
            default:
                fprintf(stderr, "Uso: %s -p nomedoarquivodeentrada.ias -i PC\n", argv[0]);
                exit(1);
        }
    }
    if (nomeArquivoEntrada == NULL) {
        fprintf(stderr, "É necessário fornecer os argumentos -p e -i\n");
        exit(1);
    }

    if (nomeArquivoEntrada[0] == '<' && nomeArquivoEntrada[strlen(nomeArquivoEntrada) - 1] == '>') {
        nomeArquivoEntrada++;
        nomeArquivoEntrada[strlen(nomeArquivoEntrada) - 1] = '\0';
    }

    *fdEntrada = fopen(nomeArquivoEntrada, "r");
    if (*fdEntrada == NULL) {
        perror("Erro ao abrir arquivo de entrada");
        exit(1);
    }

    *fdSaida = fopen("inoutfiles/saida.ias.m", "wb"); 
    if(*fdSaida == NULL) {
        perror("Erro ao abrir arquivo de saída");
        exit(1);
    }
}

void testarPesos(){
    printf("Testando os Pesos inseridos. \n");
    for(int i = 0; i< 22; i++){
        printf("Na operacao: %s ", nomesOperacoes[i]);
        printf("O peso atribuido foi: %i \n", Pesos[i]);
    }
    
}

void verificaPesos(FILE * fdEntrada){
    char caracter[2];
    caracter[1] = '\0';
    char instrucao[10];
    char peso[10];
    caracter[0] = fgetc(fdEntrada);
    if(caracter[0] == '/'){
        caracter[0] = fgetc(fdEntrada);
    }
    else{
        fseek(fdEntrada, -1, SEEK_CUR);
    }
    caracter[0] = 'm'; //teste
    zerarString(instrucao, 10);
    while(caracter[0] != '*'){
        zerarString(peso, 10);
        while(caracter[0] != ' '){
            caracter[0] = fgetc(fdEntrada);
            if(caracter[0] != ' ' && caracter[0] != '\n'){
                strcat(instrucao, caracter);
            }
        }
        caracter[0] = fgetc(fdEntrada);
        while (caracter[0] != '\n'){
            strcat(peso, caracter);
            caracter[0] = fgetc(fdEntrada);
        }
        instrucao[strlen(instrucao) - 1] = '\0';

        setar_peso(instrucao, atoi(peso));

        instrucao[0] = '\0';
        peso[0] = '\0';
        
        caracter[0] = fgetc(fdEntrada);
        if(caracter[0] != '*'){
            fseek(fdEntrada, -1, SEEK_CUR);
        }
        
    }
    caracter[0] = fgetc(fdEntrada);
    caracter[0] = fgetc(fdEntrada);
}

void inicializarPesos(){
    for (int i = 0; i < 23; i++)
    {
        Pesos[i] = 1;
    }
    
}


void setar_peso(char* operacao, int peso){
    for (int i = 0; i < 22; i++) {
        if (strcmp(operacao, nomesOperacoes[i]) == 0) {
            Pesos[i] = peso;
        }
    }
}

char* itoa(int value, char* result, int base) {
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
  
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

void printaEnderecoMar(){
    int endereco = 0;
    endereco |= BR.MAR[3];
    endereco <<= 8;
    endereco |= BR.MAR[4];
}

unsigned long long int registradorParaInteiro(unsigned char valor[5], bool isMemoria, int indiceMemoria){
    unsigned long long int retorno = 0;
    if(isMemoria){
        retorno |= m[indiceMemoria];
        indiceMemoria++;
        retorno <<= 8;
        retorno |= m[indiceMemoria];
        indiceMemoria++;
        retorno <<= 8;
        retorno |= m[indiceMemoria];
        indiceMemoria++;
        retorno <<= 8;
        retorno |= m[indiceMemoria];
        indiceMemoria++;
        retorno <<= 8;
        retorno |= m[indiceMemoria];
    }else{
        retorno |= valor[0];
        retorno <<= 8;
        retorno |= valor[1];
        retorno <<= 8;
        retorno |= valor[2];
        retorno <<= 8;
        retorno |= valor[3];
        retorno <<= 8;
        retorno |= valor[4];
    }
    return retorno;
}

void inteiroParaRegistrador(unsigned long long int numero, unsigned char dado[5]){
    dado[0] = (numero & 0XFF00000000) >>32;

    dado[1] = (numero & 0X00FF000000) >> 24;

    dado[2] = (numero & 0X0000FF0000) >> 16;

    dado[3] = (numero & 0X000000FF00) >> 8;

    dado[4] = numero & 0X00000000FF;


}

bool isNegativeChar(unsigned char c) {
    if (c & 0x80) {
        return true;
    } else {
        return false;
    }
}

unsigned long long int modulo(unsigned long long int n){
    return n &= (QUADRAGESIMO_BIT -1);
}

unsigned short enderecoParaShort(unsigned char endereco[]){
    unsigned short retorno = 0;
    retorno |= endereco[0];
    retorno <<= 8;
    retorno |= endereco[1];
    
    return retorno;
}

int fornecerPeso(enum Operacoes Operacao){
    switch (Operacao){
        case ADD:
            return Pesos[0];
            break;
        case ADDModulo:
            return Pesos[1];
            break;
        case SUB:
            return Pesos[2];
            break;
        case SUBModulo:
            return Pesos[3];
            break;
        case MUL:
            return Pesos[4];
            break;
        case DIV:
            return Pesos[5];
            break;
        case LSH:
            return Pesos[6];
            break;
        case RSH:
            return Pesos[7];
            break;
        case STOR:
            return Pesos[8];
            break;
        case STOREsq:
            return Pesos[9];
            break;
        case STORDir: 
            return Pesos[10];
            break;
        case LOADMQ:
            return Pesos[11];
            break;
        case LOADMQM:
            return Pesos[12];
            break;
        case LOAD:
            return Pesos[13];
            break;
        case LOADMenos:
            return Pesos[14];
            break;
        case LOADModulo:
            return Pesos[15];
            break;
        case LOADMenosModulo:
            return Pesos[16];
            break;
        case JUMPDir:
            return Pesos[17];
            break;
        case JUMPEsq:
            return Pesos[18];
            break;
        case JUMPPDir:
            return Pesos[19];
            break;
        case JUMPPEsq:
            return Pesos[20];
            break;
        case EXIT:
            return Pesos[21];
            break;
        default:
            perror("Não existe esse peso!");
            exit(1);
            break;
    };
};

bool isNegativeULL(unsigned long long int n){
    
    if((n & QUADRAGESIMO_BIT) == QUADRAGESIMO_BIT){
        return true;
    }else{
        return false;
    }
}