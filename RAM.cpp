#include "RAM.h"
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>

#define START_ADDRESS 0x0200
#define FONTSET_ADDRESS 0x50


chip8VM::RAM::RAM(){
    memory=std::vector<uint8_t>(4096,0);   //to maintain realism, do not initialize memory 
}

uint8_t chip8VM::RAM::read(uint16_t PC){
    return memory[PC];
}

void chip8VM::RAM::write(uint16_t PC, uint8_t val){
    memory[PC]=val;
    return;
}


