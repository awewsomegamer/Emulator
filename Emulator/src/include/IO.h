#ifndef IO_H
#define IO_H

#include <stdint.h>

void outb(uint16_t address, uint8_t value);
uint8_t inb(uint16_t address);

void outw(uint16_t address, uint16_t value);
uint16_t inw(uint16_t address);

void outd(uint16_t address, uint32_t value);
uint32_t ind(uint16_t address);

#endif