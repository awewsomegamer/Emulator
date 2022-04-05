#include <emulator.h>
#include <functions.h>
#include <interrupts.h>
#include <stdbool.h>
#include <assert.h>

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
	bool in_file_set = false;
	int start_address = 0;
	uint64_t max_memory = UINT16_MAX;

	for (int i = 1; i < argc; i++){
		if (startsWith(argv[i], "-i")){
        	in_file = fopen(argv[i+1], "r");
			in_file_set = true;
		}

		if (startsWith(argv[i], "-org"))
			start_address = atoi(argv[i+1]);

		if (startsWith(argv[i], "-mmax"))
			if (startsWith(argv[i+1], "h"))
				max_memory = strtol(argv[i+2], NULL, 16);
			else
				max_memory = atoi(argv[i+1]);

		if (startsWith(argv[i], "-h")){
			printf("Visit https://github.com/awewsomegamer/Emulator/blob/main/README.md#cli-usage\n");
			return 0;
		}

	}

	memory = (uint8_t*)malloc(max_memory * sizeof(uint32_t));
	stack = (uint8_t*)malloc(8129 * sizeof(uint32_t));

	if (in_file_set == false){
		printf("No program was specified\n");
		return 1;
	}

	long file_length = 0;
	fseek(in_file, 0, SEEK_END);
	file_length = ftell(in_file);

	rewind(in_file);

	if (max_memory * sizeof(uint32_t) < file_length){
		printf("%08X bytes of memory not enough to hold program\n", max_memory);
		return 1;
	}

	for (int i = 0; i < file_length; i++)
		fread((memory+i+start_address), 1, 1, in_file);

	init_ivt();
	init_operator_functions();


	while (true){
		uint8_t operation =  *(memory + registers[IP]);
		uint8_t indices =  *(memory + registers[IP]+1);
		uint32_t v1 = *(memory + registers[IP]+7) << 16 | *(memory + registers[IP]+6) << 12 | *(memory + registers[IP]+5) << 8 | *(memory + registers[IP]+4);
		uint32_t v2 = *(memory + registers[IP]+11) << 16 | *(memory + registers[IP]+10) << 12 | *(memory + registers[IP]+9) << 8 | *(memory + registers[IP]+8);

		// printf("%d %d %d %d\n", operation, indices, v1, v2);
		
		(*operation_fuctions[operation])(indices, v1, v2);

		// print_regs();

		registers[IP] += 12;

		// Temporary emulator execution termination
		if (registers[IP] >= 0x100)
			break;
	}

	free(memory);
	free(stack);

	return 0;
}
