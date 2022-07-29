#include "CPU.h"
#include "RAM.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>

#define FONTSET_ADDRESS 0x50
#define START_ADDRESS 0x200

using namespace chip8VM;




CPU::CPU(){    //the start up routine        
    srand(time(NULL));

    ram=RAM();
    registers=std::vector<uint8_t>(18,0);
    videoMemory=std::vector<bool>(2048,0);
    keyboardInput=std::vector<bool>(128);

    std::vector<uint8_t> fontset
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

    for(int i=0;i<80;i++){
		ram.write(FONTSET_ADDRESS+i,fontset[i]);
    }
}

void CPU::setKeyboardInput(std::vector<bool> _keyboardInput){
    keyboardInput=_keyboardInput;
    //printf("new keyboardInput set\n");
}

void CPU::decrement(){
    
    decrementDT();
    decrementST();

}


void CPU::decrementDT(){
    if(registers[16]>0){
        registers[16]--;
    }
    usleep(1000);


}

void CPU::decrementST(){
    if(registers[17]>0){
        registers[17]--;
    }
}



void CPU::loadRom(std::string rom){
    std::ifstream file(rom, std::ios::binary | std::ios::ate);

	if (file.is_open())
	{
		std::streampos size = file.tellg();
		char* buffer = new char[size];

		file.seekg(0, std::ios::beg);
		file.read(buffer, size);
		file.close();

		for (long i = 0; i < size; ++i)
		{
			//memory[START_ADDRESS + i]=buffer[i];
			ram.write(START_ADDRESS + i,buffer[i]);
		}
		delete[] buffer;
	}
}

void CPU::fetch(){
    if(PC>=0x0FFF){
        return;
    }
	instruction=ram.read(PC)<<8;    //lower address is MSB
	PC++;
	instruction|=ram.read(PC);
	PC++;
}

void CPU::execute(){    //determines what function to call based on instruction

    if(PC>=0x0FFF){
        return;
    }

    if(instruction==0x00E0){
        CLS();
    }
    else if(instruction==0x00EE){
        RET();
    }
    else if((instruction&0xF000)==0x1000){
        JPAddr();
    }
    else if((instruction&0xF000)==0x2000){
        CALL();
    }
    else if((instruction&0xF000)==0x3000){
        SEVxByte();
    }
    else if((instruction&0xF000)==0x4000){
        SNEVxByte();
    }
    else if((instruction&0xF000)==0x5000){
        SEVxByte();
    }
    else if((instruction&0xF000)==0x6000){
        LDVxByte();
    }
    else if((instruction&0xF000)==0x7000){
        ADDVxByte();
    }    
    else if((instruction&0xF00F)==0x8000){
        LDVxVy();
    }
    else if((instruction&0xF00F)==0x8001){
        OR();
    }
    else if((instruction&0xF00F)==0x8002){
        AND();
    }
    else if((instruction&0xF00F)==0x8003){
        XOR();
    }
    else if((instruction&0xF00F)==0x8004){
        ADDVxVy();
    }
    else if((instruction&0xF00F)==0x8005){
        SUB();
    }
    else if((instruction&0xF00F)==0x8006){
        SHR();
    }
    else if((instruction&0xF00F)==0x8007){
        SUBN();
    }
    else if((instruction&0xF00F)==0x800E){
        SHL();
    }
    else if((instruction&0xF00F)==0x9000){
        SNEVxVy();
    }
    else if((instruction&0xF000)==0xA000){
        LDIAddr();
    }
    else if((instruction&0xF000)==0xB000){
        JPV0Addr();
    }
    else if((instruction&0xF000)==0xD000){
        DRW();
    }
    else if((instruction&0xF0FF)==0xE09E){
        SKP();
    }
    else if((instruction&0xF0FF)==0xE0A1){
        SKNP();
    }
    else if((instruction&0xF0FF)==0xF007){
        LDVxDT();
    }
    else if((instruction&0xF0FF)==0xF00A){
        LDVxK();
    }
    else if((instruction&0xF0FF)==0xF015){
        LDDTVx();
    }
    else if((instruction&0xF0FF)==0xF018){
        LDSTVx();
    }
    else if((instruction&0xF0FF)==0xF01E){
        ADDIVx();
    }
    else if((instruction&0xF0FF)==0xF029){
        LDFVx();
    }
    else if((instruction&0xF0FF)==0xF033){
        LDBVx();
    }
    else if((instruction&0xF0FF)==0xF055){
        LDIVx();
    }
    else if((instruction&0xF0FF)==0xF065){
        LDVxI();
    }
}



bool CPU::getVideoMemory(int index){
    return videoMemory[index];
}


void CPU::PCToStack(){  //store PC in stack
    SP++;
    ram.write(SP,(PC&0xFF00)>>8);
    SP++;
    ram.write(SP,(PC&0x00FF));
}


void CPU::PCFromtStack(){   //Get PC from TOS
    PC=ram.read(SP);
    SP--;
    PC|=(ram.read(SP)<<8);
    SP--;
}


void CPU::SYS(){   
                     //not used in modern interpreters
    PC=instruction & 0x0FFF; //mask top bit to 0. address is bottom 12 bits of instruction  
};

void CPU::CLS(){
    for(int i=0;i<2048;i++){
        videoMemory[i]=0;
    }
};

void CPU::RET(){    //return from subroutine
    PCFromtStack();
    
};

void CPU::JPAddr(){
    PC=instruction & 0x0FFF; //mask top bit to 0. address is bottom 12 bits of instruction  
};

void CPU::CALL(){   //call subroutine. not same as jump
    PCToStack();
    PC=instruction&0x0FFF; //ignore top bit
    return;
};


void CPU::SEVxByte(){
    if(registers[(instruction&0x0F00)>>8]==(instruction&0x00FF)){
        PC++;
        PC++;
    }
    return;
};

void CPU::SNEVxByte(){
    if(registers[(instruction&0x0F00)>>8]!=(instruction&0x00FF)){
        PC++;
        PC++;
    }

    return;
};

void CPU::SEVxVy(){
    if(registers[(instruction&0x0F00)>>8]==registers[instruction&0x00F0]){
        PC++;
        PC++;
    }
    return;
};

void CPU::LDVxByte(){
    registers[(instruction&0x0F00)>>8]=instruction&0x00FF;
    return;
};

void CPU::ADDVxByte(){
    registers[(instruction&0x0F00)>>8]+=instruction&0x00FF;
    return;
};  

void CPU::LDVxVy(){
    registers[(instruction&0x0F00)>>8]=registers[(instruction&0x00F0)>>4];
    return;
}; 

void CPU::OR(){
    int index1=(instruction&0x0F00)>>8;
    int index2=(instruction&0x00F0)>>4;

    registers[index1]|=registers[index2];

    return;
};

void CPU::AND(){
    int index1=(instruction&0x0F00)>>8;
    int index2=(instruction&0x00F0)>>4;

    registers[index1]&=registers[index2];

    return;
}; 

void CPU::XOR(){
    int index1=(instruction&0x0F00)>>8;
    int index2=(instruction&0x00F0)>>4;

    registers[index1]^=registers[index2];

    return;
}; 

void CPU::ADDVxVy(){    //add Vx and Vy. Set VF if the value wraps around
    uint16_t sum=registers[(instruction&0x0F00)>>8]+registers[(instruction&0x00F0)>>4];
    registers[(instruction&0x0F00)>>8]=sum;

    if(sum>255){
        registers[15]=1; //set VF to 1 if overflow
    }
};

void CPU::SUB(){
    registers[(instruction&0x0F00)>>8]=registers[(instruction&0x0F00)>>8]-registers[(instruction&0x00F0)>>4];

    if(registers[(instruction&0x0F00)>>8]>registers[(instruction&0x00F0)>>4]){
        registers[15]=1;
    }
    else{
        registers[15]=0;
    }
    return;

};

void CPU::SHR(){
    int index=(instruction&0x0F00)>>8;

    if((registers[index]&0x0001)==1){
        registers[15]=1;
    }
    else{
        registers[15]=0;
    }
    registers[(index)>>8]=registers[(index)>>8]>>1;
};   

void CPU::SUBN(){
    registers[(instruction&0x0F00)>>8]=registers[(instruction&0x00F0)>>4]-registers[(instruction&0x0F00)>>8];

    if(registers[(instruction&0x00F0)>>4]>registers[(instruction&0x0F00)>>8]){
        registers[15]=1;
    }
    else{
        registers[15]=0;
    }
    return;
};  


void CPU::SHL(){
    int x=(instruction&0x0F00)>>8;
    int y=(instruction&0x00F0)>>4;
    
    registers[x]=registers[y];

    if((registers[x]&0x80)==0x80){
        registers[15]=1;
    }
    else{
        registers[15]=0;
    }
    registers[x]=registers[x]<<1;
    return;
};    


void CPU::SNEVxVy(){
    int index1=(instruction&0x0F00)>>8;
    int index2=(instruction&0x00F0)>>4;
    
    if(registers[index1]!=registers[index2]){
        PC++;
        PC++;
    }
    return;

};

void CPU::LDIAddr(){
    index=instruction&0x0FFF;
    return;

}; 

void CPU::JPV0Addr(){
    PC=instruction&0x0FFF+registers[0];
}; 

void CPU::RND(){    //generate random number
    int index1=(instruction&0x0F00)>>8;
    registers[index1]=(rand()%0xF)&(instruction&0x00FF);    //possible error with mismatching sizes
};


void CPU::DRW(){    //reads n bytes from index I and xors them into screen

    int bytes=(instruction&0x000F); //read display data
    uint8_t sprite=0x00;    //the 8 bit seg currently being printed to display

    int x=registers[((instruction&0x0F00)>>8)]%64;  //ITS REGISTER X/Y!!!! 
    int y=registers[((instruction&0x00F0)>>4)]%32;

    int VFCount=0;
    registers[15]=0;

    for(int i=0;i<bytes;i++){   //reads byte at index+i (ie: 0x00001111)
        sprite=ram.read(index+i);
        //write sprite into correct index in videoMemory
        for(int j=0;j<8;j++){
            int topBit=(int)sprite/128;
            int vIndex=x+(y+i)*64+j;
            if((videoMemory[vIndex]&topBit)==1 && VFCount==0){
                registers[15]=1;
            }
            videoMemory[vIndex]=videoMemory[vIndex]^topBit;
            sprite=sprite<<1;
        }
    }
    return;
};


void CPU::SKP(){    //if key with value in Vx is pressed, skip next instruction
    int Vx=(instruction&0x0F00)>>8;

    if(keyboardInput[registers[Vx]]==true){
        PC++;
        PC++;
    }
    return;
};

void CPU::SKNP(){
    
    int Vx=(instruction&0x0F00)>>8;

    if(keyboardInput[registers[Vx]]!=true){
        PC++;
        PC++;
    }
    return;
    
}; 



void CPU::LDVxDT(){

    registers[(instruction&0x0F00)>>8]=registers[16];

};


void CPU::LDVxK(){  //wait for keypress

    int Vx=(instruction&0x0F00)>>8;
    int flag=0;

    while(flag==0){
        for(int i=0;i<keyboardInput.size();i++){
            if(keyboardInput[i]==1){
                registers[Vx]=i;
                flag=1;
            }
        }
    }
    
};

void CPU::LDDTVx(){
    registers[16]=(instruction&0x0F00)>>8;

}; 

void CPU::LDSTVx(){
    registers[17]=(instruction&0x0F00)>>8;
};     

void CPU::ADDIVx(){
    index=index+registers[(instruction&0x0F00)>>8];
};     

void CPU::LDFVx(){
    int Vx=(instruction&0x0F00)>>8;
    index=FONTSET_ADDRESS+registers[Vx]*5;
};

void CPU::LDBVx(){
    uint8_t Vx=registers[(instruction&0x0F00)>>8];

    ram.write(index+2,Vx%10);
    Vx=Vx/10;
    ram.write(index+1,Vx%10);
    Vx=Vx/10;
    ram.write(index,Vx%10);

};    

void CPU::LDIVx(){

	uint8_t Vx = (instruction & 0x0F00u) >> 8u;

	for (uint8_t i = 0; i <= Vx; i++)
	{
        ram.write(index,registers[i]);
        index++;
	}
};    


void CPU::LDVxI(){
    int x=(instruction&0x0F00)>>8;

    for(int i=0;i<=x;i++){
        registers[i]=ram.read(index);
        index++;
    }
    return;
};