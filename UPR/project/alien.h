#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "globals.h"
#include "dynamic_array.h"
#include "player.h"

#define ALIEN_WIDTH 40
#define ALIEN_ROWS 5
#define ALIEN_COLS 10
#define ALIEN_WIDTH 40
#define ALIEN_HEIGHT 40
#define ALIEN_SPACING 15
#define SPACE_SHIP_WIDTH 52
#define SPACE_SHIP_HEIGHT 23


typedef struct {
    SDL_Texture* image;
    SDL_Rect destRect;
    int health;
} Alien;

void initAliens (SDL_Renderer *renderer, Alien aliens[ALIEN_ROWS][ALIEN_COLS]);
void renderAliens (SDL_Renderer *renderer, Alien aliens[ALIEN_ROWS][ALIEN_COLS], Alien *spaceShip);
void moveAliens (Alien aliens[ALIEN_ROWS][ALIEN_COLS]);
void alienRocket(SDL_Renderer *renderer, dynarray *rockets, Alien aliens[ALIEN_ROWS][ALIEN_COLS]);
void alienRocketMovement(dynarray *alienRockets);
void renderAlienRockets(SDL_Renderer *renderer, dynarray *alienRockets);
int detectAlienCollision (SDL_Rect rocket, Alien aliens[ALIEN_ROWS][ALIEN_COLS]);
void initSpaceShip (SDL_Renderer *renderer, Alien *spaceShip);
void renderSpaceShip (SDL_Renderer *renderer, Alien spaceShip);
void moveSpaceShip (Alien *spaceShip);
int detectSpaceShipCollision (SDL_Rect rocket, Alien *spaceShip);
void collisionCheck(dynarray *rockets, Alien aliens[ALIEN_ROWS][ALIEN_COLS], Alien *spaceShip);
