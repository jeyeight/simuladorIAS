#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "headers/memoria.h"
#include "headers/utils.h"
#include "headers/types.h"
#include "headers/processador.h"

void executaULA(enum Operacoes Operacao, int Operando1, long long int reg){
    long long int acumulador;
    long long int memoria;
    switch (Operacao){
        case ADD:
            printf("%i - Peso ADD", Pesos[ADD]);
            int nmr = 10;
            BR.AC[4] |= nmr;
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            acumulador += Operando1;
            inteiroParaRegistrador(acumulador, BR.AC, false, -1);
            break;
        case ADDModulo:
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            acumulador += abs(Operando1);
            inteiroParaRegistrador(acumulador, BR.AC, false, -1);
            break;
        case SUB:
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            acumulador -= Operando1;
            inteiroParaRegistrador(acumulador, BR.AC, false, -1);
            break;
        case SUBModulo:
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            acumulador -= abs(Operando1);
            inteiroParaRegistrador(acumulador, BR.AC, false, -1);
            break;
        case MUL:
            long long int Mq = registradorParaInteiro(BR.MQ, false, -1);
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            acumulador = Mq * Operando1;
            if(acumulador > LIMITE_39_BITS){
                Mq = acumulador - LIMITE_39_BITS;
                acumulador = LIMITE_39_BITS;
            }
            inteiroParaRegistrador(Mq, BR.MQ, false, -1);
            inteiroParaRegistrador(acumulador, BR.AC, false, -1);
            break;
        case DIV:
            long long int mq = registradorParaInteiro(BR.MQ, false, -1);
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            mq = (Operando1 / acumulador);
            acumulador = (Operando1 % acumulador);
            inteiroParaRegistrador(mq, BR.MQ, false, -1);
            inteiroParaRegistrador(acumulador, BR.AC, false, -1);
            break;
        case LSH:
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            acumulador <<= 1;
            inteiroParaRegistrador(acumulador, BR.AC, false, -1);
            break;
        case RSH:
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            acumulador >>= 1;
            inteiroParaRegistrador(acumulador, BR.AC, false, -1);
            break;
        case STOR:
            transferirRM(BR.AC, m, Operando1);
            break;
        case STOREsq:
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            memoria = registradorParaInteiro(NULL, true, Operando1);
            acumulador &= LONG_INT_ULTIMOS12_ALTOS_DIR;
            memoria &= LONG_INT_ULTIMOS12_BAIXOS_DIR;
            memoria |= acumulador;
            break;
        case STORDir: 
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            memoria = registradorParaInteiro(NULL, true, Operando1);
            acumulador &= LONG_INT_ULTIMOS12_ALTOS;
            memoria &= LONG_INT_ULTIMOS12_BAIXOS;
            memoria |= acumulador;
            break;
        case LOADMQ:
            transferirRR(BR.AC, BR.MQ);
            break;
        case LOADMQM:
            transferirRR(BR.AC, BR.MQ);
            BR.AC[0] ^= PRIMEIRO_BIT;
            break;
        case LOAD:
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

void busca(){

}

void decodificacao(bool newInstruction){ //posicao = posicao da primeira instrucao
    //posicao n precisa, vai estar em MBR ja.
    bool opcode_exit = false;
    int opcode = 0;
    if(newInstruction){
        unsigned char temp;
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
    busca();
}

void buscaOperandos(){
    decodificacao(true);
}

void execucao(){
    buscaOperandos();
}

void escritaResultados(){
    if (EX_ER.classe == EscritaRegistrador)
    {
        //escrever no registrador
        //ULA -> AC
        transferirRR(EX_ER.reg1, EX_ER.Dado);
    }
    else if(EX_ER.classe == EscritaMemoria)
    {
        //escrever na memoria
        //
        if(EX_ER.opc == OPC_STOR){
            //ULA -> MBR
            //*Dado foi puxado do AC anteriormente.
            transferirRR(EX_ER.Dado, BR.MBR);
            
            EX_ER.endereco[0] = BR.MAR[3];
            EX_ER.endereco[1] = BR.MAR[4];
            //verificação de apenas pegar os últimos dois bytes, 
            BR.MAR[3] &= 0b00001111;
            setBarramentoDados(BR.MBR);
            setBarramentoEndereco();

        }


    }
    else if(EX_ER.classe == EscritaDoisRegistradores){

        //escrever nos dois registradores.
    }
    else{
        printf("Classe inexistente, abortando.");
        exit(1);
    }
    
    execucao();
}

void pipeline(){
    escritaResultados();
}