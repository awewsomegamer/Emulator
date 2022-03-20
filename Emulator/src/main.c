#include <emulator.h>

void print_regs(){
	printf("-= REGISTER DUMP =-\n");
	printf("+-AX : %d\n", registers[0]);
	printf("+-BX : %d\n", registers[1]);
	printf("+-CX : %d\n", registers[2]);
	printf("+-DX : %d\n", registers[3]);
	printf("+-IP : %d\n", registers[4]);
	printf("+-SP : %d\n", registers[5]);
	printf("+-BP : %d\n", registers[6]);
	printf("+-I1 : %d\n", registers[7]);
	printf("+-I2 : %d\n", registers[8]);
	printf("+-I3 : %d\n", registers[9]);
	printf("+-I4 : %d\n", registers[10]);
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

	for (int i = 0; i < file_length; i+=12){
		uint8_t operation =  *(bytes + i);
		uint8_t indices =  *(bytes + i+1);
		uint32_t v1 = *(bytes + i+7) << 16 | *(bytes + i+6) << 12 | *(bytes + i+5) << 8 | *(bytes + i+4);
		uint32_t v2 = *(bytes + i+11) << 16 | *(bytes + i+10) << 12 | *(bytes + i+9) << 8 | *(bytes + i+8);

		if (operation == 1){
			if (indices == 0){
				// value 1 == register
				registers[v1 / 16 - 1] = v2;
			}

			if (indices == 1) {
				// value 2 == register
			}

			if (indices == 2){
				// both values are registers
				registers[v1 / 16 - 1] = registers[v2 / 16 - 1];
			}
		}

		print_regs();
	}

	free(bytes);

	return 0;
}
