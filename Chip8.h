#ifndef CHIP8_H_
#define CHIP8_H_
#include "CPU.h"
#include "RAM.h"
#include <vector>
#include "SDL2/SDL.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <iostream>

namespace chip8VM{
    
    class Chip8{

        private:
            RAM* ram;
            CPU cpu();
            std::vector<bool> videoMemory;  //set bit indicates pixel at that address
    
        private:    //members for video rendering

			SDL_Window *window;
			SDL_Event event;
			SDL_Renderer *renderer;
			SDL_Texture *texture;
            

            


        private:    //helper functions


    


        public:
            Chip8(RAM * _ram);
            void run();
            void createWindow();
			void printRam();
            void drawScreen(int x, int y);
            void drawPixel(int x, int y);

    };
} //namespace chip8VM



#endif
