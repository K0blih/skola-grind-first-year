#include "player.h"
#include "globals.h"

void initPlayer (SDL_Renderer *renderer, Player *player) {
    player->image = IMG_LoadTexture(renderer, "assets/player.png");
    player->destRect.x = TAB_WIDTH / 2;
    player->destRect.y = TAB_HEIGHT - 30;
    player->destRect.w = 50;
    player->destRect.h = 25;
    player->health = 3;
    player->destRect.x -= player->destRect.w / 2;
}