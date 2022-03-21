#include <functions.h>
#include <emulator.h>

void init_operator_functions(){
    operation_fuctions[1] = MOV_OPERATOR;
    operation_fuctions[2] = SUB_OPERATOR;
}

void MOV_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch(indices){
    case 0:
        memory[v1] = v2;
        break;
    case 1:
		registers[v1 / 16 - 1] = v2;
        break;
    case 2:
		memory[v1] = registers[v2 / 16 - 1];
        break;
    case 3:
		registers[v1 / 16 - 1] = registers[v2 / 16 - 1];
        break;
    }
}

void SUB_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch(indices){
    case 0:
        memory[v1] = memory[v1]-v2;
        break;
    case 1:
		registers[v1 / 16 - 1] = registers[v1 / 16 - 1]-v2;
        break;
    case 2:
		memory[v1] = memory[v1]-registers[v2 / 16 - 1];
        break;
    case 3:
		registers[v1 / 16 - 1] = registers[v1 / 16 - 1]-registers[v2 / 16 - 1];
        break;
    }
}