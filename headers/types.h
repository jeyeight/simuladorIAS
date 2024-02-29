#ifndef TYPES_H
#define TYPES_H

typedef unsigned char Registrador[5];
typedef unsigned char* Memoria; 
typedef char FlagsDoSistema; 
typedef int ClockDoSistema;
typedef char Dado[5];
typedef char Endereco[3];
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
}BancoDeRegistradores;

typedef struct {
    int A;
    int B;
    int C;
    int Resultado;
}UnidadeLogicaAritmetica;

typedef struct {
    Endereco ed; 
    Dado dd;
} BarramentoMemoria;

typedef struct {
    Dado dados;
} BarramentoDados;

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

Memoria m;
BancoDeRegistradores BR;
UnidadeLogicaAritmetica ULA;
FlagsDoSistema flags;
ClockDoSistema clock;
BarramentoDados BD;
BarramentoMemoria BM;

#endif;
