#include "CPU.h"
#include "RAM.h"

using namespace chip8VM;





CPU::CPU(RAM &_ram): ram(&_ram){    //the start up routine
                                
    for(int i=0;i<4096;i++){
        ram->write(i, 0);
    }




    
}

void CPU::SYS(){     //(0nnn) jump to nnn
                     //push to stack?
                     //not used in modern interpreters
    PC=instruction & 0x0FFF; //mask top bit to 0. address is bottom 12 bits of instruction  
};

void CPU::CLS(){

    
};
void CPU::RET(){    //return from subroutine
    //PC=(ram->read(SP)<<8)&0xFF00;
    //SP--;
    //PC|=(ram->read(SP))&0x00FF;
    PCFromtStack();
    
};

void CPU::JPAddr(){
    
    PC=instruction & 0x0FFF; //mask top bit to 0. address is bottom 12 bits of instruction  
};

void CPU::CALL(){   //call subroutine. not same as jump
    //SP++;
    //ram->write(SP,PC&0x00FF);   //big endian. smaller address is smaller value (lsb)
    //SP++;
    //ram->write(SP,(PC&0xFF00)>>8);
    
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

void CPU::ADDVxVy(){
    
    

};   

void CPU::SUB(){

};

void CPU::SHR(){

};   

void CPU::SUBN(){

};  

void CPU::SHL(){

};    

void CPU::SNEVxVy(){

};

void CPU::LDIAddr(){

}; 

void CPU::JPV0Addr(){

}; 

void CPU::RND(){

};

void CPU::DRW(){

};

void CPU::SKP(){

};

void CPU::SKNP(){

}; 

void CPU::LDVxDT(){

};

void CPU::LDVxK(){

};

void CPU::LDDTVx(){

}; 

void CPU::LDSTVx(){


};     

void CPU::ADDIVx(){

};     

void CPU::LDFVx(){

};

void CPU::LDBVx(){

};    

void CPU::LDIVx(){

};    

void CPU::LDVxI(){

};  


