#include "SDL2/SDL.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <vector>
#include <iostream>


//size of a pixel is 10x10 word, for instance


void draw(int x, int y, SDL_Texture *texture, SDL_Renderer *renderer){	//

	
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



int main(int argc, char *argv[])
{
        SDL_Window *window;
        SDL_Event event;

		SDL_Renderer *renderer;
		SDL_Texture *texture;


		std::vector<int> video_mem(2048,0);

		video_mem[0]=1;
		video_mem[1]=1;

		video_mem[2]=1;
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
                return 3;
        }

        window = SDL_CreateWindow("SDL_CreateTexture",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        640, 320,
                        SDL_WINDOW_RESIZABLE);


        renderer = SDL_CreateRenderer(window, -1, 0);

        texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 640,320);


		


		for(int i=0;i<2048;i++){
			std::cout<<i<<":"<<video_mem[i]<<", ";
			if(video_mem[i]==1){
			
				//draw((video_mem[i]%64)*10, (i%64)*10, texture,renderer);
				draw((i%64)*10,(i/64)*10, texture,renderer);

				//draw(0,0, texture,renderer);
			}
		}

        while (1) {
                SDL_PollEvent(&event);
                if(event.type == SDL_QUIT)
                        break;


        }
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return 0;
}
