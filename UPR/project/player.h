#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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