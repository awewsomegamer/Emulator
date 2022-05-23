#include <interrupts.h>
#include <emulator.h>
#include <screen.h>
#include <IO.h>

// Set pointers of the IVT to the proper functions
void init_ivt(){
    ivt[0] = ivt_0;
    ivt[1] = ivt_1;
    ivt[2] = ivt_2;
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
