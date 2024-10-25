#include <stdio.h>
#include <stdlib.h>

enum Direction {
    dirUp = 0,
    dirLeft = 1,
    dirDown = 2,
    dirRight = 3
};

struct Turtle {
    int locRow;
    int locCol;
    enum Direction dir;
};

void allocateGrid(char ***grid, int rows, int cols);
void initGrid(char ***grid, int rows, int cols);
void printGrid(char ***grid, int rows, int cols);
void deallocateGrid(char ***grid, int rows);
void doAction(char ***grid, struct Turtle *turtle, char action, int rows, int cols);
void updateGrid(char ***grid, struct Turtle *turtle);

int main() {
    
    long unsigned int rows = 0;
    long unsigned int cols = 0;
    int turtleCount = 1;
    struct Turtle turtle[3] = {
        {0, 0, dirRight},
        {0, 0, dirRight},
        {0, 0, dirRight}
    };

    scanf("%lu %lu", &rows, &cols);

    char** grid = NULL;
    allocateGrid(&grid, rows, cols);
    initGrid(&grid, rows, cols);

    while (1) {

        char tmp = '0';
        scanf("%c", &tmp);


        if (tmp == 'x') {
            break;
        }
        else if (tmp == 'f') {
            if (turtleCount < 3) {
                turtleCount++;
            }
        }
        for(int i = 0; i < turtleCount; i++) {
            doAction(&grid, &turtle[i], tmp, rows, cols);
        }
    }

    printGrid(&grid, rows, cols);
    deallocateGrid(&grid, rows);

    return 0;
}

void allocateGrid(char ***grid, int rows, int cols) {
    *grid = (char**)malloc(sizeof(char*) * rows);
    for (int i = 0; i < rows; i++) {
        (*grid)[i] = (char*)malloc(sizeof(char) * cols);
    }
}

void initGrid(char ***grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            (*grid)[i][j] = '.';
        }
    }
}

void printGrid(char ***grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", (*grid)[i][j]);
        }
        printf("\n");
    }
}

void deallocateGrid(char ***grid, int rows) {
    for (int i = 0; i < rows; i++) {
        free((*grid)[i]);
    }
    free(*grid);
    *grid = NULL;
}

void doAction(char ***grid, struct Turtle *turtle, char action, int rows, int cols) {
    if (action == 'l') {
        turtle->dir = (turtle->dir + 1) % 4;
    } 
    else if (action == 'r') {
        turtle->dir = (turtle->dir + 3) % 4;
    } 
    else if (action == 'm') {
        if (turtle->dir == dirUp) {
            turtle->locRow--;
        } 
        else if (turtle->dir == dirLeft) {
            turtle->locCol--;
        } 
        else if (turtle->dir == dirDown) {
            turtle->locRow++;
        } 
        else if (turtle->dir == dirRight) {
            turtle->locCol++;
        }
        if (turtle->locRow < 0) {
            turtle->locRow = rows - 1;
        } 
        else if (turtle->locRow >= rows) {
            turtle->locRow = 0;
        }
        if (turtle->locCol < 0) {
            turtle->locCol = cols - 1;
        } 
        else if (turtle->locCol >= cols) {
            turtle->locCol = 0;
        }
    }
    else if (action == 'o') {
        updateGrid(grid, turtle);
    }
}

void updateGrid(char ***grid, struct Turtle *turtle) {
    if ((*grid)[turtle->locRow][turtle->locCol] == '.') {
        (*grid)[turtle->locRow][turtle->locCol] = 'o';
    } 
    else if ((*grid)[turtle->locRow][turtle->locCol] == 'o') {
        (*grid)[turtle->locRow][turtle->locCol] = '.';
    }
}