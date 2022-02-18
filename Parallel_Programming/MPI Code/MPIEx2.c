#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <sys/types.h>
#include <unistd.h>

#define MSGSIZE 20

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	int rank;
	int size;
	pid_t pid = getpid();

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	char msg[MSGSIZE];
	if(rank == 0) {
		MPI_Status stat;
		for(int i = 1; i < size; i++) {
			// recv
			printf("I will do my %d recv\n", i);
			MPI_Recv(msg, MSGSIZE, MPI_CHAR, MPI_ANY_SOURCE, 1234, MPI_COMM_WORLD, &stat);
			// print
			printf("%s\n", msg);
		}
		printf("done\n");
	} else {
		// prepare message
		sprintf(msg, "Hello from %d\0", rank);
		// send
		if(rank != 1)
			MPI_Send(msg, MSGSIZE, MPI_CHAR, 0, 1234, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}
