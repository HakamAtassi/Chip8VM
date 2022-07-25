#include "../../RAM.h"
#include "../../CPU.h"
#include "../../Chip8.h"
#include <cstdint>
#include <iostream>




using namespace chip8VM;


int main(){


    

	RAM * ram=new RAM();

	
    ram->write(0x0000, 0xF0);
    ram->write(0x0001, 0x90);
    ram->write(0x0002, 0x90);
    ram->write(0x0003, 0x90);
    ram->write(0x0004, 0xF0);
    
	
/*
	for(int i=0;i<4096;i++){
		ram->write(i,1);
	}
*/
	
    
	

	Chip8 chip8(ram);

	//std::cout<<(int)ram->read(0)<<"\n";


	chip8.createWindow();
	chip8.drawScreen(0,0);

	//chip8.printRam();

}
