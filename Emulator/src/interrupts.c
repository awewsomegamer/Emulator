#include <interrupts.h>
#include <emulator.h>
#include <screen.h>
#include <IO.h>
#include <stdbool.h>

bool defined_interrupts[256];
uint32_t defined_interrupt_ptrs[256];

// Set pointers of the IVT to the proper functions
void init_ivt(){
    for (int i = 0; i < 256; i++){
        defined_interrupts[i] = false;
        defined_interrupt_ptrs[i] = 0;
    }

    ivt[TIMER_INT] = IVT_NOP;
    ivt[PRINT_INT] = IVT_0; // Screen functions
    ivt[DISK_IO_INT] = IVT_1; // Disk functions
    ivt[KEYBOARD_INT] = IVT_NOP; // Keyboard interrupt
}

void define_interrupt(int interrupt, int address){
    defined_interrupts[interrupt] = 1;
    defined_interrupt_ptrs[interrupt] = address;
}

void undefine_interrupt(int interrupt){
    defined_interrupts[interrupt] = 0;
    defined_interrupt_ptrs[interrupt] = 0;
}

void call_interrupt(int interrupt){
    if (defined_interrupts[interrupt]){
        stack_push(registers[IP]);
        registers[IP] = defined_interrupt_ptrs[interrupt];
    }else{
        (*ivt[interrupt])();
    }
}

void IVT_NOP(){ }

// Temporary print(AX)
// AX Char / uint16_t x | uint16_t y
// BX Mode

void IVT_0(){
    printf("CALLED MODE 0 INT 0\n");

    switch (registers[B]){
    case 1: // Set current cursor position
        set_cursor_position((registers[A] >> 16) & 0xFFFF, registers[A] & 0xFFFF);

        break;

    case 2: // Get current cursor position
        registers[A] = get_cursor_position();

        break;

    case 3: // Print int
        char number_string[64];
        sprintf(number_string, "%d", registers[A]);
        for (int i = 0; i < strlen(number_string); i++)
            sputc(number_string[i]);

        break;

    case 4: // Put pixel
        // I1 -> (X << 16)  | Y
        // I2 -> 0xRRGGBBAA

        draw_pixel(registers[I1], registers[I2]);

        break;

    case 0:
        char c = registers[A];

        switch (c){
        case '\n': 
            cursor_x = 0;
            cursor_y += GLYPH_HEIGHT;

            break;

        default:
            sputc(c);
            break;
        }
    
    }    
}

// Disk functions
// AX - 0 = read, 1 = write
// BX - Buffer pointer (where to write / read from)
// CX - Start Sector
// DX - Sector count
// I1 - Will be later used for disk specific

void IVT_1(){
    fseek(disk, registers[C] * 512, SEEK_SET);
    
    if (!registers[A])
        fread(memory + registers[B], registers[D] * 512, 1, disk);
    else
        fwrite(memory + registers[B], registers[D] * 512, 1, disk);
}