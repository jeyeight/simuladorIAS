#ifndef FLAGS_H
#define FLAGS_H

#include <stdbool.h>

#define FLAG_B  0b00000001
#define FLAG_D  0b00000010
#define FLAG_BO 0b00000100
#define FLAG_EX 0b00001000
#define FLAG_ER 0b00010000
#define FLAG_PIPE 0b00100000

#define ZERAR_ESTAGIOS 0b1111111111000000



extern short flags;

void set_flag_b(bool value);

bool get_flag_b();

void set_flag_d(bool value);

bool get_flag_d();

void set_flag_bo(bool value);

bool get_flag_bo();

void set_flag_ex(bool value);

bool get_flag_ex();

void set_flag_er(bool value);

bool get_flag_er();

void set_flag_pipe(bool value);

bool get_flag_pipe();

void zerarEstagiosPipe();

#endif