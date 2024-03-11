#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "headers/types.h"
#include "headers/utils.h"
#include "headers/barramento.h"
#include "headers/memoria.h"
#include "headers/processador.h"
#include "headers/flags.h"
#include "headers/uc.h"


int statusB = Vazio; // tem q ter 3, vazio, finalizado, fazendo. 
int statusD = Vazio; //tecnicamente, o fazendo estaria apenas no
int statusBO = Vazio;
int statusEX = Vazio;
int statusER = Vazio;

void executaULA(enum Operacoes Operacao, unsigned long long int Operando1){
    unsigned long long int acumulador;
    unsigned long long int memoria;
    switch (Operacao){
        case ADD:
            printf("%i - Peso ADD", Pesos[ADD]);
            int nmr = 10;
            BR.AC[4] |= nmr;
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            acumulador += Operando1;
            //inteiroParaRegistrador(acumulador, BR.AC, false, -1);
            transferirRR(ex_er.reg1, BR.AC);
            inteiroParaRegistrador(acumulador, ex_er.dado, false, -1);
            ex_er.classe = EscritaRegistrador;
            break;
        case ADDModulo:
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            acumulador += modulo(Operando1);
            //inteiroParaRegistrador(acumulador, BR.AC, false, -1);
            transferirRR(ex_er.reg1, BR.AC);
            inteiroParaRegistrador(acumulador, ex_er.dado, false, -1);
            ex_er.classe = EscritaRegistrador;
            break;
        case SUB:
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            acumulador -= Operando1;
            //inteiroParaRegistrador(acumulador, BR.AC, false, -1);
            transferirRR(ex_er.reg1, BR.AC);
            inteiroParaRegistrador(acumulador, ex_er.dado, false, -1);
            ex_er.classe = EscritaRegistrador;
            break;
        case SUBModulo:
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            acumulador -= modulo(Operando1);
            //inteiroParaRegistrador(acumulador, BR.AC, false, -1);
            transferirRR(ex_er.reg1, BR.AC);
            inteiroParaRegistrador(acumulador, ex_er.dado, false, -1);
            ex_er.classe = EscritaRegistrador;
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
            ex_er.classe = EscritaDoisRegistradores;
            break;
        case DIV:
            long long int mq = registradorParaInteiro(BR.MQ, false, -1);
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            mq = (Operando1 / acumulador);
            acumulador = (Operando1 % acumulador);
            inteiroParaRegistrador(mq, BR.MQ, false, -1);
            inteiroParaRegistrador(acumulador, BR.AC, false, -1);
            ex_er.classe = EscritaDoisRegistradores;
            break;
        case LSH:
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            acumulador <<= 1;
            //inteiroParaRegistrador(acumulador, BR.AC, false, -1);
            transferirRR(ex_er.reg1, BR.AC);
            inteiroParaRegistrador(acumulador, ex_er.dado, false, -1);
            ex_er.classe = EscritaRegistrador;
            break;
        case RSH:
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            acumulador >>= 1;
            //inteiroParaRegistrador(acumulador, BR.AC, false, -1);
            transferirRR(ex_er.reg1, BR.AC);
            inteiroParaRegistrador(acumulador, ex_er.dado, false, -1);
            ex_er.classe = EscritaRegistrador;
            break;
        case STOR:
            //transferirRM(BR.AC, m, Operando1);
            inteiroParaRegistrador(Operando1, ex_er.dado, false, -1); //valor que estava em AC.
            ex_er.classe = EscritaMemoria;

            break;
        case STOREsq:
            // acumulador = registradorParaInteiro(BR.AC, false, -1);
            // memoria = registradorParaInteiro(NULL, true, Operando1);
            // acumulador &= LONG_INT_ULTIMOS12_ALTOS_DIR;
            // memoria &= LONG_INT_ULTIMOS12_BAIXOS_DIR;
            // memoria |= acumulador;
            inteiroParaRegistrador(Operando1, ex_er.dado, false, -1); //valor que estava em AC
            ex_er.classe = EscritaMemoria;

            break;
        case STORDir: 
            //acumulador = registradorParaInteiro(BR.AC, false, -1);
            //inteiroParaRegistrador(acumulador, ex_er.dado, false, -1);
            // memoria = registradorParaInteiro(NULL, true, Operando1);
            // acumulador &= LONG_INT_ULTIMOS12_ALTOS;
            // memoria &= LONG_INT_ULTIMOS12_BAIXOS;
            // memoria |= acumulador;
            inteiroParaRegistrador(Operando1, ex_er.dado, false, -1); //valor que estava em AC
            ex_er.classe = EscritaMemoria;
            break;
        case LOADMQ:
            //transferirRR(BR.AC, BR.MQ);
            transferirRR(ex_er.reg1, BR.AC);
            Operando1 = registradorParaInteiro(BR.MQ, false, -1);
            inteiroParaRegistrador(Operando1, ex_er.dado, false, -1);
            ex_er.classe = EscritaRegistrador;
            break;
        case LOADMQM:
            //transferirRR(BR.AC, BR.MQ);
            //BR.AC[0] ^= PRIMEIRO_BIT;
            transferirRR(ex_er.reg1, BR.MQ);
            inteiroParaRegistrador(Operando1, ex_er.dado, false, -1);
            ex_er.classe = EscritaRegistrador;
            break;
        case LOAD:
            //transferirMR(BR.AC, m, Operando1);
            transferirRR(ex_er.reg1, BR.AC);
            inteiroParaRegistrador(Operando1, ex_er.dado, false, -1);
            ex_er.classe = EscritaRegistrador;
            break;
        case LOADMenos:
            //transferirMR(BR.AC, m, Operando1);
            //BR.AC[0] ^= PRIMEIRO_BIT;
            Operando1 ^= QUADRAGESIMO_BIT;
            transferirRR(ex_er.reg1, BR.AC);
            inteiroParaRegistrador(Operando1, ex_er.dado, false, -1);
            ex_er.classe = EscritaRegistrador;
            break;
        case LOADModulo:
            //transferirMR(BR.AC, m, modulo(Operando1));
            transferirRR(ex_er.reg1, BR.AC);
            inteiroParaRegistrador(modulo(Operando1), ex_er.dado, false, -1);
            ex_er.classe = EscritaRegistrador;
            break;
        case LOADMenosModulo:
            //transferirMR(BR.AC, m, modulo(Operando1));
            //BR.AC[0] ^= PRIMEIRO_BIT;
            Operando1 = modulo(Operando1);
            Operando1 ^= QUADRAGESIMO_BIT;
            transferirRR(ex_er.reg1, BR.AC);
            inteiroParaRegistrador(Operando1, ex_er.dado, false, -1);

            ex_er.classe = EscritaRegistrador;
            break;
        case JUMPDir:
            printf("Operação de Salto Direto.\n");
            ex_er.classe = EscritaRegistrador;
            transferirRR(ex_er.reg1, BR.PC);
            inteiroParaRegistrador(Operando1, ex_er.dado, false, -1);
            set_flag_lir(false);
            break;
        case JUMPEsq:
            printf("Operação de Salto Indireto.\n");
            transferirRR(ex_er.reg1, BR.PC);
            inteiroParaRegistrador(Operando1, ex_er.dado, false, -1);
            ex_er.classe = EscritaRegistrador;
            break;
        case JUMPPDir:
            printf("Operação de Salto Positivo Direto.\n");
            acumulador = registradorParaInteiro(BR.AC, false, -1);
            if(!isNegativeChar(BR.AC[0])){
                set_flag_lir(false);
                transferirRR(ex_er.reg1, BR.PC);
                inteiroParaRegistrador(Operando1, ex_er.dado, false, -1);
                ex_er.classe = EscritaRegistrador;

            }
            else{
                ex_er.classe = EscritaVazia;
            }

            break;
        case JUMPPEsq:
            printf("Operação de Salto Positivo Indireto.\n");
            if(!isNegativeChar(BR.AC[0])){
                ex_er.classe = EscritaRegistrador;
                transferirRR(ex_er.reg1, BR.PC);
                inteiroParaRegistrador(Operando1, ex_er.dado, false, -1);

            }
            else{
                ex_er.classe = EscritaVazia;
            }
            break;
        case EXIT:
            exit(1);
            break;
        default:
            printf("Operação não reconhecida.\n");
    };

    
};

void busca(){
    //primeiro, verifica se na busca está disponível pra usar, se tiver, vai realizar a busca.
    // ele verifica na decodificação anterior se ele precisa mesmo realizar a busca, ou se vai apenas puxar de IBR na próxima decodificação.    
    if(statusB == Vazio){ // ta liberado para fazer la.
        //fazer mais uma verificação, se precisa buscar ou n.
        transferirRR(BR.MAR, BR.PC);
        //próxima etapa, buscar na memória. usar UC e barramento.
        Endereco mar;
        mar[1] = BR.MAR[4];
        mar[0] = BR.MAR[3];
        printf("%i - mar1 ", mar[1]);
        printf("%i - mar0 ", mar[0]);
        setBarramentoEndereco(mar); 
        //por comando da UC, vai ter que dar getBarramentoEndereco, e aí realizar a busca.
        buscarMemoria();

        //buscar

        for(int i = 0; i<5; i++){
            b_d.linha[i] = BR.MBR[i];
            printf("LINHA %i = %i\n", i, b_d.linha[i]);
        }

        //colocar dados obtidos no registrador entre.
        //status 1 = finalizado.
        statusB = 1; //uma função passará dps pelo pipeline, e jogará cada um pro próximo
    }
    
    

}

void decodificacao(bool newInstruction){ //posicao = posicao da primeira instrucao
    unsigned char temp;
    //posicao n precisa, vai estar em MBR ja.
    if(statusD == Pronto){
        bool opcode_exit = false;
        int opcode = 0;
        if(newInstruction){
            if(get_flag_lir()){
                
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
                    printf("%i - IBR 4\n", BR.IBR[4]);
                    BR.IBR[2] &= 15;

                    printf("\n%i - Pedaco 1 da Instrucao 2", BR.IBR[2]);
                    printf("\n%i - Pedaco 2 da Instrucao 2", BR.IBR[3]);
                    printf("oi");
                    printf("%i - Pedaco 3 da Instrucao 2", BR.IBR[4]);
                    printf("tchau");

                    //jogar informações no entre.

                    d_bo.novoIBR[2] = BR.IBR[2];
                    d_bo.novoIBR[3] = BR.IBR[3];
                    d_bo.novoIBR[4] = BR.IBR[4];
                }

                //jogar informações no D_BO.
                d_bo.opc_linha = BR.IR[4];
                d_bo.end[0] = BR.MAR[3];
                d_bo.end[1] = BR.MAR[4]; 

                newInstruction = false;
            }else{
                //pegar só a instrução da direita
                set_flag_lir(true);
                BR.IR[4] = BR.MBR[2];
                BR.IR[4] <<= 4;
                temp = BR.MBR[3];
                temp >>= 4;
                BR.IR[4] |= temp;

                BR.MAR[3] = BR.MBR[3];
                BR.MAR[3] &= 0b00001111;
                BR.MAR[4] = BR.MBR[4];
                d_bo.opc_linha = BR.IR[4];
                d_bo.end[0] = BR.MAR[3];
                d_bo.end[1] = BR.MAR[4]; 

                for(int i = 0; i<5;i++){
                    d_bo.novoIBR[i] = 0;
                }

                unsigned long long int pc = registradorParaInteiro(BR.PC, false, -1);
                pc++;
                inteiroParaRegistrador(pc, BR.PC, false, -1);

                
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
            d_bo.opc_linha = BR.IR[4];

            //colocar o endereço da instrução 2 em MAR. 
            BR.MAR[3] = BR.IBR[3]; //receba  =°3°=
            BR.MAR[3] &= 15;
            BR.MAR[4] = BR.IBR[4];
            
            d_bo.end[0] = BR.MAR[3];
            d_bo.end[1] = BR.MAR[4]; 

            printf("\n%i - Endereço segunda instrucao parte 1", BR.MAR[3]);
            printf("\n%i - Endereço segunda instrucao parte 2\n", BR.MAR[4]);
            
            printaEnderecoMar();    

            unsigned long long int pc2 = registradorParaInteiro(BR.PC, false, -1);
            pc2++;
            inteiroParaRegistrador(pc2, BR.PC, false, -1);
            newInstruction = true;
        }
        statusD = 1;
    }

    set_flag_b(true);
    verificaAcao();
}

void buscaOperandos(){
    //em Stor e StorM(addres modify), LSH, RSH, a busca será no AC.  *LOAD MQ busca no MQ.
    //na maioria a busca é lá na memória
    //pra alguns não há busca, como EXIT,, (Talvez os Jump também, né?)
    //

    //Endereco address;
    if(statusBO == Pronto){

        unsigned long long int enderecoo = 0;
        unsigned long long int valor = 0;
        Endereco buscar;
        buscar[0] = d_bo.end[0];
        buscar[1] = d_bo.end[1];

        enderecoo |= d_bo.end[0];
        enderecoo <<= 8;
        enderecoo |= d_bo.end[1];
        opc opc_instrucao = d_bo.opc_linha;

        

        //address[0]= d_bo.end[0];
        //address[1]= d_bo.end[1];
        //puxando da struct q fica entre.


        if(enderecoo == 0){ //acrescentar os jumps provavelmente tb.
            //n precisa fazer busca de operandos.
            if(opc_instrucao != OPC_EXIT){
                // LSH, RSH, LOAD MQ
                if(opc_instrucao == OPC_LOADMQ){
                    valor = registradorParaInteiro(BR.MQ, false, -1);
                    for(int i = 0; i<5; i++){ //ver se chegou em MBR.
                        bo_ex.dado[i] = BR.MBR[i];
                        printf("Dado %i = %i\n", i, bo_ex.dado[i]);
                    }

                }
                else{ //LSH, RSH
                    valor = registradorParaInteiro(BR.AC, false, -1);
                    for(int i = 0; i<5; i++){ //ver se chegou em MBR.
                        bo_ex.dado[i] = BR.AC[i];
                        printf("Dado %i = %i\n", i, bo_ex.dado[i]);
                    }
                }
            }
            else{
                valor = -1; //detectar EXIT.
            }
        }else if(opc_instrucao == OPC_STOR || opc_instrucao == OPC_STOREsq || opc_instrucao == OPC_STORDir){
            valor = registradorParaInteiro(BR.AC, false, -1);
            for(int i = 0; i<5; i++){ //ver se chegou em MBR.
                bo_ex.dado[i] = BR.AC[i];
                printf("Dado %i = %i\n", i, bo_ex.dado[i]);
            }
        }else if(opc_instrucao == OPC_JUMPEsq || opc_instrucao == OPC_JUMPPEsq || opc_instrucao == OPC_JUMPDir || opc_instrucao == OPC_JUMPPDir){
            //n tem B.O
            bo_ex.dado[4] = buscar[1];
            bo_ex.dado[3] = buscar[0];
            bo_ex.dado[2] = 0;
            bo_ex.dado[1] = 0;
            bo_ex.dado[0] = 0;
        }
        else{ //buscar na memória.

            setBarramentoEndereco(buscar);

            for(int i = 0; i<5; i++){ //ver se chegou em MBR.
                bo_ex.dado[i] = BR.MBR[i];
                printf("Dado %i = %i\n", i, bo_ex.dado[i]);
            }


        }
        bo_ex.opc_linha = opc_instrucao;
        bo_ex.endereco[0] = buscar[0];
        bo_ex.endereco[1] = buscar[1];


    
    }

    set_flag_d(true);
    verificaAcao();
}

void execucao(){
    if(statusEX == Pronto){

        unsigned long long int operando = 0;
        
        operando = registradorParaInteiro(bo_ex.dado, false, -1);
        int operation = (int)bo_ex.opc_linha;

        executaULA(operation, operando);

        ex_er.opc_linha = bo_ex.opc_linha;
        ex_er.endereco[0] = bo_ex.endereco[0];
        ex_er.endereco[1] = bo_ex.endereco[1];
    }


    set_flag_bo(true);
    verificaAcao();
}

void escritaResultados(){
    opc opc_instrucao = ex_er.opc_linha;
    if(statusER == Pronto){

        if (ex_er.classe == EscritaRegistrador)
        {
            if(opc_instrucao == OPC_JUMPEsq || opc_instrucao == OPC_JUMPPEsq || opc_instrucao == OPC_JUMPDir || opc_instrucao == OPC_JUMPPDir){
                //apagar pipe,
                newInstruction = true;

            }
            //escrever no registrador
            //ULA -> AC
            transferirRR(ex_er.reg1, ex_er.dado);
        }
        else if(ex_er.classe == EscritaMemoria)
        {
            enum escritaMemoria tipo;
            //escrever na memoria
            //
            if(ex_er.opc_linha == OPC_STOR){
                //ULA -> MBR
                //*Dado foi puxado do AC anteriormente.
                transferirRR(ex_er.dado, BR.MBR);
                Dado valor;
                for (int i = 0; i<5; i++){
                    valor[i] = BR.MBR[i];
                }
                tipo = Tudo;
                
                ex_er.endereco[0] = BR.MAR[3];
                ex_er.endereco[1] = BR.MAR[4];
                //verificação de apenas pegar os últimos dois bytes, 
                BR.MAR[3] &= 0b00001111;
                setBarramentoDados(valor);
                setBarramentoEndereco(ex_endereco);
                escreverMemoria(tipo);
            }
            else if(ex_er.opc_linha == OPC_STOREsq){
                transferirRR(ex_er.dado, BR.MBR);
                Dado valor;
                for (int i = 0; i<5; i++){
                    valor[i] = BR.MBR[i];
                }
                tipo = Esquerda;
                ex_er.endereco[0] = BR.MAR[3];
                ex_er.endereco[1] = BR.MAR[4];
                //verificação de apenas pegar os últimos dois bytes, 
                BR.MAR[3] &= 0b00001111;
                setBarramentoDados(valor);
                setBarramentoEndereco(ex_endereco);
                escreverMemoria(tipo);
                
            }
            else if(ex_er.opc_linha == OPC_STORDir){
                transferirRR(ex_er.dado, BR.MBR);
                Dado valor;
                for (int i = 0; i<5; i++){
                    valor[i] = BR.MBR[i];
                }
                tipo = Direita;
                ex_er.endereco[0] = BR.MAR[3];
                ex_er.endereco[1] = BR.MAR[4];
                //verificação de apenas pegar os últimos dois bytes, 
                BR.MAR[3] &= 0b00001111;
                setBarramentoDados(valor);
                setBarramentoEndereco(ex_endereco);
                escreverMemoria(tipo);
            }


        }
        else if(ex_er.classe == EscritaDoisRegistradores){
            //escrever nos dois registradores.
        }
        else if(ex_er.classe == EscritaVazia){ //jump condiiconal que n vai pular

        }
        else{
            printf("Classe inexistente, abortando.");
            exit(1);
        }
    }
    
    set_flag_ex(true);
    verificaAcao();
}

void pipeline(){
    set_flag_er(true);
    verificaAcao();

}


