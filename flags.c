#include <stdio.h>
#include <stdbool.h>
#include "headers/types.h"
#include "headers/flags.h"

short flags = 0;

void set_flag_b(bool value) {
    if (value){
        flags |= FLAG_B;
    }
    else
    {
        flags &= ~FLAG_B;
    }
}

bool get_flag_b() {
    return flags & FLAG_B;
}

void set_flag_d(bool value) {
    if (value)
    {
        flags |= FLAG_D; 
    }
    else
    {
        flags &= ~FLAG_D;
    }
}

bool get_flag_d() {
    return flags & FLAG_D;
}

void set_flag_bo(bool value) {
    if (value)
    {
        flags |= FLAG_BO; 
    }
    else
    {
        flags &= ~FLAG_BO;
    }
}

bool get_flag_bo() {
    return flags & FLAG_BO;
}

void set_flag_ex(bool value) {
    if (value)
    {
        flags |= FLAG_EX;
    }
    else
    {
        flags &= ~FLAG_EX;
    }
}

bool get_flag_ex() {
    return flags & FLAG_EX;
}

void set_flag_er(bool value) {
    if (value)
    {
        flags |= FLAG_ER; 
    }
    else
    {
        flags &= ~FLAG_ER;
    }
}

bool get_flag_er() {
    return flags & FLAG_ER;
}

void set_flag_pipe(bool value) {
    if (value)
    {
        flags |= FLAG_PIPE; 
    }
    else{
        flags &= ~FLAG_PIPE;
    }
}

bool get_flag_pipe() {
    return flags & FLAG_PIPE;
}

void set_flag_lir(bool value) {
    if (value)
    {
        flags |= FLAG_LIR; 
    }
    else
    {
        flags &= ~FLAG_LIR;
    }
}

bool get_flag_lir() {
    return flags & FLAG_LIR;
}

void set_flag_dependencia_stor(bool value){
    if (value)
    {
        flags |= FLAG_DPS; 
    }
    else
    {
        flags &= ~FLAG_DPS;
    }
}

bool get_flag_dependencia_stor(){
    return flags & FLAG_DPS;

}

void set_flag_dependencia_address(bool value){
    if (value)
    {
        flags |= FLAG_DPA; 
    }
    else
    {
        flags &= ~FLAG_DPA;
    }
}

bool get_flag_dependencia_address(){
    return flags & FLAG_DPA;
}

void set_flag_flush(bool value){
    if (value)
    {
        flags |= FLAG_FLUSH; 
    }
    else
        flags &= ~FLAG_FLUSH;
}

bool get_flag_flush(){
    return flags & FLAG_FLUSH;
}

void set_flag_clk(bool value){
    if (value)
    {
        flags |= FLAG_CLK; 
    }
    else
        flags &= ~FLAG_CLK;
}

bool get_flag_clk(){
    return flags & FLAG_CLK;
}

void zerarEstagiosPipe(){
    flags &= ZERAR_ESTAGIOS;
}

void setFlagsIniciais(){
    set_flag_flush(false);
    set_flag_dependencia_address(false);
    set_flag_dependencia_stor(false);
    set_flag_lir(true);
    set_flag_clk(false);
}