#include <stdio.h>
#include <headers/types.h>

void setBarramentoMemoria(Dado data){
    for(int i = 0; i < 5; i++){
        BM.dd[i] = data[i];
    }
}

Dado* getBarramentoMemoria(){
    Dado* ptrDado = (Dado*)malloc(sizeof(Dado));
    for (int i = 0; i < 5; i++) {
        *ptrDado[i] = BM.dd[i]; 
    }    
    return ptrDado;
};
void setBarramentoDados(Dado data){
    for(int i = 0; i < 5; i++){
        BM.dd[i] = data[i];
    }
}

Dado* getBarramentoDados(){
    Dado* ptrDado = (Dado*)malloc(sizeof(Dado));
    for (int i = 0; i < 5; i++) {
        *ptrDado[i] = BM.dd[i]; 
    }    
    return ptrDado;
};
