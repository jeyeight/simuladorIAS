#ifndef BARRAMENTO_H
#define BARRAMENTO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"

void setBarramentoDados(Dado dado);
void getBarramentoDados(bool MBR);
void setBarramentoEndereco(Endereco ende);
Endereco* getBarramentoEndereco();

#endif