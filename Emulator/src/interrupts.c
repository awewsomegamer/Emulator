#include <interrupts.h>
#include <emulator.h>

void init_ivt(){

}

// Temporary print(AX)
void ivt_0(){
    printf("%c", registers[A]);
}