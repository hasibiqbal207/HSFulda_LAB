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
	
	char buffer[64];
	if(rank == 0) {
		// A: Receive from all the others
		// B: Receive Rank and SIZE from all others
		for(int i = 1; i<size; i++){
			MPI_Recv(buffer, 64, MPI_BYTE, MPI_ANY_SOURCE, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%s\n", buffer);
		}
	} else {
		bzero(buffer, 64);
		sprintf(buffer, "Hello from %d", rank);
		MPI_Send(buffer,64, MPI_BYTE, 0, 123, MPI_COMM_WORLD);
		// A: SEND "Hello from Rank"  to rank 0
		// Send Rank & size as integer
	}

	MPI_Finalize();	

	return 0;
}

