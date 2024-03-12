#ifndef FILA_H 
#define FILA_H

#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAX_FILA 100

typedef struct {
    int itens[TAMANHO_MAX_FILA];
    int frente;
    int tras;
} Fila;

#endif