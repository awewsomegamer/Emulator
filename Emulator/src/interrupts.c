#include <interrupts.h>
#include <emulator.h>

// Set pointers of the IVT to the proper functions
void init_ivt(){
    ivt[0] = ivt_0;
}

// Temporary print(AX)
void ivt_0(){
    printf("%c", registers[A]);
}