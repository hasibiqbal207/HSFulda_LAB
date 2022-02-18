#include <stdlib.h>
#include <stdio.h>
#ifdef _OPENMP
#include <omp.h>
#endif
#define SIZE 1000000

float *A, *B, *C;

int main (int argc, char** argv) {
	A = (float*) malloc(sizeof(float)*SIZE);
	B = (float*) malloc(sizeof(float)*SIZE);
	C = (float*) malloc(sizeof(float)*SIZE);

	for(int i = 0; i < SIZE; i++) {
		A[i] = i;
		B[i] = SIZE-i;
		C[i] = 0;
	}


	int i;
#ifdef _OPENMP
	double start = omp_get_wtime();
#pragma omp parallel for private(i)  
#endif
		for(i = 0; i < SIZE; i++) {
			C[i] = A[i] + B[i];
		}
#ifdef _OPENMP
	double end = omp_get_wtime();
	printf("Time: %lf\n", end-start);
#endif

	printf("%f %f ... %f %f\n", C[0], C[1], C[SIZE-2], C[SIZE-1]);
	
	
	return 0;
}
