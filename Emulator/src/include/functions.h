#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stddef.h>
#include <stdint.h>

void init_operator_functions();

void NOP_OPERATOR(uint8_t, uint32_t, uint32_t);
void MOV_OPERATOR(uint8_t, uint32_t, uint32_t);
void SUB_OPERATOR(uint8_t, uint32_t, uint32_t);
void ADD_OPERATOR(uint8_t, uint32_t, uint32_t);
void DIV_OPERATOR(uint8_t, uint32_t, uint32_t);
void MUL_OPERATOR(uint8_t, uint32_t, uint32_t);
void AND_OPERATOR(uint8_t, uint32_t, uint32_t);
void OR_OPERATOR(uint8_t, uint32_t, uint32_t);
void XOR_OPERATOR(uint8_t, uint32_t, uint32_t);
void NOT_OPERATOR(uint8_t, uint32_t, uint32_t);
void SHL_OPERATOR(uint8_t, uint32_t, uint32_t);
void SHR_OPERATOR(uint8_t, uint32_t, uint32_t);
void SIVTE_OPERATOR(uint8_t, uint32_t, uint32_t);
void RIVTE_OPERATOR(uint8_t, uint32_t, uint32_t);
void INT_OPERATOR(uint8_t, uint32_t, uint32_t);
void CALL_OPERATOR(uint8_t, uint32_t, uint32_t);
void JMP_OPERATOR(uint8_t, uint32_t, uint32_t);
void CMP_OPERATOR(uint8_t, uint32_t, uint32_t);
void JE_OPERATOR(uint8_t, uint32_t, uint32_t);
void JNE_OPERATOR(uint8_t, uint32_t, uint32_t);
void JG_OPERATOR(uint8_t, uint32_t, uint32_t);
void JGE_OPERATOR(uint8_t, uint32_t, uint32_t);
void JL_OPERATOR(uint8_t, uint32_t, uint32_t);
void JLE_OPERATOR(uint8_t, uint32_t, uint32_t);
void JZ_OPERATOR(uint8_t, uint32_t, uint32_t);
void JNZ_OPERATOR(uint8_t, uint32_t, uint32_t);
void JC_OPERATOR(uint8_t, uint32_t, uint32_t);
void JNC_OPERATOR(uint8_t, uint32_t, uint32_t);
void PUSH_OPERATOR(uint8_t, uint32_t, uint32_t);
void POP_OPERATOR(uint8_t, uint32_t, uint32_t);
void RET_OPERATOR(uint8_t, uint32_t, uint32_t);

#endif