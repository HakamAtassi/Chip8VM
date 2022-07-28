#ifndef CHIP8_H_
#define CHIP8_H_
#include "CPU.h"
#include "RAM.h"

#include "SDL2/SDL.h"
#include <string>
#include <vector>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <iostream>

namespace chip8VM{
    
    class Chip8{

        public: //interface
            Chip8();
            ~Chip8();
            void loadRom(std::string rom);
            void run();

        private:    //member variables
            CPU cpu;
            std::vector<bool>keyboardInput;


            SDL_Window *window;
			SDL_Event event;
			SDL_Renderer *renderer;
			SDL_Texture *texture;
            SDL_Rect r;

        private:    //members for video rendering

            void drawPixels(int x, int y,int index);
            void refreshDisplay();
            void getInput();    


        private: //test functions

            void fetchExecute();

    };
} //namespace chip8VM



#endif
