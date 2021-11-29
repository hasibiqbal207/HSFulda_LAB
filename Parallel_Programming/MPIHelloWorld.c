#include<mpi.h>
#include<stdio.h>
#include<unistd.h>

// Compile: mpicc filename.c -o programName
//   e.g  : mpicc MPIFirstProg.c -o MPIFirstProg
// Run    : mpirun -n <#procs> programName
//   e.g  : mpirun -n 4 ./MPIFirstProg

int main(int argc, char** argv){
	MPI_Init(&argc, &argv);
	char buf[128];
	gethostname(buf, 128); 
	printf("Hello World from %s\n", buf);	
	sleep(10);
	MPI_Finalize();	

	return 0;
}

