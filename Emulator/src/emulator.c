#include <emulator.h>

uint8_t* memory;
// uint8_t* stack;
uint8_t* ports;

FILE* disk = NULL;

uint8_t flags = 0;