#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){

  int n=5;

  int s = 0;
  for(int i=0;i<n;i++){
    s += i*3;
  }
  for(int i=0;i<n;i++){
    s += i*3;
  }
  
  printf("Original sum: %d\n", s);
  
  int sum=0;
  #pragma omp parallel
  {
    printf("No of total threads: %d\n", omp_get_num_threads());
    
    #pragma omp for
    for(int i=0;i<n;i++){
      
      #pragma omp critical(sum)
      sum += i*3;
      
      #pragma omp critical(print)
      printf("in top for loop\n");
    }
    
    #pragma omp for 
    for(int i=0;i<n;i++){
      #pragma omp critical(sum)
      sum += i*3;
    }
  }
  
  printf("Parallel sum: %d\n", sum);
  
  return 0;
}