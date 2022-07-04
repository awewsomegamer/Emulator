#include <emulator.h>

bool IP_SET = true;
uint32_t ticks = 0;

uint32_t current_ms = 0;
uint32_t last_millisecond = 0;

uint8_t* memory;
uint8_t* ports;

FILE* disk = NULL;

uint8_t flags = 0;