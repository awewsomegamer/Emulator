#include <functions.h>
#include <emulator.h>

#define REGISTER(value) (value / 16 - 1)
#define FLAG(flag) ((flags >> flag) & 0x1)
#define FLAG_SET(flag, value) flags ^= (-value ^ flags) & (1 << flag);


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
    operation_fuctions[18] = JG_OPERATOR; // JZ
    operation_fuctions[19] = JGE_OPERATOR; // JNZ
    operation_fuctions[20] = JL_OPERATOR; // JC
    operation_fuctions[21] = JLE_OPERATOR; // JNC

    // These takes no arguments
    operation_fuctions[0] = NOP_OPERATOR;
    operation_fuctions[22] = RET_OPERATOR;
}

void NOP_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2) { 
    return;
}

void MOV_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch (indices){
    case 0x00:
    case 0x03:
        memory[v1] = v2;
        break;

    case 0x10:
    case 0x13:
        memory[v1] = registers[REGISTER(v2)];
        break;

    case 0x23:
        memory[v1] = memory[registers[REGISTER(v2)]];
        break;

    case 0x22:
        memory[registers[REGISTER(v1)]] = memory[registers[REGISTER(v2)]];
        break;

    case 0x12:
        memory[registers[REGISTER(v1)]] = registers[REGISTER(v2)];
        break;

    case 0x11:
        registers[REGISTER(v1)] = registers[REGISTER(v2)];
        break;

    case 0x01:
        registers[REGISTER(v1)] = v2;
        break;
    }

    // case 0x00:
    // case 0x03:
    //     memory[v1] = v2;
    //     break;
    
    // case 0x01:
    //     registers[REGISTER(v1)] = v2;
    //     break;
    // case 0x10:
    //     memory[v1] = registers[REGISTER(v1)];
    //     break;
    
    // case 0x11:
    //     registers[REGISTER(v1)] = registers[REGISTER(v2)];
    //     break;

    // case 0x13:
    //     memory[v1] = registers[REGISTER(v2)];
    //     break;
    
    // case 0x22:
    //     memory[registers[REGISTER(v1)]] = memory[registers[REGISTER(v2)]];
    //     break;

    /* 
    mov 0x100 or [0x100], 100 (0x00 0x03) (done)
    mov 0x100 or [0x100], [100] (0x30 0x33)
    mov ax, bx (0x11)
    mov [ax], bx (0x21)
    mov ax, [bx] (0x12)
    mov ax, 100 (0x01)
    mov [ax], 100 (0x20)
    mov [ax], [bx] (0x22) (done)

    -= Support =-
    mov [0x100], 100 (0x00 0x03)
    mov [0x100], ax (0x10 0x13)
    mov [0x100], [ax] (0x23)
    mov [ax], [bx] (0x22)
    mov [ax], bx (0x12)
    mov ax, bx (0x11)
    mov ax, 100 (0x10)
    */
    
    // switch(indices){
    // case 0x00:
    //     memory[v1] = v2;
    //     break;
    // case 0x01:
	//     registers[REGISTER(v1)] = v2;
    //     break;
    // case 0x02:
	// 	memory[v1] = registers[REGISTER(v2)];
    //     break;
    // case 0x11:
	// 	registers[REGISTER(v1)] = registers[REGISTER(v2)];
    //     break;
    // case 0x40:
    //     memory[v1] = memory[v2];
    //     break;
    // case 0x41:
    //     registers[REGISTER(v1)] = memory[v2];
    //     break;
    // }
}

void SUB_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch(indices){
    case 0:
        memory[v1] = memory[v1] - v2;
        break;
    case 1:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] - v2;
        break;
    case 2:
		memory[v1] = memory[v1] - registers[REGISTER(v2)];
        break;
    case 3:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] - registers[REGISTER(v2)];
        break;
    case 4:
        memory[v1] = memory[v1] - memory[v2];
        break;
    case 5:
        registers[REGISTER(v1)] = registers[REGISTER(v1)] - memory[v2];
        break;
    }
}

void ADD_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch(indices){
    case 0:
        memory[v1] = memory[v1] + v2;
        break;
    case 1:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] + v2;
        break;
    case 2:
		memory[v1] = memory[v1] + registers[REGISTER(v2)];
        break;
    case 3:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] + registers[REGISTER(v2)];
        break;
    case 4:
        memory[v1] = memory[v1] + memory[v2];
        break;
    case 5:
        registers[REGISTER(v1)] = registers[REGISTER(v1)] + memory[v2];
        break;
    }
}

void DIV_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch(indices){
    case 0:
        memory[v1] = memory[v1] / v2;
        break;
    case 1:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] / v2;
        break;
    case 2:
		memory[v1] = memory[v1] / registers[REGISTER(v2)];
        break;
    case 3:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] / registers[REGISTER(v2)];
        break;
    case 4:
        memory[v1] = memory[v1] / memory[v2];
        break;
    case 5:
        registers[REGISTER(v1)] = registers[REGISTER(v1)] / memory[v2];
        break;
    }
}

void MUL_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch(indices){
    case 0:
        memory[v1] = memory[v1] * v2;
        break;
    case 1:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] * v2;
        break;
    case 2:
		memory[v1] = memory[v1] * registers[REGISTER(v2)];
        break;
    case 3:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] * registers[REGISTER(v2)];
        break;
    case 4:
        memory[v1] = memory[v1] * memory[v2];
        break;
    case 5:
        registers[REGISTER(v1)] = registers[REGISTER(v1)] * memory[v2];
        break;
    }
}

void AND_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch(indices){
    case 0:
        memory[v1] = memory[v1] & v2;
        break;
    case 1:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] & v2;
        break;
    case 2:
		memory[v1] = memory[v1] & registers[REGISTER(v2)];
        break;
    case 3:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] & registers[REGISTER(v2)];
        break;
    case 4:
        memory[v1] = memory[v1] & memory[v2];
        break;
    case 5:
        registers[REGISTER(v1)] = registers[REGISTER(v1)] & memory[v2];
        break;
    }
}

void OR_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch(indices){
    case 0:
        memory[v1] = memory[v1] | v2;
        break;
    case 1:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] | v2;
        break;
    case 2:
		memory[v1] = memory[v1] | registers[REGISTER(v2)];
        break;
    case 3:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] | registers[REGISTER(v2)];
        break;
    case 4:
        memory[v1] = memory[v1] | memory[v2];
        break;
    case 5:
        registers[REGISTER(v1)] = registers[REGISTER(v1)] | memory[v2];
        break;
    }
}

void XOR_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch(indices){
    case 0:
        memory[v1] = memory[v1] ^ v2;
        break;
    case 1:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] ^ v2;
        break;
    case 2:
		memory[v1] = memory[v1] ^ registers[REGISTER(v2)];
        break;
    case 3:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] ^ registers[REGISTER(v2)];
        break;
    case 4:
        memory[v1] = memory[v1] ^ memory[v2];
        break;
    case 5:
        registers[REGISTER(v1)] = registers[REGISTER(v1)] ^ memory[v2];
        break;
    }
}

void NOT_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch(indices){
    case 0:
        memory[v1] = ~memory[v1];
        break;
    case 1:
		registers[REGISTER(v1)] = ~registers[REGISTER(v1)];
        break;
    case 2:
		memory[v1] = ~memory[v1];
        break;
    case 3:
		registers[REGISTER(v1)] = ~registers[REGISTER(v1)];
        break;
    case 4:
        memory[v1] = ~memory[v1];
        break;
    case 5:
        registers[REGISTER(v1)] = ~registers[REGISTER(v1)];
        break;
    }
}

void SHL_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch(indices){
    case 0:
        memory[v1] = memory[v1] << v2;
        break;
    case 1:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] << v2;
        break;
    case 2:
		memory[v1] = memory[v1] << registers[REGISTER(v2)];
        break;
    case 3:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] << registers[REGISTER(v2)];
        break;
    case 4:
        memory[v1] = memory[v1] << memory[v2];
        break;
    case 5:
        registers[REGISTER(v1)] = registers[REGISTER(v1)] << memory[v2];
        break;
    }
}

void SHR_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch(indices){
    case 0:
        memory[v1] = memory[v1] >> v2;
        break;
    case 1:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] >> v2;
        break;
    case 2:
		memory[v1] = memory[v1] >> registers[REGISTER(v2)];
        break;
    case 3:
		registers[REGISTER(v1)] = registers[REGISTER(v1)] >> registers[REGISTER(v2)];
        break;
    case 4:
        memory[v1] = memory[v1] >> memory[v2];
        break;
    case 5:
        registers[REGISTER(v1)] = registers[REGISTER(v1)] >> memory[v2];
        break;
    }
}

void INT_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    if (v1 == 0)
        (*ivt[v1])();
}

void CALL_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    stack_push(registers[IP]);
    registers[IP] = v1 - 12;
}

void JMP_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    registers[IP] = v1 - 12;
    // printf("%04X : %04X\n", memory[registers[IP]], registers[IP]);
}

void CMP_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    uint32_t value1;
    uint32_t value2;

    switch (indices){
    case 0:{
        value1 = v1;
        value2 = v2;

        break;
    }

    case 1:{
        value1 = registers[REGISTER(v1)];
        value2 = v2;
        
        break;
    }

    case 2:{
        value1 = v1;
        value2 = registers[REGISTER(v1)];
        
        break;
    }

    case 3:{
        value1 = registers[REGISTER(v1)];
        value2 = registers[REGISTER(v2)];
        
        break;
    }

    case 4:{
        value1 = memory[v1];
        value2 = memory[v2];

        break;
    }

    case 5:{
        value1 = registers[REGISTER(v1)];
        value2 = memory[v2];
        
        break;
    }
    }

    if (value1 == value2)
        FLAG_SET(EQUAL_FLAG, 1)
    else
        FLAG_SET(EQUAL_FLAG, 0)

    if (value1 > value2)
        FLAG_SET(GREATER_FLAG, 1)
    else
        FLAG_SET(GREATER_FLAG, 0)

    if (value1 >= value2)
        FLAG_SET(GREATER_EQU_FLAG, 1)
    else
        FLAG_SET(GREATER_EQU_FLAG, 0)

    // Implement Zero Flag and Carry Flag
}

void JE_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    if (FLAG(EQUAL_FLAG))
        JMP_OPERATOR(0, v1, 0);
}

void JNE_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    if (!FLAG(EQUAL_FLAG))
        JMP_OPERATOR(0, v1, 0);
}

void JG_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    if (FLAG(GREATER_FLAG))
        JMP_OPERATOR(0, v1, 0);
}

void JGE_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    if (FLAG(GREATER_EQU_FLAG))
        JMP_OPERATOR(0, v1, 0);
}

void JL_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    if (!FLAG(GREATER_FLAG))
        JMP_OPERATOR(0, v1, 0);
}

void JLE_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    if (!FLAG(GREATER_EQU_FLAG))
        JMP_OPERATOR(0, v1, 0);
}

// void JZ_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
//     if (flags[ZERO_FLAG])
//         JMP_OPERATOR(0, v1, 0);
// }

// void JNZ_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
//     if (!flags[ZERO_FLAG])
//         JMP_OPERATOR(0, v1, 0);
// }

// void JC_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
//     if (flags[CARRY_FLAG])
//         JMP_OPERATOR(0, v1, 0);
// }

// void JNC_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
//     if (!flags[CARRY_FLAG])
//         JMP_OPERATOR(0, v1, 0);
// }

void RET_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    registers[IP] = stack[registers[SP]]; // Should always be address to return to, need to figure out better solution later
    stack[registers[SP]] = 0;
    registers[SP]--;
}