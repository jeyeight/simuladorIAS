#ifndef TYPES_H
#define TYPES_H

typedef unsigned char Registrador[5];
typedef unsigned char Dado[5];
typedef unsigned char Endereco[2];
typedef unsigned char* Memoria; 
typedef unsigned char opc;
typedef char FlagsDoSistema; 
typedef long long int ClockDoSistema;

//Definições
#define size_memory 4096
#define numeros_memoria 500
#define null_address 0b000000000000
#define tamanho_max_num 14
#define quantidade_dados 500
#define tam_max_byte 255
#define negativo_byte 128
#define fim_entrada_dados 2500
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

typedef struct{
    char ExemploDeFlag;
    char ExemploDeFLag2;
}Flags;

enum Operacoes {
    ADD,
    ADDModulo,
    SUB, 
    SUBModulo,
    MUL,
    DIV,
    LSH,
    RSH,
    STOR,
    STOREsq,
    STORDir,
    LOADMQ,
    LOADMQM,
    LOAD,
    LOADMenos,
    LOADModulo, 
    LOADMenosModulo,
    JUMPDir,
    JUMPEsq,
    JUMPPDir,
    JUMPPEsq,
    EXIT
};

const char *nomesOperacoes[] = {
    "ADD",
    "ADD|",
    "SUB", 
    "SUB|",
    "MUL",
    "DIV",
    "LSH",
    "RSH",
    "STOR",
    "STORM",
    "STORM",
    "LOADM",
    "LOADMM",
    "LOAD",
    "LOAD-M",
    "LOAD|M", 
    "LOAD-|M",
    "JUMP",
    "JUMP",
    "JUMP+",
    "JUMP+",
    "EXIT"
};
typedef struct{
    Registrador IR;
    Registrador IBR;
    Registrador MAR;
    Registrador MBR;
    Registrador AC;
    Registrador PC;
    Registrador MQ;
    Registrador B_D;
    Registrador D_BO;
    Registrador BO_EX;
    Registrador EX_ER;
}banco_de_registradores;

typedef struct{
    int A;
    int B;
    int C;
    int Resultado;
}UnidadeLogicaAritmetica;

typedef struct{
    Endereco end;
}BarramentoEndereco;

typedef struct{
    Dado dado;
}BarramentoDados;


typedef struct{
    Registrador linha;
}B_D;
typedef struct{
    opc opc_linha;
    Endereco end;
    Registrador novoIBR;
}D_BO;
typedef struct{
    opc opc_linha;
    Endereco endereco;
    Dado dado;
}BO_EX;
typedef struct{
    opc opc_linha;
    Endereco endereco;
}EX_ER;


short enderecoLeft;
int posicao_memoria = 0;
int Pesos[23];
char flags = 0;

B_D     b_d;
D_BO    d_bo;
BO_EX   bo_ex;
EX_ER   ex_er;
BarramentoDados BD;
BarramentoEndereco BE;
opc opcodeLeft;
banco_de_registradores BR;
UnidadeLogicaAritmetica ULA; 
Memoria m;
FlagsDoSistema flags;
ClockDoSistema cpu_clk;

#endif
