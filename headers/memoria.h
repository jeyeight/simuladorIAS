#ifndef MEMORIA_H
#define MEMORIA_H

//Funções
short determinarEndereco(opc opcode, char inputDir[]);
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
void preencherZero(unsigned char* memoria);

void transferirRR(registrador reg1, registrador reg2);
void transferirRM(registrador reg, Memoria m, int PosicaoInicialMemoria);
void transferirMR(registrador reg, Memoria m, int PosicaoMemoria);
void transferirMM(Memoria m, int PosicaoMemoriaSrc, int PosicaoMemoriaDest);

#endif