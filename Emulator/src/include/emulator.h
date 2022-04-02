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
extern uint8_t* stack;

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
uint16_t registers[REGISTER_MAX];

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
	INT,
	CALL,
	JMP,
	CMP,
	JE,
	JNE,
	JZ,
	JNZ,
	JC,
	JNC,
	RET,
	OPERATION_MAX
} OPERATIONS_T;
void (*operation_fuctions[OPERATION_MAX])(uint8_t, uint32_t, uint32_t);

void (*ivt[UINT8_MAX+1])();

#endif