#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/utils.h"
#include "headers/types.h"

#define LIMITE_39_BITS 549755813888

char executaULA(enum Operacoes Operacao, int Operando1, int Operando2){
    char result = 0;
    switch (Operacao){
        case ADD:
            printf("%i - Peso ADD", Pesos[ADD]);
            int acumulador = atoi(BR.AC);
            acumulador += Operando1;
            sprintf(BR.AC, "%d", acumulador);
            break;
        case ADDModulo:
            printf("Operação de Adição com Módulo.\n");
            int acumulador = atoi(BR.AC);
            acumulador += abs(Operando1);
            sprintf(BR.AC, "%d", acumulador);
            break;
        case SUB:
            printf("%i - Peso ADD", Pesos[ADD]);
            int acumulador = atoi(BR.AC);
            acumulador -= Operando1;
            sprintf(BR.AC, "%d", acumulador);
            break;
        case SUBModulo:
            printf("Operação de Subtração com Módulo.\n");
            printf("Operação de Adição com Módulo.\n");
            int acumulador = atoi(BR.AC);
            acumulador -= abs(Operando1);
            sprintf(BR.AC, "%d", acumulador);
            break;
        case MUL:
            printf("Operação de Multiplicação.\n");
            long int mq = atoi(BR.MQ);
            long int acumulador = atoi(BR.MQ);
            acumulador = mq * Operando1;
            if(acumulador > LIMITE_39_BITS){
                
            }
            sprintf(BR.MQ, "%d", mq);
            sprintf(BR.AC, "%d", acumulador);
            break;
        case DIV:
            printf("Operação de Divisão.\n");
            int mq = atoi(BR.MQ);
            int acumulador = atoi(BR.AC);
            mq = (Operando1 / acumulador);
            acumulador = (Operando1 % acumulador);
            sprintf(BR.MQ, "%d", mq);
            sprintf(BR.AC, "%d", acumulador);
            break;
        case LSH:
            printf("Operação de Deslocamento à Esquerda.\n");
            int acumulador = atoi(BR.AC);
            acumulador <<= 1;
            sprintf(BR.AC, "%d", acumulador);
            break;
        case RSH:
            printf("Operação de Deslocamento à Direita.\n");
            int acumulador = atoi(BR.AC);
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
