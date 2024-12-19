#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define ALIEN_WIDTH 40
#define ALIEN_ROWS 5
#define ALIEN_COLS 10
#define ALIEN_WIDTH 40
#define ALIEN_HEIGHT 40
#define ALIEN_SPACING 15
#define SPACE_SHIP_WIDTH 88
#define SPACE_SHIP_HEIGHT 42


typedef struct {
    SDL_Texture* image;
    SDL_Rect destRect;
    int health;
} Alien;

void initAliens (SDL_Renderer *renderer, Alien aliens[ALIEN_ROWS][ALIEN_COLS]);
void drawAliens (SDL_Renderer *renderer, Alien aliens[ALIEN_ROWS][ALIEN_COLS]);
void moveAliens (Alien aliens[ALIEN_ROWS][ALIEN_COLS]);
int detectAlienCollision (SDL_Rect rocket, Alien aliens[ALIEN_ROWS][ALIEN_COLS]);
void initSpaceShip (SDL_Renderer *renderer, Alien *spaceShip);
void drawSpaceShip (SDL_Renderer *renderer, Alien spaceShip);
void moveSpaceShip (Alien *spaceShip);
int detectSpaceShipCollision (SDL_Rect rocket, Alien *spaceShip);