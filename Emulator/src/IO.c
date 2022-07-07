#include <IO.h>
#include <interrupts.h>
#include <emulator.h>

void outb(uint16_t address, uint8_t value){
	ports[address] = value;
}

uint8_t inb(uint16_t address){
	return ports[address];
}

void outw(uint16_t address, uint16_t value){
	outb(address, value & 0xFF);
	outb(address + 1, (value >> 8) & 0xFF);
}

uint16_t inw(uint16_t address){
	return inb(address) | inb(address + 1) << 8;
}

void outd(uint16_t address, uint32_t value){
	outw(address, value & 0xFFFF);
	outw(address + 2, (value >> 16) & 0xFFFF);
}

uint32_t ind(uint16_t address){
	return inw(address) | inw(address + 2) << 16;
}

void call_hardware_interrupt(int interrupt, int data, int data_size, int data_location){
	switch(data_size){
	case 1:
		outb(data_location, data);
		break;

	case 2:
		outw(data_location, data);
		break;

	case 4:
		outd(data_location, data);
		break;

	default:
		e_error("Invalid size %d", __FILE__, __LINE__);
		break;
	}

	call_interrupt(interrupt);
}