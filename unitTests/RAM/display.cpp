#include "../../RAM.h"
#include "../../CPU.h"
#include "../../Chip8.h"
#include <cstdint>
#include <iostream>

using namespace chip8VM;


int main(){

	RAM ram;

	ram.write(0x0200,0x05);
	ram.write(0x0201,0xD0);
	ram.write(0x0000,0xF0);
	ram.write(0x0001,0x80);
	ram.write(0x0002,0xF0);
	ram.write(0x0003,0x80);
	ram.write(0x0004,0x80);
	ram.write(0x0202,0xFF);	
	ram.write(0x0203,0xFF);	

	std::vector<bool> * videoMemory=new std::vector<bool>(2048,0);
	


	Chip8 chip8(ram,videoMemory);


	chip8.createWindow();
	chip8.run();


}
