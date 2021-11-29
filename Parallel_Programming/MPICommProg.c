#include<mpi.h>
#include<stdio.h>
#include<unistd.h>

// Compile: mpicc filename.c -o programName
//   e.g  : mpicc MPIFirstProg.c -o MPIFirstProg
// Run    : mpirun -n <#procs> programName
//   e.g  : mpirun -n 4 ./MPIFirstProg

int main(int argc, char** argv){
	int rank, size;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if(rank == 0) {
		fprintf(stderr, "%d of %d: Hello World. I am the  \n", rank, size);
		// A: Receive from all the others
		// B: Receive Rank and SIZE from all others
	} else {
		fprintf(stderr, "%d of %d: Hello World. I am the  \n", rank, size);
		char buffer[64];
		bzero(buffer, 64);
		sprintf(buffer, "Hello from %d", rank);

		// A: SEND "Hello from Rank"  to rank 0
		// Send Rank & size as integer
	}

	MPI_Finalize();	

	return 0;
}

