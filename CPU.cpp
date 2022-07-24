#include "CPU.h"
#include "RAM.h"
#include <cstdint>
#include <cstdlib>

using namespace chip8VM;


CPU::CPU(RAM &_ram): ram(&_ram){    //the start up routine
                                
    for(int i=0;i<4096;i++){
        ram->write(i, 0);
    }

    srand(time(NULL));
}


void CPU::PCToStack(){  //store PC in stack
    SP++;
    ram->write(SP,(PC&0x00FF));
    SP++;
    ram->write(SP,(PC&0xFF00)>>8);

}


void CPU::PCFromtStack(){   //Get PC from TOS

    PC=(ram->read(SP)<<8)&0xFF00;
    SP--;
    PC|=(ram->read(SP))&0x00FF;

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

void CPU::DRW(){

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

    ram->write(index+2,Vx%10);
    Vx=Vx/10;
    ram->write(index+1,Vx%10);
    Vx=Vx/10;
    ram->write(index,Vx%10);

};    

void CPU::LDIVx(){

    for(int i=0;i<16;i++){
        ram->write(index+i,Register[i]);
    }

};    

void CPU::LDVxI(){

    for(int i=0;i<16;i++){
        Register[i]=ram->read(index+i);
    }
    return;
};  


