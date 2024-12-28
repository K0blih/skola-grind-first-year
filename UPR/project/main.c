#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "dynamic_array.h"
#include "player.h"
#include "globals.h"
#include "alien.h"
#include "text.h"
#include "menu.h"

int main() {
    // seed
    srand((unsigned int)time(NULL));

    // SDL init
    SDL_Init(SDL_INIT_VIDEO);
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
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    TTF_Font *font = TTF_OpenFont("assets/Arial.ttf", 80);
    SDL_Color white = {255, 255, 255, 255};
    SDL_Rect scoreRect = {100, 0, 150, 40};
    SDL_Rect healthRect = {TAB_WIDTH - 250, 0, 150, 40};

    // game loop
    int running = 1;
    int afterGame = 0;
    int gameStart = 1;
    int leftKey = 0;
    int rightKey = 0;
    int rocketDelay = 60;
    int alientMoveDelay = 0;
    int startAlientRocketDelay = 0;

    int score = 0;
    int difficulty = 0;

    int targetFPS = 60;
    int frameDelay = 1000 / targetFPS;
    while (running) {
        Uint32 frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    running = 0;
                    afterGame = 0;
                    break;
                }
                case SDL_KEYDOWN: {
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        running = 0;
                        afterGame = 0;
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
                    break;
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
                    break;
                }
                default: {
                    break;
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
        if (alientMoveDelay < 60) {
            alientMoveDelay++;
        }
        if (startAlientRocketDelay < 120) {
            startAlientRocketDelay++;
        }
        if (player.health == 0) {
            afterGame = 1;
        }

        // menu
        while (gameStart) {
            menu(renderer, font, white, &running);
            gameStart = 0;
        }
        
        // game over
        while (afterGame) {
            gameOverLoop(renderer, font, white, &running, score, &rockets, &alienRockets);
            initPlayer(renderer, &player);
            initAliens(renderer, aliens);
            initSpaceShip(renderer, &spaceShip);
            dynarray_init(&rockets, 3);
            dynarray_init(&alienRockets, 10);
            afterGame = 0;
            score = 0;
            leftKey = 0;
            rightKey = 0;
            rocketDelay = 60;
            alientMoveDelay = 0;
            startAlientRocketDelay = 0;
            difficulty = 0;
        }
        
        // move textures and check collisions
        if (alientMoveDelay >= 60 - difficulty) {
            moveAliens(aliens);
            alientMoveDelay = 0;
        }
        rocketMovement(&rockets);
        collisionCheck(&rockets, aliens, &spaceShip, &score);
        if (startAlientRocketDelay == 120) {
            alienRocket(renderer, &alienRockets, aliens);
        }
        alienRocketMovement(&alienRockets);
        playerCollisionCheck(&alienRockets, &player);
        int check = checkAliensReachedPlayerLevel(aliens, player);
        if (check) {
            player.health = 0;
        }

        // render stuff
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        updateScore(renderer, font, white, scoreRect, score);
        updateHealth(renderer, font, white, healthRect, player);

        SDL_RenderCopy(renderer, player.image, NULL, &player.destRect);
        renderAliens(renderer, aliens, &spaceShip, &difficulty);
        renderAlienRockets(renderer, &alienRockets);
        renderSpaceShip(renderer, spaceShip);
        moveSpaceShip(&spaceShip);
        renderRockets(renderer, &rockets);
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