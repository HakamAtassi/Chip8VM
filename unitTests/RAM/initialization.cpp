#include "../../RAM.h"
#include <cstdint>
#include <iostream>

using namespace chip8VM;

int main(){

    RAM ram;




    for(uint16_t i=0;i<4096;i++){
        std::cout<<ram.read(i)<<" ";
    }

    

}
