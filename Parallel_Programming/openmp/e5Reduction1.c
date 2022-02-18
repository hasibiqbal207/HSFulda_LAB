/* OpenMp reduction */

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv){
	int val = 0;

#pragma omp parallel num_threads(4)
{
	#pragma omp for schedule(static) reduction(-: val)
	for(int i=0; i<4; i++){
		val = val + i;
	}
}
	printf("Value %d\n", val);
	return 0;
}
