//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>

// Functions
// void some_asm_function();

void countPositive();
void countEven();
void charToInt();
void countSpaces();

// Variables
// type g_some_c_variable;

int g_int_soucet = 0;
int g_int_pole[10] = {-1,-2,-3,-4,-5,6,7,8,9,10};
long g_int_pocet = 0;
int g_long_pole[10] = {1,2,3,4,5,6,7,8,9,10};
char g_char_pole[10] = { 10, -20, 30, -40, 50, -60, 70, -80, 90, -100 };
int g_int_ext[10] = {0};
char g_char_str[] = " progra mova ni je za bava ! ";
int g_int_mezer = 0;

int main()
{
    countPositive();
    countEven();
    charToInt();
    countSpaces();

    printf("%d\n", g_int_soucet);
    printf("%ld\n", g_int_pocet);
    for (int i = 0; i < 10; i++) {
        printf("%d ", g_int_ext[i]);
    }
    printf("\n");
    printf("%d\n", g_int_mezer);

    return 0;
}
