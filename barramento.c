#include "headers/types.h"
#include <stdio.h>
#include <string.h>

void setBarramentoDados(Dado dado){
    strcpy(BD.dado,dado); 
};

Dado* getBarramentoDados(){
    Dado *ptrBD = (Dado*)malloc(sizeof(Dado)); 
    if (ptrBD != NULL) {
        memcpy(ptrBD, BD.dado, sizeof(BD.dado)); 
    }
    return ptrBD;
}

void setBarramentoEndereco(Endereco ende){
    strcpy(BE.end,ende); 
};

Endereco* getBarramentoEndereco(){
    Endereco *ptrBE = (Endereco*)malloc(sizeof(Endereco)); 
    if (ptrBE != NULL) {
        memcpy(ptrBE, BE.end, sizeof(BE.end)); 
    }
    return ptrBE;
}
