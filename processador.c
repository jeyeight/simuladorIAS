#include <stdio.h>
#include "headers/utils.h"
#include "headers/types.h"

char executaULA(enum Operacoes Operacao, int Operando1, int Operando2, int Pesos[], int* Custo){
    char result = 0;
    switch (Operacao){
        case ADD:
            result = Operando1 + BR.AC;
            break;
        case ADDModulo:
            printf("Operação de Adição com Módulo.\n");
            break;
        case SUB:
            result = Operando1 + Operando2;
            break;
        case SUBModulo:
            printf("Operação de Subtração com Módulo.\n");
            break;
        case MUL:
            printf("Operação de Multiplicação.\n");
            break;
        case DIV:
            printf("Operação de Divisão.\n");
            break;
        case LSH:
            printf("Operação de Deslocamento à Esquerda.\n");
            break;
        case RSH:
            printf("Operação de Deslocamento à Direita.\n");
            break;
        case STOR:
            transferirRR(BR.AC, m);
            break;
        case STOREsq:
            printf("Operação de Armazenamento Quadrado.\n");
            break;
        case STORDir:
            printf("Operação de Armazenamento Direto.\n");
            break;
        case LOADMQ:
            printf("Operação de Carregamento MQ.\n");
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
