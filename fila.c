#include "headers/fila.h"
// Função para criar uma fila vazia
Fila* criarFila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->frente = -1;
    fila->tras = -1;
    return fila;
}

// Função para verificar se a fila está vazia
short estaVazia(Fila* fila) {
    return fila->frente == -1;
}

// Função para verificar se a fila está cheia
short estaCheia(Fila* fila) {
    return (fila->tras + 1) % TAMANHO_MAX_FILA == fila->frente;
}

// Função para enfileirar um elemento
void enfileirar(Fila* fila, short item) {
    if (estaCheia(fila)) {
        printf("A fila está cheia!\n");
        return;
    }
    if (estaVazia(fila))
        fila->frente = 0;
    fila->tras = (fila->tras + 1) % TAMANHO_MAX_FILA;
    fila->itens[fila->tras] = item;
    printf("%d enfileirado na posição %d\n", item, fila->tras);
}

// Função para desenfileirar um elemento
short desenfileirar(Fila* fila) {
    short item;
    if (estaVazia(fila)) {
        printf("A fila está vazia!\n");
        return -1;
    }
    item = fila->itens[fila->frente];
    if (fila->frente == fila->tras) {
        fila->frente = -1;
        fila->tras = -1;
    } else {
        fila->frente = (fila->frente + 1) % TAMANHO_MAX_FILA;
    }
    return item;
}

// Função para obter o primeiro elemento da fila sem removê-lo
short primeiroElemento(Fila* fila) {
    if (estaVazia(fila)) {
        printf("A fila está vazia!\n");
        return -1;
    }
    return fila->itens[fila->frente];
}

void mostrarFila(Fila* fila) {
    short i;
    if (estaVazia(fila)) {
        printf("A fila está vazia\n");
        return;
    }
    printf("\nElementos da fila: ");
    for (i = fila->frente; i != fila->tras; i = (i + 1) % TAMANHO_MAX_FILA) {
        printf("%d ", fila->itens[i]);
    }
    printf("%d\n", fila->itens[i]);
}

bool elementoNaFila(Fila* fila, short elemento) {
    if (estaVazia(fila)) {
        return false;
    }
    
    short i = fila->frente;
    do {
        if (fila->itens[i] == elemento) {
            return true;
        }
        i = (i + 1) % TAMANHO_MAX_FILA;
    } while (i != (fila->tras + 1) % TAMANHO_MAX_FILA);

    return false;
}