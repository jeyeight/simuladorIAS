#ifndef HEADER_H
#define HEADER_H

//Definições
typedef unsigned char opc;

#define size_memory 4096
#define numeros_memoria 500
#define null_address 0b000000000000
#define tamanho_max_num 14
#define quantidade_dados 500
#define tam_max_byte 255
#define negativo_byte 128
//Opcodes
    //Data transfer
    #define OPC_LOADMQ 0b00001010
    #define OPC_LOADMQM 0b00001001
    #define OPC_STOR 0b00100001
    #define OPC_LOAD 0b00000001
    #define OPC_LOADMenos 0b00000010
    #define OPC_LOADModulo 0b00000011
    #define OPC_LOADMenosModulo 0b00000100

    //Unconditional branch
    #define OPC_JUMPEsq 0b00001101
    #define OPC_JUMPDir 0b00001110

    //Conditional Branch
    #define OPC_JUMPPEsq 0b00001111
    #define OPC_JUMPPDir 0b00010000

    //Arithmetic
    #define  OPC_ADD 0b00000101
    #define  OPC_ADDM 0b00000111
    #define  OPC_SUB 0b00000110
    #define  OPC_SUBM 0b00001000
    #define  OPC_MUL 0b00001011
    #define  OPC_DIV 0b00001100
    #define  OPC_LSH 0b00010100
    #define  OPC_RSH 0b00010101

    //Address modify
    #define OPC_STOREsq 0b00010010
    #define OPC_STORDir 0b00010011

    //Exit
    #define OPC_EXIT 0b11111111

//Structs

//Funções
void carregarMemoria(unsigned char* memoria, FILE* fdEntrada, FILE* fdSaida);
void converterNumeros(unsigned char* memoria, FILE* fdEntrada);
opc converterInstrucao(char instrucaoEsq[], char instrucaoDir[], short* endereco);
void escreveInstrucao(unsigned char opcode, short endereco, bool isLeft, bool isExit, unsigned char* memoria);

//Verificar opcode
opc verificaLoad(char instrucaoDir[]);
opc verificaJump(char instrucaoDir[]);
opc verificaJumpP(char instrucaoDir[]);
opc verificaAdd(char instrucaoDir[]);
opc verificaSub(char instrucaoDir[]);
opc verificaStor(char instrucaoDir[]);
opc verificaLoadMenos(char inputDir[]);
short verificaEndereco(char instrucaoDir[], bool isLeftRight);

void escreverArquivo(unsigned char* memoria, FILE* fdSaida);

void zerarString(char string[], int tamanho);
#endif