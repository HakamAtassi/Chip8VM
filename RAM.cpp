#include "RAM.h"
#include <cstdint>



chip8VM::RAM::RAM(){
    memory.reserve(4096);   //to maintain realism, do not initialize memory 
}

uint8_t chip8VM::RAM::read(uint16_t PC){
    return memory[PC];
}  


void chip8VM::RAM::write(uint16_t PC, uint8_t val){
    
    memory[PC]=val;


    return;
}
