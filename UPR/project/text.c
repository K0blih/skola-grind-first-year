#include "text.h"

SDL_Texture* createTextTexture(SDL_Renderer *renderer, char *text, SDL_Color color, TTF_Font *font) {

    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

void renderText(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *destRect) {
    SDL_RenderCopy(renderer, texture, NULL, destRect);
}

void renderSimpleText(SDL_Renderer *renderer, int x, int y, SDL_Color color, const char *text) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int textWidth = strlen(text) * 8;
    int textHeight = 16; // Assuming 8x16 characters

    SDL_Rect destRect = {x, y, textWidth, textHeight};
    SDL_RenderDrawRect(renderer, &destRect);

    // Render each character (very basic method)
    for (int i = 0; i < strlen(text); i++) {
        SDL_Rect charRect = {x + (i * 8), y, 8, 16};
        SDL_RenderFillRect(renderer, &charRect);
    }
}