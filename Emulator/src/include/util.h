#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool startsWith(const char* str, const char* lookfor);
bool containsCharacter(char* line, char c);
int strToBinary(char* line);
void removeCharacter(char* line, char c);
void stack_push(uint32_t);
uint32_t stack_pop();

#endif
