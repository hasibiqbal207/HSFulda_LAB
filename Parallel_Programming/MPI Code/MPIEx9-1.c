#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <strings.h>

int main(int argc, char** argv) {
  typedef struct {
    int rank;
    int size;
  } buffer;
  buffer buf;
  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &buf.rank);
  MPI_Comm_size(MPI_COMM_WORLD, &buf.size);

  MPI_Datatype ourBufferType;
  MPI_Type_contiguous(2, MPI_INT, &ourBufferType);

  buffer sbuffer;
  buffer rbuffer;
  sbuffer.rank = buf.rank;
  sbuffer.size = buf.size;
  rbuffer.rank = buf.rank;
  rbuffer.size = buf.size;
  
  int sum = 0;
  int left = (buf.rank + buf.size - 1) % buf.size;
  int right = (buf.rank + 1) % buf.size;

  MPI_Request req;

  // send rank and size in a derived datatype arounf and sum the ranks up
  for(int i = 0; i < buf.size, i++){
    MPI_Issend(&sbuffer, 1, ourBufferType, right, 1234, MPI_COMM_WORLD, &req);
    MPI_Recv(&rbuffer, 1, ourBufferType, left, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Wait(&req, MPI_STATUS_IGNORE);
    sum += rbuffer.rank;
    sbuffer.rank = rbuffer.rank;
  }

  printf("rank %d got sum=%d\n", buf.rank, sum);
  MPI_Finalize();
}