#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv) {
	int size = 1000;

	if(argc == 2){
		size = atoi(argv[1]);
	}

	int** matrix = malloc(size*sizeof(int*));
	for(int i=0; i<size; i++){
		matrix[i] = malloc(size*sizeof(int));
	}

	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			matrix[i][j] = (i*size+j)%5;
	}}

	int numberOfZero = 0;

#pragma omp parallel default(none) shared(size, matrix, numberOfZero) num_threads(1)
{
//	#pragma omp for
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			if(matrix[i][j] == 0){
				#pragma omp single 
				{numberOfZero++;}
			}
	}}
}
	printf("Number of Zeros %d\n", numberOfZero);
	return 0;
}
