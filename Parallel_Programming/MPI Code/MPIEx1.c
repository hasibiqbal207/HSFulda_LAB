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

	fprintf(stderr, "[%d] Hello World from %d of %d\n", pid, rank, size);
	if(rank == 0) {
		printf("I distribute the work\n");
	} else {
		usleep(1);
		printf("I do the work\n");	
	}
	MPI_Finalize();

	return 0;
}
