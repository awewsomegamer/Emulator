#include <bus.h>
#include <error_handler.h>

#define IS_ROM(address) ((address >= ROM_START) && (address <= ROM_END))

uint8_t read_address_b(int address){
	return memory[address];	
}

uint16_t read_address_w(int address){
	return (read_address_b(address) << 8) | read_address_b(address + 1);
}

uint32_t read_address_d(int address){
	return (read_address_w(address) << 16) | read_address_w(address + 2);
}

void write_address_b(int address, uint8_t value){
	if (IS_ROM(address)){
		e_error("Tried to write to ROM address");
		return;
	}

	memory[address] = value;
}

void write_address_w(int address, uint16_t value){
	write_address_b(address, value & 0xFF);
	write_address_b(address + 1, (value >> 8) & 0xFF);
}

void write_address_d(int address, uint32_t value){
	write_address_w(address, value & 0xFFFF);
	write_address_w(address + 2, (value >> 16) & 0xFFFF);
}
