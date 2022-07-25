#ifndef CPU_H_
#define CPU_H_
#include "RAM.h"
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <random>

namespace chip8VM{
    
    class CPU{
        

        //Note: data is big-Endian. Largest address is msb

        private:
            
            RAM ram;   //CPU needs a pointer to ram to get instruction
            uint16_t PC=0x0200;   //only lower 3 bytes used (2^12=4096)
            uint16_t SP=0x0000; //stack pointer


            /**RAM RANGES**/
            
            /*
             * 0x000 to 0x1FF Reserved for interpreter
             *
             *
             *        0x200 - 0xFFF => RAM
             * 0x200 Start of (most) Chip8 programs
             *
             * 0x600 Start of ETI 660 Chip8 programs
             *
             * 0xFFF RAM END
             *
             */


            /*              Registers           
            uint8_t V0,                uint8_t V8,
            uint8_t V1,                uint8_t V9,
            uint8_t V2,                uint8_t VA,
            uint8_t V3,                uint8_t VB,
            uint8_t V4,                uint8_t VC,
            uint8_t V5,                uint8_t VD,
            uint8_t V6,                uint8_t VE,
            uint8_t V7,                uint8_t VF,
            uint8_t DT,                uint8_t ST,
            */

            uint16_t index=0x0000;

            std::vector<uint8_t> Register;    //[0-15]GP + DT + ST
            std::vector<bool> videoMemory;    

           //DT: delay timer. Decerements by 1 when non-zero @ 60hz. If 0, do nothing. 
          //ST: sound timer. Decerements ... @ 60hz. If non 0, make buzzing noise. If 0, do nothing. 



            /*                                 OPCODES                              */
            void SYS();         void CLS();         void RET();         void JPAddr();
            void CALL();        void SEVxByte();    void SNEVxByte();   void SEVxVy();
            void LDVxByte();    void ADDVxByte();   void LDVxVy();      void OR();
            void AND();         void XOR();         void ADDVxVy();     void SUB();
            void SHR();         void SUBN();        void SHL();         void SNEVxVy();
            void LDIAddr();     void JPV0Addr();    void RND();         void DRW();
            void SKP();         void SKNP();        void LDVxDT();      void LDVxK();
            void LDDTVx();      void LDSTVx();      void ADDIVx();      void LDFVx();
            void LDBVx();       void LDIVx();       void LDVxI();       


            //note: CPU::* is needed beccause the function pointers != member function pointers. 
            //a type must be specified. These types are also disticetly different
            //std::vector<void (CPU::*)(void)> a={&CPU::SYS};   
            //**decided to just go with if else. opcodes are neumerically too large and a map is too slow



	
			/*		Display		*/
			//The dispaly is essentially a matrix of 64 pixels wide and 32 pixels high
			//all hex outputs (0-F) are 4 wide and 5 high. 
			//ex:
			//	**** **** ****
			//	**** **** ****
			//	**** **** ****
			//	**** **** ****
			//	**** **** ****
			
			//(x,y) values wrap around when they exceed the display values. ie: (x % 64, y % 32).
			//maximum possible sprite size is 8B x 15B, which is 32 bit x 60 bit. 
            //input keys
        
        private: //helpers
            uint16_t instruction;

            void PCToStack();    //put PC in std::stack(TOS)
            void PCFromtStack(); //get PC from stack (TOS)

        public:
            CPU(){};
            CPU(RAM & _ram, std::vector<bool> _videoMemory);
            void setRegister(int reg,uint8_t val);
            uint8_t getRegister(int reg);
            void fetch();		//updates instruction and increments PC
            void execute();
            
    };

}   //namespace chip8VM


#endif
