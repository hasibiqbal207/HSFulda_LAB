/* Pie with Pragma */

#include <stdio.h>

#define f(A) (4.0/(1.0+A*A))

//const int n = 1000000000;
const int n = 100;

int main(int argc, char* argv[]) {
	int i;
	double w, x, sum, pi;
	w = 1.0/n;
	sum = 0.0;

#pragma omp parallel for  private(i, x) reduction(+:sum)
	for (i=0; i<n; i++) {
		x = w * ((double)i + 0.5);
//		#pragma omp critical
		{
			sum = sum + f(x);
		}
	}

	printf("pi = %.15f\n", w*sum);

	return 0;
}

