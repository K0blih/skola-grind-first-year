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

void allocateGrid(char **grid, int rows, int cols);
void initGrid(char *grid, int rows, int cols);
void printGrid(char *grid, int rows, int cols);
void deallocateGrid(char *grid);
void doAction(char **grid, struct Turtle *turtle, char action, int rows, int cols);
void updateGrid(char **grid, struct Turtle *turtle, int cols);

int main() {
    
    int rows = 0;
    int cols = 0;
    int turtleCount = 1;
    struct Turtle turtle[3] = {
        {0, 0, dirRight},
        {0, 0, dirRight},
        {0, 0, dirRight}
    };

    scanf("%d %d", &rows, &cols);

    char* grid = NULL;
    allocateGrid(&grid, rows, cols);
    initGrid(grid, rows, cols);

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

    printGrid(grid, rows, cols);
    deallocateGrid(grid);

    return 0;
}

void allocateGrid(char **grid, int rows, int cols) {
    *grid = (char*)malloc(sizeof(char) * (size_t)rows * (size_t)cols);
}

void initGrid(char *grid, int rows, int cols) {
    for (int i = 0; i < rows * cols; i++) {
        grid[i] = '.';
    }
}

void printGrid(char *grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", grid[i * cols + j]);
        }
        printf("\n");
    }
}

void deallocateGrid(char *grid) {
    free(grid);
    grid = NULL;
}

void doAction(char **grid, struct Turtle *turtle, char action, int rows, int cols) {
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
        updateGrid(grid, turtle, cols);
    }
}

void updateGrid(char **grid, struct Turtle *turtle, int cols) {
    int index = turtle->locRow * cols + turtle->locCol;
    if ((*grid)[index] == '.') {
        (*grid)[index] = 'o';
    } 
    else if ((*grid)[index] == 'o') {
        (*grid)[index] = '.';
    }
}