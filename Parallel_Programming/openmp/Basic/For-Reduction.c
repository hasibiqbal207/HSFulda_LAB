#include <stdio.h>

int main(int argc, char** argv){

  int n=100000;
  long int sum=0.0;
  for(int i=0;i<n ;i++){
    sum += (long int) i* 3 / 100;
  }
  printf("Original sum: %ld\n", sum);
  
  long int s=0.0;
  #pragma omp parallel for reduction(+:s)
  for(int i=0;i<n ;i++){
    s += (long int) i* 3 / 100;
  }
  printf("Parallel sum: %ld\n", s);
}