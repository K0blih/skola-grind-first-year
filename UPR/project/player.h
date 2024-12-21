#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dynamic_array.h"
#include "globals.h"

typedef struct {
    SDL_Texture* image;
    SDL_Rect destRect;
    int health;
} Player;

typedef struct {
    SDL_Texture* image;
    SDL_Rect destRect;
} Rocket;

void initPlayer(SDL_Renderer *renderer, Player *player);
void playerRocket(SDL_Renderer *renderer, dynarray *rockets, Player player);
void rocketMovement(dynarray *rockets);
void renderRockets(SDL_Renderer *renderer, dynarray *rockets);