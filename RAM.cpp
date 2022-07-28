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

void chip8VM::RAM::print(){

}

void chip8VM::RAM::loadRom(std::string rom){
	std::ifstream file(rom, std::ios::binary | std::ios::ate);

	if (file.is_open())
	{
		std::streampos size = file.tellg();
		char* buffer = new char[size];

		file.seekg(0, std::ios::beg);
		file.read(buffer, size);
		file.close();

		for (long i = 0; i < size; ++i)
		{
			memory[START_ADDRESS + i]=buffer[i];
		}
		delete[] buffer;
	}
}