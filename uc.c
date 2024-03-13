#include <stdio.h>
#include "headers/types.h"
#include "headers/barramento.h"
#include "headers/flags.h"
#include "headers/uc.h"
#include "headers/processador.h"
#include "headers/memoria.h"


// 0 0 0 0 0 0 0 0    0 0 0 0 0 0 0 0 
//primeiro - chamar pipeline
//segundo - chamar escrita_resultados
//terceiro - chamar execucao
//quarto - chamar bo
//quinto - chamar decodificao
//sexto - chamar busca
//setimo - leftinstructionrequired
//oitavo

//nono - mostra se multiplicacao sobrou pro AC
//decimo pra frente - status dos ciclos? ou guardar em variaveis separadas.
//... // ps: flag para talvez identificar se preicsa ou n fazer busca 
//(a busca as vezes é feita) ou não, depende se na instrução passada ele buscou já na memória, ou se só puxou de IBR.
// 
//talvez mexer nas flags?

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
    Dado * linha;
    Endereco ende = "23";
    //setBarramentoEndereco(ende);
    ptrBD = getBarramentoEndereco();
    printf("%i\n", *ptrBD[0]);
    printf("%i\n", *ptrBD[1]);
    
    unsigned long long int posicao = converteEndereco(ptrBD);
    transferirMR(BR.MBR, m, posicao); //joga no barramento.

    getBarramentoDados(true); //MBR recebe dado

    for(int i = 0; i< 5; i++){
        printf("%i\n", BR.MBR[i]);
    }

}

void escreverMemoria(enum escritaMemoria tipo){
    Endereco* ptrBE;
    ptrBE = getBarramentoEndereco();
    unsigned long long int posicao = converteEndereco(ptrBE);
    if(tipo == Tudo){
        escreverTudo(posicao);
        // printf("\nOLHA EU COMEÇANDO A BRINCAR:\n");
        // m[posicao] = BD.dado[index];
        // printf("\n%i", m[posicao]);
        // posicao++;
        // index++;
        // m[posicao] = BD.dado[index];
        // printf("\n%i", m[posicao]);
        // posicao++;
        // index++;
        // m[posicao] = BD.dado[index];
        // printf("\n%i", m[posicao]);
        // posicao++;
        // index++;
        // m[posicao] = BD.dado[index];
        // printf("\n%i", m[posicao]);
        // posicao++;
        // index++;
        // m[posicao] = BD.dado[index];
        // printf("\n%i", m[posicao]);
        // printf("\nOLHA EU TERMINANDO DE BRINCAR:\n");
    }
    else if (tipo == Esquerda){ //apenas trocar endereço da esquerda.
        escreverEsquerda(posicao);
        // posicao++;
        // BD.dado[3] <<= 4;
        // temp = BD.dado[4];
        // temp >>= 4;
        // BD.dado[3] |= temp;
        // m[posicao] = BD.dado[3];
        // posicao++;
        // BD.dado[4] <<= 4;
        // m[posicao] &= 0b00001111;
        // m[posicao] |= BD.dado[4];
    }
    else if(tipo == Direita){
        escreverDireita(posicao);
        // posicao++;
        // posicao++;
        // posicao++; //alterar dps
        // m[posicao] &= 0b11110000;
        // m[posicao] |= BD.dado[3];
        // posicao++;
        // m[posicao] = BD.dado[4];
    }
    
}

void flushPipeline(){
    statusB = Vazio;
    statusD = Vazio;
    statusBO = Vazio;
    //statusEX = Vazio;
    printf("Flushamos");
    //exit(1);
}

void escreverTudo(unsigned long long int posicao){
        int index = 0;
        printf("\nOLHA EU COMEÇANDO A BRINCAR:\n");
        m[posicao] = BD.dado[index];
        printf("\n%i", m[posicao]);
        posicao++;
        index++;
        m[posicao] = BD.dado[index];
        printf("\n%i", m[posicao]);
        posicao++;
        index++;
        m[posicao] = BD.dado[index];
        printf("\n%i", m[posicao]);
        posicao++;
        index++;
        m[posicao] = BD.dado[index];
        printf("\n%i", m[posicao]);
        posicao++;
        index++;
        m[posicao] = BD.dado[index];
        printf("\n%i", m[posicao]);
        printf("\nOLHA EU TERMINANDO DE BRINCAR:\n");
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
        // posicao++;
        // posicao++;
        // posicao++; alterar dps
        posicao += 3;
        m[posicao] &= 0b11110000;
        m[posicao] |= BD.dado[3];
        posicao++;
        m[posicao] = BD.dado[4];
}