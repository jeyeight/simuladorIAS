#ifndef TYPES_H
#define TYPES_H

typedef unsigned char registrador[5];
typedef unsigned char Dado[5];
typedef unsigned char Endereco[2];
typedef unsigned char* Memoria; 
typedef unsigned char opc;
typedef char FlagsDoSistema; 
typedef int ClockDoSistema;
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
    registrador IR;
    registrador IBR;
    registrador MAR;
    registrador MBR;
    registrador AC;
    registrador PC;
    registrador MQ;
    registrador B_D;
    registrador D_BO;
    registrador BO_EX;
    registrador EX_ER;
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

short enderecoLeft;
int posicao_memoria = 0;
int Pesos[23];
char flags = 0;

BarramentoDados BD;
BarramentoEndereco BE;
opc opcodeLeft;
banco_de_registradores BR;
UnidadeLogicaAritmetica ULA; 
Memoria m;
FlagsDoSistema flags;
ClockDoSistema clock;
#endif
