#ifndef TYPES_H
#define TYPES_H

typedef unsigned char registrador[5];
typedef unsigned char* Memoria; 
struct banco_de_registradores{
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
};

struct UnidadeLogicaAritmetica{
    int A;
    int B;
    int C;
    int Resultado;
};

struct Flags{
    char ExemploDeFlag;
    char ExemploDeFLag2;
};

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
struct banco_de_registradores BR;
struct UnidadeLogicaAritmetica ULA;
char flags;
int clock;
#endif