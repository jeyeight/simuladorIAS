#ifndef BARRAMENTO_H
#define BARRAMENTO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"

void setBarramentoDados(Dado dado);
void getBarramentoDados(boolean MBR);
void setBarramentoEndereco(Endereco ende);
Endereco* getBarramentoEndereco();

#endif