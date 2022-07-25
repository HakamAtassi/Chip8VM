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

	std::vector<bool> * videoMemory=new std::vector<bool>(2048,0);


/*
	videoMemory[0]=1; videoMemory[1]=1; videoMemory[2]=1;videoMemory[3]=1;
	videoMemory[64]=1; 									 videoMemory[67]=1;
	videoMemory[128]=1; 							     videoMemory[131]=1;
	videoMemory[192]=1; 							     videoMemory[195]=1;
	videoMemory[192+64]=1; 							     videoMemory[195+64]=1;
	videoMemory[256+64]=1; videoMemory[257+64]=1; videoMemory[258+64]=1;videoMemory[259+64]=1;
	*/
	


	Chip8 chip8(ram,videoMemory);

	chip8.setRegister(0,0x44);
	chip8.setRegister(1,0xFF);




	chip8.createWindow();
	chip8.run();


}
