#ifndef EMULATOR_H
#define EMULATOR_H

#define LINE_SIZE 256

#define BYTE 0x1
#define KBYTE BYTE * 1000
#define MBYTE KBYTE * 1000
#define GBYTE MBYTE * 1000
#define DEFINE_INSTRUCTION(key, argc) {key, argc}

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

extern int current_instruction_size;

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

struct INSTRUCTION_INFORMATION {
	char* key;
	int argc;
};

static const struct INSTRUCTION_INFORMATION INSTRUCTION_SET[] = {
	[NOP] 					= DEFINE_INSTRUCTION("nop",			0),
	[MOV] 					= DEFINE_INSTRUCTION("mov",			2),
	[SUB] 					= DEFINE_INSTRUCTION("sub",			2),
	[ADD] 					= DEFINE_INSTRUCTION("add", 		2),
	[DIV] 					= DEFINE_INSTRUCTION("div",			2),
	[MUL] 					= DEFINE_INSTRUCTION("mul",			2),
	[AND] 					= DEFINE_INSTRUCTION("and",			2),
	[OR]  					= DEFINE_INSTRUCTION("or", 			2),
	[XOR] 					= DEFINE_INSTRUCTION("xor",			2),
	[NOT] 					= DEFINE_INSTRUCTION("not",			1),
	[SHL] 					= DEFINE_INSTRUCTION("shl",			2),
	[SHR] 					= DEFINE_INSTRUCTION("shr",			2),
	[SIVTE] 				= DEFINE_INSTRUCTION("sivte",		2),
	[RIVTE] 				= DEFINE_INSTRUCTION("rivte",		2),
	[INT] 					= DEFINE_INSTRUCTION("int",			1),
	[CALL]  				= DEFINE_INSTRUCTION("call", 		1),
	[JMP] 					= DEFINE_INSTRUCTION("jmp",			1),
	[CMP] 					= DEFINE_INSTRUCTION("cmp",			2),
	[JE] 					= DEFINE_INSTRUCTION("je",			1),
	[JNE] 					= DEFINE_INSTRUCTION("jne",			1),
	[JG] 					= DEFINE_INSTRUCTION("jg", 			1),
	[JGE] 					= DEFINE_INSTRUCTION("jge",			1),
	[JL] 					= DEFINE_INSTRUCTION("jl",			1),
	[JLE] 					= DEFINE_INSTRUCTION("jle",			1),
	[JZ] 					= DEFINE_INSTRUCTION("jz",			1),
	[JNZ] 					= DEFINE_INSTRUCTION("jnz", 		1),
	[JC] 					= DEFINE_INSTRUCTION("jc",			1),
	[JNC] 					= DEFINE_INSTRUCTION("jnc",			1),
	[RET] 					= DEFINE_INSTRUCTION("ret",			0),
	[IRET] 					= DEFINE_INSTRUCTION("iret",		0),
	[PUSH]  				= DEFINE_INSTRUCTION("push", 		1),
	[POP] 					= DEFINE_INSTRUCTION("pop",			1),
	[INB] 					= DEFINE_INSTRUCTION("inb",			2),
	[INW] 					= DEFINE_INSTRUCTION("inw",			2),
	[IND] 					= DEFINE_INSTRUCTION("ind",			2),
	[OUTB]  				= DEFINE_INSTRUCTION("outb", 		2),
	[OUTW] 					= DEFINE_INSTRUCTION("outw",		2),
	[OUTD] 					= DEFINE_INSTRUCTION("outd",		2),
	[DEFINITION_STRING] 	= DEFINE_INSTRUCTION("ds",			3),
	[DEFINITION_BYTES] 		= DEFINE_INSTRUCTION("db",			3),
	[INCLUDE]				= DEFINE_INSTRUCTION("inc",			3)
};

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