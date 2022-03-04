#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            printf("(a) Thread ID: %d\n", omp_get_thread_num());

            #pragma omp section
            printf("(b) Thread ID: %d\n", omp_get_thread_num());

            #pragma omp section
            printf("(c) Thread ID: %d\n", omp_get_thread_num());

            #pragma omp section
            printf("(d) Thread ID: %d\n", omp_get_thread_num());

        }
    }
    
    return 0;
}
