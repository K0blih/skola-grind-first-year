#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dynamic_array.h"
#include "player.h"
#include "globals.h"
#include "alien.h"

int main() {
    // SDL init
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Window* window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TAB_WIDTH, TAB_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;
    
    // init player
    Player player;
    initPlayer(renderer, &player);

    // init rockets
    dynarray rockets;
    dynarray_init(&rockets, 3);

    const int MOVEMENT_VELOCITY = 6;
    const int ROCKET_VELOCITY = 6;

    // init aliens
    Alien aliens[ALIEN_ROWS][ALIEN_COLS];
    initAliens(renderer, aliens);

    // init bonus space ship
    Alien spaceShip;
    initSpaceShip(renderer, &spaceShip);

    // game loop
    int running = 1;
    int leftKey = 0;
    int rightKey = 0;
    int upKey = 0;
    int spacekey = 0;
    int rocketDelay = 60;
    int alientMoveDelay = 0;

    int targetFPS = 60;
    int frameDelay = 1000 / targetFPS;
    while(running) {
        Uint32 frameStart = SDL_GetTicks();

        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    running = 0;
                    break;
                }
                case SDL_KEYDOWN: {
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        running = 0;
                        break;
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                        leftKey = 1;
                        break;
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                        rightKey = 1;
                        break;
                    }
                    if ((event.key.keysym.scancode == SDL_SCANCODE_SPACE || event.key.keysym.scancode == SDL_SCANCODE_UP) && rocketDelay == 60) {
                        // create rocket
                        Rocket* newRocket = (Rocket*)malloc(sizeof(Rocket));
                        newRocket->image = IMG_LoadTexture(renderer, "assets/player_rocket.png");
                        newRocket->destRect.x = player.destRect.x + player.destRect.w / 2 - 2;
                        newRocket->destRect.y = player.destRect.y - 3;
                        newRocket->destRect.w = 5;
                        newRocket->destRect.h = 15;
                        dynarray_push(&rockets, newRocket);
                        rocketDelay = 0;
                        break;
                    }
                }
                case SDL_KEYUP: {
                    if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                        leftKey = 0;
                        break;
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                        rightKey = 0;
                        break;
                    }
                }
            }
        }

        if (leftKey) {
            if (player.destRect.x > 10) {
                player.destRect.x -= MOVEMENT_VELOCITY;
            }
        }
        if (rightKey) {
            if (player.destRect.x < TAB_WIDTH - 60) { // playerWidth - 10
                player.destRect.x += MOVEMENT_VELOCITY;
            }
        }
        if (rocketDelay < 60) {
            rocketDelay++;
        }
        if (alientMoveDelay < 90) {
            alientMoveDelay++;
        }
        
        for (int i = 0; i < rockets.size; i++) {
            Rocket* rocket = (Rocket*) rockets.items[i];

            rocket->destRect.y -= ROCKET_VELOCITY;

            if (rocket->destRect.y < 0) {
                SDL_DestroyTexture(rocket->image);
                dynarray_remove(&rockets, rocket);
            }
        }
        for (int i = 0; i < rockets.size; i++) {
            Rocket* rocket = (Rocket*) rockets.items[i];
            int collision = detectAlienCollision(rocket->destRect, aliens);
            int SScollision = detectSpaceShipCollision(rocket->destRect, &spaceShip);
            if (collision) {
                SDL_DestroyTexture(rocket->image);
                dynarray_remove(&rockets, rocket);
            }
            if (SScollision) {
                SDL_DestroyTexture(rocket->image);
                dynarray_remove(&rockets, rocket);
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, player.image, NULL, &player.destRect);
        drawAliens(renderer, aliens);
        drawSpaceShip(renderer, spaceShip);
        if (alientMoveDelay == 90) {
            moveAliens(aliens);
            alientMoveDelay = 0;
        }
        moveSpaceShip(&spaceShip);
        for (int i = 0; i < rockets.size; i++) {
            Rocket* rocket = (Rocket*) rockets.items[i];
            SDL_RenderCopy(renderer, rocket->image, NULL, &rocket->destRect);
        }

        SDL_RenderPresent(renderer);

        // 60 fps
        Uint32 frameEnd = SDL_GetTicks();
        int frameTime = frameEnd - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // quit loop
    dynarray_free(&rockets);
    SDL_DestroyTexture(player.image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}