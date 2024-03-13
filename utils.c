#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
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
        printf("receba");
        switch (opt) {
            case 'p':
                nomeArquivoEntrada = optarg;
                break;
            case 'i':
                //strcpy((char*)BR.PC, optarg);
                //printf("%s", optarg);
                long long int optnovo = atoi(optarg);
                inteiroParaRegistrador(optnovo, BR.PC, false, -1);
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
    caracter[0] = fgetc(fdEntrada); //ler novamente o *
    caracter[0] = fgetc(fdEntrada); //ler a /
    //caracter[0] = fgetc(fdEntrada); //ler a \n sei la
}

void setar_peso(char* operacao, int peso){
    for (int i = 0; i < 22; i++) {
        if (strcmp(operacao, nomesOperacoes[i]) == 0) {
            Pesos[i] = peso;
        }
    }
}

void printBits(long long int num)
{
   for(int bit=0;bit<(int)(sizeof(long long int) * 8); bit++)
   {
      printf("%i ", num & 0x01);
      num = num >> 1;
   }
   printf("\n");
}

void printBitsChar(char num)
{
   for(int bit=0;bit<(int)(sizeof(unsigned char) * 8); bit++)
   {
      printf("%i ", num & 0x01);
      num = num >> 1;
   }
   printf("\n");
}

char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
  
    // Reverse the string
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

    printf("endereco bumbumzinho %i\n", endereco);
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

void inteiroParaRegistrador(unsigned long long int numero, unsigned char dado[5], bool isMemoria, int posMemoria){
    //dado = reg ou dado mesmo! anderson tem dado em casa? :0
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
    return n &= QUADRAGESIMO_BIT;
}

unsigned short enderecoParaShort(unsigned char endereco[]){
    unsigned short retorno = 0;
    retorno |= endereco[0];
    retorno <<= 8;
    retorno |= endereco[1];
    
    return retorno;
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