#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "text.h"

void gameOverLoop(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, int *again, int score, dynarray *rockets, dynarray *alienRockets);