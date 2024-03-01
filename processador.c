#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/utils.h"
#include "headers/types.h"

#define LIMITE_39_BITS 549755813888

char executaULA(enum Operacoes Operacao, int Operando1, int Operando2){
    char result = 0;
    int acumulador;
    switch (Operacao){
        case ADD:
            printf("%i - Peso ADD", Pesos[ADD]);
            acumulador = atoi(BR.AC);
            acumulador += Operando1;
            sprintf(BR.AC, "%d", acumulador);
            break;
        case ADDModulo:
            printf("Operação de Adição com Módulo.\n");
            acumulador = atoi(BR.AC);
            acumulador += abs(Operando1);
            sprintf(BR.AC, "%d", acumulador);
            break;
        case SUB:
            printf("%i - Peso ADD", Pesos[ADD]);
            acumulador = atoi(BR.AC);
            acumulador -= Operando1;
            sprintf(BR.AC, "%d", acumulador);
            break;
        case SUBModulo:
            printf("Operação de Subtração com Módulo.\n");
            printf("Operação de Adição com Módulo.\n");
            acumulador = atoi(BR.AC);
            acumulador -= abs(Operando1);
            sprintf(BR.AC, "%d", acumulador);
            break;
        case MUL:
            printf("Operação de Multiplicação.\n");
            long int Mq = atoi(BR.MQ);
            long int Acumulador = atoi(BR.MQ);
            Acumulador = Mq * Operando1;
            if(Acumulador > LIMITE_39_BITS){
                
            }
            sprintf(BR.MQ, "%d", Mq);
            sprintf(BR.AC, "%d", Acumulador);
            break;
        case DIV:
            printf("Operação de Divisão.\n");
            int mq = atoi(BR.MQ);
            acumulador = atoi(BR.AC);
            mq = (Operando1 / acumulador);
            acumulador = (Operando1 % acumulador);
            sprintf(BR.MQ, "%d", mq);
            sprintf(BR.AC, "%d", acumulador);
            break;
        case LSH:
            printf("Operação de Deslocamento à Esquerda.\n");
            acumulador = atoi(BR.AC);
            acumulador <<= 1;
            sprintf(BR.AC, "%d", acumulador);
            break;
        case RSH:
            printf("Operação de Deslocamento à Direita.\n");
            acumulador = atoi(BR.AC);
            acumulador >>= 1;
            sprintf(BR.AC, "%d", acumulador);
            break;
        case STOR:
            transferirRR(BR.AC, m);
            int posicao = Operando1 * 5;
            for(int i = posicao; i<posicao+5; i++){
                
            }
            break;
        case STOREsq:
            printf("Operação de Armazenamento Quadrado.\n");
            break;
        case STORDir:
            printf("Operação de Armazenamento Direto.\n");
            break;
        case LOADMQ:
            printf("Operação de Carregamento MQ.");
            printf("Peso = %i", Pesos[LOADMQ]);
            break;
        case LOADMQM:
            printf("Operação de Carregamento MQ Multiplicação.\n");
            break;
        case LOAD:
            printf("Operação de Carregamento.\n");
            //apenas testando, precisará passar pelo barramento.



            break;
        case LOADMenos:
            printf("Operação de Carregamento Negativo.\n");
            break;
        case LOADModulo:
            printf("Operação de Carregamento com Módulo.\n");
            break;
        case LOADMenosModulo:
            printf("Operação de Carregamento Negativo com Módulo.\n");
            break;
        case JUMPDir:
            printf("Operação de Salto Direto.\n");
            break;
        case JUMPEsq:
            printf("Operação de Salto Indireto.\n");
            break;
        case JUMPPDir:
            printf("Operação de Salto Positivo Direto.\n");
            break;
        case JUMPPEsq:
            printf("Operação de Salto Positivo Indireto.\n");
            break;
        case EXIT:
            printf("Operação de Saída.\n");
            break;
        default:
            printf("Operação não reconhecida.\n");
    };
    return result;
};


void decodificacao(int posicao, bool newInstruction){ //posicao = posicao da primeira instrucao
    int numero = 0;
    int end1 = 0;
    int end2 = 0;
    int opcode = 0;
    int opcode2 = 0;
    long long int linha = 0;
    if(newInstruction){
        int segunda_instrucao = 0;
        //busca foi realizada antes.
        linha |= m[posicao];
        opcode = linha;
        printf("\nopcode1 = %i\n", opcode); //certo!
        sprintf(BR.IR, "%d", opcode);
        
        posicao++;
        linha = 0; //resetei
        linha |= m[posicao];
        linha <<= 8;
        posicao++;
        linha |= m[posicao];
        linha >>= 4;
        end1 = linha;

        printf("endereco 1 = %i\n", end1);
        sprintf(BR.MAR, "%d", end1);
        //fará essa parte se houverem duas instrução, se houver só 1, não.
        linha = 0;
        linha |= m[posicao];
        linha <<= 8;
        posicao++;
        linha |= m[posicao];
        linha <<= 8;
        posicao++;
        linha |= m[posicao];
        segunda_instrucao = linha & 1048575;
        sprintf(BR.IBR, "%d", segunda_instrucao);

    }else{ //else está tudo torto, ta qualquer coisa.


    linha |= m[posicao];
    opcode = linha;
    printf("\nopcode1 = %i\n", opcode); //certo!
    sprintf(BR.IR, "%d", opcode);
    
    posicao++;
    linha = 0; //resetei
    linha |= m[posicao];
    linha <<= 8;
    posicao++;
    linha |= m[posicao];
    linha >>= 4;
    end1 = linha;

    printf("endereco 1 = %i\n", end1);
    
    linha = 0;
    linha |= m[posicao];
    //printf("%i - posicao\n", posi);
    //printf("linha agora - %lld\n", linha);
    linha <<= 8;
    //printf("linha agora entaummm - %lld\n", linha);

    posicao++;
    linha |= m[posicao];
    //printf("linha agora entaummm22 - %lld\n", linha);

    opcode2 = linha & 4080;
    opcode2 >>= 4;

    printf("opcode2 = %i\n", opcode2);
    linha = 0;
    linha |= m[posicao];
    linha <<= 8;
    posicao++;
    linha |= m[posicao];
    end2 = linha & 4095;

    printf("endereco 2 = %i\n", end2);

    
    
    }

    
    


}