#include "menu.h"

void gameOverLoop (SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, int *again, int score, dynarray *rockets, dynarray *alienRockets) {

    SDL_Rect gameOverRect = {TAB_WIDTH / 2 - 200, (TAB_HEIGHT / 3) - 40, 400, 80};
    SDL_Rect topScoreRect = {TAB_WIDTH / 2 - 200, (TAB_HEIGHT / 2) - 60, 400, 80};
    SDL_Rect scoreRect = {TAB_WIDTH / 2 - 175, (TAB_HEIGHT / 2) + 20, 350, 80};
    // SDL_Rect end = {10, (TAB_HEIGHT / 3 * 2), 350, 80};
    // SDL_Rect retry = {TAB_WIDTH - 360, (TAB_HEIGHT / 3 * 2), 350, 80};
    SDL_Rect retry = {TAB_WIDTH / 2 - 225, (TAB_HEIGHT / 3 * 2), 450, 80};
    SDL_Rect end = {TAB_WIDTH / 2 - 200, (TAB_HEIGHT / 3 * 2) + 80, 400, 80};

    // get and update top score
    int topScore = 0;
    FILE *readFile = fopen("topScore.txt", "r");
    if (readFile == NULL) {
        topScore = score;        
        FILE *writeFile = fopen("topScore.txt", "w");
        fprintf(writeFile, "%d\n", topScore);
        fclose(writeFile);
    }
    else {
        char buffer[10];
        while (fgets(buffer, sizeof(buffer), readFile) != NULL) {
            topScore = atoi(buffer);
            if (topScore < score) {
                topScore = score;

                FILE *writeFile = fopen("topScore.txt", "w");
                fprintf(writeFile, "%d\n", topScore);
                fclose(writeFile);
            }
        }
        fclose(readFile);
    }

    // create score strings
    int bufferSize = 16;
    char *scoreStr = (char*)malloc(bufferSize * sizeof(char));
    sprintf(scoreStr, "SCORE %d", score);
    char *topScoreStr = (char*)malloc(bufferSize * sizeof(char));
    sprintf(topScoreStr, "TOP SCORE %d", topScore);

    int gameOverLoop = 1;
    SDL_Event event;
    while (gameOverLoop) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    gameOverLoop = 0;
                    (*again) = 0;
                    break;
                }
                case SDL_KEYDOWN: {
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        gameOverLoop = 0;
                        (*again) = 0;
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                        gameOverLoop = 0;
                    }
                }
            }
        }

        // render game over
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        sdl_draw_text(renderer, font, color, gameOverRect, "GAME OVER");
        sdl_draw_text(renderer, font, color, topScoreRect, topScoreStr);
        sdl_draw_text(renderer, font, color, scoreRect, scoreStr);
        sdl_draw_text(renderer, font, color, retry, "PRESS SPACE TO RETRY");
        sdl_draw_text(renderer, font, color, end, "PRESS ESC TO QUIT");

        SDL_RenderPresent(renderer);
    }

    dynarray_free(rockets);
    dynarray_free(alienRockets);
    free(scoreStr);
    free(topScoreStr);
}

void menu (SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, int *again) {
    
    SDL_Rect gameStartRect = {TAB_WIDTH / 2 - 200, (TAB_HEIGHT / 3) - 40, 400, 80};
    SDL_Rect retry = {TAB_WIDTH / 2 - 225, (TAB_HEIGHT / 3 * 2), 450, 80};
    SDL_Rect end = {TAB_WIDTH / 2 - 200, (TAB_HEIGHT / 3 * 2) + 80, 400, 80};

    int gameStartLoop = 1;
    SDL_Event event;
    while (gameStartLoop) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    gameStartLoop = 0;
                    (*again) = 0;
                    break;
                }
                case SDL_KEYDOWN: {
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        gameStartLoop = 0;
                        (*again) = 0;
                    }
                    if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                        gameStartLoop = 0;
                    }
                }
            }
        }

        // render game over
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        sdl_draw_text(renderer, font, color, gameStartRect, "SPACE INVADERS");
        sdl_draw_text(renderer, font, color, retry, "PRESS SPACE TO START");
        sdl_draw_text(renderer, font, color, end, "PRESS ESC TO QUIT");

        SDL_RenderPresent(renderer);
    }
}