#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){

#pragma omp parallel for collapse(2)
  for(int i=0;i<4;i++){
    for(int j=0;j<10;j++){
      printf("i: %d, j: %d, threadId: %d\n", i, j, omp_get_thread_num());
    }
  }

}