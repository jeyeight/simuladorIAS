#ifndef TYPES_H
#define TYPES_H

typedef unsigned char registrador[5];
typedef struct banco_de_registradores{
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

struct banco_de_registradores BR;
struct UnidadeLogicaAritmetica ULA;
typedef struct UnidadeLogicaAritmetica
{
    int A;
    int B;
    int C;
    int Resultado;
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

#endif