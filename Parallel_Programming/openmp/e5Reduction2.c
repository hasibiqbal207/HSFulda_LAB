/* OpenMp reduction */

#include<stdio.h>

#define f(A) (4.0/(1.0+A*A))

const long long n = 10000000000;

int main(int argc, char* argv[]) {
	long long i;
	double w,x,sum,pi;
	w=1.0/n;
	sum=0.0;

#pragma omp parallel for reduction(+: sum)
	
	for(i=0; i<n; i++){
		x=w* ((double)i + 0.5);
		sum=sum+f(x);
	}
	printf("pi = %.15\n", w*sum);
	return 0;
}