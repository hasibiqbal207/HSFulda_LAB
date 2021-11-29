#include<stdlib.h>
#include<stdio.h>

#define SIZE 1024

typrdef struct {
	int* A;
	int* B;
	int* C;
	int start;
	int end;
}Parameters;

void* vecAdd(void* args){
	Parameters* p = (Parameters*) args;
	for(int i=p->start; i< p->end; i++){
		p->C[i] = p->A[i] + p->B[i];
}

int main(int argc, char** argv){
	int A[SIZE];
	int B[SIZE];
	int C[SIZE];

	for(int i=0; i<SIZE; i++){
		A[i] = i;
		B[i] = SIZE - i;
		C[i] = 0;
	}

	
	pthread_t ths[2];
	Parameters para[2];
	para[0].A = A;
	para[0].B = B;
	para[0].C = C;
	para[0].start = 0;
	para[0].end = SIZE/2;

	
	para[0] = {A, B, C, 0, SIZE/2);
	para[1] = {A, B, C, SIZE/2, SIZE};

	pthread_create(&ths[0], NULL, vecAdd, para[0]);
	

	for(int i=0; i<SIZE; i++){
		C[i] = A[i] + B[i];
	}

	printf("%d %d %d ... %d\n", C[0], C[1], C[2], C[SIZE-1]);
	return 0;
}
