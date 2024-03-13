#ifndef UC_H
#define UC_H

#include "processador.h"

void verificarAcao();
void buscarMemoria();
void escreverMemoria(enum escritaMemoria tipo);
void flushPipeline();
void escreverTudo(unsigned long long int posicao);
void escreverEsquerda(unsigned long long int posicao);
void escreverDireita(unsigned long long int posicao);

#endif
