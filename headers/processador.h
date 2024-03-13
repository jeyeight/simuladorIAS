#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#include <stdio.h>
#include "fila.h"

#define ENDERECO_ESQUERDO_ALTO 0xFFF00000
#define LONG_INT_ULTIMOS12_BAIXOS 0xFFFFFFFFFFFFF000
#define LONG_INT_ULTIMOS12_ALTOS 0xFFF
#define LONG_INT_ULTIMOS12_BAIXOS_DIR 0xFFF00000
#define LONG_INT_ULTIMOS12_ALTOS_DIR 0xFF00000000
#define LIMITE_39_BITS 549755813888
#define PRIMEIRO_BIT 0b10000000


enum statusFasePipeline{Vazio, Pronto, Travado, Finalizado};

enum escritaMemoria{Tudo, Esquerda, Direita};

void clockTick();
void executaULA(enum Operacoes Operacao, unsigned long long int Operando1);
void decodificacao();
void buscaOperandos();
void escritaResultados();
void busca();
void execucao();
void pipeline();
void avancarPipeline();
void inicializarProcessador();
extern int statusB; // tem q ter 3, vazio, finalizado, fazendo. 
extern int statusD; //tecnicamente, o fazendo estaria apenas no
extern int statusBO;
extern int statusEX;
extern int statusER;
extern bool newInstruction;
extern bool isExit;

#endif