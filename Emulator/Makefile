CSTUFF := $(wildcard src/*.c)
CC := gcc
CFLAGS := -I ./src/include/ -Wall -Wl,--allow-multiple-definition

all: $(OSTUFF) 
	$(CC) $(CFLAGS) $(CSTUFF) -o emulator.out
	