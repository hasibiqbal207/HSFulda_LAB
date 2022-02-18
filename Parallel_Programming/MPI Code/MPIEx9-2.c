#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <strings.h>

int main(int argc, char** argv) {
  typedef struct {
    short rank;
    int size;
  } buffer;
  buffer buf;
  MPI_Init(&argc, &argv);

  int tmp;
  MPI_Comm_rank(MPI_COMM_WORLD, &tmp);
  buf.rank = (short)tmp;
  MPI_Comm_size(MPI_COMM_WORLD, &buf.size);

  MPI_Datatype ourBufferType;
  MPI_Datatype aot[2];
  int aob[2];
  MPI_Aint aod[2];
  aot[0] = MPI_SHORT;
  aot[0] = MPI_INT;
  aob[0] = 1;
  aob[1] = 1;
  aod[0] = 0;

  MPI_Aint a0, a1, d;
  MPI_Get_address(&buf.rank, &a0);
  MPI_Get_address(&buf.size, &a1);
  d = MPI_Aint_diff(a1, a0);
  aod[1] = d;
  MPI_Type_create_struct(2, aob, aod, aot, &ourBufferType);
  MPI_Type_commit(&ourBufferType);

  buffer sbuffer;
  buffer rbuffer;
  sbuffer.rank = buf.rank;
  sbuffer.size = buf.size;
  rbuffer.rank = buf.rank;
  rbuffer.size = buf.size;
  
  int sum = 0;
  int left = (buf.rank + buf.size -1) % buf.size;
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