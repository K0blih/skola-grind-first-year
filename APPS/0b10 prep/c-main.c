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

void uprav_pole( int *t_pole, int t_N );
int hledej_max_msb( long *t_pole, int t_N );
int pocet_cislic( char *t_str );
void nahrada_mezer( char *t_str, char t_nahradni_znak );

// Variables
// type g_some_c_variable;

int t1_pole[] = {1,-2,3,-4,5,-6,7,-8,8,-10};
int t1_N = 10;
long t2_pole[] = {0x1000000000000000, 0x1200000000000000, 0xBB00000000000000, 0x2500000000000000, 0x1100000000000000, 0x3300000000000000, 0x4500000000000000, 0xAB00000000000000, 0x8800000000000000, 0x9900000000000000};
int t2_N = 10;
char t1_str[] = "as1dsadsa1dsad4sad8as";
char t2_str[] = "ahoj jak se mas ";
char t_nahradni_znak = '_';

int main()
{
    uprav_pole(t1_pole, t1_N);
    for(int i = 0; i < t1_N; i++) {
        printf("%d ", t1_pole[i]);
    }
    printf("\n");

    printf("%d\n", hledej_max_msb(t2_pole, t2_N));

    printf("%d\n", pocet_cislic(t1_str));

    nahrada_mezer(t2_str, t_nahradni_znak);
    printf("%s\n", t2_str);

    return 0;
}
