#include<mpi.h>
#include<stdio.h>
#include<unistd.h>

// Compile: mpicc filename.c -o programName
//   e.g  : mpicc MPIFirstProg.c -o MPIFirstProg
// Run    : mpirun -n <#procs> programName
//   e.g  : mpirun -n 4 ./MPIFirstProg 
// If node is more than 1000, dont use mpirun, use hydra(check the name)
#define MSGSIZE 20

int main(int argc, char** argv){
	int rank, size;

	MPI_Init(&argc, &argv);

	pid_t pid = getpid();
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	char msg[MSGSIZE];

	if(rank == 0) {
		MPI_Status stat;
		o World. I am the  \n", rank, size);
		// A: Receive from all the others
		// B: Receive Rank and SIZE from all others
		for(int i=1; i<size; i++){
			MPI_Recv(msg, MSGSIZE, MPI_CHAR, MPI_ANY_SOURCE, 1234, MPI_COMM_WORLD, &stat)
		
	printf("%s\n", msg);
	} else {
		fprintf(stderr, "%d of %d: Hello World. I am the  \n", rank, size);
		char buffer[64];
		bzero(buffer, 64);
		sprintf(buffer, "Hello from %d", rank);
		MPI_Send(msg, MSGSIZE, MPI_CHAR, 0, 1234, MPI_COMM_WORLD);
		// A: SEND "Hello from Rank"  to rank 0
		// Send Rank & size as integer
	}

	MPI_Finalize();	

	return 0;
}

