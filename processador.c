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

int statusB = Vazio; // tem q ter 3, vazio, finalizado, fazendo. 
int statusD = Vazio; //tecnicamente, o fazendo estaria apenas no
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
    unsigned long long int memoria;
    long long int negOP1 = 0;
    long long int negOP2 = 0;
    if(!get_flag_clk()) {
        clkTemp = cpu_clk;
        set_flag_clk(true);
        printf("clkTemp virou o %i\n", clkTemp);
    }

    int Peso = fornecerPeso(Operacao);
    printf("Peso = %i, clkTemp = %i, cpu_clock = %i\n", Peso, clkTemp, cpu_clk);
    if((cpu_clk - clkTemp) >= (Peso-1)){
        clkTemp = 0;
        
        printf("Entramos para Executar! \ncpu_clock = %i e clkTemp = %i\n", cpu_clk, clkTemp);
        set_flag_clk(false);
        switch (Operacao){
            case ADD:
                printf("Entrando no add!\n");
                printf("%i - Peso ADD", Pesos[ADD]);
                //exit(1);

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

                //inteiroParaRegistrador(acumulador, BR.AC, false, -1);
                if(statusER == Finalizado || statusER == Vazio)  transferirRR(ex_er.reg1, BR.AC);
                if(statusER == Finalizado || statusER == Vazio) inteiroParaRegistrador(acumulador, ex_er.dado, false, -1);
                if(statusER == Finalizado || statusER == Vazio) ex_er.classe = EscritaRegistrador;
                break;
            case ADDModulo:
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                acumulador += modulo(Operando1);
                //inteiroParaRegistrador(acumulador, BR.AC, false, -1);
                if(statusER == Finalizado || statusER == Vazio) transferirRR(ex_er.reg1, BR.AC);
                if(statusER == Finalizado || statusER == Vazio) inteiroParaRegistrador(acumulador, ex_er.dado, false, -1);
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

                //inteiroParaRegistrador(acumulador, BR.AC, false, -1);
                if(statusER == Finalizado || statusER == Vazio)  transferirRR(ex_er.reg1, BR.AC);
                if(statusER == Finalizado || statusER == Vazio) inteiroParaRegistrador(acumulador, ex_er.dado, false, -1);
                if(statusER == Finalizado || statusER == Vazio) ex_er.classe = EscritaRegistrador;
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
                unsigned long long int Mq = registradorParaInteiro(BR.MQ, false, -1);
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                acumulador = Mq * Operando1;
                if(acumulador > LIMITE_39_BITS){
                    unsigned long long int temporario = acumulador >> 40;
                    inteiroParaRegistrador(temporario,ex_er.reg1, false, -1);
                    acumulador &= FULL_BYTE;
                    // Mq = acumulador - LIMITE_39_BITS;
                    // acumulador = LIMITE_39_BITS;
                }else{
                    inteiroParaRegistrador(0, ex_er.reg1, false, -1);
                }
                inteiroParaRegistrador(acumulador,ex_er.reg2, false, -1);
                //inteiroParaRegistrador(Mq, BR.MQ, false, -1);
                //inteiroParaRegistrador(acumulador, BR.AC, false, -1);
                ex_er.classe = EscritaDoisRegistradores;
                break;
            case DIV:
                long long int mq = registradorParaInteiro(BR.MQ, false, -1);
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                mq = (acumulador / Operando1);
                acumulador = (acumulador % Operando1);
                inteiroParaRegistrador(mq, ex_er.reg2, false, -1);
                inteiroParaRegistrador(acumulador, ex_er.reg1, false, -1);
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
                printf("Executando Stor!\n");
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                printf("Pegando o valor: %lld no Stor\n", acumulador);
                //transferirRM(BR.AC, m, Operando1);
                inteiroParaRegistrador(acumulador, ex_er.dado, false, -1); //valor que estava em AC.
                ex_er.classe = EscritaMemoria;

                break;
            case STOREsq:
                printf("Entrei para storesq");
                mostrarFila(dependencia_address);
                //exit(1);
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                // memoria = registradorParaInteiro(NULL, true, Operando1);
                // acumulador &= LONG_INT_ULTIMOS12_ALTOS_DIR;
                // memoria &= LONG_INT_ULTIMOS12_BAIXOS_DIR;
                // memoria |= acumulador;
                inteiroParaRegistrador(acumulador, ex_er.dado, false, -1); //valor que estava em AC
                ex_er.classe = EscritaMemoria;

                break;
            case STORDir: 
                printf("Entrei na Execução do STORDir\n");
                //exit(1);
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                //inteiroParaRegistrador(acumulador, ex_er.dado, false, -1);
                // memoria = registradorParaInteiro(NULL, true, Operando1);
                // acumulador &= LONG_INT_ULTIMOS12_ALTOS;
                // memoria &= LONG_INT_ULTIMOS12_BAIXOS;
                // memoria |= acumulador;
                inteiroParaRegistrador(acumulador, ex_er.dado, false, -1); //valor que estava em AC
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
                printf("Fazendo o load!\n");
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
                printf("OPERANDO1 no JUMPDIR - %i", Operando1);
                set_flag_lir(false);
                flushPipeline();
                set_flag_flush(true);
                break;
            case JUMPEsq:
                printf("Operação de Salto Indireto.\n");
                transferirRR(ex_er.reg1, BR.PC);
                inteiroParaRegistrador(Operando1, ex_er.dado, false, -1);
                ex_er.classe = EscritaRegistrador;
                flushPipeline();
                set_flag_flush(true);
                break;
            case JUMPPDir:
                printf("Operação de Salto Positivo Direto.\n");
                acumulador = registradorParaInteiro(BR.AC, false, -1);
                if(!isNegativeChar(BR.AC[0])){
                    set_flag_lir(false);
                    transferirRR(ex_er.reg1, BR.PC);
                    inteiroParaRegistrador(Operando1, ex_er.dado, false, -1);
                    ex_er.classe = EscritaRegistrador;
                    flushPipeline();
                    set_flag_flush(true);
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
                    flushPipeline();
                    set_flag_flush(true);
                }
                else{
                    ex_er.classe = EscritaVazia;
                }
                break;
            case EXIT:
                printf("Cheguei Final\n");
                //exit(1);
                isExit = true;
                break;
            default:
                printf("Operação não reconhecida.\n");
                printf("%i - Operação \n", Operacao);
                printf("%i - Opcode\n", bo_ex.opc_linha);
                exit(1);

        };
        ex_er.opc_linha = bo_ex.opc_linha;
        ex_er.endereco[1] = bo_ex.endereco[1];
        ex_er.endereco[0] = bo_ex.endereco[0];
        statusEX = Finalizado;
    }
};

void busca(){
    printf("\nEntramos na busca.\n");
    //primeiro, verifica se na busca está disponível pra usar, se tiver, vai realizar a busca.
    // ele verifica na decodificação anterior se ele precisa mesmo realizar a busca, ou se vai apenas puxar de IBR na próxima decodificação.  
    mostrarFila(dependencia_address);
    bool temDependencia = false;
    if (get_flag_dependencia_address()){
        Endereco pc;
        pc[1] = BR.PC[4];
        pc[0] = BR.PC[3] & 0b00001111;

        
        temDependencia = elementoNaFila(dependencia_address, enderecoParaShort(pc));
        printf("Veficando dependencia, PC é : %hd\n", enderecoParaShort(pc));
        
    } 

    // Endereco pc;
    // pc[1] = BR.PC[4];
    // pc[0] = BR.PC[3] & 0b00001111;   

    // temDependencia = elementoNaFila(dependencia_address, enderecoParaShort(pc));
    // printf("PC - 3 = %i\n", BR.PC[3]);
    // printf("PC - 4 = %i\n", BR.PC[4]);
    // printf("Veficando dependencia, PC é : %i\n", enderecoParaShort(pc));
    if(statusB != Travado){
        printf("nÃO TA TRAVADOO\n");

        if (!get_flag_flush()){
            //printf("nao flush");
            if(statusB == Vazio && newInstruction && !temDependencia){ // ta liberado para fazer la.
                //fazer mais uma verificação, se precisa buscar ou n.
                transferirRR(BR.MAR, BR.PC);
                //próxima etapa, buscar na memória. usar UC e barramento.
                Endereco mar;
                mar[1] = BR.MAR[4];
                mar[0] = BR.MAR[3]; // & 0b00001111;
                printf("Endereco onde buscaremos instrucao parte 1 - %i\n", mar[0]);
                printf("Endereco onde buscaremos instrucao parte 2 - %i\n", mar[1]);
                setBarramentoEndereco(mar); 
                //por comando da UC, vai ter que dar getBarramentoEndereco, e aí realizar a busca.
                buscarMemoria();

                //buscar
                if((statusD == Finalizado || statusD == Vazio) && statusB != Travado){
                    for(int i = 0; i<5; i++){
                        b_d.linha[i] = BR.MBR[i];
                        //printf("LINHA %i = %i\n", i, b_d.linha[i]);
                    }
                    printf("Busca Finalizada.");
                    statusB = Finalizado;
                    b_d.pc[0] = mar[0];
                    b_d.pc[1] = mar[1];

                }else{

                }

                //colocar dados obtidos no registrador entre.
                
                // uma função passará dps pelo pipeline, e jogará cada um pro próximo
            }else if(!newInstruction && !temDependencia){ 
                if((statusD == Finalizado  ||statusD == Vazio) && (statusB != Travado)){
                    statusB = Finalizado; // se atentar a essa condição em específico, mas acho q tá deboa
                }
            }
        }else{
            set_flag_flush(false);
            //exit(1);
        }
        // printf("B - %i\n", statusB);
        // printf("D - %i\n", statusD);
        // printf("BO - %i\n", statusBO);
        // printf("EX - %i\n", statusEX);
        // printf("ER - %i\n", statusER);
        //mostrarFila(dependencia_stor);
    }
    avancarPipeline();
}

void decodificacao(){ //posicao = posicao da primeira instrucao
    unsigned char temp; 
    //posicao n precisa, vai estar em MBR ja.
    if(statusD == Pronto){
        printf("Entrando na Decodificação\n");
        bool opcode_exit = false;
        int opcode = 0;
        if(newInstruction){
            printf("Entrei NEW INSTRUCTION\n");
            if(get_flag_lir()){
                BR.IR[4] = b_d.linha[0];
                printf("%i - Opcode 1 em IR\n", BR.IR[4]);
                opcode = BR.IR[4];
                //printf("opcodeeeee %i\n", opcode);

                if(opcode == OPC_EXIT){
                    opcode_exit = true;
                    printf("tem um exit");
                    //exit(1);
                }

                //Pegar o primeiro endereco e colocar em MAR.
                BR.MAR[3] = b_d.linha[1];
                BR.MAR[4] = b_d.linha[2];

                BR.MAR[4] >>= 4;

                temp = BR.MAR[3] << 4;

                BR.MAR[3] >>= 4;
                BR.MAR[4] |= temp;

                printf("\n%i - Endereco 1 Parte 1", BR.MAR[3]);
                printf("\n%i - Endereco 1 Parte 2\n", BR.MAR[4]);

                printaEnderecoMar();
                
                if(!opcode_exit){ //precisa das duas instruções, não é um EXIT.
                    //colocar a segunda instrucao em IBR        
                    BR.IBR[2] = b_d.linha[2];
                    BR.IBR[3] = b_d.linha[3];
                    BR.IBR[4] = b_d.linha[4];
                    //printf("%i - IBR 4\n", BR.IBR[4]);
                    BR.IBR[2] &= 15;

                    printf("\n%i - Pedaco 1 da Instrucao 2", BR.IBR[2]);
                    printf("\n%i - Pedaco 2 da Instrucao 2", BR.IBR[3]);
                    printf("\n%i - Pedaco 3 da Instrucao 2", BR.IBR[4]);

                    //jogar informações no entre.
                    if(statusBO == Finalizado || statusBO == Vazio){
                        d_bo.novoIBR[2] = BR.IBR[2];
                        d_bo.novoIBR[3] = BR.IBR[3];
                        d_bo.novoIBR[4] = BR.IBR[4];
                        //printf("passsei aq tb");
                    }
                }else{
                    //isExit = true;
                }

                if(statusBO == Finalizado || statusBO == Vazio){
                    d_bo.end[0] = BR.MAR[3];
                    d_bo.end[1] = BR.MAR[4];
                    d_bo.opc_linha = BR.IR[4];

                    if(d_bo.opc_linha == OPC_STOR){
                        set_flag_dependencia_stor(true);
                         
                        //printf("\n%i - d end 0\n", d_bo.end[0]);
                        //printf("%i - d end 1\n", d_bo.end[1]);
                        enfileirar(dependencia_stor, enderecoParaShort(d_bo.end));
                        //printf("enfileirei - %hd \n", enderecoParaShort(d_bo.end));
                        mostrarFila(dependencia_stor);
 
                        //desenfileirar(dependencia_stor);
                        mostrarFila(dependencia_stor);
                        //exit(1);

                    }else if(d_bo.opc_linha == OPC_STORDir || d_bo.opc_linha == OPC_STOREsq){
                        set_flag_dependencia_address(true);
                        enfileirar(dependencia_address, enderecoParaShort(d_bo.end));
                        //verificar se a instrução que peguei já tem o endereco, alterar.
                        if(d_bo.opc_linha == OPC_STORDir){
                            //verificar
                            Endereco prox;
                            prox[0] = b_d.pc[0];
                            prox[1] = b_d.pc[1];
                            // prox[0] = d_bo.novoIBR[3]; //receba  =°3°=
                            // prox[0] &= 15;
                            // prox[1] = d_bo.novoIBR[4];
                            if(enderecoParaShort(d_bo.end) == enderecoParaShort(prox)){
                                //alterar em execução.
                                // ou na vdd, parar tudo aqui atrás, e dps dar flush.
                                // manter o mesmo PC e só setar LIR.
                                set_flag_lir(false);
                                // statusD = Travado;
                                statusB = Travado;
                                printf("setei travado");
                                statusD = Finalizado;
                                //exit(1);
                                //travar_pipe();

                            }

                        }
                    }

                    //printf("peguei o endereco %i \n", d_bo.end[0]);
                    //printf("peguei o endereco %i \n", d_bo.end[1]);
                    newInstruction = false; // n tenho certexaaa
                    if(statusB == Travado){
                        newInstruction = true;
                        printf("\nCom statusD travado, newInstruction = true\n");
                        // exit(1);
                    }
                }

                //jogar informações no D_BO.

            }else{
                //pegar só a instrução da direita
                set_flag_lir(true);
                BR.IR[4] = b_d.linha[2];
                BR.IR[4] <<= 4;
                temp = b_d.linha[3];
                temp >>= 4;
                BR.IR[4] |= temp;

                BR.MAR[3] = b_d.linha[3];
                BR.MAR[3] &= 0b00001111;
                BR.MAR[4] = b_d.linha[4];
                if(d_bo.opc_linha == OPC_EXIT){
                    //isExit = true;
                }

                if(statusBO == Finalizado || statusBO == Vazio){
                    d_bo.opc_linha = BR.IR[4];

                    d_bo.end[0] = BR.MAR[3];
                    d_bo.end[1] = BR.MAR[4]; 

                    for(int i = 0; i<5;i++){
                        d_bo.novoIBR[i] = 0;
                    }

                    if(d_bo.opc_linha == OPC_STOR){
                        printf("\nStor detectado na decodificação, vou enfileirar o valor %hd\n ", enderecoParaShort(d_bo.end));
                        set_flag_dependencia_stor(true);
                        enfileirar(dependencia_stor, enderecoParaShort(d_bo.end));
                        mostrarFila(dependencia_stor);
                    }else if(d_bo.opc_linha == OPC_STORDir || d_bo.opc_linha == OPC_STOREsq){
                        set_flag_dependencia_address(true);
                        //verificar se a instrução que peguei ja tem o endereco.
                        enfileirar(dependencia_address, enderecoParaShort(d_bo.end));
                        mostrarFila(dependencia_stor);
                    }

                    newInstruction = true; //n tenho certeza disso tb, acho qé
                    unsigned long long int pc = registradorParaInteiro(BR.PC, false, -1);
                    pc++;
                    inteiroParaRegistrador(pc, BR.PC, false, -1);
                }


            }


        }else{ 
            unsigned char temp2;

            //colocar o opcode da instrução 2 em IR.
            BR.IR[4] = d_bo.novoIBR[2];

            BR.IR[4] <<= 4;

            temp2 = d_bo.novoIBR[3] & 240;
            temp2 >>= 4;

            BR.IR[4] |= temp2;

            //printf("\n%i - Opcode 2", BR.IR[4]);

            

            //colocar o endereço da instrução 2 em MAR. 
            BR.MAR[3] = d_bo.novoIBR[3]; //receba  =°3°=
            BR.MAR[3] &= 15;
            BR.MAR[4] = d_bo.novoIBR[4];
            
            if(statusBO == Finalizado || statusBO == Vazio){
                d_bo.opc_linha = BR.IR[4];
                d_bo.end[0] = BR.MAR[3];
                d_bo.end[1] = BR.MAR[4];

                if(d_bo.opc_linha == OPC_STOR){
                    printf("Stor identificado na decodificação, enfileirando o valor: %hd\n ", enderecoParaShort(d_bo.end));
                    mostrarFila(dependencia_stor);
                    set_flag_dependencia_stor(true);
                    enfileirar(dependencia_stor, enderecoParaShort(d_bo.end));
                }else if(d_bo.opc_linha == OPC_STORDir || d_bo.opc_linha == OPC_STOREsq){
                    set_flag_dependencia_address(true);
                    //verificar se a instrucao que eu peguei ja tem o endereco.
                    
                    enfileirar(dependencia_address, enderecoParaShort(d_bo.end));
                }
                unsigned long long int pc2 = registradorParaInteiro(BR.PC, false, -1);
                pc2++;
                inteiroParaRegistrador(pc2, BR.PC, false, -1);
                newInstruction = true;
            }

            printf("\n%i - Endereço segunda instrucao parte 1", BR.MAR[3]);
            printf("\n%i - Endereço segunda instrucao parte 2\n", BR.MAR[4]);
            
            printaEnderecoMar();    

        }

        if((statusBO == Finalizado || statusBO == Vazio) && (statusB != Travado)){
            printf("Decodificação Finalizada.\n");
            printf("Status B = % i \n", statusB);
            //exit(1);

            statusD = Finalizado;
        }
    }


    set_flag_b(true);
    verificaAcao();
}

void buscaOperandos(){
    //em Stor e StorM(addres modify), LSH, RSH, a busca será no AC.  *LOAD MQ busca no MQ.
    //na maioria a busca é lá na memória
    //pra alguns não há busca, como EXIT,, (Talvez os Jump também, né?)
    //
    bool temDependencia = false;
    if (get_flag_dependencia_stor()){
            if(d_bo.opc_linha != OPC_STOR){
                temDependencia = elementoNaFila(dependencia_stor, enderecoParaShort(d_bo.end));
            }
    }
    
    //Endereco address;
    if(statusBO == Pronto && !temDependencia){
        printf("\n Entrando na BO\n");
        // exit(1);
        unsigned long long int enderecoo = 0;
        unsigned long long int valor = 0;
        Endereco buscar;
        buscar[0] = d_bo.end[0];
        buscar[1] = d_bo.end[1];

        enderecoo |= d_bo.end[0];
        enderecoo <<= 8;
        enderecoo |= d_bo.end[1];
        opc opc_instrucao = d_bo.opc_linha;
        printf("O opcode da BO agora é: %i\n", opc_instrucao);

        

        //address[0]= d_bo.end[0];
        //address[1]= d_bo.end[1];
        //puxando da struct q fica entre.


        if(opc_instrucao == OPC_EXIT || opc_instrucao == OPC_LOADMQ || opc_instrucao == OPC_LSH || opc_instrucao == OPC_RSH){ //acrescentar os jumps provavelmente tb.
            //n precisa fazer busca de operandos.
            if(opc_instrucao != OPC_EXIT){
                // LSH, RSH, LOAD MQ
                if(opc_instrucao == OPC_LOADMQ){
                    // valor = registradorParaInteiro(BR.MQ, false, -1);
                    // for(int i = 0; i<5; i++){ //ver se chegou em MBR.
                    //     bo_ex.dado[i] = BR.MBR[i];
                    //     printf("Dado %i = %i\n", i, bo_ex.dado[i]);
                    // }

                }
                else{ //LSH, RSH
                    // valor = registradorParaInteiro(BR.AC, false, -1);
                    // for(int i = 0; i<5; i++){ //ver se chegou em MBR.
                    //     bo_ex.dado[i] = BR.AC[i];
                    //     printf("Dado %i = %i\n", i, bo_ex.dado[i]);
                    // }
                }
            }
            else{
                valor = -1; //detectar EXIT.
            }
        }else if(opc_instrucao == OPC_STOR || opc_instrucao == OPC_STOREsq || opc_instrucao == OPC_STORDir){
            // valor = registradorParaInteiro(BR.AC, false, -1);
            // for(int i = 0; i<5; i++){ //ver se chegou em MBR.
            //     bo_ex.dado[i] = BR.AC[i];
            //     printf("Dado %i = %i\n", i, bo_ex.dado[i]);
            // }
        }else if(opc_instrucao == OPC_JUMPEsq || opc_instrucao == OPC_JUMPPEsq || opc_instrucao == OPC_JUMPDir || opc_instrucao == OPC_JUMPPDir){
            //n tem B.O
            if(statusEX == Finalizado || statusEX == Vazio){
                bo_ex.dado[4] = buscar[1];
                bo_ex.dado[3] = buscar[0];
                bo_ex.dado[2] = 0;
                bo_ex.dado[1] = 0;
                bo_ex.dado[0] = 0;
            }
        }
        else{ //buscar na memória.
            printf("\n Busca na memoria, no BO, meu endereco eh %lld \n", enderecoo);
            setBarramentoEndereco(buscar);
            buscarMemoria();

            if(statusEX == Finalizado || statusEX == Vazio){
                for(int i = 0; i<5; i++){ //ver se chegou em MBR.

                    bo_ex.dado[i] = BR.MBR[i];
                    printf("BO Finalizada.");
                    printf("Dado %i = %i\n", i, bo_ex.dado[i]);
                }

            }



        }

        if(statusEX == Finalizado || statusEX == Vazio){
            bo_ex.opc_linha = d_bo.opc_linha;
            printf("BO Finalizada");
            printf("\nOpcode que estou passando na execução: %i\n", bo_ex.opc_linha);
            bo_ex.endereco[0] = buscar[0];
            bo_ex.endereco[1] = buscar[1];
            statusBO = Finalizado;

        }
    }

    set_flag_d(true);
    verificaAcao();
}

void execucao(){
    if(statusEX == Pronto){
        printf("Entrando na Execução\n");
        // enfileirar(dependencia_stor, 10);
        // enfileirar(dependencia_stor, 20);
        // enfileirar(dependencia_stor, 30);
        //desenfileirar(dependencia_stor);
        mostrarFila(dependencia_stor);
        //exit(1);
        unsigned long long int operando = 0;
        
        operando = registradorParaInteiro(bo_ex.dado, false, -1);
        int operation = (int)bo_ex.opc_linha;


        if(statusER == Finalizado || statusER == Vazio){            
            executaULA(operation, operando);
        }
    }
    set_flag_bo(true);
    verificaAcao();
}

void escritaResultados(){
    opc opc_instrucao = ex_er.opc_linha;
    if(statusER == Pronto){
        printf("Entrando na Escrita de Resultados\n");
        mostrarFila(dependencia_stor);

        //exit(1);

        if (ex_er.classe == EscritaRegistrador){
            printf("Escrita em registrador\n");
            if(opc_instrucao == OPC_JUMPEsq || opc_instrucao == OPC_JUMPPEsq || opc_instrucao == OPC_JUMPDir || opc_instrucao == OPC_JUMPPDir){
                transferirRR(BR.PC, ex_er.dado);    
                newInstruction = true;

            }
            //escrever no registrador
            //ULA -> AC
            if(opc_instrucao == OPC_LOAD || opc_instrucao == OPC_LOADMQ || opc_instrucao == OPC_LOADMenos ||
            opc_instrucao == OPC_LOADModulo || opc_instrucao == OPC_LOADMenosModulo || opc_instrucao == OPC_ADD ||
            opc_instrucao == OPC_ADDM || opc_instrucao == OPC_SUB ||opc_instrucao == OPC_SUBM ||
            opc_instrucao == OPC_LSH ||opc_instrucao == OPC_RSH){
                if(opc_instrucao == OPC_ADD){
                    printf("Instrucao ADD\n");
                    //exit(1);
                }
                transferirRR(BR.AC, ex_er.dado);    
            }else if(opc_instrucao == OPC_LOADMQM){
                transferirRR(BR.MQ, ex_er.dado);
            }

            
            //transferirRR(ex_er.reg1, ex_er.dado); //ver aq quando voltar.
            printf("Na Escrita de Registrador, escrevendo o dado: ");
            for(int i = 0; i<5; i++){
                printf("%i\n", ex_er.dado[i]);
            }
        }
        else if(ex_er.classe == EscritaMemoria)
        {

            printf("Escrita em memoria\n");
           // exit(1);
            enum escritaMemoria tipo;
            //escrever na memoria
            //
            if(ex_er.opc_linha == OPC_STOR){
                //ULA -> MBR
                //*Dado foi puxado do AC anteriormente.
                transferirRR(BR.MBR, ex_er.dado);
                printf("Escrevendo Stor, puxamos pra MBR o dado: \n");
                for(int i = 0; i<5; i++){
                    printf("%i\n", BR.MBR[i]);
                }
                Dado valor;
                for (int i = 0; i<5; i++){
                    valor[i] = BR.MBR[i];
                }
                tipo = Tudo;
                
                BR.MAR[3] = ex_er.endereco[0];
                BR.MAR[4] = ex_er.endereco[1];
                //verificação de apenas pegar os últimos dois bytes, 
                BR.MAR[3] &= 0b00001111;
                Endereco temp;
                temp[0] = BR.MAR[3];
                temp[1] = BR.MAR[4];
                setBarramentoDados(valor);
                setBarramentoEndereco(temp);
                escreverMemoria(tipo);

                
                if(elementoNaFila(dependencia_stor, enderecoParaShort(temp))){
                    mostrarFila(dependencia_stor);
                    desenfileirar(dependencia_stor);
                    //printf("desenfileirei\n");
                }
                if(estaVazia(dependencia_stor)){
                    set_flag_dependencia_stor(false);
                }
                


            }
            else if(ex_er.opc_linha == OPC_STOREsq){
                transferirRR(BR.MBR, ex_er.dado);
                Dado valor;
                printf("opc stores esq escrita");
                //exit(1);
                for (int i = 0; i<5; i++){
                    valor[i] = BR.MBR[i];
                }
                tipo = Esquerda;
                BR.MAR[3] = ex_er.endereco[0];
                BR.MAR[4] = ex_er.endereco[1];

                ex_er.endereco[0] = BR.MAR[3];
                ex_er.endereco[1] = BR.MAR[4];
                //verificação de apenas pegar os últimos dois bytes, 
                BR.MAR[3] &= 0b00001111;
                setBarramentoDados(valor);
                setBarramentoEndereco(ex_er.endereco);
                escreverMemoria(tipo);

                mostrarFila(dependencia_address);
                printf("endereco - %hd\n", enderecoParaShort(ex_er.endereco));

                //exit(1);
                if(elementoNaFila(dependencia_address, enderecoParaShort(ex_er.endereco))){
                    printf("ESTA AQIO! VOU DESENFILEIREAS");
                    desenfileirar(dependencia_address);
                    //exit(1);
                }
                if(estaVazia(dependencia_address)){
                    set_flag_dependencia_address(false);
                }
                
            }
            else if(ex_er.opc_linha == OPC_STORDir){
                printf("Escrevendo STOR-DIR\n");
                transferirRR(BR.MBR, ex_er.dado);
                Dado valor;
                //exit(1);
                for (int i = 0; i<5; i++){
                    valor[i] = BR.MBR[i];
                }
                tipo = Direita;
                BR.MAR[3] = ex_er.endereco[0];
                BR.MAR[4] = ex_er.endereco[1];

                ex_er.endereco[0] = BR.MAR[3];
                ex_er.endereco[1] = BR.MAR[4];
                //verificação de apenas pegar os últimos dois bytes, 
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
        else if(ex_er.classe == EscritaVazia){ //jump condiiconal que n vai pular
        }
        else{
            printf("Classe inexistente, abortando.");
            exit(1);
        }
        statusER = Finalizado;
    }
    set_flag_ex(true);
    verificaAcao();
}

void pipeline(){
    set_flag_er(true);
    verificaAcao();
}

void avancarPipeline(){
    printf("Status do Pipeline");
    printf("CLOCK ATUAL TAL %i", cpu_clk);
    printf("\nANTES AVANÇO---\n");
    printf("B - %i\n", statusB);
        printf("D - %i\n", statusD);
        printf("BO - %i\n", statusBO);
        printf("EX - %i\n", statusEX);
        printf("ER - %i\n", statusER);
    
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
        if(statusB == Travado){
            //statusD = Travado;
        }
    }
    if(statusB == Finalizado && statusD == Vazio){
        statusD = Pronto;
        statusB = Vazio;
    }
    printf("\n PÓS AVANÇO---\n");
        printf("B - %i\n", statusB);
        printf("D - %i\n", statusD);
        printf("BO - %i\n", statusBO);
        printf("EX - %i\n", statusEX);
        printf("ER - %i\n\n", statusER);
    
}

void clockTick(){
    cpu_clk++;
}

