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

void bubble( int *tp_int, int t_N );
void strup( char *t_str );
char nejcastejsi( char *t_str );
long prvocislo( long t_cislo );

// Variables
// type g_some_c_variable;

int tp_int[] = {5, 3, 2, 4, 1};
int t_N = 5;
char t_str[] = "ahoooj";
long t_cislo = 4;


int main()
{
    bubble(tp_int, t_N);
    for (int i = 0; i < t_N; i++) {
        printf("%d ", tp_int[i]);
    }
    printf("\n");

    strup(t_str);
    printf("%s\n", t_str);

    printf("%c\n", nejcastejsi(t_str));

    printf("%ld\n", prvocislo(t_cislo));
    return 0;
}
