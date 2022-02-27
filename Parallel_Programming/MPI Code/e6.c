#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<strings.h>
#include<stdlib.h>

int main(int argc, char** argv){
	int rank, size;
	MPI_Init(&argc, &argv);

	//     left     right
	// r0   ->   r1  ->   r2 -> r3
	// A

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int sbuffer = rank;
	int rbuffer = rank;
	int sum = 0;
	int buffer;
	int left = (rank + size -1) % size;
	int right = (rank+1) % size;
	MPI_Request req;

	for(int i=0; i<size; i++){
		MPI_Issend(&sbuffer, 1, MPI_INT, right, 1234, MPI_COMM_WORLD, &req);
		MPI_Irecv(&rbuffer, 1, MPI_INT, left, 1234, MPI_COMM_WORLD, &req);
		MPI_Wait(&req, MPI_STATUS_IGNORE);
		sum = sum + rbuffer;
		printf("Local Index %d Sbuffer %d Rbuffer %d Sum %d\n", i, sbuffer, rbuffer, sum);
		sbuffer = rbuffer;
	}
	printf("Rank %d Sum %d\n", rank, sum);
	MPI_Finalize();
	return 0;
}
