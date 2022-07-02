#ifndef CLOCK_H
#define CLOCK_H

#define CLOCK_WRITE 0x4 
#define CLOCK_MASK 0x5
#define CLOCK_DATA 0x6 // 0x6 -> 0x9

#include <IO.h>
#include <emulator.h>

void update_clock();
void generate_clock_signal();

#endif