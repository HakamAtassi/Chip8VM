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
        //data is Big-Endian. Largest address is MSB
        private:
            
            RAM * ram;   //CPU needs a pointer to ram to get instruction
            std::vector<bool> * videoMemory;
            std::vector<bool> * keyboardInput;


            uint16_t SP=0x0000; //stack pointer
            uint16_t index=0x0000;
            std::vector<uint8_t> registers;    //[0-15]GP + DT + ST

			public:
				uint16_t PC=0x0200;   //only lower 3 bytes used (2^12=4096)



        private: //function vector table

			/*
            std::vector<void (CPU::*)(void)> opcodes={
                &CPU::SYS,&CPU::CLS,&CPU::RET,&CPU::JPAddr,
                &CPU::CALL,&CPU::SEVxByte,&CPU::SNEVxByte,&CPU::SEVxVy,
                &CPU::LDVxByte,&CPU::ADDVxByte,&CPU::LDVxVy,&CPU::OR,
                &CPU::AND,&CPU::XOR,&CPU::ADDVxVy,&CPU::SUB,
                &CPU::SHR,&CPU::SUBN,&CPU::SHL,&CPU::SNEVxVy,
                &CPU::LDIAddr,&CPU::JPV0Addr,&CPU::RND,&CPU::DRW,
                &CPU::SKP,&CPU::SKNP,&CPU::LDVxDT,&CPU::LDVxK,
                &CPU::LDDTVx,&CPU::LDSTVx,&CPU::ADDIVx,&CPU::LDFVx,
                &CPU::LDBVx,&CPU::LDIVx,&CPU::LDVxI};   
			*/

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
        
        private: //helpers
            uint16_t instruction;
            void PCToStack();    //put PC in std::stack(TOS)
            void PCFromtStack(); //get PC from stack (TOS)


        public:
            CPU(){};
            CPU(RAM * _ram, std::vector<bool> * _videoMemory,
            std::vector<bool> * _keyboardInput);
            void decrementDT();   //decrement DT and ST
            void decrementST();   //decrement DT and ST


            void setRegister(int reg,uint8_t val);
            uint8_t getRegister(int reg);
            void fetch();		//updates instruction and increments PC
            void execute();

    };
}   //namespace chip8VM


#endif
