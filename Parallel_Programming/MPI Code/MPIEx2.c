#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	int rank, size;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int msg[2];
	msg[0] = size;
	msg[1] = rank;

	if(rank == 0) {
		MPI_Status stat;
		for(int i = 1; i < size; i++) {
			// recv
			MPI_Recv(msg, 2, MPI_INT, MPI_ANY_SOURCE, 1234, MPI_COMM_WORLD, &stat);
			// print
			printf("Size %d & Rank %d\n", msg[0], msg[1]);
		}
		printf("done\n");
	} else {
		MPI_Send(msg, 2, MPI_INT, 0, 1234, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}
