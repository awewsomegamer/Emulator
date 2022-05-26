#ifndef EMULATOR_H
#define EMULATOR_H
#define LINE_SIZE 256

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <util.h>

extern const char* CLI_USAGE;

extern uint8_t* memory;
// extern uint8_t* stack;
extern uint8_t* ports;

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

static const char* OPERATION_T_NAMES[] = {"nop", "mov", "sub", "add", 
										  "div", "mul", "and", "or", 
										  "xor", "not", "shl", "shr",
										  "sivte", "rivte", "int", "call", 
										  "jmp", "cmp", "je", "jne", "jg", 
										  "jge", "jl", "jle", "jz", "jnz", 
										  "jc", "jnc", "ret", "inc", "push", 
										  "pop"};

typedef enum{
	OVERFLOW_FLAG = 0,
	ZERO_FLAG,
	CARRY_FLAG,
	FLAG_MAX
} FLAGS_T;
extern uint8_t flags;

typedef enum{
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
	INCLUDE,
	PUSH,
	POP,
	OPERATION_MAX
} OPERATIONS_T;
// List of operation functtion pointers
void (*operation_fuctions[OPERATION_MAX])(uint8_t, uint32_t, uint32_t);

// Interrupt Vector Table
void (*ivt[UINT8_MAX+1])();

#endif