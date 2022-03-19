#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <util.h>

#define LINE_SIZE 256

typedef union {
	struct {
		uint32_t ax;
		uint32_t bx;
		uint32_t cx;
		uint32_t dx;
		uint32_t ip;
		uint32_t sp;
		uint32_t bp;
		uint32_t i1;
		uint32_t i2;
		uint32_t i3;
		uint32_t i4;
	};
	uint32_t registers[11];
} REGISTERS_T;

void print_regs(REGISTERS_T regs){
	printf("-= REGISTER DUMP =-\n");
	printf("+-AX : %d\n", regs.ax);
	printf("+-BX : %d\n", regs.bx);
	printf("+-CX : %d\n", regs.cx);
	printf("+-DX : %d\n", regs.dx);
	printf("+-IP : %d\n", regs.ip);
	printf("+-SP : %d\n", regs.sp);
	printf("+-BP : %d\n", regs.bp);
	printf("+-I1 : %d\n", regs.i1);
	printf("+-I2 : %d\n", regs.i2);
	printf("+-I3 : %d\n", regs.i3);
	printf("+-I4 : %d\n", regs.i4);
}

int main(int argc, char* argv[]){
	FILE* in_file;
	FILE* out_file_test;
	out_file_test = fopen("outtest.out", "w");

	for (int i = 1; i < argc; i++)
		if (startsWith(argv[i], "-i"))
			in_file = fopen(argv[i+1], "r");

	long file_length = 0;
	fseek(in_file, 0, SEEK_END);
	file_length = ftell(in_file);
	rewind(in_file);

	uint8_t* bytes = (uint8_t*)malloc(sizeof(uint8_t)*(file_length+1));

	for (int i = 0; i < file_length; i++)
		fread((bytes+i), 1, 1, in_file);

	REGISTERS_T regs;

	for (int i = 0; i < 11; i++)
		regs.registers[i] = 0;

	for (int i = 0; i < file_length; i+=12){
		uint8_t operation =  *(bytes + i);
		uint8_t indices =  *(bytes + i+1);
		uint32_t v1 = *(bytes + i+7) << 16 | *(bytes + i+6) << 12 | *(bytes + i+5) << 8 | *(bytes + i+4);
		uint32_t v2 = *(bytes + i+11) << 16 | *(bytes + i+10) << 12 | *(bytes + i+9) << 8 | *(bytes + i+8);

		if (operation == 1){
			if (indices == 0){
				// value 1 == register
				regs.registers[v1 / 16 - 1] = v2;
			}

			if (indices == 1) {
				// value 2 == register
			}

			if (indices == 2){
				// both values are registers
				regs.registers[v1 / 16 - 1] = regs.registers[v2 / 16 - 1];
			}
		}

		print_regs(regs);
	}

	free(bytes);

	return 0;
}
