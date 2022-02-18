#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>


// compile: mpicc filename.c -o progname
// run	  : mpirun -n <#procs> progname
// mpirun -n 512 --oversubscribe --machinefile machines ./MPIHelloWorld

int main(int argc, char** argv) {
	int rank, size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if(rank==0){
		printf("%d of %d : Hello World. I am the master\n", rank, size);
	} else {
		printf("%d of %d : Hello World. I am the slave\n", rank, size);
	}
	
	MPI_Finalize();
	return 0;
}
