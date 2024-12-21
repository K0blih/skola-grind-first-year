#include "alien.h"

int reachedEdge = 0;
int SSreachedEdge = 0;
int direction = 1;
int SSdirection = 1;
int alienSpeed = 10;
int SSspeed = 6;

void initAliens (SDL_Renderer *renderer, Alien aliens[ALIEN_ROWS][ALIEN_COLS]) {
    int totalGridWidth = (ALIEN_COLS * ALIEN_WIDTH) + ((ALIEN_COLS - 1) * ALIEN_SPACING);
    int startX = (TAB_WIDTH - totalGridWidth) / 2;
    int offsetY = 60;

    for (int i = 0; i < ALIEN_ROWS; i++) {
        for (int j = 0; j < ALIEN_COLS; j++) {
            if (i == 0) {
                aliens[i][j].image = IMG_LoadTexture(renderer, "assets/top_alien.png");
            }
            else if (i > 0 && i < ALIEN_ROWS - 1) {
                aliens[i][j].image = IMG_LoadTexture(renderer, "assets/middle_alien.png");
            }
            else {
                aliens[i][j].image = IMG_LoadTexture(renderer, "assets/bottom_alien.png");
            }
            aliens[i][j].destRect.x = startX + j * (ALIEN_WIDTH + ALIEN_SPACING);
            aliens[i][j].destRect.y = offsetY + i * (ALIEN_HEIGHT + ALIEN_SPACING);
            aliens[i][j].destRect.w = ALIEN_WIDTH;
            aliens[i][j].destRect.h = ALIEN_HEIGHT;
            aliens[i][j].health = 1;
        }
    }
}

void renderAliens (SDL_Renderer *renderer, Alien aliens[ALIEN_ROWS][ALIEN_COLS], Alien *spaceShip) {
    // atleast 1 alive check
    int alive = 0;
    for (int i = 0; i < ALIEN_ROWS; i++) {
        for (int j = 0; j < ALIEN_COLS; j++) {
            if (aliens[i][j].health) {
                SDL_RenderCopy(renderer, aliens[i][j].image, NULL, &aliens[i][j].destRect);
                alive++;
            }
        }
    }

    if (alive == 0) {
        initAliens(renderer, aliens);
        if (spaceShip->health == 0) {
            initSpaceShip(renderer, spaceShip);
        }
    }
}

void moveAliens (Alien aliens[ALIEN_ROWS][ALIEN_COLS]) {
    // edge check
    for (int i = 0; i < ALIEN_ROWS; i++) {
        for (int j = 0; j < ALIEN_COLS; j++) {
            if (aliens[i][j].health) {
                if ((aliens[i][j].destRect.x + direction * alienSpeed) < 0 || (aliens[i][j].destRect.x + direction * alienSpeed + ALIEN_WIDTH) > TAB_WIDTH) {
                    reachedEdge = 1;
                    break;
                }
            }
        }
    }

    // direction change
    if (reachedEdge) {
        direction *= -1;
    }

    // move aliens
    for (int i = 0; i < ALIEN_ROWS; i++) {
        for (int j = 0; j < ALIEN_COLS; j++) {
            if (aliens[i][j].health) {
                aliens[i][j].destRect.x += direction * alienSpeed;
                if (reachedEdge) {
                    aliens[i][j].destRect.y += ALIEN_HEIGHT;
                }
            }
        }
    }

    if (reachedEdge) {
        reachedEdge = 0;
    }
}

void alienRocket (SDL_Renderer *renderer, dynarray *alienRockets, Alien aliens[ALIEN_ROWS][ALIEN_COLS]) {
    
    for (int col = 0; col < ALIEN_COLS; col++) {
        // lowest in column and alive
        for (int row = ALIEN_ROWS - 1; row >= 0; row--) {
            if (aliens[row][col].health) {
                if (rand() % 420 < 1) { // 420 / 60 = 7% chance per move
                    Rocket *newAlienRocket = (Rocket*)malloc(sizeof(Rocket));
                    newAlienRocket->image = IMG_LoadTexture(renderer, "assets/rocket.png");
                    newAlienRocket->destRect.x = aliens[row][col].destRect.x + aliens[row][col].destRect.w / 2 - 3;
                    newAlienRocket->destRect.y = aliens[row][col].destRect.y + aliens[row][col].destRect.h - 12;
                    newAlienRocket->destRect.w = 5;
                    newAlienRocket->destRect.h = 15;
                    dynarray_push(alienRockets, newAlienRocket);
                }
                break; // first row only
            }
        }
    }
}

void alienRocketMovement (dynarray *alienRockets) {
    for (int i = 0; i < alienRockets->size; i++) {
        Rocket* rocket = (Rocket*) alienRockets->items[i];

        rocket->destRect.y += ROCKET_VELOCITY;

        if (rocket->destRect.y > TAB_HEIGHT) {
            SDL_DestroyTexture(rocket->image);
            dynarray_remove(alienRockets, rocket);
        }
    }
}

void renderAlienRockets (SDL_Renderer *renderer, dynarray *alienRockets) {
    for (int i = 0; i < alienRockets->size; i++) {
        Rocket* alienRocket = (Rocket*) alienRockets->items[i];
        SDL_RenderCopy(renderer, alienRocket->image, NULL, &alienRocket->destRect);
    }
}

int detectAlienCollision (SDL_Rect rocket, Alien aliens[ALIEN_ROWS][ALIEN_COLS]) {
    for (int i = 0; i < ALIEN_ROWS; i++) {
        for (int j = 0; j < ALIEN_COLS; j++) {
            if (aliens[i][j].health) {
                int collision = SDL_HasIntersection(&rocket, &aliens[i][j].destRect);
                if (collision) {
                    aliens[i][j].health = 0;
                    return 1;
                }
            }
        }
    }
    return 0;
}

void initSpaceShip (SDL_Renderer *renderer, Alien *spaceShip) {
    int startX = (TAB_WIDTH - SPACE_SHIP_WIDTH) / 2;
    int offsetY = 20;
    spaceShip->image = IMG_LoadTexture(renderer, "assets/space_ship.png");
    spaceShip->destRect.x = startX;
    spaceShip->destRect.y = offsetY;
    spaceShip->destRect.w = SPACE_SHIP_WIDTH;
    spaceShip->destRect.h = SPACE_SHIP_HEIGHT;
    spaceShip->health = 1;
}

void renderSpaceShip (SDL_Renderer *renderer, Alien spaceShip) {
    if (spaceShip.health) {
        SDL_RenderCopy(renderer, spaceShip.image, NULL, &spaceShip.destRect);
    }
}

void moveSpaceShip (Alien *spaceShip) {
    // edge check
    if (spaceShip->health) {
        if ((spaceShip->destRect.x + SSdirection * SSspeed) < 0 || (spaceShip->destRect.x + SSdirection * SSspeed + SPACE_SHIP_WIDTH) > TAB_WIDTH) {
            SSreachedEdge = 1;
        }
    }

    // direction change
    if (SSreachedEdge) {
        SSdirection *= -1;
    }

    // move space ship
    if (spaceShip->health) {
        spaceShip->destRect.x += SSdirection * SSspeed;
    }

    if (SSreachedEdge) {
        SSreachedEdge = 0;
    }
}

int detectSpaceShipCollision (SDL_Rect rocket, Alien *spaceShip) {
    if (spaceShip->health) {
        int collision = SDL_HasIntersection(&rocket, &spaceShip->destRect);
        if (collision) {
            spaceShip->health = 0;
            return 1;
        }
    }
    return 0;
}

void collisionCheck(dynarray *rockets, Alien aliens[ALIEN_ROWS][ALIEN_COLS], Alien *spaceShip) {
    for (int i = 0; i < rockets->size; i++) {
            Rocket* rocket = (Rocket*) rockets->items[i];
            int collision = detectAlienCollision(rocket->destRect, aliens);
            int SScollision = detectSpaceShipCollision(rocket->destRect, spaceShip);
            if (collision) {
                SDL_DestroyTexture(rocket->image);
                dynarray_remove(rockets, rocket);
            }
            if (SScollision) {  
                SDL_DestroyTexture(rocket->image);
                dynarray_remove(rockets, rocket);
            }
        }
}