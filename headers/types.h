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



#endif