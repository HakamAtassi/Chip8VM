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

        private:
            RAM * ram;
            CPU * cpu;
            std::vector<bool> * videoMemory;  //set bit indicates pixel at that address
            std::vector<bool> * keyboardInput;

        private:    //members for video rendering

			SDL_Window *window;
			SDL_Event event;
			SDL_Renderer *renderer;
			SDL_Texture *texture;
            
            void drawPixels(int x, int y,int index);
            void refreshDisplay();
            void getInput();    //get keyboard input and pipe into SDL

        public: //test functions
            void setRegister(int reg,uint8_t val);
            uint8_t getRegister(int reg);
            void fetchExecute();


        public:
            Chip8(RAM * _ram, std::vector<bool> * _videoMemory,
            std::vector<bool> * _keyboardInput);

            void printRam();
            void createWindow();
            void run();


    };
} //namespace chip8VM



#endif
