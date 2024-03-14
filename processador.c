#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "headers/types.h"
#include "headers/utils.h"
#include "headers/fila.h"
#include "headers/barramento.h"
#include "headers/memoria.h"
#include "headers/flags.h"
#include "headers/uc.h"
#include "headers/processador.h"

int statusB = Vazio;  
int statusD = Vazio; 
int statusBO = Vazio;
int statusEX = Vazio;
int clkTemp;
int statusER = Vazio;
bool newInstruction = true;
bool isExit = false;
Fila* dependencia_address;
Fila* dependencia_stor;

void inicializarProcessador(){
    dependencia_address = criarFila();
    dependencia_stor = criarFila();
}
void executaULA(enum Operacoes Operacao, unsigned long long int Operando1){
    bool negativeOP1;
    bool negativeOP2;
    unsigned long long int acumulador;
    long long int negOP1 = 0;
    long long int negOP2 = 0;
    if(!get_flag_clk()) {
        clkTemp = cpu_clk;
        set_flag_clk(true);
    }

    int Peso = fornecerPeso(Operacao);
    if((cpu_clk - clkTemp) >= (Peso-1)){
        clkTemp = 0;
        set_flag_clk(false);
        switch (Operacao){
            case ADD:
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                if(isNegativeULL(acumulador)){
                    negativeOP1 = true;
                    acumulador &= (QUADRAGESIMO_BIT-1);
                    negOP1 = acumulador;
                    negOP1 = -negOP1;
                }else{
                    negOP1 = acumulador;
                }

                if(isNegativeULL(Operando1)){
                    negativeOP2 = true;
                    Operando1 &= (QUADRAGESIMO_BIT-1);
                    negOP2 = Operando1;
                    negOP2 = -negOP2;
                }
                else{
                    negOP2 = Operando1;
                }
                
                negOP1 += negOP2;
                if(negOP1 < 0){
                    negOP1 = -negOP1;
                    acumulador = negOP1;
                    acumulador |= QUADRAGESIMO_BIT;
                }
                else{
                    acumulador = negOP1;
                }
                if(statusER == Finalizado || statusER == Vazio)  transferirRR(ex_er.reg1, BR.AC);
                if(statusER == Finalizado || statusER == Vazio) inteiroParaRegistrador(acumulador, ex_er.dado);
                if(statusER == Finalizado || statusER == Vazio) ex_er.classe = EscritaRegistrador;
                break;
            case ADDModulo:
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                if(isNegativeULL(acumulador)){
                    negativeOP1 = true;
                    acumulador &= (QUADRAGESIMO_BIT-1);
                    negOP1 = acumulador;
                    negOP1 = -negOP1;
                }else{
                    negOP1 = acumulador;
                }
                negOP2 = Operando1;
                negOP1 += modulo(negOP2);
                if(negOP1 < 0){
                    negOP1 = -negOP1;
                    acumulador = negOP1;
                    acumulador |= QUADRAGESIMO_BIT;
                }
                else{
                    acumulador = negOP1;
                }
                if(statusER == Finalizado || statusER == Vazio)  transferirRR(ex_er.reg1, BR.AC);
                if(statusER == Finalizado || statusER == Vazio) inteiroParaRegistrador(acumulador, ex_er.dado);
                if(statusER == Finalizado || statusER == Vazio) ex_er.classe = EscritaRegistrador;
                break;
            case SUB:
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                
                if(isNegativeULL(acumulador)){
                    negativeOP1 = true;
                    acumulador &= (QUADRAGESIMO_BIT-1);
                    negOP1 = acumulador;
                    negOP1 = -negOP1;
                }else{
                    negOP1 = acumulador;
                }

                if(isNegativeULL(Operando1)){
                    negativeOP2 = true;
                    Operando1 &= (QUADRAGESIMO_BIT-1);
                    negOP2 = Operando1;
                    negOP2 = -negOP2;
                }
                else{
                    negOP2 = Operando1;
                }
                negOP1 -= negOP2;
                if(negOP1 < 0){
                    negOP1 = -negOP1;
                    acumulador = negOP1;
                    acumulador |= QUADRAGESIMO_BIT;
                }
                else{
                    acumulador = negOP1;
                }
                if(statusER == Finalizado || statusER == Vazio)  transferirRR(ex_er.reg1, BR.AC);
                if(statusER == Finalizado || statusER == Vazio) inteiroParaRegistrador(acumulador, ex_er.dado);
                if(statusER == Finalizado || statusER == Vazio) ex_er.classe = EscritaRegistrador;
                break;
            case SUBModulo:
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                if(isNegativeULL(acumulador)){
                    negativeOP1 = true;
                    acumulador &= (QUADRAGESIMO_BIT-1);
                    negOP1 = acumulador;
                    negOP1 = -negOP1;
                }else{
                    negOP1 = acumulador;
                }
                negOP2 = Operando1;
                negOP1 -= modulo(negOP2);
                if(negOP1 < 0){
                    negOP1 = -negOP1;
                    acumulador = negOP1;
                    acumulador |= QUADRAGESIMO_BIT;
                }
                else{
                    acumulador = negOP1;
                }
                if(statusER == Finalizado || statusER == Vazio)  transferirRR(ex_er.reg1, BR.AC);
                if(statusER == Finalizado || statusER == Vazio) inteiroParaRegistrador(acumulador, ex_er.dado);
                if(statusER == Finalizado || statusER == Vazio) ex_er.classe = EscritaRegistrador;
                break;
            case MUL:
                bool acIsNegative = false;
                bool mqIsNegative = false;
                unsigned long long int Mq = registradorParaInteiro(BR.MQ, false, -1);
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                if(isNegativeULL(Mq)){
                    negativeOP1 = true;
                    Mq &= (QUADRAGESIMO_BIT-1);
                    negOP1 = Mq;
                    negOP1 = -negOP1;
                }else{
                    negOP1 = Mq;
                }
                if(isNegativeULL(Operando1)){
                    negativeOP2 = true;
                    Operando1 &= (QUADRAGESIMO_BIT-1);
                    negOP2 = Operando1;
                    negOP2 = -negOP2;
                }
                else{
                    negOP2 = Operando1;
                }
                negOP1 = negOP1 * negOP2;
                if(negOP1 < 0){
                    if(-negOP1 > LIMITE_39_BITS){
                        acIsNegative = true;
                    }
                    else{
                        mqIsNegative = true;
                    }
                    negOP1 = -negOP1;
                    acumulador = negOP1;
                }
                else{
                    acumulador = negOP1;
                }
                if(acIsNegative || mqIsNegative){
                    if(acIsNegative){
                        unsigned long long int temporario = acumulador >> 40;
                        temporario |= QUADRAGESIMO_BIT;
                        inteiroParaRegistrador(temporario,ex_er.reg1);
                        acumulador &= FULL_BYTE;
                        inteiroParaRegistrador(acumulador,ex_er.reg2);
                    }
                    else{
                        inteiroParaRegistrador(0, ex_er.reg1);
                        acumulador |= QUADRAGESIMO_BIT;
                        inteiroParaRegistrador(acumulador,ex_er.reg2);
                    }
                }else{
                    inteiroParaRegistrador(0, ex_er.reg1);
                    inteiroParaRegistrador(acumulador,ex_er.reg2);
                }
                ex_er.classe = EscritaDoisRegistradores;
                break;
            case DIV:
                long long int resultado = 0;
                long long int resto = 0;
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                if(isNegativeULL(acumulador)){
                    negativeOP1 = true;
                    acumulador &= (QUADRAGESIMO_BIT-1);
                    negOP1 = acumulador;
                    negOP1 = -negOP1;
                }else{
                    negOP1 = acumulador;
                }

                if(isNegativeULL(Operando1)){
                    negativeOP2 = true;
                    Operando1 &= (QUADRAGESIMO_BIT-1);
                    negOP2 = Operando1;
                    negOP2 = -negOP2;
                }
                else{
                    negOP2 = Operando1;
                }
                resultado = (negOP1 / negOP2);
                resto = (negOP1 % negOP2);
                if(resultado < 0){
                    resultado = -resultado;
                    resultado |= QUADRAGESIMO_BIT;
                }
                if(resto < 0){
                    resto = -resto;
                    resto |= QUADRAGESIMO_BIT;
                }
                long long int mq = registradorParaInteiro(BR.MQ, false, -1);
                inteiroParaRegistrador(resultado, ex_er.reg2);
                inteiroParaRegistrador(resto, ex_er.reg1);
                ex_er.classe = EscritaDoisRegistradores;
                break;
            case LSH:
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                acumulador <<= 1;
                transferirRR(ex_er.reg1, BR.AC);
                inteiroParaRegistrador(acumulador, ex_er.dado);
                ex_er.classe = EscritaRegistrador;
                break;
            case RSH:
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                acumulador >>= 1;
                transferirRR(ex_er.reg1, BR.AC);
                inteiroParaRegistrador(acumulador, ex_er.dado);
                ex_er.classe = EscritaRegistrador;
                break;
            case STOR:
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                inteiroParaRegistrador(acumulador, ex_er.dado); 
                ex_er.classe = EscritaMemoria;
                break;
            case STOREsq:
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                inteiroParaRegistrador(acumulador, ex_er.dado); 
                ex_er.classe = EscritaMemoria;
                break;
            case STORDir: 
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                inteiroParaRegistrador(acumulador, ex_er.dado);
                ex_er.classe = EscritaMemoria;
                break;
            case LOADMQ:
                transferirRR(ex_er.reg1, BR.AC);
                Operando1 = registradorParaInteiro(BR.MQ, false, -1);
                inteiroParaRegistrador(Operando1, ex_er.dado);
                ex_er.classe = EscritaRegistrador;
                break;
            case LOADMQM:
                transferirRR(ex_er.reg1, BR.MQ);
                inteiroParaRegistrador(Operando1, ex_er.dado);
                ex_er.classe = EscritaRegistrador;
                break;
            case LOAD:
                transferirRR(ex_er.reg1, BR.AC);
                inteiroParaRegistrador(Operando1, ex_er.dado);
                ex_er.classe = EscritaRegistrador;
                break;
            case LOADMenos:
                Operando1 ^= QUADRAGESIMO_BIT;
                transferirRR(ex_er.reg1, BR.AC);
                inteiroParaRegistrador(Operando1, ex_er.dado);
                ex_er.classe = EscritaRegistrador;
                break;
            case LOADModulo:
                transferirRR(ex_er.reg1, BR.AC);
                inteiroParaRegistrador(modulo(Operando1), ex_er.dado);
                ex_er.classe = EscritaRegistrador;
                break;
            case LOADMenosModulo:
                Operando1 = modulo(Operando1);
                Operando1 ^= QUADRAGESIMO_BIT;
                transferirRR(ex_er.reg1, BR.AC);
                inteiroParaRegistrador(Operando1, ex_er.dado);
                ex_er.classe = EscritaRegistrador;
                break;
            case JUMPDir:
                ex_er.classe = EscritaRegistrador;
                transferirRR(ex_er.reg1, BR.PC);
                inteiroParaRegistrador(Operando1, ex_er.dado);
                set_flag_lir(false);
                flushPipeline();
                set_flag_flush(true);
                break;
            case JUMPEsq:
                transferirRR(ex_er.reg1, BR.PC);
                inteiroParaRegistrador(Operando1, ex_er.dado);
                ex_er.classe = EscritaRegistrador;
                flushPipeline();
                set_flag_flush(true);
                break;
            case JUMPPDir:
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                if(!isNegativeChar(BR.AC[0])){
                    set_flag_lir(false);
                    transferirRR(ex_er.reg1, BR.PC);
                    inteiroParaRegistrador(Operando1, ex_er.dado);
                    ex_er.classe = EscritaRegistrador;
                    flushPipeline();
                    set_flag_flush(true);
                }
                else{
                    ex_er.classe = EscritaVazia;
                }
                break;
            case JUMPPEsq:
                if(!isNegativeChar(BR.AC[0])){
                    ex_er.classe = EscritaRegistrador;
                    transferirRR(ex_er.reg1, BR.PC);
                    inteiroParaRegistrador(Operando1, ex_er.dado);
                    flushPipeline();
                    set_flag_flush(true);
                }
                else{
                    ex_er.classe = EscritaVazia;
                }
                break;
            case EXIT:
                isExit = true;
                break;
            default:
                printf("Operação não reconhecida.\n");
                exit(1);
        };
        ex_er.opc_linha = bo_ex.opc_linha;
        ex_er.endereco[1] = bo_ex.endereco[1];
        ex_er.endereco[0] = bo_ex.endereco[0];
        statusEX = Finalizado;
    }
};

void busca(){
    bool temDependencia = false;
    if (get_flag_dependencia_address()){
        Endereco pc;
        pc[1] = BR.PC[4];
        pc[0] = BR.PC[3] & 0b00001111;
        temDependencia = elementoNaFila(dependencia_address, enderecoParaShort(pc));
        
    } 

    if(statusB != Travado){
        if (!get_flag_flush()){
            if(statusB == Vazio && newInstruction && !temDependencia){ 
                transferirRR(BR.MAR, BR.PC);
                Endereco mar;
                mar[1] = BR.MAR[4];
                mar[0] = BR.MAR[3]; 
                setBarramentoEndereco(mar); 
                buscarMemoria();
                if((statusD == Finalizado || statusD == Vazio) && statusB != Travado){
                    for(int i = 0; i<5; i++){
                        b_d.linha[i] = BR.MBR[i];
                    }
                    statusB = Finalizado;
                    b_d.pc[0] = mar[0];
                    b_d.pc[1] = mar[1];

                }
            }else if(!newInstruction && !temDependencia){ 
                if((statusD == Finalizado  ||statusD == Vazio) && (statusB != Travado)){
                    statusB = Finalizado;
                }
            }
        }else{
            set_flag_flush(false);
        }
    }
    avancarPipeline();
}

void decodificacao(){ 
    unsigned char temp; 
    if(statusD == Pronto){
        bool opcode_exit = false;
        int opcode = 0;
        if(newInstruction){
            if(get_flag_lir()){
                BR.IR[4] = b_d.linha[0];
                opcode = BR.IR[4];
                if(opcode == OPC_EXIT){
                    opcode_exit = true;
                }
                BR.MAR[3] = b_d.linha[1];
                BR.MAR[4] = b_d.linha[2];
                BR.MAR[4] >>= 4;
                temp = BR.MAR[3] << 4;
                BR.MAR[3] >>= 4;
                BR.MAR[4] |= temp;
                printaEnderecoMar();
                if(!opcode_exit){ 
                    BR.IBR[2] = b_d.linha[2];
                    BR.IBR[3] = b_d.linha[3];
                    BR.IBR[4] = b_d.linha[4];
                    BR.IBR[2] &= 15;
                    if(statusBO == Finalizado || statusBO == Vazio){
                        d_bo.novoIBR[2] = BR.IBR[2];
                        d_bo.novoIBR[3] = BR.IBR[3];
                        d_bo.novoIBR[4] = BR.IBR[4];
                    }
                }
                if(statusBO == Finalizado || statusBO == Vazio){
                    d_bo.end[0] = BR.MAR[3];
                    d_bo.end[1] = BR.MAR[4];
                    d_bo.opc_linha = BR.IR[4];

                    if(d_bo.opc_linha == OPC_STOR){
                        set_flag_dependencia_stor(true);
                        enfileirar(dependencia_stor, enderecoParaShort(d_bo.end));
                    }else if(d_bo.opc_linha == OPC_STORDir || d_bo.opc_linha == OPC_STOREsq){
                        set_flag_dependencia_address(true);
                        enfileirar(dependencia_address, enderecoParaShort(d_bo.end));
                        if(d_bo.opc_linha == OPC_STORDir){
                            Endereco prox;
                            prox[0] = b_d.pc[0];
                            prox[1] = b_d.pc[1];
                            if(enderecoParaShort(d_bo.end) == enderecoParaShort(prox)){
                                set_flag_lir(false);
                                statusB = Travado;
                                statusD = Finalizado;
                            }
                        }
                    }
                    newInstruction = false;
                    if(statusB == Travado){
                        newInstruction = true;
                    }
                }
            }else{
                set_flag_lir(true);
                BR.IR[4] = b_d.linha[2];
                BR.IR[4] <<= 4;
                temp = b_d.linha[3];
                temp >>= 4;
                BR.IR[4] |= temp;
                BR.MAR[3] = b_d.linha[3];
                BR.MAR[3] &= 0b00001111;
                BR.MAR[4] = b_d.linha[4];

                if(statusBO == Finalizado || statusBO == Vazio){
                    d_bo.opc_linha = BR.IR[4];
                    d_bo.end[0] = BR.MAR[3];
                    d_bo.end[1] = BR.MAR[4]; 

                    for(int i = 0; i<5;i++){
                        d_bo.novoIBR[i] = 0;
                    }

                    if(d_bo.opc_linha == OPC_STOR){
                        set_flag_dependencia_stor(true);
                        enfileirar(dependencia_stor, enderecoParaShort(d_bo.end));
                        //mostrarFila(dependencia_stor);
                    }else if(d_bo.opc_linha == OPC_STORDir || d_bo.opc_linha == OPC_STOREsq){
                        set_flag_dependencia_address(true);
                        enfileirar(dependencia_address, enderecoParaShort(d_bo.end));
                        //mostrarFila(dependencia_stor);
                    }

                    newInstruction = true;
                    unsigned long long int pc = registradorParaInteiro(BR.PC, false, -1);
                    pc++;
                    inteiroParaRegistrador(pc, BR.PC);
                }
            }
        }else{ 
            unsigned char temp2;
            BR.IR[4] = d_bo.novoIBR[2];
            BR.IR[4] <<= 4;
            temp2 = d_bo.novoIBR[3] & 240;
            temp2 >>= 4;
            BR.IR[4] |= temp2;
            BR.MAR[3] = d_bo.novoIBR[3];
            BR.MAR[3] &= 15;
            BR.MAR[4] = d_bo.novoIBR[4];
            
            if(statusBO == Finalizado || statusBO == Vazio){
                d_bo.opc_linha = BR.IR[4];
                d_bo.end[0] = BR.MAR[3];
                d_bo.end[1] = BR.MAR[4];
                if(d_bo.opc_linha == OPC_STOR){
                    set_flag_dependencia_stor(true);
                    enfileirar(dependencia_stor, enderecoParaShort(d_bo.end));
                }else if(d_bo.opc_linha == OPC_STORDir || d_bo.opc_linha == OPC_STOREsq){
                    set_flag_dependencia_address(true);
                    enfileirar(dependencia_address, enderecoParaShort(d_bo.end));
                }
                unsigned long long int pc2 = registradorParaInteiro(BR.PC, false, -1);
                pc2++;
                inteiroParaRegistrador(pc2, BR.PC);
                newInstruction = true;
            }
            printaEnderecoMar();    
        }

        if((statusBO == Finalizado || statusBO == Vazio) && (statusB != Travado)){
            statusD = Finalizado;
        }
    }
    set_flag_b(true);
    verificarAcao();
}

void buscarOperandos(){
    bool temDependencia = false;
    if (get_flag_dependencia_stor()){
            if(d_bo.opc_linha != OPC_STOR){
                temDependencia = elementoNaFila(dependencia_stor, enderecoParaShort(d_bo.end));
            }
    }
    
    if(statusBO == Pronto && !temDependencia){
        unsigned long long int enderecoo = 0;
        Endereco buscar;
        buscar[0] = d_bo.end[0];
        buscar[1] = d_bo.end[1];

        enderecoo |= d_bo.end[0];
        enderecoo <<= 8;
        enderecoo |= d_bo.end[1];
        opc opc_instrucao = d_bo.opc_linha;
        if(opc_instrucao == OPC_JUMPEsq || opc_instrucao == OPC_JUMPPEsq || opc_instrucao == OPC_JUMPDir || opc_instrucao == OPC_JUMPPDir){
            if(statusEX == Finalizado || statusEX == Vazio){
                bo_ex.dado[4] = buscar[1];
                bo_ex.dado[3] = buscar[0];
                bo_ex.dado[2] = 0;
                bo_ex.dado[1] = 0;
                bo_ex.dado[0] = 0;
            }
        }
        else{ 
            setBarramentoEndereco(buscar);
            buscarMemoria();
            if(statusEX == Finalizado || statusEX == Vazio){
                for(int i = 0; i<5; i++){ 
                    bo_ex.dado[i] = BR.MBR[i];
                }
            }
        }
        if(statusEX == Finalizado || statusEX == Vazio){
            bo_ex.opc_linha = d_bo.opc_linha;
            bo_ex.endereco[0] = buscar[0];
            bo_ex.endereco[1] = buscar[1];
            statusBO = Finalizado;
        }
    }
    set_flag_d(true);
    verificarAcao();
}

void execucao(){
    if(statusEX == Pronto){
        unsigned long long int operando = 0;
        operando = registradorParaInteiro(bo_ex.dado, false, -1);
        int operation = (int)bo_ex.opc_linha;
        if(statusER == Finalizado || statusER == Vazio){            
            executaULA(operation, operando);
        }
    }
    set_flag_bo(true);
    verificarAcao();
}

void escritaResultados(){
    opc opc_instrucao = ex_er.opc_linha;
    if(statusER == Pronto){
        if (ex_er.classe == EscritaRegistrador){
            if(opc_instrucao == OPC_JUMPEsq || opc_instrucao == OPC_JUMPPEsq || opc_instrucao == OPC_JUMPDir || opc_instrucao == OPC_JUMPPDir){
                transferirRR(BR.PC, ex_er.dado);    
                newInstruction = true;
            }
            if(opc_instrucao == OPC_LOAD || opc_instrucao == OPC_LOADMQ || opc_instrucao == OPC_LOADMenos ||
            opc_instrucao == OPC_LOADModulo || opc_instrucao == OPC_LOADMenosModulo || opc_instrucao == OPC_ADD ||
            opc_instrucao == OPC_ADDM || opc_instrucao == OPC_SUB ||opc_instrucao == OPC_SUBM ||
            opc_instrucao == OPC_LSH ||opc_instrucao == OPC_RSH){
                transferirRR(BR.AC, ex_er.dado);    
            }else if(opc_instrucao == OPC_LOADMQM){
                transferirRR(BR.MQ, ex_er.dado);
            }
        }
        else if(ex_er.classe == EscritaMemoria)
        {
            enum escritaMemoria tipo;
            if(ex_er.opc_linha == OPC_STOR){
                transferirRR(BR.MBR, ex_er.dado);
                Dado valor;
                for (int i = 0; i<5; i++){
                    valor[i] = BR.MBR[i];
                }
                tipo = Tudo;
                BR.MAR[3] = ex_er.endereco[0];
                BR.MAR[4] = ex_er.endereco[1];
                BR.MAR[3] &= 0b00001111;
                Endereco temp;
                temp[0] = BR.MAR[3];
                temp[1] = BR.MAR[4];
                setBarramentoDados(valor);
                setBarramentoEndereco(temp);
                escreverMemoria(tipo);
                
                if(elementoNaFila(dependencia_stor, enderecoParaShort(temp))){
                    //mostrarFila(dependencia_stor);
                    desenfileirar(dependencia_stor);
                    //mostrarFila(dependencia_stor);
                }
                if(estaVazia(dependencia_stor)){
                    set_flag_dependencia_stor(false);
                }
            }
            else if(ex_er.opc_linha == OPC_STOREsq){
                transferirRR(BR.MBR, ex_er.dado);
                Dado valor;
                for (int i = 0; i<5; i++){
                    valor[i] = BR.MBR[i];
                }
                tipo = Esquerda;
                BR.MAR[3] = ex_er.endereco[0];
                BR.MAR[4] = ex_er.endereco[1];

                ex_er.endereco[0] = BR.MAR[3];
                ex_er.endereco[1] = BR.MAR[4];
                BR.MAR[3] &= 0b00001111;
                setBarramentoDados(valor);
                setBarramentoEndereco(ex_er.endereco);
                escreverMemoria(tipo);

                if(elementoNaFila(dependencia_address, enderecoParaShort(ex_er.endereco))){
                    desenfileirar(dependencia_address);
                }
                if(estaVazia(dependencia_address)){
                    set_flag_dependencia_address(false);
                }
            }
            else if(ex_er.opc_linha == OPC_STORDir){
                transferirRR(BR.MBR, ex_er.dado);
                Dado valor;
                for (int i = 0; i<5; i++){
                    valor[i] = BR.MBR[i];
                }
                tipo = Direita;
                BR.MAR[3] = ex_er.endereco[0];
                BR.MAR[4] = ex_er.endereco[1];

                ex_er.endereco[0] = BR.MAR[3];
                ex_er.endereco[1] = BR.MAR[4];
                BR.MAR[3] &= 0b00001111;
                setBarramentoDados(valor);
                setBarramentoEndereco(ex_er.endereco);
                escreverMemoria(tipo);
                if(elementoNaFila(dependencia_address, enderecoParaShort(ex_er.endereco))){
                    desenfileirar(dependencia_address);
                }
                if(estaVazia(dependencia_address)){
                    set_flag_dependencia_address(false);
                }

                if(statusB == Travado){
                    flushPipeline();
                }
                
            }
        }
        else if(ex_er.classe == EscritaDoisRegistradores){
            transferirRR(BR.AC, ex_er.reg1);
            transferirRR(BR.MQ, ex_er.reg2);
        }
        else if(ex_er.classe == EscritaVazia){ 
        }
        else{
            printf("Classe inexistente, abortando.");
            exit(1);
        }
        statusER = Finalizado;
    }
    set_flag_ex(true);
    verificarAcao();
}

void pipeline(){
    set_flag_er(true);
    verificarAcao();
}

void avancarPipeline(){
    if(statusER == Finalizado){
        statusER = Vazio;
    }
    if(statusEX == Finalizado && statusER == Vazio){
        statusER = Pronto;
        statusEX = Vazio;
    }
    if(statusBO == Finalizado && statusEX == Vazio){
        statusEX = Pronto;
        statusBO = Vazio;
    }
    if(statusD == Finalizado && statusBO == Vazio){
        statusBO = Pronto;
        statusD = Vazio;
    }
    if(statusB == Finalizado && statusD == Vazio){
        statusD = Pronto;
        statusB = Vazio;
    }
}

void clockTick(){
    cpu_clk++;
}