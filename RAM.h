#ifndef RAM_H_
#define RAM_H_
#include <vector>
#include <cstdint>
#include <string>

namespace chip8VM{

    class RAM{
        private:
            //4kB (4096 Bytes) of ram
            std::vector<uint8_t> memory;    //just reserve memory during init.  

        public:
            RAM();
            uint8_t read(uint16_t PC);  //reads the value at that exact address 
            void write(uint16_t PC, uint8_t val);   //writes data to address PC. returns nothing
    };

}

#endif  //namespace chip8VM
