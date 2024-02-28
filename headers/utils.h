#ifndef UTILS_H
#define UTILS_H

void zerarString(char string[], int tamanho);
void verificaArgumentos(int argc, char* argv[], FILE** fdEntrada, FILE** fdSaida, struct banco_de_registradores *BR);
void transferirRegistradores(registrador Src, registrador Dest);

#endif