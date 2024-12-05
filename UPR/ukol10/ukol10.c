#include "sdl.h"
#include "dynamic_array.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdio.h>

typedef struct {
    SDL_Rect destRect;
    float angle;
    float fallSpeed;
    float rRotation;
    SDL_Point center;
} Snowflake;

int main() {

    srand((unsigned int)time(NULL));

    SDL_Context ctx = sdl_context_init("snowflakes", 750, 750);

    SDL_Event event;
    SDL_Texture* texture = IMG_LoadTexture(ctx.renderer, "snowflake.svg");

    dynarray snowflakes;
    dynarray_init(&snowflakes, 5);

    int running = 1;
    while(running) {
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    running = 0;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int mouseX = 0;
                        int mouseY = 0;
                        SDL_GetMouseState(&mouseX, &mouseY);

                        float rFallSpeed = 3.0f + ((float)rand() / (float)RAND_MAX * (3.0f - 1.0f));
                        int rSize = rand() % 100 + 50;
                        float rRotation = 2.0f + ((float)rand() / (float)RAND_MAX * (3.0f - 1.0f));

                        Snowflake* newSnowflake = (Snowflake*)malloc(sizeof(Snowflake));
                        newSnowflake->destRect = (SDL_Rect) { mouseX - rSize / 2, mouseY - rSize / 2, rSize, rSize };
                        newSnowflake->angle = 0.0f;
                        newSnowflake->fallSpeed = rFallSpeed;
                        newSnowflake->rRotation = rRotation;
                        newSnowflake->center = (SDL_Point) { rSize / 2, rSize / 2 };
                        dynarray_push(&snowflakes, newSnowflake);
                    }
                    break;
                }
            }
        }

        for (int i = 0; i < snowflakes.size; i++) {
            Snowflake* snowflake = (Snowflake*) snowflakes.items[i];

            snowflake->destRect.y += (int)snowflake->fallSpeed;
            snowflake->angle += snowflake->rRotation;
            if (snowflake->angle >= 360) {
                snowflake->angle -= 360;
            }

            if (snowflake->destRect.y > 750) {
                dynarray_remove(&snowflakes, snowflake);
            }
        }

        SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 0);
        SDL_RenderClear(ctx.renderer);

        for (int i = 0; i < snowflakes.size; i++) {
            Snowflake* snowflake = (Snowflake*) snowflakes.items[i];
            SDL_RenderCopyEx(ctx.renderer, texture, NULL, &snowflake->destRect, snowflake->angle, &snowflake->center, SDL_FLIP_NONE);
        }

        SDL_RenderPresent(ctx.renderer);
        SDL_Delay(16);
    }

    dynarray_free(&snowflakes);
    SDL_DestroyTexture(texture);
    IMG_Quit();
    sdl_context_free(&ctx);

    return 0;
}