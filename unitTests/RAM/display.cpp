#include "../../RAM.h"
#include "../../CPU.h"
#include "../../Chip8.h"
#include <cstdint>
#include <iostream>
#include <bits/stdc++.h>
#include <iostream>

using namespace chip8VM;


int main(){

	Chip8 chip8;

	//chip8.loadRom("test_opcode.ch8");
	//chip8.loadRom("IBMLogo.ch8");
	//chip8.loadRom("Maze.ch8");
	chip8.loadRom("Pong.ch8");

	chip8.run();


}
