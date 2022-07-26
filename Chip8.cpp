#include "Chip8.h"
#include "SDL2/SDL.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <vector>
#include <iostream>
#include <unistd.h>

#define WIDTH 640
#define HEIGHT 320
#define PIXELSIZE 10


using namespace chip8VM;

Chip8::Chip8(RAM & _ram, std::vector<bool> * _videoMemory, std::vector<bool> * _keyboardInput): ram(_ram), videoMemory(_videoMemory)
,keyboardInput(_keyboardInput){
	cpu=new CPU(_ram,_videoMemory, _keyboardInput);
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

		texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 640,320);
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
					(*keyboardInput)[(int)'0']=true;
					return;
					break;

				case SDLK_1:
					printf("1 pressed\n");
					(*keyboardInput)[(int)'1']=true;
					return;
					break;

				case SDLK_2:
					printf("2 pressed\n");
					(*keyboardInput)[(int)'2']=true;
					return;
					break;	

				case SDLK_3:
					printf("3 pressed\n");
					(*keyboardInput)[(int)'3']=true;
					return;
					break;

				case SDLK_4:
					printf("4 pressed\n");
					(*keyboardInput)[(int)'4']=true;
					return;
					break;

				case SDLK_5:
					printf("5 pressed\n");
					(*keyboardInput)[(int)'5']=true;
					return;
					break;

				case SDLK_6:
					printf("6 pressed\n");
					(*keyboardInput)[(int)'6']=true;
					return;
					break;

				case SDLK_7:
					printf("7 pressed\n");
					(*keyboardInput)[(int)'7']=true;
					return;
					break;

				case SDLK_8:
					printf("8 pressed\n");
					(*keyboardInput)[(int)'8']=true;
					return;
					break;

				case SDLK_9:
					printf("9 pressed\n");
					(*keyboardInput)[(int)'9']=true;
					return;
					break;

				case SDLK_q:
					printf("q pressed\n");
					(*keyboardInput)[(int)'q']=true;
					return;
					break;

				case SDLK_w:
					printf("w pressed\n");
					(*keyboardInput)[(int)'w']=true;
					return;
					break;

				case SDLK_e:
					printf("e pressed\n");
					(*keyboardInput)[(int)'e']=true;
					return;
					break;

				case SDLK_r:
					printf("r pressed\n");
					(*keyboardInput)[(int)'r']=true;
					return;
					break;
				
				case SDLK_a:
					printf("a pressed\n");
					(*keyboardInput)[(int)'a']=true;
					return;
					break;

				case SDLK_s:
					printf("s pressed\n");
					(*keyboardInput)[(int)'s']=true;
					return;
					break;
				
				case SDLK_d:
					printf("d pressed\n");
					(*keyboardInput)[(int)'d']=true;
					return;
					break;

				case SDLK_f:
					printf("f pressed\n");
					(*keyboardInput)[(int)'f']=true;
					return;
					break;

				case SDLK_z:
					printf("z pressed\n");
					(*keyboardInput)[(int)'z']=true;
					return;
					break;

				case SDLK_x:
					printf("x pressed\n");
					(*keyboardInput)[(int)'x']=true;
					return;
					break;

				case SDLK_c:
					printf("c pressed\n");
					(*keyboardInput)[(int)'c']=true;
					return;
					break;
				
				case SDLK_v:
					printf("v pressed\n");
					(*keyboardInput)[(int)'v']=true;
					return;
					break;

				case SDLK_t:
					printf("t pressed\n");
					(*keyboardInput)[(int)'t']=true;
					return;
					break;
				
				case SDLK_y:
					printf("y pressed\n");
					(*keyboardInput)[(int)'y']=true;
					return;
					break;

				case SDLK_u:
					printf("u pressed\n");
					(*keyboardInput)[(int)'u']=true;
					return;
					break;

				case SDLK_i:
					printf("i pressed\n");
					(*keyboardInput)[(int)'i']=true;
					return;
					break;

				case SDLK_o:
					printf("o pressed\n");
					(*keyboardInput)[(int)'o']=true;
					return;
					break;
				
				case SDLK_p:
					printf("p pressed\n");
					(*keyboardInput)[(int)'p']=true;
					return;
					break;

				case SDLK_g:
					printf("g pressed\n");
					(*keyboardInput)[(int)'g']=true;
					return;
					break;
				
				case SDLK_h:
					printf("h pressed\n");
					(*keyboardInput)[(int)'h']=true;
					return;
					break;

				case SDLK_j:
					printf("j pressed\n");
					(*keyboardInput)[(int)'j']=true;
					return;
					break;

				case SDLK_k:
					printf("k pressed\n");
					(*keyboardInput)[(int)'k']=true;
					return;
					break;

				case SDLK_l:
					printf("l pressed\n");
					(*keyboardInput)[(int)'l']=true;
					return;
					break;

				case SDLK_b:
					printf("b pressed\n");
					(*keyboardInput)[(int)'b']=true;
					return;
					break;

				case SDLK_n:
					printf("n pressed\n");
					(*keyboardInput)[(int)'n']=true;
					return;
					break;

				case SDLK_m:
					printf("m pressed\n");
					(*keyboardInput)[(int)'m']=true;
					return;
					break;
					
				default:
					break;
			}

			case SDL_KEYUP:
				switch (event.key.keysym.sym){

				case SDLK_0:
					printf("0 released\n");
					(*keyboardInput)[(int)'0']=false;
					return;
					break;

				case SDLK_1:
					printf("1 released\n");
					(*keyboardInput)[(int)'1']=false;
					return;
					break;

				case SDLK_2:
					printf("2 released\n");
					(*keyboardInput)[(int)'2']=false;
					return;
					break;	

				case SDLK_3:
					printf("3 released\n");
					(*keyboardInput)[(int)'3']=false;
					return;
					break;

				case SDLK_4:
					printf("4 released\n");
					(*keyboardInput)[(int)'4']=false;
					return;
					break;

				case SDLK_5:
					printf("5 released\n");
					(*keyboardInput)[(int)'5']=false;
					return;
					break;

				case SDLK_6:
					printf("6 released\n");
					(*keyboardInput)[(int)'6']=false;
					return;
					break;

				case SDLK_7:
					printf("7 released\n");
					(*keyboardInput)[(int)'7']=false;
					return;
					break;

				case SDLK_8:
					printf("8 released\n");
					(*keyboardInput)[(int)'8']=false;
					return;
					break;

				case SDLK_9:
					printf("9 released\n");
					(*keyboardInput)[(int)'9']=false;
					return;
					break;

				case SDLK_q:
					printf("q released\n");
					(*keyboardInput)[(int)'q']=false;
					return;
					break;

				case SDLK_w:
					printf("w released\n");
					(*keyboardInput)[(int)'w']=false;
					return;
					break;

				case SDLK_e:
					printf("e released\n");
					(*keyboardInput)[(int)'e']=false;
					return;
					break;

				case SDLK_r:
					printf("r released\n");
					(*keyboardInput)[(int)'r']=false;
					return;
					break;
				
				case SDLK_a:
					printf("a released\n");
					(*keyboardInput)[(int)'a']=false;
					return;
					break;

				case SDLK_s:
					printf("s released\n");
					(*keyboardInput)[(int)'s']=false;
					return;
					break;
				
				case SDLK_d:
					printf("d released\n");
					(*keyboardInput)[(int)'d']=false;
					return;
					break;

				case SDLK_f:
					printf("f released\n");
					(*keyboardInput)[(int)'f']=false;
					return;
					break;

				case SDLK_z:
					printf("z released\n");
					(*keyboardInput)[(int)'z']=false;
					return;
					break;

				case SDLK_x:
					printf("x released\n");
					(*keyboardInput)[(int)'x']=false;
					return;
					break;

				case SDLK_c:
					printf("c released\n");
					(*keyboardInput)[(int)'c']=false;
					return;
					break;
				
				case SDLK_v:
					printf("v released\n");
					(*keyboardInput)[(int)'v']=false;
					return;
					break;

				case SDLK_t:
					printf("t released\n");
					(*keyboardInput)[(int)'t']=false;
					return;
					break;
				
				case SDLK_y:
					printf("y released\n");
					(*keyboardInput)[(int)'y']=false;
					return;
					break;

				case SDLK_u:
					printf("u released\n");
					(*keyboardInput)[(int)'u']=false;
					return;
					break;

				case SDLK_i:
					printf("i released\n");
					(*keyboardInput)[(int)'i']=false;
					return;
					break;

				case SDLK_o:
					printf("o released\n");
					(*keyboardInput)[(int)'o']=false;
					return;
					break;
				
				case SDLK_p:
					printf("p released\n");
					(*keyboardInput)[(int)'p']=false;
					return;
					break;

				case SDLK_g:
					printf("g released\n");
					(*keyboardInput)[(int)'g']=false;
					return;
					break;
				
				case SDLK_h:
					printf("h released\n");
					(*keyboardInput)[(int)'h']=false;
					return;
					break;

				case SDLK_j:
					printf("j released\n");
					(*keyboardInput)[(int)'j']=false;
					return;
					break;

				case SDLK_k:
					printf("k released\n");
					(*keyboardInput)[(int)'k']=false;
					return;
					break;

				case SDLK_l:
					printf("l released\n");
					(*keyboardInput)[(int)'l']=false;
					return;
					break;

				case SDLK_b:
					printf("b released\n");
					(*keyboardInput)[(int)'b']=false;
					return;
					break;

				case SDLK_n:
					printf("n released\n");
					(*keyboardInput)[(int)'n']=false;
					return;
					break;

				case SDLK_m:
					printf("m released\n");
					(*keyboardInput)[(int)'m']=false;
					return;
					break;

				default:
					return;
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