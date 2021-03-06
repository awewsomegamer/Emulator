#include <util.h>
#include <ctype.h>
#include <emulator.h>

bool startsWith(const char* str, const char* lookfor){
	if (strncmp(str, lookfor, strlen(lookfor)) == 0)
		return true;

	return false;
}

bool containsCharacter(char* line, char c){
	int contains_c = 0;

	for (int i = 0; i < strlen(line); i++) {
		if (*(line + i) == c){
			contains_c = 1;
			break;
		}
	}
}

// 0b included
int strToBinary(char* line){
	int result = 0;

	int multiplier = 1;
	for (size_t i = strlen(line)-1; i >= 2; i--){
		if (i <= 0) break;

		if (*(line+i) == '1')
			result += multiplier;

		multiplier *= 2;
	}

	return result/2;
}

void removeCharacter(char* line, char c){
	if (containsCharacter(line, c)){
		char* tmp = malloc(strlen(line));
		strcpy(tmp, line);
		memset(line, 0, strlen(tmp));

		int line_clean_i = 0;
		for (int i = 0; i < strlen(tmp); i++){
			if (*(tmp + i) != c){
				*(line + line_clean_i) = *(tmp + i);
				line_clean_i++;
			}
		}

		memset(tmp, 0, strlen(tmp));
		free(tmp);
	}
}

void stack_push(uint32_t value){
	memory[registers[SP]++] = value 		& 0xFF;
	memory[registers[SP]++] = value >> 8 	& 0xFF;
	memory[registers[SP]++] = value >> 16 	& 0xFF;
	memory[registers[SP]++] = value >> 24 	& 0xFF;
}

uint32_t stack_pop(){
	registers[SP] -= 4;

	uint32_t ret = memory[registers[SP]] | memory[registers[SP] + 1] << 8 | memory[registers[SP] + 2] << 16 |memory[registers[SP] + 3] << 24;

	memory[registers[SP]] = 0;
	memory[registers[SP] + 1] = 0;
	memory[registers[SP] + 2] = 0;
	memory[registers[SP] + 3] = 0;

	return ret;
}
