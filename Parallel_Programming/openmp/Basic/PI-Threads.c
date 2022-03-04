#include <stdio.h>
#include <pthread.h>

#include <stdlib.h>

#define f(A) (4.0/(1.0+A*A))

int threadsNo = 2;
const long long n = 100000000;

double PI = 0.0;
double w = 1.0/n;

pthread_mutex_t mut; // Use for locking

void* worker (void* _args){
	int threadID = *((int*)_args);
    printf("Thread ID: %d\n", threadID);
	long long i;
	double x, sumPart, pi;
	sumPart = 0.0;

	long long limit = n /threadsNo;
	if(threadID == threadsNo - 1)
		limit = n;

	//for (i= threadID*ThreadNo; i < limit*(threadID+1); i++) {
	for (i= threadID; i < n; i+=threadsNo) {
		x = w * ((double)i + 0.5);
		//sumPart = sumPart + f(x);
		pthread_mutex_lock(&mut);
		PI = PI + f(x);
		pthread_mutex_unlock(&mut);
	}

//	pthread_mutex_lock(&mut);
//	PI += sumPart;
//	pthread_mutex_unlock(&mut);

	return 0;
}

int main(int argv, char** argc){

    if(argv == 2){
        threadsNo = atoi(argc[1]);
    }

    printf("No of threads: %d\n", threadsNo);    

    pthread_t threads[threadsNo];

    int indices[threadsNo];

    pthread_mutex_init(&mut, NULL);
    
    for (int i = 0; i < threadsNo; i++) {
		indices[i] = i;
		pthread_create(&threads[i], NULL, worker, &indices[i]);
	}

    for (int i = 0; i < threadsNo; i++) {
		pthread_join(threads[i], NULL);
	}

	printf("pi = %.15f\n", w*PI);
	return 0;
}
