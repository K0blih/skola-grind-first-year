#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

// void swap(int* a, int* b){
//     int tmp = *a;
//     *a = *b;
//     *b = tmp;
// }

// int main () {

//     int a = 5;
//     int b = 10;

//     swap(&a, &b);

//     printf("a: %d, b: %d\n", a, b);
    
//     return 0;
// }

// void sumArray(int* a, int N, int* result) {
//     for (int i = 0, j = 0; i < N - N % 2; i += 2, j++) {
//         result[j] = a[i] + a[i+1];
//     }
// }

// int main() {
    
//     int a[] = {0,1,2,3,4,5,6,7,8,9,10};
//     int N = sizeof(a) / sizeof(a[0]);
//     int M = N / 2;
//     int result[M];
//     sumArray(a, N, result);
//     for (int i = 0; i < M; i++) {
//         printf("%d\n", result[i]);
//     }
//     return 0;
// }

// void init_1D(int* p, int  N) {
//     for (int i = 0; i < N; i++) {
//         p[i] = i;
//     }
// }

// void print_1D(int* p, int  N) {
//     for (int i = 0; i < N; i++) {
//         printf("%d\n", p[i]);
//     }
// }

// void allocate_1D(int **p, int N) {
//     *p = (int*)malloc(sizeof(int)*N);
// }

// void deallocate_1D(int **p) {
//     free(*p);
//     *p = NULL;
// }

// void init_2D(int *p, int rows, int cols) {
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//             p[i * cols + j] = i * cols + j;
//         }
//     }
// }

// void print_2D(int *p, int rows, int cols) {
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//             printf("%d\t", p[i*cols+j]);
//         }
//         printf("\n");
//     }
// }

// int main() {

//     // int N = 10;
//     // int* p = NULL;

//     // allocate_1D(&p, N);
//     // init_1D(p, N);
//     // print_1D(p, N);
//     // deallocate_1D(&p);

//     int rows = 10;
//     int cols = 5;
//     int *p = NULL;

//     allocate_1D(&p, rows * cols);
//     init_2D(&p, rows, cols);
//     print_2D(&p, rows, cols);
//     deallocate_1D(&p);

//     if (p == NULL) {
//         printf("OK\n");
//     }

//     int** q = NULL;
//     q = (int**)malloc(sizeof(int*) * rows);

//     for (int i = 0; i < rows; i++) {
//         q[i] = (int*)malloc(sizeof(int) * cols);
//     }

//     for ( int i = 0; i < rows; i++) {
//         free(q[i]);
//     }
//     free(q);
//     return 0;
// }

// int strlength(char* str) {
//     int i = 0;
//     while (str[i] != '\0') {
//         i++;
//     }

//     return i;
// }

// int main() {
    
//     int N = 4096;
//     char* buffer = (char*)malloc(sizeof(char) * N);
//     // char buffer[256];

//     strcpy(buffer, "retezec ,asdsa, dasd sad asd ads");

//     char* token = strtok(buffer, " ,*");
    
//     while(token != NULL) {
//         printf("%s\n", token);
//         token = strtok(NULL, " *,");
//     }

//     // int length = strlength(buffer);
//     // printf("%d\n", length);

//     // fgets(buffer, 256, stdin);
//     // printf("%s\n", buffer);

//     free(buffer);
//     buffer = NULL;

//     return 0;
// }

int main() {

    // srand(time(NULL));

    // int a = rand() % 36 - 15;
    // printf("%d", a);

    FILE* file = fopen("soubor.txt", "w");

    fputs("kys", file);
    fprintf(file, "kys x%d", 10);

    fclose(file);

    file = fopen("soubor.txt", "r");
    
    char buffer[256];
    while(fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);

    // int a = INT_MAX;
    int a[] = {0,1,2,3,4,5,6,7,8,9};
    int N = sizeof(a) / sizeof(a[0]);

    FILE* binaryFile = fopen("soubor.txt", "wb");

    fwrite(&a, sizeof(a), N, binaryFile);

    fclose(binaryFile);

    // long int b = 0;
    int intBuffer[10];

    binaryFile = fopen("soubor.txt", "rb");

    fread(intBuffer, sizeof(int), 10, binaryFile);

    fclose(binaryFile);
    return 0;
}