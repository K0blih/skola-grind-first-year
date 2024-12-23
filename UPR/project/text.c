#include "text.h"

void sdl_draw_text (SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, const char* text) {
    // Vykreslení textu se zadaným fontem a barvou do obrázku (surface)
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    // Převod surface na hardwarovou texturu
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Vykreslení obrázku
    SDL_RenderCopy(renderer, texture, NULL, &location);

    // Uvolnění textury a surface
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void updateScore (SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, int score) {
    int bufferSize = 16;
    char *str = (char*)malloc(bufferSize * sizeof(char));

    sprintf(str, "SCORE %d", score);

    sdl_draw_text(renderer, font, color, location, str);

    free(str);
}

void updateHealth (SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, Player player) {
    int bufferSize = 11;
    char *str = (char*)malloc(bufferSize * sizeof(char));

    sprintf(str, "HEALTH %d", player.health);

    sdl_draw_text(renderer, font, color, location, str);

    free(str);
}