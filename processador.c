#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "memoria.c"
#include "headers/utils.h"
#include "headers/types.h"

#define LIMITE_39_BITS 549755813888
#define PRIMEIRO_BIT 0b10000000
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
                Mq = Acumulador - LIMITE_39_BITS;
                Acumulador = LIMITE_39_BITS;
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
            transferirRM(BR.AC, m, Operando1);
            break;
        case STOREsq:
            printf("Operação de Armazenamento Quadrado.\n");
            break;
        case STORDir:
            printf("Operação de Armazenamento Direto.\n");
            break;
        case LOADMQ:
            transferirRR(BR.AC, BR.MQ);
            break;
        case LOADMQM:
            transferirRR(BR.AC, abs(BR.MQ));
            break;
        case LOAD:
            printf("Operação de Carregamento.\n");
            transferirMR(BR.AC, m, Operando1);
            break;
        case LOADMenos:

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
    //posicao n precisa, vai estar em MBR ja.
    bool opcode_exit = false;
    int numero = 0;
    int end1 = 0;
    int end2 = 0;
    int result = 0;
    int opcode = 0;
    int opcode2 = 0;
    if(newInstruction){
        unsigned char temp;
        int segunda_instrucao = 0;
        
        //busca foi realizada antes.
        
        //Pegar o primeiro opcode e colocar em IR. 
        BR.IR[4] = BR.MBR[0];
        printf("%i - Opcode 1 em IR\n", BR.IR[4]);
        opcode = BR.IR[4];
        printf("opcodeeeee %i\n", opcode);

        if(opcode == OPC_EXIT){
            opcode_exit = true;
        }

        //Pegar o primeiro endereco e colocar em MAR.
        BR.MAR[3] = BR.MBR[1];
        BR.MAR[4] = BR.MBR[2];

        BR.MAR[4] >>= 4;

        temp = BR.MAR[3] << 4;

        BR.MAR[3] >>= 4;
        BR.MAR[4] |= temp;

        printf("\n%i - Endereco 1 Parte 1", BR.MAR[3]);
        printf("\n%i - Endereco 1 Parte 2\n", BR.MAR[4]);

        printaEnderecoMar();
        
        if(!opcode_exit){ //precisa das duas instruções, não é um EXIT.
            //colocar a segunda instrucao em IBR        
            BR.IBR[2] = BR.MBR[2];
            BR.IBR[3] = BR.MBR[3];
            BR.IBR[4] = BR.MBR[4];
            BR.IBR[2] &= 15;

            printf("\n%i - Pedaco 1 da Instrucao 2", BR.IBR[2]);
            printf("\n%i - Pedaco 2 da Instrucao 2", BR.IBR[3]);
            printf("\n%i - Pedaco 3 da Instrucao 2", BR.IBR[4]);
        }

    }else{ 
        unsigned char temp2;

        //colocar o opcode da instrução 2 em IR.
        BR.IR[4] = BR.IBR[2];

        BR.IR[4] <<= 4;

        temp2 = BR.IBR[3] & 240;
        temp2 >>= 4;

        BR.IR[4] |= temp2;

        printf("\n%i - Opcode 2", BR.IR[4]);

        //colocar o endereço da instrução 2 em MAR. 
        BR.MAR[3] = BR.IBR[3];
        BR.MAR[3] &= 15;
        BR.MAR[4] = BR.IBR[4];
        
        printf("\n%i - Endereço segunda instrucao parte 1", BR.MAR[3]);
        printf("\n%i - Endereço segunda instrucao parte 2\n", BR.MAR[4]);
        
        printaEnderecoMar();
    
    }

    
    


}