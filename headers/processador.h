#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#define ENDERECO_ESQUERDO_ALTO 0XFFF00000
#define LONG_INT_ULTIMOS12_BAIXOS 0xFFFFFFFFFFFFF000
#define LONG_INT_ULTIMOS12_ALTOS 0xFFF
#define LONG_INT_ULTIMOS12_BAIXOS_DIR 0xFFF00000
#define LONG_INT_ULTIMOS12_ALTOS_DIR 0xFF00000000
#define LIMITE_39_BITS 549755813888
#define PRIMEIRO_BIT 0b10000000

void executaULA(enum Operacoes Operacao, int Operando1, long long int reg);
void decodificacao(bool newInstruction);
void pipeline();

#endif