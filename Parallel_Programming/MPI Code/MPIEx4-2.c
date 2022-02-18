/* MPI Ring NonBlocking	*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int right = (rank+1)%size;
	int left = (rank + size - 1)%size;

	MPI_Status stat;
	MPI_Request req;
	int sndbuf = rank, recvbuf = 0, sum = rank;
	
	for(int i = 0; i < size-1; i++) {
		MPI_Issend(&sndbuf, 1, MPI_INT, right, 123, MPI_COMM_WORLD, &req);
		MPI_Recv (&recvbuf, 1, MPI_INT, left, 123, MPI_COMM_WORLD, &stat);
		sum += recvbuf;
		MPI_Wait(&req, &stat);
		sndbuf = recvbuf;
	}

	printf("rank: %d sum: %d\n", rank, sum);

	MPI_Finalize();
	return 0;
}

//
//
//   /===========\
//  V             V
// r0<=>r1<=>r2<=>r3
// 3    0    1    2
//  2    3    0    1 
//   1    2    3    0
