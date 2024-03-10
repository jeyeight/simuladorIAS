#include <stdio.h>
#include <stdbool.h>
#include "headers/types.h"
#include "headers/flags.h"

short flags = 0;

void set_flag_b(bool value) {
    if (value)
        flags |= FLAG_B;
    else
        flags &= ~FLAG_B;
}

bool get_flag_b() {
    return flags & FLAG_B;
}
void set_flag_d(bool value) {
    if (value)
        flags |= FLAG_D; 
    else
        flags &= ~FLAG_D;
}

bool get_flag_d() {
    return flags & FLAG_D;
}
void set_flag_bo(bool value) {
    if (value)
        flags |= FLAG_BO; 
    else
        flags &= ~FLAG_BO;
}

bool get_flag_bo() {
    return flags & FLAG_BO;
}
void set_flag_ex(bool value) {
    if (value)
        flags |= FLAG_EX;
    else
        flags &= ~FLAG_EX;
}

bool get_flag_ex() {
    return flags & FLAG_EX;
}
void set_flag_er(bool value) {
    if (value)
        flags |= FLAG_ER; 
    else
        flags &= ~FLAG_ER;
}

bool get_flag_er() {
    return flags & FLAG_ER;
}
