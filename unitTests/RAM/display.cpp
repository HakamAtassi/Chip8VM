#include "../../RAM.h"
#include "../../CPU.h"
#include "../../Chip8.h"
#include <cstdint>
#include <iostream>
#include <bits/stdc++.h>
#include <iostream>

using namespace chip8VM;


int main(){


	time_t start, end;
    time(&start);
    std::ios_base::sync_with_stdio(false);
	

	RAM * ram=new RAM();
	//ram->loadRom("IBMLogo.ch8");
	ram->loadRom("Pong.ch8");

	std::vector<bool> * videoMemory=new std::vector<bool>(2048,0);
	std::vector<bool> * keyboardInput=new std::vector<bool>(127,0);
	
	Chip8 chip8(ram,videoMemory,keyboardInput);

	//chip8.printRam();



	chip8.createWindow();
	chip8.run();




	free(videoMemory);
	free(keyboardInput);
	free(ram);

	time(&end);

	    double time_taken = double(end - start);
    std::cout << "Time taken by program is : " << std::fixed
         << time_taken << std::setprecision(5);
    std::cout << " sec " << std::endl;

}
