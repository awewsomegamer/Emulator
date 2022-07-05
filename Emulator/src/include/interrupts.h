#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

extern bool working_on_interrupt;

void init_ivt();

void define_interrupt(int interrupt, int address);
void undefine_interrupt(int interrupt);
void call_interrupt(int interrupt);

void IVT_NOP();
void IVT_0();
void IVT_1();

#endif