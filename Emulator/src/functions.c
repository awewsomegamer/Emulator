#include <functions.h>
#include <emulator.h>

void init_operator_functions(){
    operation_fuctions[1] = MOV_OPERATOR;
}

void MOV_OPERATOR(uint8_t indices, uint16_t v1, uint16_t v2){
	if (indices == 0){
		// value 1 == register
		registers[v1 / 16 - 1] = v2;
	}

	if (indices == 1) {
		// value 2 == register
		// value 2 == memory address
		memory[v1] = registers[v2 / 16 - 1];
	}

	if (indices == 2){
		// both values are registers
		registers[v1 / 16 - 1] = registers[v2 / 16 - 1];
	}
}