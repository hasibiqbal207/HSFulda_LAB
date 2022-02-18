// gcc -O2 -fopenmp SectionEx.c -o SectionEx -lm

#include <omp.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 1000000

int main(int argc, char** argv) {
	double *A = (double*) malloc(SIZE*sizeof(double));
	double *B = (double*) malloc(SIZE*sizeof(double));
	double *C = (double*) malloc(SIZE*sizeof(double));
	double *D = (double*) malloc(SIZE*sizeof(double));

#pragma omp parallel
	{
	#pragma omp sections
		{
		#pragma omp section
			{
				for(int i = 0; i < SIZE; i++) {
					A[i] = i;
				}
			}
		#pragma omp section
			{
				for(int i = 0; i < SIZE; i++) {
					B[i] = i;
					for(int j = 0; j < i; j++)
						B[i] = pow(B[i], 2);
				}
			}
		#pragma omp section
			{
				for(int i = 0; i < SIZE; i++) {
					C[i] = i;
					for(int j = 0; j < i; j++)
						C[i] = sqrt(C[i]);
				}
			}
		}
	}

	int i;

#pragma omp parallel for private(i) shared(A, B, C, D)
	for (i = 0; i < SIZE; i++) {
		D[i] = A[i] + B[i] + C[i];
	} 

	return 0;
}
