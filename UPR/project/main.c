#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dynamic_array.h"
#include "player.h"
#include "globals.h"
#include "alien.h"
#include "text.h"

int main() {
    // seed
    srand((unsigned int)time(NULL));

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

    // init alien rockets
    dynarray alienRockets;
    dynarray_init(&alienRockets, 10);

    // init aliens
    Alien aliens[ALIEN_ROWS][ALIEN_COLS];
    initAliens(renderer, aliens);

    // init space ship
    Alien spaceShip;
    initSpaceShip(renderer, &spaceShip);

    // text init
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("assets/ARIALBD.TTF", 24);
    SDL_Color white = {122, 122, 122, 122};
    SDL_Rect scoreRect = {
        scoreRect.x = 10,
        scoreRect.y = 10,
        scoreRect.h = 40,
        scoreRect.w = 200
    };
    SDL_Rect healthRect = {50, TAB_WIDTH - 200, 200, 40};

    // game loop
    int running = 1;
    int leftKey = 0;
    int rightKey = 0;
    int upKey = 0;
    int spacekey = 0;
    int rocketDelay = 60;
    int alientMoveDelay = 0;
    int startAlientRocketDelay = 0;

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
                        playerRocket(renderer, &rockets, player);
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
        if (startAlientRocketDelay < 120) {
            startAlientRocketDelay++;
        }
        
        //move textures and check collisions
        rocketMovement(&rockets);
        collisionCheck(&rockets, aliens, &spaceShip);
        if (startAlientRocketDelay == 120) {
            alienRocket(renderer, &alienRockets, aliens);
        }
        alienRocketMovement(&alienRockets);
        
        // render stuff
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, player.image, NULL, &player.destRect);
        renderAliens(renderer, aliens, &spaceShip);
        renderAlienRockets(renderer, &alienRockets);
        renderSpaceShip(renderer, spaceShip);
        if (alientMoveDelay == 90) {
            moveAliens(aliens);
            alientMoveDelay = 0;
        }
        moveSpaceShip(&spaceShip);
        renderRockets(renderer, &rockets);

        SDL_RenderPresent(renderer);

        // render text
        // SDL_Texture *score = createTextTexture(renderer, "Score 0", white, font);
        // SDL_Texture *health = createTextTexture(renderer, "Health 100", white, font);
        // renderText(renderer, score, &scoreRect);
        // renderText(renderer, health, &healthRect);
        // renderSimpleText(renderer, 40, 40, white, "cauasdasds");

        // 60 fps
        Uint32 frameEnd = SDL_GetTicks();
        int frameTime = frameEnd - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // quit loop
    dynarray_free(&rockets);
    dynarray_free(&alienRockets);
    SDL_DestroyTexture(player.image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}