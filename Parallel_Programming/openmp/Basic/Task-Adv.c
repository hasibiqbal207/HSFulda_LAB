#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main(int argv, char** argc){
const int n=5;
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("inside sinle\n");
            #pragma omp task
            {
                usleep(10);
                for(int i=0;i<n;i++) {
                    printf("inside first task(%d): %d out of %d\n", i, omp_get_thread_num(), omp_get_num_threads());
                }
            }
  
            #pragma omp task
            {
                usleep(10);
                for(int i=0;i<n;i++) {
                      printf("inside second task(%d): %d out of %d\n", i, omp_get_thread_num(), omp_get_num_threads());
                }
                
                #pragma omp task
                {
                  for(int i=0;i<n;i++) {
                        printf("inside second (inner) task(%d): %d out of %d\n", i, omp_get_thread_num(), omp_get_num_threads());
                  }
                }
            }

            #pragma omp nowait                            
            printf("do not wait\n");
        }
    }
    printf("\n");
    return 0;
}
