#include <stdio.h>

void invalidCounter(int count);
int digitCounter(int number);
void VerticalCounter(int* count);

int main() {

    char mod = '0';
    int numbers = 0;
    int range = 0;
    int invalid = 0;
    int digitFlag = 0;
    int max = 0;
    
    scanf("%c", &mod);
    scanf("%d %d", &numbers, &range);

    int histogram[9];
    int match[9] = {0};
    for (int i = 0; i < 9; i++) {
        histogram[i] = i + range;
        if(digitFlag < digitCounter(histogram[i])) {
            digitFlag = digitCounter(histogram[i]);
        }
    }

    for (int i = 0; i < numbers; i++) {
        int tmp = 0;
        scanf("%d", &tmp);
        if (tmp < range || tmp > range + 8) {
            invalid++;
        }
        for (int i = 0; i < 9; i++) {
            if (histogram[i] == tmp) {
                match[i] += 1;
            }
        }
    }

    switch (mod) {
        case 'h':

        for (int i = 0; i < 9; i++) {
            if (digitFlag > digitCounter(histogram[i])) {
                printf(" ");
            }
            printf("%d", histogram[i]);
            if (match[i] > 0) {
                printf(" ");
                invalidCounter(match[i]);
            }
            else {
                printf("\n");
            }
        }
        if (invalid > 0) {
            printf("invalid: ");
            invalidCounter(invalid);
        }
        break;

        case 'v':
        max = invalid;
        for (int i = 0; i < 9; i++){
            if (max < match[i]) {
                max = match[i];
            }
        }
        
        invalid = max - invalid;
        for (int i = 0; i < 9; i++){
            match[i] = max - match[i];
        }

        for (int i = 0; i < max; i++) {
            VerticalCounter(&invalid);
            VerticalCounter(&match[0]);
            VerticalCounter(&match[1]);
            VerticalCounter(&match[2]);
            VerticalCounter(&match[3]);
            VerticalCounter(&match[4]);
            VerticalCounter(&match[5]);
            VerticalCounter(&match[6]);
            VerticalCounter(&match[7]);
            VerticalCounter(&match[8]);
            printf("\n");
        }
        printf("i123456789\n");
        break;

        default:
        printf("Neplatny mod vykresleni\n");
        return 1;
    }

    return 0;
}

void invalidCounter(int count) {
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

void VerticalCounter(int* count) {
    if (*count <= 0) {
        printf("#");
    }
    else {
        printf(" ");
    }
    *count -= 1;
}



