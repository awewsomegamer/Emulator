#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stddef.h>
#include <stdint.h>

void init_ivt();

void ivt_0();
void ivt_1();
void ivt_2();

#endif