#include <stdio.h>

void plnyRadek(int sirka);
void fullSquare(int sirka, int vyska);
void okrajovyRadek(int sirka);
void frame(int sirka, int vyska);
void vyplnenyRadek(int sirka, int vyska);
void filledFrame(int sirka, int vyska);
void diagonal(int sirka);
void reversedDiagonal(int sirka);
void triangle(int vyska);
void hammer(int sirka, int vyska);
void hLetter(int sirka, int vyska);
void bonus(int sirka, int vyska);

int main() {

    int obrazec = 0;
    int A = 0;
    int B = 0;
    scanf("%d %d %d", &obrazec, &A, &B);

    switch(obrazec){
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

void plnyRadek(int sirka){
    for(int i = 0; i < sirka; i++){
        printf("x");
    }
    printf("\n");
}

void fullSquare(int sirka, int vyska){
    for(int i = 0; i < vyska; i++){
        plnyRadek(sirka);
    }
}

void okrajovyRadek(int sirka){
    for(int i = 0; i < sirka; i++){
        if(i == 0 || i == sirka-1){
            printf("x");
        }
        else {
            printf(" ");
        }
    }
    printf("\n");
}

void frame(int sirka, int vyska){
    plnyRadek(sirka);
    for(int j = 0; j < vyska-2; j++){
        okrajovyRadek(sirka);
    }
    plnyRadek(sirka);
}

void vyplnenyRadek(int sirka, int vyska){
    for(int i = 0; i < vyska-2; i++){
        for(int j = 0; j < sirka; j++){
            if(j == 0 || j == sirka-1){
                printf("x");
            }
            else {
                printf("%d", ((j-1)+((sirka-2)*i)) % 10);        
            }
        }
        printf("\n");
    }
}

void filledFrame(int sirka, int vyska){
    plnyRadek(sirka);
    vyplnenyRadek(sirka, vyska);
    plnyRadek(sirka);
}

void diagonal(int sirka){
    for(int i = 0; i < sirka; i++){
        for (int j = 0; j < i; j++){ 
            printf(" "); 
        }
        printf("x");
        printf("\n");
    }
}

void reversedDiagonal(int sirka){
    for(int i = sirka; 0 < i; i--){
        for (int j = 0; j < i-1; j++){ 
            printf(" "); 
        }
        printf("x");
        for (int j = 0; j < sirka - i; j++) {
            printf(" ");
        }
        printf("\n");
    }
}

void triangle(int vyska){
    for(int i = vyska, L = -1; 1 < i; i--, L+=2){
        for (int j = 0; j < i-1; j++) { 
            printf(" "); 
        }
        printf("x");
        for (int j = 0; j < L; j++){
            printf(" "); 
        }
        if(L > 0) { printf("x"); }
        for (int j = 0; j < i-1; j++) { 
            printf(" "); 
        }
        printf("\n");
    }
    plnyRadek(vyska*2-1);
}

void hammer(int sirka, int vyska){
    plnyRadek(sirka);
    int middle = sirka / 2 + 1;
    for(int i = 0; i < vyska-1; i++){
        for(int j = 1; j <= middle; j++){
            if(j == middle){
                printf("x");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void hLetter(int sirka, int vyska){
    int middle = vyska / 2;
    for (int i = 0; i < vyska; i++){
        if(i == middle){
            plnyRadek(sirka);
            continue;
        }
        okrajovyRadek(sirka);
    }
}

void bonus(int sirka, int vyska){
    plnyRadek(sirka);
    for(int i = 0; i < vyska-2; i++){
        for(int j = 0; j < sirka; j++){
            if(j == 0 || j == sirka-1){
                printf("x");
            }
            else {
                printf("%d", ((j-1)*(vyska-2)+i) % 10);        
            }
        }
        printf("\n");
    }
    plnyRadek(sirka);
}