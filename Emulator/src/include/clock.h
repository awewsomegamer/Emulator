#ifndef CLOCK_H
#define CLOCK_H

#define CLOCK_WRITE 0x4 
#define CLOCK_MASK 0x5
#define CLOCK_DATA 0x6 // 0x6 -> 0x9

#define CLOCK_IRQ 0x4

#include <IO.h>
#include <emulator.h>

void update_clock();
void generate_clock_signal();

#endif