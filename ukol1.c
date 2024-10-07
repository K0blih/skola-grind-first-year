#include <stdio.h>

int main () {
    int money = 0;
    int ban50 = 0;
    int ban20 = 0;
    int ban10 = 0;
    int ban5 = 0;
    int ban2 = 0;
    int ban1 = 0;

    scanf("%d", &money);

    ban50 = money / 5000;

    money = money % 5000;
    ban20 = money / 2000;

    money = money % 2000;
    ban10 = money / 1000;

    money = money % 1000;
    ban5 = money / 500;

    money = money % 500;
    ban2 = money / 200;

    money = money % 200;
    ban1 = money / 100;

    printf("Bankovka 5000: %dx\n", ban50);
    printf("Bankovka 2000: %dx\n", ban20);
    printf("Bankovka 1000: %dx\n", ban10);
    printf("Bankovka 500: %dx\n", ban5);
    printf("Bankovka 200: %dx\n", ban2);
    printf("Bankovka 100: %dx\n", ban1);

    return 0;
}