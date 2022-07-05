#ifndef EMULATOR_H
#define EMULATOR_H

#define LINE_SIZE 256

#define BYTE 0x1
#define KBYTE BYTE * 1000
#define MBYTE KBYTE * 1000
#define GBYTE MBYTE * 1000

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <util.h>
#include <error_handler.h>
#include <SDL2/SDL_audio.h>

extern const char* CLI_USAGE;

extern uint32_t current_ms;
extern uint32_t last_millisecond;

extern uint8_t* memory;
extern uint8_t* ports;

extern FILE* disk;

extern bool IP_SET;
extern uint32_t ticks;

typedef enum{
	A = 0,
	B,
	C,
	D,
	IP,
	SP,
	BP,
	I1,
	I2,
	I3,
	I4,
	REGISTER_MAX
} REGISTERS_T;
uint32_t registers[REGISTER_MAX];

typedef enum{
	OVERFLOW_FLAG = 0,
	ZERO_FLAG,
	CARRY_FLAG,
	FLAG_MAX
} FLAGS_T;
extern uint8_t flags;

static const char* OPERATION_T_NAMES[] = {"nop", "mov", "sub", "add", 
										  "div", "mul", "and", "or", 
										  "xor", "not", "shl", "shr",
										  "sivte", "rivte", "int", "call", 
										  "jmp", "cmp", "je", "jne", "jg", 
										  "jge", "jl", "jle", "jz", "jnz", 
										  "jc", "jnc", "ret", "iret", "push", 
										  "pop", "inb", "inw", "ind", "outb", 
										  "outw", "outd", "ds", "db", "inc"};

static const uint8_t OPERATION_T_ARGC[] = {
	0, 2, 2, 2,
	2, 2, 2, 2,
	2, 1, 2, 2,
	2, 2, 1, 1,
	1, 2, 1, 1, 1,
	1, 1, 1, 1, 1,
	1, 1, 0, 0, 1,
	1, 2, 2, 2, 2,
	2, 2, 3, 3, 0
};

typedef enum {
	NOP = 0,
	MOV,
	SUB,
	ADD,
	DIV,
	MUL,
	AND,
	OR,
	XOR,
	NOT,
	SHL,
	SHR,
	SIVTE,
	RIVTE,
	INT,
	CALL,
	JMP,
	CMP,
	JE,
	JNE,
	JG,
	JGE,
	JL,
	JLE,
	JZ,
	JNZ,
	JC,
	JNC,
	RET,
	IRET,
	PUSH,
	POP,
	INB,
	INW,
	IND,
	OUTB,
	OUTW,
	OUTD,
	DEFINITION_STRING,
	DEFINITION_BYTES,
	INCLUDE,
	OPERATION_MAX
} OPERATION_T;
// List of operation functtion pointers
void (*operation_fuctions[OPERATION_MAX])(uint8_t, uint32_t, uint32_t);


typedef enum {
	TIMER_INT,
	PRINT_INT,
	DISK_IO_INT,
	KEYBOARD_INT
} INTERRUPT_T;
// Interrupt Vector Table
void (*ivt[UINT8_MAX+1])();

void print_regs();

#endif