#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1024*1024*1024

int main(int argc, char** argv) {

    double startTime = omp_get_wtime();
    int* A = malloc(SIZE*sizeof(int));
    int* B = malloc(SIZE*sizeof(int));
    int* C = malloc(SIZE*sizeof(int));

#pragma omp parallel
printf("Thread %d/%d\n", omp_get_thread_num(), omp_get_num_threads());

#pragma omp parallel for
    for(int i=0;i<SIZE;i++){
        A[i] = i;
        B[i] = SIZE - i;
        C[i] = 0;
    }    
    printf("%d %d %d ... %d\n", C[0], C[1], C[2], C[SIZE-1]);

#pragma omp parallel for
    for(int i=0; i<SIZE; i++){
        C[i] = B[i] + A[i];
    }
    printf("%d %d %d ... %d\n", C[0], C[1], C[2], C[SIZE-1]);
    
double endTime = omp_get_wtime();
printf("Total time: %12.4g sec\n", endTime - startTime);
    return 0;
}

