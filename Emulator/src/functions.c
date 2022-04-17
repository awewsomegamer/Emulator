#include <functions.h>
#include <emulator.h>

#define REGISTER(value) (value / 16 - 1)
#define FLAG(flag) ((flags >> flag) & 0x1)
#define FLAG_SET(flag, value) flags ^= (-value ^ flags) & (1 << flag);

// Set pointers of the operator functions table to the proper functions
void init_operator_functions(){
    // These take two arguments, and require indices in most cases
    operation_fuctions[MOV] = MOV_OPERATOR;
    operation_fuctions[SUB] = SUB_OPERATOR;
    operation_fuctions[ADD] = ADD_OPERATOR;
    operation_fuctions[DIV] = DIV_OPERATOR;
    operation_fuctions[MUL] = MUL_OPERATOR;
    operation_fuctions[AND] = AND_OPERATOR;
    operation_fuctions[OR] = OR_OPERATOR;
    operation_fuctions[XOR] = XOR_OPERATOR;
    operation_fuctions[NOT] = NOT_OPERATOR;
    operation_fuctions[SHL] = SHL_OPERATOR;
    operation_fuctions[SHR] = SHR_OPERATOR;

    // These only have one argument which should just be a label or address (doesn't require index logic)
    operation_fuctions[INT] = INT_OPERATOR; // This one takes a value, no address
    operation_fuctions[CALL] = CALL_OPERATOR;
    operation_fuctions[JMP] = JMP_OPERATOR;
    operation_fuctions[CMP] = CMP_OPERATOR;
    operation_fuctions[JE] = JE_OPERATOR;
    operation_fuctions[JNE] = JNE_OPERATOR;
    operation_fuctions[JG] = JG_OPERATOR; // JZ
    operation_fuctions[JGE] = JGE_OPERATOR; // JNZ
    operation_fuctions[JL] = JL_OPERATOR; // JC
    operation_fuctions[JLE] = JLE_OPERATOR; // JNC

    // These takes no arguments
    operation_fuctions[NOP] = NOP_OPERATOR;
    operation_fuctions[RET] = RET_OPERATOR;
}

void NOP_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2) { 
    return;
}

void MOV_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch (indices){
    // mov [0x100], 100
    // mov 0x100, 100
    case 0x00:
    case 0x03:
        memory[v1] = v2;
        break;

    // mov [0x100], ax
    // mov 0x100, ax
    case 0x10:
    case 0x13:
        memory[v1] = registers[REGISTER(v2)];
        break;

    // mov [0x100], [ax]
    // mov 0x100, [ax]
    case 0x23:
	case 0x20:
        memory[v1] = memory[registers[REGISTER(v2)]];
        break;

    // mov [ax], [bx]
    case 0x22:
        memory[registers[REGISTER(v1)]] = memory[registers[REGISTER(v2)]];
        break;

    // mov [ax], bx
    case 0x12:
        memory[registers[REGISTER(v1)]] = registers[REGISTER(v2)];
        break;

    // mov ax, bx
    case 0x11:
        registers[REGISTER(v1)] = registers[REGISTER(v2)];
        break;

    // mov ax, 100
    case 0x01:
        registers[REGISTER(v1)] = v2;
        break;
    
    // mov ax, [bx]
    case 0x21:
        registers[REGISTER(v1)] = memory[registers[REGISTER(v2)]];
        break;
    }
}

void SUB_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch (indices){
    case 0x00:
    case 0x03:
        memory[v1] -= v2;
        break;

    case 0x10:
    case 0x13:
        memory[v1] -= registers[REGISTER(v2)];
        break;

    case 0x23:
	case 0x20:
        memory[v1] -= memory[registers[REGISTER(v2)]];
        break;

    case 0x22:
        memory[registers[REGISTER(v1)]] -= memory[registers[REGISTER(v2)]];
        break;

    case 0x12:
        memory[registers[REGISTER(v1)]] -= registers[REGISTER(v2)];
        break;

    case 0x11:
        registers[REGISTER(v1)] -= registers[REGISTER(v2)];
        break;

    case 0x01:
        registers[REGISTER(v1)] -= v2;
        break;

    case 0x21:
        registers[REGISTER(v1)] -= memory[registers[REGISTER(v2)]];
        break;
    }
}

void ADD_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch (indices){
    case 0x00:
    case 0x03:
        memory[v1] += v2;
        break;

    case 0x10:
    case 0x13:
        memory[v1] += registers[REGISTER(v2)];
        break;

    case 0x23:
	case 0x20:
        memory[v1] += memory[registers[REGISTER(v2)]];
        break;

    case 0x22:
        memory[registers[REGISTER(v1)]] += memory[registers[REGISTER(v2)]];
        break;

    case 0x12:
        memory[registers[REGISTER(v1)]] += registers[REGISTER(v2)];
        break;

    case 0x11:
        registers[REGISTER(v1)] += registers[REGISTER(v2)];
        break;

    case 0x01:
        registers[REGISTER(v1)] += v2;
        break;

    case 0x21:
        registers[REGISTER(v1)] += memory[registers[REGISTER(v2)]];
        break;
    }
}

void DIV_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch (indices){
    case 0x00:
    case 0x03:
        memory[v1] /= v2;
        break;

    case 0x10:
    case 0x13:
        memory[v1] /= registers[REGISTER(v2)];
        break;

    case 0x23:
	case 0x20:
        memory[v1] /= memory[registers[REGISTER(v2)]];
        break;

    case 0x22:
        memory[registers[REGISTER(v1)]] /= memory[registers[REGISTER(v2)]];
        break;

    case 0x12:
        memory[registers[REGISTER(v1)]] /= registers[REGISTER(v2)];
        break;

    case 0x11:
        registers[REGISTER(v1)] /= registers[REGISTER(v2)];
        break;

    case 0x01:
        registers[REGISTER(v1)] /= v2;
        break;

    case 0x21:
        registers[REGISTER(v1)] /= memory[registers[REGISTER(v2)]];
        break;
    }
}

void MUL_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch (indices){
    case 0x00:
    case 0x03:
        memory[v1] *= v2;
        break;

    case 0x10:
    case 0x13:
        memory[v1] *= registers[REGISTER(v2)];
        break;

    case 0x23:
	case 0x20:
        memory[v1] *= memory[registers[REGISTER(v2)]];
        break;

    case 0x22:
        memory[registers[REGISTER(v1)]] *= memory[registers[REGISTER(v2)]];
        break;

    case 0x12:
        memory[registers[REGISTER(v1)]] *= registers[REGISTER(v2)];
        break;

    case 0x11:
        registers[REGISTER(v1)] *= registers[REGISTER(v2)];
        break;

    case 0x01:
        registers[REGISTER(v1)] *= v2;
        break;

    case 0x21:
        registers[REGISTER(v1)] *= memory[registers[REGISTER(v2)]];
        break;
    }
}

void AND_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch (indices){
    case 0x00:
    case 0x03:
        memory[v1] &= v2;
        break;

    case 0x10:
    case 0x13:
        memory[v1] &= registers[REGISTER(v2)];
        break;

    case 0x23:
	case 0x20:
        memory[v1] &= memory[registers[REGISTER(v2)]];
        break;

    case 0x22:
        memory[registers[REGISTER(v1)]] &= memory[registers[REGISTER(v2)]];
        break;

    case 0x12:
        memory[registers[REGISTER(v1)]] &= registers[REGISTER(v2)];
        break;

    case 0x11:
        registers[REGISTER(v1)] &= registers[REGISTER(v2)];
        break;

    case 0x01:
        registers[REGISTER(v1)] &= v2;
        break;

    case 0x21:
        registers[REGISTER(v1)] &= memory[registers[REGISTER(v2)]];
        break;
    }
}

void OR_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch (indices){
    case 0x00:
    case 0x03:
        memory[v1] |= v2;
        break;

    case 0x10:
    case 0x13:
        memory[v1] |= registers[REGISTER(v2)];
        break;

    case 0x23:
	case 0x20:
        memory[v1] |= memory[registers[REGISTER(v2)]];
        break;

    case 0x22:
        memory[registers[REGISTER(v1)]] |= memory[registers[REGISTER(v2)]];
        break;

    case 0x12:
        memory[registers[REGISTER(v1)]] |= registers[REGISTER(v2)];
        break;

    case 0x11:
        registers[REGISTER(v1)] |= registers[REGISTER(v2)];
        break;

    case 0x01:
        registers[REGISTER(v1)] |= v2;
        break;

    case 0x21:
        registers[REGISTER(v1)] |= memory[registers[REGISTER(v2)]];
        break;
    }
}

void XOR_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch (indices){
    case 0x00:
    case 0x03:
        memory[v1] ^= v2;
        break;

    case 0x10:
    case 0x13:
        memory[v1] ^= registers[REGISTER(v2)];
        break;

    case 0x23:
	case 0x20:
        memory[v1] ^= memory[registers[REGISTER(v2)]];
        break;

    case 0x22:
        memory[registers[REGISTER(v1)]] ^= memory[registers[REGISTER(v2)]];
        break;

    case 0x12:
        memory[registers[REGISTER(v1)]] ^= registers[REGISTER(v2)];
        break;

    case 0x11:
        registers[REGISTER(v1)] ^= registers[REGISTER(v2)];
        break;

    case 0x01:
        registers[REGISTER(v1)] ^= v2;
        break;

    case 0x21:
        registers[REGISTER(v1)] ^= memory[registers[REGISTER(v2)]];
        break;
    }
}

void NOT_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch (indices){
    case 0x00:
    case 0x03:
    case 0x10:
    case 0x13:
    case 0x23:
	case 0x20:
        memory[v1] = ~memory[v1];
        break;

    case 0x22:
    case 0x12:
        memory[registers[REGISTER(v1)]] = ~memory[registers[REGISTER(v1)]];
        break;

    case 0x11:
    case 0x01:
    case 0x21:
        registers[REGISTER(v1)] = ~registers[REGISTER(v1)];
        break;
    }
}

void SHL_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch (indices){
    case 0x00:
    case 0x03:
        memory[v1] <<= v2;
        break;

    case 0x10:
    case 0x13:
        memory[v1] <<= registers[REGISTER(v2)];
        break;

    case 0x23:
	case 0x20:
        memory[v1] <<= memory[registers[REGISTER(v2)]];
        break;

    case 0x22:
        memory[registers[REGISTER(v1)]] <<= memory[registers[REGISTER(v2)]];
        break;

    case 0x12:
        memory[registers[REGISTER(v1)]] <<= registers[REGISTER(v2)];
        break;

    case 0x11:
        registers[REGISTER(v1)] <<= registers[REGISTER(v2)];
        break;

    case 0x01:
        registers[REGISTER(v1)] <<= v2;
        break;

    case 0x21:
        registers[REGISTER(v1)] <<= memory[registers[REGISTER(v2)]];
        break;
    }
}

void SHR_OPERATOR(uint8_t indices, uint32_t v1, uint32_t v2){
    switch (indices){
    case 0x00:
    case 0x03:
        memory[v1] >>= v2;
        break;

    case 0x10:
    case 0x13:
        memory[v1] >>= registers[REGISTER(v2)];
        break;

    case 0x23:
	case 0x20:
        memory[v1] >>= memory[registers[REGISTER(v2)]];
        break;

    case 0x22:
        memory[registers[REGISTER(v1)]] >>= memory[registers[REGISTER(v2)]];
        break;

    case 0x12:
        memory[registers[REGISTER(v1)]] >>= registers[REGISTER(v2)];
        break;

    case 0x11:
        registers[REGISTER(v1)] >>= registers[REGISTER(v2)];
        break;

    case 0x01:
        registers[REGISTER(v1)] >>= v2;
        break;

    case 0x21:
        registers[REGISTER(v1)] >>= memory[registers[REGISTER(v2)]];
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

    // Determine value of the first argument
    switch(indices & 0xF){
    case 0:
        value1 = v1;
        break;
    case 1:
        value1 = registers[REGISTER(v1)];
        break;
    case 2:
        value1 = memory[registers[REGISTER(v1)]];
        break;
    case 3:
        value1 = memory[v1];
        break;
    }

    // Determine the value of the second argument
    switch((indices >> 4) & 0xF){
    case 0:
        value2 = v2;
        break;
    case 1:
        value2 = registers[REGISTER(v2)];
        break;
    case 2:
        value2 = memory[registers[REGISTER(v2)]];
        break;
    case 3:
        value2 = memory[v2];
        break;
    }

    // Preform logic and set proper flags
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