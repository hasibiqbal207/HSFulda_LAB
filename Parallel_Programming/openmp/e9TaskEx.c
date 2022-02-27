// gcc -O2 -fopenmp SectionEx.c -o SectionEx -lm

#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
#pragma omp parallel num_threads(2)
	{
	// #pragma omp single
		int tid = omp_get_thread_num();
		{
			#pragma omp task
			printf("E = %d ", tid);
			#pragma omp task
			printf(" m %d ", tid);
			#pragma omp task
			printf(" c^2 %d ", tid);
			#pragma omp taskwait
			printf(" WOW %d ", tid);
		}
	}

#pragma omp parallel num_threads(2)
	{
	int tid = omp_get_thread_num();
	#pragma omp single
		{
			printf("\nE = %d ", tid);
			#pragma omp task
			printf(" m %d ", tid);
			#pragma omp task
			printf(" c^2 %d ", tid);
			printf(" WOW %d ", tid);
		}
	}
	printf("\n");

	return 0;
}
