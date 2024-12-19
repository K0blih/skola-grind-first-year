#include "alien.h"
#include "globals.h"

int reachedEdge = 0;
int SSreachedEdge = 0;
int direction = 1;
int SSdirection = 1;
int alienSpeed = 10;

// x, y, w, h
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

void drawAliens (SDL_Renderer *renderer, Alien aliens[ALIEN_ROWS][ALIEN_COLS]) {
    for (int i = 0; i < ALIEN_ROWS; i++) {
        for (int j = 0; j < ALIEN_COLS; j++) {
            if (aliens[i][j].health) {
                SDL_RenderCopy(renderer, aliens[i][j].image, NULL, &aliens[i][j].destRect);
            }
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

    // direction change
    if (reachedEdge) {
        reachedEdge = 0;
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
    int offsetY = 10;
    spaceShip->image = IMG_LoadTexture(renderer, "assets/space_ship.png");
    spaceShip->destRect.x = startX;
    spaceShip->destRect.y = offsetY;
    spaceShip->destRect.w = SPACE_SHIP_WIDTH;
    spaceShip->destRect.h = SPACE_SHIP_HEIGHT;
    spaceShip->health = 1;
}

void drawSpaceShip (SDL_Renderer *renderer, Alien spaceShip) {
    if (spaceShip.health) {
        SDL_RenderCopy(renderer, spaceShip.image, NULL, &spaceShip.destRect);
    }
}

void moveSpaceShip (Alien *spaceShip) {

    if (spaceShip->health) {
        if ((spaceShip->destRect.x + SSdirection * alienSpeed) < 0 || (spaceShip->destRect.x + SSdirection * alienSpeed + SPACE_SHIP_WIDTH) > TAB_WIDTH) {
            SSreachedEdge = 1;
        }
    }

    if (SSreachedEdge) {
        SSdirection *= -1;
    }

    // move space ship
    if (spaceShip->health) {
        spaceShip->destRect.x += SSdirection * alienSpeed;
    }

    // direction change
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