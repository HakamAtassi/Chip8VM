#include "Chip8.h"
#include "SDL2/SDL.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <vector>
#include <iostream>
#include <unistd.h>

using namespace chip8VM;

Chip8::Chip8(RAM & _ram, std::vector<bool>& _videoMemory): ram(_ram), videoMemory(_videoMemory){


	try{cpu=new CPU(_ram,videoMemory);}
	catch(...){throw "Error in Chip8 constructor";}
}


void Chip8::createWindow(){

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
				return;
		}

		window = SDL_CreateWindow("SDL_CreateTexture",
						SDL_WINDOWPOS_UNDEFINED,
						SDL_WINDOWPOS_UNDEFINED,
						640, 320,
						SDL_WINDOW_RESIZABLE);

		renderer = SDL_CreateRenderer(window, -1, 0);

		texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 640,320);
}

void Chip8::drawPixel(int x, int y){
		SDL_Rect r;
			

		r.w = 10; //pixel size
		r.h = 10;

		r.x=x;
		r.y=y;

		SDL_SetRenderTarget(renderer, texture);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
		SDL_RenderFillRect(renderer, &r);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
}

void Chip8::drawScreen(int x, int y){


	drawPixel(x,y);

}





void Chip8::run(){


	while(1){

		for(int i=0;i<18;i++){
			std::cout<<"Register "<<i<<": "<<(int)getRegister(i)<<"\t";
		}


			for(int i=0;i<2048;i++){	//refresh screen
				//std::cout<<i<<":"<<videoMemory[i]<<", ";
				if(videoMemory[i]==true){
					//std::cout<<"\ntrue @ "<<i<<"\n";
					drawScreen((i%64)*10,(i/64)*10);
				}
			}
			

			//perform next CPU instruction

			cpu->fetch();
			cpu->execute();



		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT){
				break;
		}

	
	}

	SDL_DestroyRenderer(renderer);
	SDL_Quit();

}




void Chip8::printRam(){
	for(int i=0;i<4098;i++){
		std::cout<<(int)ram.read(i)<<" ";
	}
	std::cout<<"\n";
}


void Chip8::setRegister(int reg,uint8_t val){
	cpu->setRegister(reg,val);
}

uint8_t Chip8::getRegister(int reg){
	return cpu->getRegister(reg);
}

