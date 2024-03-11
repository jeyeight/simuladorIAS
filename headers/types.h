#ifndef TYPES_H
#define TYPES_H

typedef unsigned char Registrador[5];
typedef unsigned char Dado[5];
typedef unsigned char Endereco[2];
typedef unsigned char* Memoria; 
typedef unsigned char opc;
typedef unsigned short FlagsDoSistema; 
typedef unsigned long long int ClockDoSistema;

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

enum Operacoes {
    ADD = 5,
    ADDModulo = 7,
    SUB = 6, 
    SUBModulo = 8,
    MUL = 11,
    DIV = 12,
    LSH = 20,
    RSH = 21,
    STOR = 33,
    STOREsq = 18,
    STORDir = 19,
    LOADMQ = 10,
    LOADMQM = 9,
    LOAD = 1,
    LOADMenos = 2,
    LOADModulo = 3, 
    LOADMenosModulo = 4,
    JUMPDir = 14,
    JUMPEsq = 13,
    JUMPPDir = 16,
    JUMPPEsq = 15,
    EXIT = 255
};

enum classesEscritaResultados{EscritaRegistrador, EscritaMemoria, EscritaDoisRegistradores, EscritaVazia};

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
    FlagsDoSistema flags;
}UnidadeDeControle;


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
    Dado dado; //o que irá escrever. 
    enum classesEscritaResultados classe;
    Registrador reg1;
    Registrador reg2; //será o AC nas operações de MUL e DIV.
}EX_ER;

extern const char *nomesOperacoes[];
extern short enderecoLeft;
extern int posicao_memoria;
extern int Pesos[23];

extern B_D     b_d;
extern D_BO    d_bo;
extern BO_EX   bo_ex;
extern EX_ER   ex_er;
extern BarramentoDados BD;
extern BarramentoEndereco BE;
extern opc opcodeLeft;
extern banco_de_registradores BR;
extern UnidadeLogicaAritmetica ULA; 
extern Memoria m;
extern ClockDoSistema cpu_clk;

#endif
