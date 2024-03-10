#include <stdio.h>
#include "headers/types.h"
#include "headers/flags.h"
#include "headers/uc.h"
#include "headers/processador.h"

// 0 0 0 0 0 0 0 0    0 0 0 0 0 0 0 0 
//primeiro - chamar pipeline
//segundo - chamar escrita_resultados
//terceiro - chamar execucao
//quarto - chamar bo
//quinto - chamar decodificao
//sexto - chamar busca
//setimo
//oitavo

//nono - mostra se multiplicacao sobrou pro AC
//decimo pra frente - status dos ciclos? ou guardar em variaveis separadas.
//... // ps: flag para talvez identificar se preicsa ou n fazer busca 
//(a busca as vezes é feita) ou não, depende se na instrução passada ele buscou já na memória, ou se só puxou de IBR.
// 
//talvez mexer nas flags?

void verificaAcao(){
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
        buscaOperandos();
    }else if(get_flag_d()){
        zerarEstagiosPipe();
        decodificacao(true);
    }else if(get_flag_b()){
        zerarEstagiosPipe();
        busca();
    }
}

void buscar_na_memoria(){
    Endereco *ponteiro;
    printf("cheguei aq");
    ponteiro = getBarramentoEndereco();
    printf("%s - endereco", ponteiro);

}