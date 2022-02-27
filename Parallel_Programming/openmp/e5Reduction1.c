/* OpenMp reduction */

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv){
	int val = 0, i;

#pragma omp parallel num_threads(4)
{
	#pragma omp for schedule(static, 3) reduction(+: val)
	for(i=0; i<100; i++){
//		#pragma omp critical
		{
			val = val + i;
		}
	}
}
	printf("Value %d\n", val);
	return 0;
}
