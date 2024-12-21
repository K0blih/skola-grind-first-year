#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture* createTextTexture(SDL_Renderer *renderer, char *text, SDL_Color color, TTF_Font *font);
void renderText (SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *destRect);
void renderSimpleText(SDL_Renderer *renderer, int x, int y, SDL_Color color, const char *text);