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

void swap();
void rgb();
void nullIt();
void move();

// Variables
// type g_some_c_variable;

char g_char_msg[] = "prelkep";
char g_char_r = 186;
char g_char_g = 11;
char g_char_b = 171;
int g_int_rgb = -1;
long g_long_word = 0xBA125E34BA561178;
int g_int_cisla[2] = { -1000, 1000 };
long g_long_cisla[2];

int main()
{

    swap();
    printf("%s\n", g_char_msg);

    rgb();
    printf("0x%x\n", g_int_rgb);

    nullIt();
    printf("0x%lx\n", g_long_word);

    move();
    printf("%ld %ld\n", g_long_cisla[0], g_long_cisla[1]);
    return 0;
}
