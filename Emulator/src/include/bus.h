#ifndef BUS_H
#define BUS_H

#include <emulator.h>

#define ROM_START MBYTE
#define ROM_END ROM_START + (64 * KBYTE)

uint8_t read_address_b(int address);
uint16_t read_address_w(int address);
uint32_t read_address_d(int address);

void write_address_b(int address, uint8_t value);
void write_address_w(int address, uint16_t value);
void write_address_d(int address, uint32_t value);

#endif