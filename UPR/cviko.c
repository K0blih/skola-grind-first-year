#include <stdio.h>

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

void sumArray(int* a, int N, int* result) {
    for (int i = 0, j = 0; i < N - N % 2; i += 2, j++) {
        result[j] = a[i] + a[i+1];
    }
}

int main() {
    
    int a[] = {0,1,2,3,4,5,6,7,8,9,10};
    int N = sizeof(a) / sizeof(a[0]);
    int M = N / 2;
    int result[M];
    sumArray(a, N, result);
    for (int i = 0; i < M; i++) {
        printf("%d\n", result[i]);
    }
    return 0;
}
