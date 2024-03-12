#ifndef FILA_H 
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAMANHO_MAX_FILA 100

typedef struct {
    int itens[TAMANHO_MAX_FILA];
    int frente;
    int tras;
} Fila;

// extern Fila* dependencia_address;
// extern Fila* dependencia_stor;

Fila* criarFila();
short estaVazia(Fila* fila);
short estaCheia(Fila* fila);
void enfileirar(Fila* fila, short item);
short desenfileirar(Fila* fila);
short primeiroElemento(Fila* fila);
void mostrarFila(Fila* fila);
bool elementoNaFila(Fila* fila, short elemento);

#endif