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

Chip8::Chip8(){

	keyboardInput=std::vector<bool>(128,0);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return;
	}

	window = SDL_CreateWindow("Chip8VM",
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					WIDTH, HEIGHT,
					SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, 0);

	texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET,640,320);


	r.w = PIXELSIZE; //pixel size
	r.h = PIXELSIZE;
}


Chip8::~Chip8(){
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

void chip8VM::Chip8::loadRom(std::string rom){
	cpu.loadRom(rom);
}




void Chip8::drawPixels(int x, int y,int index){


		r.x=x*PIXELSIZE;
		r.y=y*PIXELSIZE;


		//SDL_SetRenderTarget(renderer, texture);
		//SDL_SetRenderDrawColor(renderer, videoMemory[index]*255, 
		//videoMemory[index]*255 ,videoMemory[index]*255, 0x00);
		//SDL_RenderFillRect(renderer, &r);
		//SDL_SetRenderTarget(renderer, NULL);
		//SDL_RenderCopy(renderer, texture, NULL, NULL);
		//SDL_RenderPresent(renderer);


		int vMemVal=cpu.getVideoMemory(index);


		SDL_SetRenderTarget(renderer, texture);

		SDL_RenderDrawRect(renderer,&r);
		
		SDL_SetRenderDrawColor(renderer, vMemVal*255, 
		vMemVal*255 ,vMemVal*255, 0x00);
		SDL_RenderFillRect(renderer, &r);

}


void Chip8::fetchExecute(){
	if(cpu.PC>=4095){
		return;
	}

		cpu.decrement();	//decrement DT and ST if they are non 0
		cpu.fetch();
		cpu.execute();
}

void Chip8::refreshDisplay(){


	for(int i=0;i<2048;i++){	//refresh screen
		drawPixels((i%64),(i/64),i);
	}
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

}

void Chip8::getInput(){
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type){
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym){

				case SDLK_1:
					printf("1 pressed\n");
					keyboardInput[0x01]=true;
					return;
					break;


				case SDLK_2:
					printf("2 pressed\n");
					keyboardInput[0x02]=true;
					return;
					break;

				case SDLK_3:
					printf("3 pressed\n");
					keyboardInput[0x03]=true;
					return;
					break;

				case SDLK_4:
					printf("C pressed\n");
					keyboardInput[0x0C]=true;
					return;
					break;

				
				case SDLK_q:
					printf("4 pressed\n");
					keyboardInput[0x04]=true;
					return;
					break;

				case SDLK_w:
					printf("5 pressed\n");
					keyboardInput[0x05]=true;
					return;
					break;

				case SDLK_e:
					printf("6 pressed\n");
					keyboardInput[0x06]=true;
					return;
					break;

				case SDLK_r:
					printf("D pressed\n");
					keyboardInput[0x0D]=true;
					return;
					break;
				
				case SDLK_a:
					printf("7 pressed\n");
					keyboardInput[0x07]=true;
					return;
					break;

				case SDLK_s:
					printf("8 pressed\n");
					keyboardInput[0x08]=true;
					return;
					break;
				
				case SDLK_d:
					printf("9 pressed\n");
					keyboardInput[0x9]=true;
					return;
					break;

				case SDLK_f:
					printf("E pressed\n");
					keyboardInput[0x0E]=true;
					return;
					break;

				case SDLK_z:
					printf("A pressed\n");
					keyboardInput[0x0A]=true;
					return;
					break;

				case SDLK_x:
					printf("0 pressed\n");
					keyboardInput[0x00]=true;
					return;
					break;

				case SDLK_c:
					printf("B pressed\n");
					keyboardInput[0x0B]=true;
					return;
					break;
				
				case SDLK_v:
				printf("F pressed\n");
					keyboardInput[0x0F]=true;
					return;
					break;

				default:
					break;
			}

		case SDL_KEYUP:
			switch (event.key.keysym.sym){

				case SDLK_1:
					printf("1 pressed\n");
					keyboardInput[0x01]=false;
					return;
					break;


				case SDLK_2:
					printf("2 pressed\n");
					keyboardInput[0x02]=false;
					return;
					break;

				case SDLK_3:
					printf("3 pressed\n");
					keyboardInput[0x03]=false;
					return;
					break;

				case SDLK_4:
					printf("C pressed\n");
					keyboardInput[0x0C]=false;
					return;
					break;

				
				case SDLK_q:
					printf("4 pressed\n");
					keyboardInput[0x04]=false;
					return;
					break;

				case SDLK_w:
					printf("5 pressed\n");
					keyboardInput[0x05]=false;
					return;
					break;

				case SDLK_e:
					printf("6 pressed\n");
					keyboardInput[0x06]=false;
					return;
					break;

				case SDLK_r:
					printf("D pressed\n");
					keyboardInput[0x0D]=false;
					return;
					break;
				
				case SDLK_a:
					printf("7 pressed\n");
					keyboardInput[0x07]=false;
					return;
					break;

				case SDLK_s:
					printf("8 pressed\n");
					keyboardInput[0x08]=false;
					return;
					break;
				
				case SDLK_d:
					printf("9 pressed\n");
					keyboardInput[0x9]=false;
					return;
					break;

				case SDLK_f:
					printf("E pressed\n");
					keyboardInput[0x0E]=false;
					return;
					break;

				case SDLK_z:
					printf("A pressed\n");
					keyboardInput[0x0A]=false;
					return;
					break;

				case SDLK_x:
					printf("0 pressed\n");
					keyboardInput[0x00]=false;
					return;
					break;

				case SDLK_c:
					printf("B pressed\n");
					keyboardInput[0x0B]=false;
					return;
					break;
				
				case SDLK_v:
				printf("F pressed\n");
					keyboardInput[0x0F]=false;
					return;
					break;

				default:
					break;
			}
		}
	cpu.setKeyboardInput(keyboardInput);
}

#include<unistd.h>

void Chip8::run(){


	SDL_Event eventMain;

	while(1){

		if(cpu.PC>=0xFFF){
			return;
		}


		fetchExecute();
		refreshDisplay();
		getInput();


		SDL_PollEvent(&eventMain);
		if(eventMain.type == SDL_QUIT)
				break;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}




