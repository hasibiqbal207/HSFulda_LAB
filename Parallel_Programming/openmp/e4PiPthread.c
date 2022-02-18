/* PI using pthread */

#include<stdio.h>

#define f(A) (4.0/(1.0+A*A))

const long long n = 10000000000;

int ThreadNo = 2;
double PI = 0.0;
double w = 1.0/n;
pthread_mutex_t mut;

void* partPi(void* _args) {
	int threadID = *((int*)_args);
	long long i;
	double x, sumPart, pi;
	sumPart = 0.0;
	
	long long limit = n /ThreadNo;
	if(threadID == ThreadNo - 1)
		limit = n;
		
	//for(i = threadID*ThreadNo; i<limit*(threadID+1); i++){
	for(i = threadID; i<n; i+=ThreadNo){
		x = w * ((double)i + 0.5);
		//sumPart = sumPart + f(x);
		pthread_mutex_lock(&mut);
		PI += sumPart;
		pthread_mutex_unlock(&mut);
	}
	
	//pthread_mutex_lock(&mut);
	//PI += sumPart;
	//pthread_mutex_unlock(&mut);
	
	return 0;	
}

int main(int argc, char* argv[]) {
	
	if(argc == 2){
		ThreadNo = atoi(argv[1]);
	}
	
	pthread_t threads[ThreadNo];
	int indices[ThreadNo];
	pthread_mutex_init(&mut, NULL);
	
	for(int i=0; i < ThreadNo; i++){
		indices[i] = i;
		pthread_create(&threads[i], NULL, partPi, &indices[i])
	}
	
	for(int i=0; i < ThreadNo; i++){
		pthread_join(threads[i], NULL)
	}
	
	printf("pi = %.15f\n", w*PI);
	return 0;
}