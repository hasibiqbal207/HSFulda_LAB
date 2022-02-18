#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<strings.h>
#include <stdlib.h>

// compile: mpicc filename.c -o progname
// run    : mpirun -n <#procs> progname
// mpirun -n 512 --oversubscribe --machinefile machines ./MPIHelloWorld

int main(int argc, char** argv) {
        int rank, size;
        MPI_Init(&argc,&argv);
		
		// r0 -> r1 -> r3
		// A

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
		int sum = 0;
        int buffer;
		int left = (rank + size - 1) % size;
		int right = (rank + 1) % size;

        if(rank==0){    
				MPI_Ssend(&sum, 1, MPI_INT, right, 1234, MPI_COMM_WORLD);
				MPI_Recv(&buffer, 1, MPI_INT, left, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				sum = buffer + rank;
				MPI_Ssend(&sum, 1, MPI_INT, right, 1234, MPI_COMM_WORLD);
				MPI_Recv(&sum, 1, MPI_INT, left, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else {
				MPI_Recv(&buffer, 1, MPI_INT, left, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				sum += buffer;
				MPI_Ssend(&sum, 1, MPI_INT, right, 1234, MPI_COMM_WORLD);
				MPI_Recv(&sum, 1, MPI_INT, left, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Ssend(&sum, 1, MPI_INT, right, 1234, MPI_COMM_WORLD);

        }

		printf("rank %d got sum=%d\n", rank, sum);
        MPI_Finalize();
        return 0;
}
