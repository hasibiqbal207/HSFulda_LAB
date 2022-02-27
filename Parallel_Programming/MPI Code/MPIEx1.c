#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	int rank;
	int size;
	pid_t pid = getpid();

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int data = rank;
	int ind = size-1;
//	fprintf(stderr, "[%d] Hello World from %d of %d\n", pid, rank, size);
	if(rank == 0) {
		for(int i = 1; i<size; i++){
//		printf("I distribute the work\n");
			MPI_Recv(&data, 1, MPI_INT, ind, 420, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("PID %d Incoming Rank: %d\n", pid, data);
			ind -= 1;
	}
	} else {
		usleep(rank*5);
//		printf("I do the work\n");	
		MPI_Ssend(&data, 1, MPI_INT, 0, 420, MPI_COMM_WORLD);
	}
	MPI_Finalize();

	return 0;
}
