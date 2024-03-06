#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "headers/memoria.h"
#include "headers/utils.h"
#include "headers/types.h"

#define LIMITE_39_BITS 549755813888
#define PRIMEIRO_BIT 0b10000000
void executaULA(enum Operacoes Operacao, int Operando1, Registrador reg){
    long int acumulador;
    switch (Operacao){
        case ADD:
            printf("%i - Peso ADD", Pesos[ADD]);
            int nmr = 10;
            BR.AC[4] |= nmr;
            acumulador = registradorParaInteiro(BR.AC);
            acumulador += Operando1;
            printf("acumulador ficou com isso - %ld \n", acumulador);
            inteiroParaRegistrador(acumulador, BR.AC);
            for(int i = 0; i < 5; i++){
                printf("Char - %i\n", BR.AC[i]);
            }
            break;
        case ADDModulo:
            printf("Operação de Adição com Módulo.\n");
            acumulador = registradorParaInteiro(BR.AC);
            acumulador += abs(Operando1);
            inteiroParaRegistrador(acumulador, BR.AC);
            break;
        case SUB:
            printf("%i - Peso ADD", Pesos[ADD]);
            acumulador = registradorParaInteiro(BR.AC);
            acumulador -= Operando1;
            inteiroParaRegistrador(acumulador, BR.AC);
            break;
        case SUBModulo:
            printf("Operação de Subtração com Módulo.\n");
            printf("Operação de Adição com Módulo.\n");
            acumulador = registradorParaInteiro(BR.AC);
            acumulador -= abs(Operando1);
            inteiroParaRegistrador(acumulador, BR.AC);
            break;
        case MUL:
            printf("Operação de Multiplicação.\n"); 
            long int Mq = registradorParaInteiro(BR.MQ);
            acumulador = registradorParaInteiro(BR.AC);
            acumulador = Mq * Operando1;
            if(acumulador > LIMITE_39_BITS){
                Mq = acumulador - LIMITE_39_BITS;
                acumulador = LIMITE_39_BITS;
            }
            inteiroParaRegistrador(Mq, BR.MQ);
            inteiroParaRegistrador(acumulador, BR.AC);
            break;
        case DIV:
            printf("Operação de Divisão.\n");
            long int mq = registradorParaInteiro(BR.MQ);
            acumulador = registradorParaInteiro(BR.AC);
            mq = (Operando1 / acumulador);
            acumulador = (Operando1 % acumulador);
            inteiroParaRegistrador(mq, BR.MQ);
            inteiroParaRegistrador(acumulador, BR.AC);
            break;
        case LSH:
            printf("Operação de Deslocamento à Esquerda.\n");
            acumulador = registradorParaInteiro(BR.AC);
            acumulador <<= 1;
            inteiroParaRegistrador(acumulador, BR.AC);
            break;
        case RSH:
            printf("Operação de Deslocamento à Direita.\n");
            acumulador = registradorParaInteiro(BR.AC);
            acumulador >>= 1;
            inteiroParaRegistrador(acumulador, BR.AC);
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
            transferirRR(BR.AC, BR.MQ);
            BR.AC[0] ^= PRIMEIRO_BIT;
            break;
        case LOAD:
            printf("Operação de Carregamento.\n");
            transferirMR(BR.AC, m, Operando1);
            break;
        case LOADMenos:
            transferirMR(BR.AC, m, Operando1);
            BR.AC[0] ^= PRIMEIRO_BIT;
            break;
        case LOADModulo:
            transferirMR(BR.AC, m, abs(Operando1));
            break;
        case LOADMenosModulo:
            printf("Operação de Carregamento Negativo com Módulo.\n");
            transferirMR(BR.AC, m, abs(Operando1));
            BR.AC[0] ^= PRIMEIRO_BIT;
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
            exit(1);
            break;
        default:
            printf("Operação não reconhecida.\n");
    };
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
        BR.MAR[3] = BR.IBR[3]; //receba  =°3°=
        BR.MAR[3] &= 15;
        BR.MAR[4] = BR.IBR[4];
        
        printf("\n%i - Endereço segunda instrucao parte 1", BR.MAR[3]);
        printf("\n%i - Endereço segunda instrucao parte 2\n", BR.MAR[4]);
        
        printaEnderecoMar();
    
    }

    
    


}