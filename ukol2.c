#include <stdio.h>

void plnyRadek(int length);
void fullSquare(int length, int height);
void okrajovyRadek(int length);
void frame(int length, int height);
void vyplnenyRadek(int length, int height);
void filledFrame(int length, int height);
void diagonal(int length);
void reversedDiagonal(int length);
void triangle(int height);
void hammer(int length, int height);
void hLetter(int length, int height);
void bonus(int length, int height);

int main() {

    int obrazec = 0;
    int A = 0;
    int B = 0;
    scanf("%d %d %d", &obrazec, &A, &B);

    switch (obrazec) {
        case 0:
        fullSquare(A, B);
        break;

        case 1:
        frame(A, B);
        break;

        case 2:
        filledFrame(A, B);
        break;

        case 3:
        diagonal(A);
        break;

        case 4:
        reversedDiagonal(A);
        break;

        case 5:
        triangle(A);
        break;

        case 6:
        hammer(A, B);
        break;

        case 7:
        hLetter(A, B);
        break;

        case 9:
        bonus(A, B);
        break;

        default:
        printf("Neznamy obrazec\n");
    }

    return 0;
}

void plnyRadek(int length) {
    for (int i = 0; i < length; i++) {
        printf("x");
    }
    printf("\n");
}

void fullSquare(int length, int height) {
    for (int i = 0; i < height; i++) {
         plnyRadek(length);
    }
}

void okrajovyRadek(int length) {
    for (int i = 0; i < length; i++) {
        if (i == 0 || i == length-1) {
            printf("x");
        }
        else {
            printf(" ");
        }
    }
    printf("\n");
}

void frame(int length, int height) {
    plnyRadek(length);
    for (int j = 0; j < height-2; j++) {
        okrajovyRadek(length);
    }
    plnyRadek(length);
}

void vyplnenyRadek(int length, int height) {
    for (int i = 0; i < height-2; i++) {
        for (int j = 0; j < length; j++) {
            if (j == 0 || j == length-1) {
                printf("x");
            }
            else {
                printf("%d", ((j-1)+((length-2)*i)) % 10);        
            }
        }
        printf("\n");
    }
}

void filledFrame(int length, int height) {
    plnyRadek(length);
    vyplnenyRadek(length, height);
    plnyRadek(length);
}

void diagonal(int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < i; j++) { 
            printf(" "); 
        }
        printf("x");
        printf("\n");
    }
}

void reversedDiagonal(int length) {
    for (int i = length; 0 < i; i--) {
        for (int j = 0; j < i-1; j++) { 
            printf(" "); 
        }
        printf("x");
        for (int j = 0; j < length - i; j++) {
            printf(" ");
        }
        printf("\n");
    }
}

void triangle(int height) {
    for (int i = height, L = -1; 1 < i; i--, L+=2) {
        for (int j = 0; j < i-1; j++) { 
            printf(" "); 
        }
        printf("x");
        for (int j = 0; j < L; j++) {
            printf(" "); 
        }
        if(L > 0) { printf("x"); }
        for (int j = 0; j < i-1; j++) { 
            printf(" "); 
        }
        printf("\n");
    }
    plnyRadek(height*2-1);
}

void hammer(int length, int height) {
    plnyRadek(length);
    int middle = length / 2 + 1;
    for (int i = 0; i < height-1; i++) {
        for (int j = 1; j <= middle; j++) {
            if (j == middle) {
                printf("x");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void hLetter(int length, int height) {
    int middle = height / 2;
    for (int i = 0; i < height; i++) {
        if (i == middle) {
            plnyRadek(length);
            continue;
        }
        okrajovyRadek(length);
    }
}

void bonus(int length, int height) {
    plnyRadek(length);
    for (int i = 0; i < height-2; i++) {
        for (int j = 0; j < length; j++) {
            if (j == 0 || j == length-1) {
                printf("x");
            }
            else {
                printf("%d", ((j-1)*(height-2)+i) % 10);        
            }
        }
        printf("\n");
    }
    plnyRadek(length);
}