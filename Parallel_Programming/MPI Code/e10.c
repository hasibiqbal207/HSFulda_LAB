#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<strings.h>
#include <time.h>
#include <stdlib.h>

// compile: mpicc filename.c -o progname
// run	  : mpirun -n <#procs> progname
// mpirun -n 512 --oversubscribe --machinefile machines ./MPIHelloWorld

int main(int argc, char** argv) {
	int rank, size;
	char buffer[64];
	MPI_Init(&argc,&argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int randomNumber = rand();

	if(rank==0){
		//printf("%d of %d : Hello World. I am the master\n", rank, size);
		// A: receive from all the others
		// B: receive rank and random number from all others
		
		for(int i=1; i < size; i++){
			MPI_Recv(&rank, 1, MPI_INT, MPI_ANY_SOURCE, 221, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&randomNumber, 1, MPI_INT, MPI_ANY_SOURCE, 221, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Received rank %d rand %d \n", rank, randomNumber);
		}
		
	} else {
		//printf("%d of %d : Hello World. I am the slave\n", rank, size);
		// A: Send "Hello from Rank" To Rank 0
		// B: Send Rank and random number as Integer

		bzero(buffer, 64);
		sprintf(buffer, "Hello from Rank %d", rank);
		MPI_Send(&rank, 1, MPI_BYTE, 0, 221, MPI_COMM_WORLD);
		usleep(10);
		MPI_Send(&randomNumber, 1, MPI_BYTE, 0, 221, MPI_COMM_WORLD);
		
	}
	
	MPI_Finalize();
	return 0;
}
