/* General Summation program */

#include<stdlib.h>
#include<stdio.h>

#define SIZE 1024

int main(int argc, char** argv){
	int A[SIZE];
	int B[SIZE];
	int C[SIZE];

	for(int i=0; i<SIZE; i++){
		A[i] = i;
		B[i] = SIZE - i;
		C[i] = 0;
	}

	for(int i=0; i<SIZE; i++){
		C[i] = A[i] + B[i];
	}

	printf("%d %d %d ... %d\n", C[0], C[1], C[2], C[SIZE-1]);
	return 0;
}
