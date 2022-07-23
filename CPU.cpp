#include "CPU.h"

using namespace chip8VM;





CPU::CPU(RAM &_ram): ram(&_ram){    //the start up routine
                                
    for(int i=0;i<4096;i++){
        ram->write(i, 0);
    }

    PC=0x000;
    SP=0x000;

}

void CPU::SYS(){     //(0nnn) jump to nnn
                     //push to stack?
                     //not used in modern interpreters
    PC=instruction & 0x0FFF; //mask top bit to 0. address is bottom 12 bits of instruction  
};

void CPU::CLS(){

    
};

void CPU::RET(){    //return from subroutine
    PC=ram->read(SP);
    SP--;
};

void CPU::JPAddr(){
    
    PC=instruction & 0x0FFF; //mask top bit to 0. address is bottom 12 bits of instruction  
};

void CPU::CALL(){   //call subroutine. not same as jump
    SP++;
    ram->write(SP,PC&0x00FF);   //big endian. smaller address is smaller value (lsb)
    SP++;
    ram->write(SP,(PC&0xFF00)>>8);
};

void SEVxByte(){

};

void SNEVxByte(){

};

void SEVxVy(){

};

void LDVxByte(){

};

void ADDVxByte(){

};  

void LDVxVy(){

}; 

void OR(){

};

void AND(){

}; 

void XOR(){

}; 

void ADDVxVy(){

};   

void SUB(){

};

void SHR(){

};   

void SUBN(){

};  

void SHL(){

};    

void SNEVxVy(){

};

void LDIAddr(){

}; 

void JPV0Addr(){

}; 

void RND(){

};

void DRW(){

};

void SKP(){

};

void SKNP(){

}; 

void LDVxDT(){

};

void LDVxK(){

};

void LDDTVx(){

}; 

void LDSTVx(){


};     

void ADDIVx(){

};     

void LDFVx(){

};

void LDBVx(){

};    

void LDIVx(){

};    

void LDVxI(){

};  


