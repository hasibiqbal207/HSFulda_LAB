#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<strings.h>
#include <stdlib.h>

#define REPEATATION 100

int main(int argc, char** argv) {
	double start, end;
	int rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	float msg;
	if(rank==0){
		start = MPI_Wtime();
		MPI_Ssend(&msg, 1, MPI_FLOAT, 1, 1234, MPI_COMM_WORLD);
		MPI_Recv(&msg, 1, MPI_FLOAT, 1, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		end = MPI_Wtime();
		printf("Latency: %lf\n%lf", ((end-start))/2.0, end);
	} else if(rank == 1){
		MPI_Recv(&msg, 1, MPI_FLOAT, 0, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Ssend(&msg, 1, MPI_FLOAT, 0, 1234, MPI_COMM_WORLD);
	} else {
		;
	}
	
	MPI_Finalize();
	return 0;
}
