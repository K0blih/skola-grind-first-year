#include <stdio.h>
#include <SDL2/SDL.h>

int main () {

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    SDL_Window* window = SDL_CreateWindow("Skibidi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Event event;

    int running = 1;
    int draw_line_1 = 0;
    
    while(running) {
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    running = 0;
                    break;
                }
                case SDL_KEYDOWN: {
                    if (event.key.keysym.scancode == SDL_SCANCODE_L) {
                        draw_line_1 = !draw_line_1;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 150, 150, 240, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        if (draw_line_1) {
            SDL_RenderDrawLine(renderer, 0, 0, 500, 500);
            SDL_RenderDrawLine(renderer, 0, 500, 500, 0);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    
    return 0;
}