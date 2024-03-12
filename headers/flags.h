#ifndef FLAGS_H
#define FLAGS_H

#include <stdbool.h>

#define FLAG_B      0b0000000000000001
#define FLAG_D      0b0000000000000010
#define FLAG_BO     0b0000000000000100
#define FLAG_EX     0b0000000000001000
#define FLAG_ER     0b0000000000010000
#define FLAG_PIPE   0b0000000000100000
#define FLAG_LIR    0b0000000001000000
#define FLAG_FLUSH  0b0000000010000000
#define FLAG_DPS    0b0000000100000000
#define FLAG_DPA    0b0000001000000000

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

void set_flag_lir(bool value);

bool get_flag_lir();

void set_flag_dependencia_stor(bool value);

bool get_flag_dependencia_stor();

void set_flag_dependencia_address(bool value);

bool get_flag_dependencia_address();

void set_flag_flush(bool value);

bool get_flag_flush();

void zerarEstagiosPipe();

#endif