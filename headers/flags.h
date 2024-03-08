#ifndef FLAGS_H
#define FLAGS_H

#define ZERO_FLAG_MASK 0b01
#define CARRY_FLAG_MASK 0b10
#define OutraCoisa 0b11

void set_zero_flag(bool value);

bool get_zero_flag();

#endif