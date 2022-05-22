#include <emulator.h>
#include <functions.h>
#include <interrupts.h>
#include <stdbool.h>
#include <assert.h>
#include <screen.h>
#include <IO.h>
#include <sys/time.h>

void print_regs(){
	printf("-= REGISTER DUMP =-\n");
	printf("+-AX : %X\n", registers[0]);
	printf("+-BX : %X\n", registers[1]);
	printf("+-CX : %X\n", registers[2]);
	printf("+-DX : %X\n", registers[3]);
	printf("+-IP : %X\n", registers[4]);
	printf("+-SP : %X\n", registers[5]);
	printf("+-BP : %X\n", registers[6]);
	printf("+-I1 : %X\n", registers[7]);
	printf("+-I2 : %X\n", registers[8]);
	printf("+-I3 : %X\n", registers[9]);
	printf("+-I4 : %X\n", registers[10]);
}

int run_window(void* arg){
	init_window();

	while (running){
		update();
		// render();
	}	

	return 0;
}

int main(int argc, char* argv[]){
	FILE* in_file;
	bool in_file_set = false;
	int start_address = 0;
	uint64_t max_memory = UINT16_MAX;

	// Interpret arguments
	for (int i = 1; i < argc; i++){
		if (startsWith(argv[i], "-i")){
        	in_file = fopen(argv[i+1], "r");
			in_file_set = true;
		}

		if (startsWith(argv[i], "-org"))
			start_address = atoi(argv[i+1]);

		if (startsWith(argv[i], "-mmax")){
			if (startsWith(argv[i+1], "h"))
				max_memory = strtol(argv[i+2], NULL, 16);
			else
				max_memory = atoi(argv[i+1]);
		}

		if (startsWith(argv[i], "-h")){
			printf("Visit https://github.com/awewsomegamer/Emulator/blob/main/README.md#cli-usage\n");
			return 0;
		}

	}

	// Initialize memory and stack
	memory = (uint8_t*)malloc(max_memory * sizeof(uint32_t));
	ports = (uint8_t*)malloc(1024 * sizeof(uint32_t));
	// stack = (uint8_t*)malloc(8129 * sizeof(uint32_t));

	if (in_file_set == false){
		printf("No program was specified\n");
		return 1;
	}

	long file_length = 0;
	fseek(in_file, 0, SEEK_END);
	file_length = ftell(in_file);

	rewind(in_file);

	if (max_memory * sizeof(uint32_t) < file_length){
		printf("%08lX bytes of memory not enough to hold program\n", max_memory);
		return 1;
	}

	// Load specified file into memory

	memset(memory, 0, max_memory);

	for (int i = 0; i <= file_length; i++)
		fread((memory+i+start_address), 1, 1, in_file);

	// Initialize interrupt vector table and function pointers of each operator
	init_ivt();
	init_operator_functions();

	// While program is running, read bytes of memory at IP, and call proper operation
	SDL_Thread* window_thread = SDL_CreateThread(run_window, "WINDOW_THREAD", NULL);
	
	// int64_t ticks = 0;
	// time_t now_time = time(NULL);
	// time_t last_time = time(NULL);
	
	while (running){
		uint8_t operation =  *(memory + registers[IP]);
		uint8_t indices =  *(memory + registers[IP]+1);
		uint32_t v1 = *(memory + registers[IP]+7) << 24 | *(memory + registers[IP]+6) << 16 | *(memory + registers[IP]+5) << 8 | *(memory + registers[IP]+4);
		uint32_t v2 = *(memory + registers[IP]+11) << 24 | *(memory + registers[IP]+10) << 16 | *(memory + registers[IP]+9) << 8 | *(memory + registers[IP]+8);

		// printf("%X %X %X %X\n", operation, indices, v1, v2);
		(*operation_fuctions[operation])(indices, v1, v2);

		registers[IP] += 12;
		// printf("IA: %X:\n", registers[IP]);


		// printf("M 0x1000: %d R A: %d M R C: %d M R B: %c / %d O: %s\n", memory[0x1000], registers[A], memory[registers[C]], memory[registers[B]], memory[registers[B]], OPERATION_T_NAMES[operation]);

		// print_regs();

		// ticks++;

		// Temporary emulator execution termination
		// if (registers[IP] >= file_length + 12)
		// 	running = false;

		// now_time = time(NULL);

		// if (now_time - last_time >= 1){
		// 	printf("%ld TPS\n", ticks);
		// 	ticks = 0;
		// 	last_time = now_time;
		// }

		if (registers[IP] >= max_memory)
			registers[IP] = 0;
	}

	SDL_WaitThread(window_thread, NULL);
	SDL_Quit();

	free(memory);
	// free(stack);

	return 0;
}
