#include "Chip8.h"
#include "SDL2/SDL.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>

#define WIDTH 640
#define HEIGHT 320
#define PIXELSIZE 10
#define START_ADDRESS 0x200

#define FONTSET_ADDRESS 0x50

using namespace chip8VM;

Chip8::Chip8(RAM * _ram, std::vector<bool> * _videoMemory, std::vector<bool> * _keyboardInput): ram(_ram), videoMemory(_videoMemory)
,keyboardInput(_keyboardInput){
	cpu=new CPU(_ram,_videoMemory, _keyboardInput);

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
		ram->write(FONTSET_ADDRESS+i,fontset[i]);
    }
}

void Chip8::createWindow(){

		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
				return;
		}

		window = SDL_CreateWindow("SDL_CreateTexture",
						SDL_WINDOWPOS_UNDEFINED,
						SDL_WINDOWPOS_UNDEFINED,
						WIDTH, HEIGHT,
						SDL_WINDOW_RESIZABLE);

		renderer = SDL_CreateRenderer(window, -1, 0);

		texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET,640,320);
}

void Chip8::drawPixels(int x, int y){
		SDL_Rect r;

		r.w = PIXELSIZE; //pixel size
		r.h = PIXELSIZE;

		r.x=x;
		r.y=y;

		SDL_SetRenderTarget(renderer, texture);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
		SDL_RenderFillRect(renderer, &r);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
}


void Chip8::fetchExecute(){
		cpu->fetch();
		cpu->execute();
}

void Chip8::refreshDisplay(){
	for(int i=0;i<2048;i++){	//refresh screen
		if((*videoMemory)[i]==true){
			drawPixels((i%64)*10,(i/64)*10);
		}
	}
}

void Chip8::getInput(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch (event.type){

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
				case SDLK_ESCAPE:
					printf("Quit\n");
					SDL_DestroyRenderer(renderer);
					SDL_Quit();
					return;
					break;

				case SDLK_0:
					printf("0 pressed\n");
					(*keyboardInput)[0x00]=true;
					return;
					break;

				case SDLK_1:
					printf("1 pressed\n");
					(*keyboardInput)[0x01]=true;
					return;
					break;

				case SDLK_2:
					printf("2 pressed\n");
					(*keyboardInput)[0x02]=true;
					return;
					break;	

				case SDLK_3:
					printf("3 pressed\n");
					(*keyboardInput)[0x03]=true;
					return;
					break;

				case SDLK_4:
					printf("4 pressed\n");
					(*keyboardInput)[0x04]=true;
					return;
					break;

				case SDLK_5:
					printf("5 pressed\n");
					(*keyboardInput)[0x05]=true;
					return;
					break;

				case SDLK_6:
					printf("6 pressed\n");
					(*keyboardInput)[0x06]=true;
					return;
					break;

				case SDLK_7:
					printf("7 pressed\n");
					(*keyboardInput)[0x07]=true;
					return;
					break;

				case SDLK_8:
					printf("8 pressed\n");
					(*keyboardInput)[0x08]=true;
					return;
					break;

				case SDLK_9:
					printf("9 pressed\n");
					(*keyboardInput)[0x09]=true;
					return;
					break;

				case SDLK_q:
					printf("q pressed\n");
					(*keyboardInput)[0x0A]=true;
					return;
					break;

				case SDLK_w:
					printf("w pressed\n");
					(*keyboardInput)[0x0B]=true;
					return;
					break;

				case SDLK_e:
					printf("e pressed\n");
					(*keyboardInput)[0x0C]=true;
					return;
					break;

				case SDLK_r:
					printf("r pressed\n");
					(*keyboardInput)[0x0D]=true;
					return;
					break;
				
				case SDLK_a:
					printf("a pressed\n");
					(*keyboardInput)[0x0E]=true;
					return;
					break;

				case SDLK_s:
					printf("s pressed\n");
					(*keyboardInput)[0x0F]=true;
					return;
					break;
				
				case SDLK_d:
					printf("d pressed\n");
					(*keyboardInput)[0x10]=true;
					return;
					break;

				case SDLK_f:
					printf("f pressed\n");
					(*keyboardInput)[0x11]=true;
					return;
					break;

				case SDLK_z:
					printf("z pressed\n");
					(*keyboardInput)[0x12]=true;
					return;
					break;

				case SDLK_x:
					printf("x pressed\n");
					(*keyboardInput)[0x13]=true;
					return;
					break;

				case SDLK_c:
					printf("c pressed\n");
					(*keyboardInput)[0x14]=true;
					return;
					break;
				
				case SDLK_v:
					printf("v pressed\n");
					(*keyboardInput)[0x15]=true;
					return;
					break;

				case SDLK_t:
					printf("t pressed\n");
					(*keyboardInput)[0x16]=true;
					return;
					break;
				
				case SDLK_y:
					printf("y pressed\n");
					(*keyboardInput)[0x17]=true;
					return;
					break;

				case SDLK_u:
					printf("u pressed\n");
					(*keyboardInput)[0x18]=true;
					return;
					break;

				case SDLK_i:
					printf("i pressed\n");
					(*keyboardInput)[0x19]=true;
					return;
					break;

				case SDLK_o:
					printf("o pressed\n");
					(*keyboardInput)[0x1A]=true;
					return;
					break;
				
				case SDLK_p:
					printf("p pressed\n");
					(*keyboardInput)[0x1B]=true;
					return;
					break;

				case SDLK_g:
					printf("g pressed\n");
					(*keyboardInput)[0x1C]=true;
					return;
					break;
				
				case SDLK_h:
					printf("h pressed\n");
					(*keyboardInput)[0x1D]=true;
					return;
					break;

				case SDLK_j:
					printf("j pressed\n");
					(*keyboardInput)[0x1E]=true;
					return;
					break;

				case SDLK_k:
					printf("k pressed\n");
					(*keyboardInput)[0x1F]=true;
					return;
					break;

				case SDLK_l:
					printf("l pressed\n");
					(*keyboardInput)[0x20]=true;
					return;
					break;

				case SDLK_b:
					printf("b pressed\n");
					(*keyboardInput)[0x21]=true;
					return;
					break;

				case SDLK_n:
					printf("n pressed\n");
					(*keyboardInput)[0x22]=true;
					return;
					break;

				case SDLK_m:
					printf("m pressed\n");
					(*keyboardInput)[0x23]=true;
					return;
					break;
					
				default:
					break;
			}

			case SDL_KEYUP:
				switch (event.key.keysym.sym){

				case SDLK_0:
					printf("0 released\n");
					(*keyboardInput)[0x00]=false;
					return;
					break;

				case SDLK_1:
					printf("1 released\n");
					(*keyboardInput)[0x01]=false;
					return;
					break;

				case SDLK_2:
					printf("2 released\n");
					(*keyboardInput)[0x02]=false;
					return;
					break;	

				case SDLK_3:
					printf("3 released\n");
					(*keyboardInput)[0x03]=false;
					return;
					break;

				case SDLK_4:
					printf("4 released\n");
					(*keyboardInput)[0x04]=false;
					return;
					break;

				case SDLK_5:
					printf("5 released\n");
					(*keyboardInput)[0x05]=false;
					return;
					break;

				case SDLK_6:
					printf("6 released\n");
					(*keyboardInput)[0x06]=false;
					return;
					break;

				case SDLK_7:
					printf("7 released\n");
					(*keyboardInput)[0x07]=false;
					return;
					break;

				case SDLK_8:
					printf("8 released\n");
					(*keyboardInput)[0x08]=false;
					return;
					break;

				case SDLK_9:
					printf("9 released\n");
					(*keyboardInput)[0x09]=false;
					return;
					break;

				case SDLK_q:
					printf("q released\n");
					(*keyboardInput)[0x0A]=false;
					return;
					break;

				case SDLK_w:
					printf("w released\n");
					(*keyboardInput)[0x0B]=false;
					return;
					break;

				case SDLK_e:
					printf("e released\n");
					(*keyboardInput)[0x0C]=false;
					return;
					break;

				case SDLK_r:
					printf("r released\n");
					(*keyboardInput)[0x0D]=false;
					return;
					break;
				
				case SDLK_a:
					printf("a released\n");
					(*keyboardInput)[0x0E]=false;
					return;
					break;

				case SDLK_s:
					printf("s released\n");
					(*keyboardInput)[0x0F]=false;
					return;
					break;
				
				case SDLK_d:
					printf("d released\n");
					(*keyboardInput)[0x10]=false;
					return;
					break;

				case SDLK_f:
					printf("f released\n");
					(*keyboardInput)[0x11]=false;
					return;
					break;

				case SDLK_z:
					printf("z released\n");
					(*keyboardInput)[0x12]=false;
					return;
					break;

				case SDLK_x:
					printf("x released\n");
					(*keyboardInput)[0x13]=false;
					return;
					break;

				case SDLK_c:
					printf("c released\n");
					(*keyboardInput)[0x14]=false;
					return;
					break;
				
				case SDLK_v:
					printf("v released\n");
					(*keyboardInput)[0x15]=false;
					return;
					break;

				case SDLK_t:
					printf("t released\n");
					(*keyboardInput)[0x16]=false;
					return;
					break;
				
				case SDLK_y:
					printf("y released\n");
					(*keyboardInput)[0x17]=false;
					return;
					break;

				case SDLK_u:
					printf("u released\n");
					(*keyboardInput)[0x18]=false;
					return;
					break;

				case SDLK_i:
					printf("i released\n");
					(*keyboardInput)[0x19]=false;
					return;
					break;

				case SDLK_o:
					printf("o released\n");
					(*keyboardInput)[0x1A]=false;
					return;
					break;
				
				case SDLK_p:
					printf("p released\n");
					(*keyboardInput)[0x1B]=false;
					return;
					break;

				case SDLK_g:
					printf("g released\n");
					(*keyboardInput)[0x1C]=false;
					return;
					break;
				
				case SDLK_h:
					printf("h released\n");
					(*keyboardInput)[0x1D]=false;
					return;
					break;

				case SDLK_j:
					printf("j released\n");
					(*keyboardInput)[0x1E]=false;
					return;
					break;

				case SDLK_k:
					printf("k released\n");
					(*keyboardInput)[0x1F]=false;
					return;
					break;

				case SDLK_l:
					printf("l released\n");
					(*keyboardInput)[0x20]=false;
					return;
					break;

				case SDLK_b:
					printf("b released\n");
					(*keyboardInput)[0x21]=false;
					return;
					break;

				case SDLK_n:
					printf("n released\n");
					(*keyboardInput)[0x22]=false;
					return;
					break;

				case SDLK_m:
					printf("m released\n");
					(*keyboardInput)[0x23]=false;
					return;
					break;
					
				default:
					break;
			
			}
		}
	}
}



void Chip8::run(){
	while(1){
		fetchExecute();
		refreshDisplay();
		getInput();

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
		printf("%d:%X ",i,ram->read(i));

		//std::cout<<(int)ram->read(i)<<" ";
	}
	std::cout<<"\n";
}


void Chip8::setRegister(int reg,uint8_t val){
	cpu->setRegister(reg,val);
}

uint8_t Chip8::getRegister(int reg){
	return cpu->getRegister(reg);
};

