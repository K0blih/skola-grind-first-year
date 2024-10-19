#include <stdio.h>

void printMatches(int count);
int digitCounter(int number);
void printHorizontalMatches(int range, int* match);
void printVerticalMatches(int* match);

int main()
{
    char mod = '0';
    int numbers = 0;
    int range = 0;

    scanf("%c", &mod);
    scanf("%d %d", &numbers, &range);

    int match[10] = {0};

    for (int i = 0; i < numbers; i++) {
        int tmp = 0;
        scanf("%d", &tmp);
        if (tmp < range || tmp > range + 8) {
            match[9] += 1;
        }
        else {
            match[tmp-range] += 1;
        }
    }

    switch (mod) {
        case 'h':
        printHorizontalMatches(range, match);
        break;

        case 'v':
        printVerticalMatches(match);
        printf("i123456789\n");
        break;

        default:
        printf("Neplatny mod vykresleni\n");
        return 1;
    }

    return 0;
}

void printMatches(int count) {
    for (int i = 0; i < count; i++) {
        printf("#");
    }
    printf("\n");
}

int digitCounter(int number) {
    int count = 0;
    if (number < 10) {
        return 1;
    }
    while(number != 0) {
        number /= 10;
        count++;
    }
    return count;
}

void printHorizontalMatches(int range, int* match) {
    int maxLen = digitCounter(range + 8);
    for (int i = 0; i < 9; i++) {
        printf("%*d", maxLen, range + i);
        if (match[i] > 0) {
            printf(" ");
            printMatches(match[i]);
        }
        else {
            printf("\n");
        }
    }
    if (match[9] > 0) {
        printf("invalid: ");
        printMatches(match[9]);
    }
}

void printVerticalMatches(int* match) {
    int maxHeight = match[9];
    for (int i = 0; i < 9; i++){
        if (maxHeight < match[i]) {
            maxHeight = match[i];
        }
    }

    for (int row = 0; row < maxHeight; row++) {
        if ((maxHeight - row) <= match[9]) {
            printf("#");
        }
        else {
            printf(" ");
        }
        for (int i = 0; i <= 8; i++) {
            if ((maxHeight - row) <= match[i]) {
                printf("#");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
