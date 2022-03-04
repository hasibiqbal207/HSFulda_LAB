#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){

    int n=5;
#pragma omp parallel for
    for (int i=0;i<n;i++){
        printf("Thread ID: %d\n", omp_get_thread_num());
    }

    return 0;
}
