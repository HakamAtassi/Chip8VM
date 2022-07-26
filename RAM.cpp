#include "RAM.h"
#include <cstdint>
#include <iostream>


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

void chip8VM::RAM::print(){
	for(int i=0;i<4096;i++){
		std::cout<<(int)read(i)<<", ";
	}
	std::cout<<"\n";
}
