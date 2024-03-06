#ifndef UTILS_H
#define UTILS_H

void zerarString(char string[], int tamanho);
void verificaArgumentos(int argc, char* argv[], FILE** fdEntrada, FILE** fdSaida);
void testarPesos();
void verificaPesos(FILE * fdEntrada);
void setar_peso(char* operacao, int peso);
char* itoa(int value, char* result, int base);
void printaEnderecoMar();
long int registradorParaInteiro(Registrador reg);
void inteiroParaRegistrador(long int numero, Registrador reg);
#endif