#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<strings.h>
#include<stdlib.h>

int main(int argc, char** argv){
	int rank, size;
	MPI_Init(&argc, &argv);
	int msg[2];

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	msg[0] = rank;

	srand48(rank);
	msg[1] = (int)lrand48();
	if(rank==0){
		// A: Receive from all the others
		// B: Receive rank & random number from all others
		for(int i=1; i<size; i++){
			MPI_Recv(msg, 1, MPI_INT, MPI_ANY_SOURCE, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Received: Rank- %d rand- %d\n", msg[0], msg[1]);
		}
	}  else {
			MPI_Send(msg, 1, MPI_INT, 0, 1234, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
