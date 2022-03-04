#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024*1024*1024

int main(int argc, char** argv) {

    int* A = malloc(SIZE*sizeof(int));
    int* B = malloc(SIZE*sizeof(int));
    int* C = malloc(SIZE*sizeof(int));

    for(int i=0;i<SIZE;i++){
        A[i] = i;
        B[i] = SIZE - i;
        C[i] = 0;
    }    
    printf("%d %d %d ... %d\n", C[0], C[1], C[2], C[SIZE-1]);

    for(int i=0; i<SIZE; i++){
        C[i] = B[i] + A[i];
    }
    printf("%d %d %d ... %d\n", C[0], C[1], C[2], C[SIZE-1]);
    
    return 0;
}

