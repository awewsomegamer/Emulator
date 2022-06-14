#include <error_handler.h>

void e_fatal(char* message){
	printf("[FATAL]: %s", message);
	exit(1);
}

void e_error(char* message){
	printf("[ERROR]: %s (%d)", message);
}
