#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <util.h>

#define LINE_SIZE 256

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

	fwrite((bytes), file_length, sizeof(bytes), out_file_test);

	free(bytes);

	return 0;
}
