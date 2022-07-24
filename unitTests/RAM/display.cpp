#include "../../RAM.h"
#include "../../CPU.h"
#include <cstdint>
#include <iostream>




using namespace chip8VM;


int main(){


    chip8VM::RAM ram;
    chip8VM::CPU cpu(ram);
    

    ram.write(0x0000, 0xF0);
    ram.write(0x0001, 0x90);
    ram.write(0x0002, 0x90);
    ram.write(0x0003, 0x90);
    ram.write(0x0004, 0xF0);
    

    


}
