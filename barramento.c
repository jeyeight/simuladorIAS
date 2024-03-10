#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/types.h"

void setBarramentoDados(Dado dado){
    strcpy((char*)BD.dado,(char*)dado); 
};

Dado* getBarramentoDados(){
    Dado *ptrBD = (Dado*)malloc(sizeof(Dado)); 
    if (ptrBD != NULL) {
        memcpy(ptrBD, BD.dado, sizeof(BD.dado)); 
    }
    return ptrBD;
}

void setBarramentoEndereco(Endereco ende){
    strcpy((char*)BE.end,(char*)ende); 
};

Endereco* getBarramentoEndereco(){
    Endereco *ptrBE = (Endereco*)malloc(sizeof(Endereco)); 
    if (ptrBE != NULL) {
        memcpy(ptrBE, BE.end, sizeof(BE.end)); 
    }
    return ptrBE;
}
