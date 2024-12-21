#include "player.h"

void initPlayer (SDL_Renderer *renderer, Player *player) {
    player->image = IMG_LoadTexture(renderer, "assets/player.png");
    player->destRect.x = TAB_WIDTH / 2;
    player->destRect.y = TAB_HEIGHT - 30;
    player->destRect.w = 50;
    player->destRect.h = 25;
    player->health = 3;
    player->destRect.x -= player->destRect.w / 2;
}

void playerRocket(SDL_Renderer *renderer, dynarray *rockets, Player player) {
    Rocket* newRocket = (Rocket*)malloc(sizeof(Rocket));
    newRocket->image = IMG_LoadTexture(renderer, "assets/player_rocket.png");
    newRocket->destRect.x = player.destRect.x + player.destRect.w / 2 - 2;
    newRocket->destRect.y = player.destRect.y - 3;
    newRocket->destRect.w = 5;
    newRocket->destRect.h = 15;
    dynarray_push(rockets, newRocket);
}

void rocketMovement(dynarray *rockets) {
    for (int i = 0; i < rockets->size; i++) {
        Rocket* rocket = (Rocket*) rockets->items[i];

        rocket->destRect.y -= ROCKET_VELOCITY;

        if (rocket->destRect.y < 0) {
            SDL_DestroyTexture(rocket->image);
            dynarray_remove(rockets, rocket);
        }
    }
}

void renderRockets(SDL_Renderer *renderer, dynarray *rockets) {
    for (int i = 0; i < rockets->size; i++) {
        Rocket* rocket = (Rocket*) rockets->items[i];
        SDL_RenderCopy(renderer, rocket->image, NULL, &rocket->destRect);
    }
}