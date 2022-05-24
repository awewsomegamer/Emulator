#include <interrupts.h>
#include <emulator.h>
#include <screen.h>
#include <IO.h>
#include <stdbool.h>

bool defined_interrupts[256];
uint32_t defined_interrupt_ptrs[256];


// Set pointers of the IVT to the proper functions
void init_ivt(){
    ivt[0] = ivt_0;
    ivt[1] = ivt_1;
    ivt[2] = ivt_2;
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

// Temporary print(AX)
void ivt_0(){
    printf("%c", registers[A]);
}

// Place pixel
// AX -> Index (y * WIDTH + x)
// I1 -> 0xAABBGGRR

void ivt_1(){
    // draw_pixel(registers[A], registers[I1]);
}

// Keyboard interrupt
// IO Port 0x0 -> keyboard input
// Defined by user
void ivt_2(){
    
}
