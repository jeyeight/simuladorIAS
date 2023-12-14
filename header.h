#ifndef HEADER_H
#define HEADER_H

//Definições
#define size_memory 4096
#define numeros_memoria 500

//Structs

//Funções
void pegarMemoria(char* memoria, FILE* fd);
int converterInstrucao(char* instrucaoDir, char* instrucaoEsq);

#endif