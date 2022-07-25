#include "CPU.h"
#include "RAM.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>
using namespace chip8VM;

CPU::CPU(RAM & _ram, std::vector<bool> _videoMemory): ram(_ram), videoMemory(_videoMemory){    //the start up routine
                      

    srand(time(NULL));
    //std::vector<uint8_t> Register(18,0);    //[0-15]GP + DT + ST
    Register=std::vector<uint8_t>(18,0);
}

void CPU::fetch(){
	instruction=0x00FF&ram.read(PC);
	PC++;
	instruction|=0xFF00&ram.read(PC);
	PC++;
}

void CPU::execute(){    //determines what function to call based on instruction

    if(instruction==0x00E0){
        CLS();
    }
    else if(instruction==0x00EE){
        RET();
    }
    else if(instruction&0x1000==0x1000){
        JPAddr();
    }
    else if(instruction&0x2000==0x2000){
        CALL();
    }
    else if(instruction&0x3000==0x3000){
        SEVxByte();
    }
    else if(instruction&0x4000==0x4000){
        SNEVxByte();
    }
    else if(instruction&0x5000==0x5000){
        SEVxByte();
    }
    else if(instruction&0x6000==0x6000){
        LDVxByte();
    }
    else if(instruction&0x7000==0x7000){
        ADDVxByte();
    }    
    else if(instruction&0x800F==0x8000){
        LDVxVy();
    }
    else if(instruction&0x800F==0x8001){
        OR();
    }
    else if(instruction&0x800F==0x8002){
        AND();
    }
    else if(instruction&0x800F==0x8003){
        XOR();
    }
    else if(instruction&0x800F==0x8004){
        ADDVxVy();
    }
    else if(instruction&0x800F==0x8005){
        SUB();
    }
    else if(instruction&0x800F==0x8006){
        SHR();
    }
    else if(instruction&0x800F==0x8007){
        SUBN();
    }
    else if(instruction&0x800F==0x800E){
        SHL();
    }
    else if(instruction&0x900F==0x9000){
        SNEVxVy();
    }
    else if(instruction&0xA000==0xA002){
        LDIAddr();
    }
    else if(instruction&0xB000==0xB000){
        JPV0Addr();
    }
    else if(instruction&0xD000==0xD000){
        DRW();
    }
    else if(instruction&0xF0FF==0xE09E){
        SKP();
    }
    else if(instruction&0xF0FF==0xE0A1){
        SKNP();
    }
    else if(instruction&0xF0FF==0xF007){
        LDVxDT();
    }
    else if(instruction&0xF0FF==0xF00A){
        LDVxK();
    }
    else if(instruction&0xF0FF==0xF015){
        LDDTVx();
    }
    else if(instruction&0xF0FF==0xF018){
        LDSTVx();
    }
    else if(instruction&0xF0FF==0xF01E){
        ADDIVx();
    }
    else if(instruction&0xF0FF==0xF029){
        LDFVx();
    }
    else if(instruction&0xF0FF==0xF033){
        LDBVx();
    }
    else if(instruction&0xF0FF==0xF055){
        LDIVx();
    }
    else if(instruction&0xF0FF==0xF065){
        LDVxI();
    }
    
}
void CPU::setRegister(int reg,uint8_t val){
    std::cout<<"Writing "<<(int)val<<" to register "<<(int)reg<<"\n";
    Register[reg]=val;
}

uint8_t CPU::getRegister(int reg){
    return Register[reg];
}


void CPU::PCToStack(){  //store PC in stack
    SP++;
    ram.write(SP,(PC&0x00FF));
    SP++;
    ram.write(SP,(PC&0xFF00)>>8);

}


void CPU::PCFromtStack(){   //Get PC from TOS

    PC=(ram.read(SP)<<8)&0xFF00;
    SP--;
    PC|=(ram.read(SP))&0x00FF;

}


void CPU::SYS(){   
                     //not used in modern interpreters
    PC=instruction & 0x0FFF; //mask top bit to 0. address is bottom 12 bits of instruction  
};

void CPU::CLS(){
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

    if(Register[(instruction&0x0F00)>>8]==(instruction&0x00FF)){
        PC++;
        PC++;
    }

    return;
};

void CPU::SNEVxByte(){
    if(Register[(instruction&0x0F00)>>8]!=(instruction&0x00FF)){
        PC++;
        PC++;
    }

    return;
};

void CPU::SEVxVy(){
    if(Register[(instruction&0x0F00)>>8]==Register[instruction&0x00F0]){
        PC++;
        PC++;
    }

    return;
};

void CPU::LDVxByte(){
    Register[(instruction&0x0F00)>>8]=instruction&0x00FF;

    return;
};

void CPU::ADDVxByte(){

    Register[(instruction&0x0F00)>>8]+=instruction&0x00FF;

    return;
};  

void CPU::LDVxVy(){

    Register[(instruction&0x0F00)>>8]=Register[(instruction&0x00F0)>>4];

    return;
}; 

void CPU::OR(){
    
    Register[(instruction&0x0F00)>>8]|=instruction&0x00FF;

    return;
};

void CPU::AND(){

    Register[(instruction&0x0F00)>>8]&=instruction&0x00FF;

    return;
}; 

void CPU::XOR(){

    Register[(instruction&0x0F00)>>8]^=instruction&0x00FF;

    return;
}; 

void CPU::ADDVxVy(){    //add Vx and Vy. Set VF if the value wraps around
    
    uint16_t sum=Register[instruction&0x0F00]+Register[instruction&0x00F0];
    Register[instruction&0x0F00]=sum;

    if(sum>255){
        Register[15]=1; //set VF to 1 if overflow
    }


};   

void CPU::SUB(){

    Register[(instruction&0x0F00)>>8]=Register[(instruction&0x0F00)>>8]-Register[(instruction&0x00F0)>>4];

    if(Register[(instruction&0x0F00)>>8]>Register[(instruction&0x00F0)>>4]){
        Register[15]=1;
    }
    else{
        Register[15]=0;
    }
    return;

};

void CPU::SHR(){
    if((Register[(instruction&0x0F00)]&0x0001)==1){
        Register[15]=1;
    }
    else{
        Register[15]=0;
    }
    Register[(instruction&0x0F00)]=Register[(instruction&0x0F00)]>>1;
};   

void CPU::SUBN(){
 
    Register[(instruction&0x0F00)>>8]=Register[(instruction&0x00F0)>>4]-Register[(instruction&0x0F00)>>8];

    if(Register[(instruction&0x00F0)>>4]>Register[(instruction&0x0F00)>>8]){
        Register[15]=1;
    }
    else{
        Register[15]=0;
    }
    return;

};  

void CPU::SHL(){
 
    if((Register[(instruction&0x0F00)]&0x8000)==0x8000){
        Register[15]=1;
    }
    else{
        Register[15]=0;
    }
    Register[(instruction&0x0F00)]=Register[(instruction&0x0F00)]<<1;
    return;
};    

void CPU::SNEVxVy(){
    if(Register[(instruction&0x0F00)>>8]!=Register[instruction&0x00F0]){
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
    PC=instruction&0x0FFF+Register[0];
}; 

void CPU::RND(){    //generate random number
    
    Register[(instruction&0x0F00)>>8]=(rand()%0xF)&(instruction&0x00FF);    //possible error with mismatching sizes
};

void CPU::DRW(){    //reads n bytes from index I and xors them into screen

    int bytes=(instruction&0x000F); //read display data
    uint8_t sprite=0x00;    //the 8 bit seg currently being printed to display
    int x=(instruction&0x0F00)>>8;
    int y=(instruction&0x00F0)>>4;
    int counter=0;  //the number of bits already processed to index display vector

    for(int i=0;i<bytes;i++){
        sprite=ram.read(index+i);

        for(int bit=0;bit<8;bit++){ //add every bit to display by XOR (as per spec)
            if((sprite&0x80)==0x80){
                videoMemory[x+y*64+counter]=videoMemory[x+y*64+counter]^(sprite>>8);
            }
            sprite=sprite<<1;
            counter++;
        }
    }
    return;

};

void CPU::SKP(){

};

void CPU::SKNP(){

}; 

void CPU::LDVxDT(){

    Register[(instruction&0x0F00)>>8]=Register[16];

};

void CPU::LDVxK(){

};

void CPU::LDDTVx(){
  
    Register[16]=(instruction&0x0F00)>>8;

}; 

void CPU::LDSTVx(){
	

    Register[17]=(instruction&0x0F00)>>8;

};     

void CPU::ADDIVx(){


    index=index+Register[(instruction&0x0F00)>>8];

};     

void CPU::LDFVx(){


};

void CPU::LDBVx(){

    
    uint8_t Vx=Register[(instruction&0x0F00>>8)];

    ram.write(index+2,Vx%10);
    Vx=Vx/10;
    ram.write(index+1,Vx%10);
    Vx=Vx/10;
    ram.write(index,Vx%10);

};    

void CPU::LDIVx(){


    for(int i=0;i<16;i++){
        ram.write(index+i,Register[i]);
    }

};    

void CPU::LDVxI(){


    for(int i=0;i<16;i++){
        Register[i]=ram.read(index+i);
    }
    return;
};  


