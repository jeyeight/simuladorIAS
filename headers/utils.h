#ifndef UTILS_H
#define UTILS_H

#define QUADRAGESIMO_BIT 0b1000000000000000000000000000000000000000
#define FULL_BYTE 0XFFFFFFFFFF

void zerarString(char string[], int tamanho);
void verificaArgumentos(int argc, char* argv[], FILE** fdEntrada, FILE** fdSaida);
void testarPesos();
void verificaPesos(FILE * fdEntrada);
void setar_peso(char* operacao, int peso);
char* itoa(int value, char* result, int base);
void printaEnderecoMar();
unsigned long long int registradorParaInteiro(unsigned char valor[5], bool isMemoria, int indiceMemoria);
void inteiroParaRegistrador(unsigned long long int numero, unsigned char dado[5], bool isMemoria, int posMemoria);
bool isNegativeChar(unsigned char c);
unsigned long long int modulo(unsigned long long int n);
unsigned short enderecoParaShort(unsigned char endereco[]);
int fornecerPeso(enum Operacoes Operacao);
bool isNegativeULL(unsigned long long int n);

#endif