#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "player.h"

void sdl_draw_text(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, const char* text);
void updateScore(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, int score);
void updateHealth(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, Player player);