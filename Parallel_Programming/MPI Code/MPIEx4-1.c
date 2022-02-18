/* MPI Ring Blocking */

#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int right = (rank+1)%size;
	int left = (rank + size - 1)%size;

	MPI_Status stat;
	int buf = 0, sum = 0;
	if(rank == 0) {
		MPI_Ssend(&buf, 1, MPI_INT, right, 123, MPI_COMM_WORLD);
		MPI_Recv (&sum, 1, MPI_INT, left, 123, MPI_COMM_WORLD, &stat);
	} else {
		MPI_Recv (&buf, 1, MPI_INT, left, 123, MPI_COMM_WORLD, &stat);
		buf += rank;
		MPI_Ssend(&buf, 1, MPI_INT, right, 123, MPI_COMM_WORLD);
	}

	if(rank == 0) {
		MPI_Ssend(&sum, 1, MPI_INT, right, 123, MPI_COMM_WORLD);
		MPI_Recv (&sum, 1, MPI_INT, left, 123, MPI_COMM_WORLD, &stat);
	} else {
		MPI_Recv (&sum, 1, MPI_INT, left, 123, MPI_COMM_WORLD, &stat);
		MPI_Ssend(&sum, 1, MPI_INT, right, 123, MPI_COMM_WORLD);
	}
	printf("rank: %d sum: %d\n", rank, sum);

	MPI_Finalize();
	return 0;
}

