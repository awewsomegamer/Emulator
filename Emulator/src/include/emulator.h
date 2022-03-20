#ifndef EMULATOR_H
#define EMULATOR_H
#define LINE_SIZE 256

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <util.h>

uint16_t memory[UINT16_MAX];

#define TEST 5

typedef enum{
	A = 1,
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
uint16_t operations[OPERATION_MAX];

#endif 