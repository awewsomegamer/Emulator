#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <emulator.h>
#include <stdarg.h>

void e_fatal(char* message, char* file, int line, ...);
void e_error(char* message, char* file, int line, ...);

#endif