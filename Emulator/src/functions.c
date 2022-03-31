#include <functions.h>
#include <emulator.h>

void init_operator_functions(){
    // These take two arguments, and require indices in most cases
    operation_fuctions[1] = MOV_OPERATOR;
    operation_fuctions[2] = SUB_OPERATOR;
    operation_fuctions[3] = ADD_OPERATOR;
    operation_fuctions[4] = DIV_OPERATOR;
    operation_fuctions[5] = MUL_OPERATOR;
    operation_fuctions[6] = AND_OPERATOR;
    operation_fuctions[7] = OR_OPERATOR;
    operation_fuctions[8] = XOR_OPERATOR;
    operation_fuctions[9] = NOT_OPERATOR;
    operation_fuctions[10] = SHL_OPERATOR;
    operation_fuctions[11] = SHR_OPERATOR;

    // These only have one argument which should just be a label or address (doesn't require index logic)
    operation_fuctions[12] = INT_OPERATOR; // This one takes a value, no address
    operation_fuctions[13] = CALL_OPERATOR;
    operation_fuctions[14] = JMP_OPERATOR;
    operation_fuctions[15] = CMP_OPERATOR;
    operation_fuctions[16] = JE_OPERATOR;
    operation_fuctions[17] = JNE_OPERATOR;
    operation_fuctions[18] = JZ_OPERATOR;
    operation_fuctions[19] = JNZ_OPERATOR;
    operation_fuctions[20] = JC_OPERATOR;
    operation_fuctions[21] = JNC_OPERATOR;

    // These takes no arguments
    operation_fuctions[0] = NOP_OPERATOR;
    operation_fuctions[22] = RET_OPERATOR;
}

void NOP_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2) { 
    return;
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

void ADD_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void DIV_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void MUL_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void AND_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void OR_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void XOR_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void NOT_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void SHL_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void SHR_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    
}

void INT_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    
}

void CALL_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void JMP_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void CMP_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void JE_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void JNE_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void JZ_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void JNZ_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void JC_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void JNC_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}

void RET_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){

}