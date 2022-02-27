#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define SIZE 100000

int main (int argc, char** argv) {
	double work[SIZE];
	for(int i = 0; i < SIZE; i++) {
		work[i] = (float) i;
	}

	#pragma omp parallel for schedule(runtime)
	for(int i = 0; i < SIZE; i++) {
//		double start = omp_get_wtime();
		for(int j = 0; j < i; j++) {
			work[i] = sqrt(work[i]);
		}
//		double end = omp_get_wtime();
//		printf("time: %lf\n", end-start);
	}

	return 0;
}
