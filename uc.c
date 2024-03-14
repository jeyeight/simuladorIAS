#include <stdio.h>
#include "headers/types.h"
#include "headers/barramento.h"
#include "headers/flags.h"
#include "headers/uc.h"
#include "headers/processador.h"
#include "headers/memoria.h"
#include "headers/fila.h"
// 0 0 0 0 0 0 0 0    0 0 0 0 0 0 0 0 
//primeiro - chamar pipeline
//segundo - chamar escrita_resultados
//terceiro - chamar execucao
//quarto - chamar bo
//quinto - chamar decodificao
//sexto - chamar busca
//setimo - leftinstructionrequired
//oitavo - flush
//nono - Dependência Stor
//décimo - Dependência Address
//décimo primeiro - clock

void verificarAcao(){
    if(get_flag_pipe()){
        zerarEstagiosPipe();
        pipeline();
    }else if(get_flag_er()){
        zerarEstagiosPipe();
        escritaResultados();
    }else if(get_flag_ex()){
        zerarEstagiosPipe();
        execucao();
    }else if(get_flag_bo()){
        zerarEstagiosPipe();
        buscarOperandos();
    }else if(get_flag_d()){
        zerarEstagiosPipe();
        decodificacao(true);
    }else if(get_flag_b()){
        zerarEstagiosPipe();
        busca();
    }
}

void buscarMemoria(){
    Endereco* ptrBD;
    ptrBD = getBarramentoEndereco();
    
    unsigned long long int posicao = converteEndereco(ptrBD);
    transferirMR(m, posicao); 

    getBarramentoDados(true); 
}

void escreverMemoria(enum escritaMemoria tipo){
    Endereco* ptrBE;
    ptrBE = getBarramentoEndereco();
    unsigned long long int posicao = converteEndereco(ptrBE);
    if(tipo == Tudo){
        escreverTudo(posicao);
    }
    else if (tipo == Esquerda){ 
        escreverEsquerda(posicao);
    }
    else if(tipo == Direita){
        escreverDireita(posicao);
    }
    
}

void flushPipeline(){
    statusB = Vazio;
    statusD = Vazio;
    statusBO = Vazio;
}

void escreverTudo(unsigned long long int posicao){
        int index = 0;
        m[posicao] = BD.dado[index];
        posicao++;
        index++;
        m[posicao] = BD.dado[index];
        posicao++;
        index++;
        m[posicao] = BD.dado[index];
        posicao++;
        index++;
        m[posicao] = BD.dado[index];
        posicao++;
        index++;
        m[posicao] = BD.dado[index];
}

void escreverEsquerda(unsigned long long int posicao){
    unsigned char temp;
    posicao++;
    BD.dado[3] <<= 4;
    temp = BD.dado[4];
    temp >>= 4;
    BD.dado[3] |= temp;
    m[posicao] = BD.dado[3];
    posicao++;
    BD.dado[4] <<= 4;
    m[posicao] &= 0b00001111;
    m[posicao] |= BD.dado[4];
}

void escreverDireita(unsigned long long int posicao){
        posicao += 3;
        m[posicao] &= 0b11110000;
        m[posicao] |= BD.dado[3];
        posicao++;
        m[posicao] = BD.dado[4];
}