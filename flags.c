#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ZERO_FLAG_MASK 0b01
#define CARRY_FLAG_MASK 0b10 // 0b10
#define OutraCoisa 0b11

char flags = 0;

void set_zero_flag(bool value) {
    if (value)
        flags |= ZERO_FLAG_MASK; // 0b0000_0001 ((flag & (ZERO_FLAG_MASK | CARRY_FLAG_MASK) ) == 1)
    else
        flags &= ~ZERO_FLAG_MASK;
}

bool get_zero_flag() {
    return flags & ZERO_FLAG_MASK;
}
