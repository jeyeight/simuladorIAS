#include "headers/barramento.h"

void setBarramentoDados(Dado dado){
    for (int i = 0; i < 5; i++){
        BD.dado[i] = dado[i];
    }
};

Dado* getBarramentoDados(){
    Dado *ptrBD = (Dado*)malloc(sizeof(Dado)); 
    if (ptrBD != NULL) {
        for (int i = 0; i < 5; i++)
        {
            *ptrBD[i] = BD.dado[i];
        }
    }
    return ptrBD;
}

void setBarramentoEndereco(Endereco ende){
    for (int i = 0; i < 2; i++){
        BE.end[i] = ende[i];
    }};

Endereco* getBarramentoEndereco(){
    Endereco *ptrBE = (Endereco*)malloc(2 * sizeof(Endereco)); 
    if (ptrBE != NULL) {
        for (int i = 0; i < 2; i++)
        {
            *ptrBE[i] = BE.end[i];
        }    
    }
    return *ptrBE;
}
