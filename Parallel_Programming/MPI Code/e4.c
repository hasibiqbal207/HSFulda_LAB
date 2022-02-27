#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<strings.h>

// compile: mpicc filename.c -o progname
// run	  : mpirun -n <#procs> progname
// mpirun -n 512 --oversubscribe --machinefile machines ./MPIHelloWorld

int main(int argc, char** argv) {
	int rank, size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	char buffer[64];
	if(rank==0){
		//printf("%d of %d : Hello World. I am the master\n", rank, size);
		// A: receive from all the others
		// B: receive rank and size from all others
		
		for(int i=1; i < size; i++){
			MPI_Recv(buffer, 64, MPI_BYTE, MPI_ANY_SOURCE, 221, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%s", buffer);
		}
		
	} else {
		//printf("%d of %d : Hello World. I am the slave\n", rank, size);
		// A: Send "Hello from Rank" To Rank 0
	// B: Send Rank and size as Integer
		printf("Before: \n%s\n", buffer);	
		bzero(buffer, 64);
		printf("After: \n%s\n", buffer);
		sprintf(buffer, "Hello from Rank = %d\n", rank);
		printf("After Print: \n%s\n", buffer);
		MPI_Send(buffer, 64, MPI_BYTE, 0, 221, MPI_COMM_WORLD);

	}
	
	MPI_Finalize();
	return 0;
}
