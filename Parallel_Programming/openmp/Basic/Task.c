#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main(int argv, char** argc){
    #pragma omp parallel
    {
    
        // all thread should be sync if entry barr: 
        
        #pragma omp single
        {
            // printf("Thread # in single region: %d\n", omp_get_thread_num());
            //printf("No of threads in single region: %d\n", omp_get_num_threads());
            printf("E= \n");
            #pragma omp task
            {
                usleep(1010);
              //  printf("Thread # in first task region: %d\n", omp_get_thread_num());
              //  printf("No of threads in first task region: %d\n", omp_get_num_threads());
                printf("m\n");
            }
  
            #pragma omp task
            {
                usleep(1011);
              //  printf("Thread # in second task region: %d\n", omp_get_thread_num());
              //  printf("No of threads in second task region: %d\n", omp_get_num_threads());
                printf("c²\n");
            }

                                        
            printf(" WOW\n");
        }
        printf("\nhello");
    }
    printf("\n");
    return 0;
}
