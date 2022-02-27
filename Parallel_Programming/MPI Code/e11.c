#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<strings.h>
#include <time.h>
#include <stdlib.h>

// compile: mpicc filename.c -o progname
// run    : mpirun -n <#procs> progname
// mpirun -n 512 --oversubscribe --machinefile machines ./MPIHelloWorld

int main(int argc, char** argv) {
        int rank, size;
        MPI_Init(&argc,&argv);
        int msg[2];
	int buff[2];

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        msg[0] = rank;
        srand48(rank);
        msg[1] = (int)lrand48();

        if(rank==0){
                // A: receive from all the others
                // B: receive rank and random number from all others

                for(int i=1; i < size; i++){
                        MPI_Recv(&buff, 2, MPI_INT, MPI_ANY_SOURCE, 221, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        printf("Received rank %d rand %d \n", buff[0], buff[1]);
                }

        } else {
                // A: Send "Hello from Rank" To Rank 0
                // B: Send Rank and random number as Integer
		 printf("Sent rank %d rand %d \n", msg[0], msg[1]);
                MPI_Send(msg, 2, MPI_INT, 0, 221, MPI_COMM_WORLD);
        }

        MPI_Finalize();
        return 0;
}
