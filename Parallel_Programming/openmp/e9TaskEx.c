// gcc -O2 -fopenmp SectionEx.c -o SectionEx -lm

#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
#pragma omp parallel num_threads(2)
	{
	// #pragma omp single
		{
			printf("E = ");
			#pragma omp task
			printf(" m ");
			#pragma omp task
			printf(" c^2 ");
			#pragma omp taskwait
			printf(" WOW ");
		}
	}

#pragma omp parallel num_threads(2)
	{
	#pragma omp single
		{
			printf("\nE = ");
			#pragma omp task
			printf(" m ");
			#pragma omp task
			printf(" c^2 ");
			printf(" WOW ");
		}
	}
	printf("\n");

	return 0;
}
