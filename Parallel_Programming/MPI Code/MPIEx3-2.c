/*
    MPI Latency Test
*/

#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define N 1000

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    float msg = 0;
    double start, end;
    if(rank == 0) {
        MPI_Ssend(&msg, 1, MPI_FLOAT, 1, 17, MPI_COMM_WORLD);
        MPI_Recv( &msg, 1, MPI_FLOAT, 1, 23, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else if(rank == 1) {
        MPI_Recv( &msg, 1, MPI_FLOAT, 0, 17, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Ssend(&msg, 1, MPI_FLOAT, 0, 23, MPI_COMM_WORLD);
    }
    int counter = 0;
    start = MPI_Wtime();
    while (counter < N) {
        if(rank == 0) {
            MPI_Ssend(&msg, 1, MPI_FLOAT, 1, 17, MPI_COMM_WORLD);
            MPI_Recv( &msg, 1, MPI_FLOAT, 1, 23, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else if(rank == 1) {
            MPI_Recv( &msg, 1, MPI_FLOAT, 0, 17, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Ssend(&msg, 1, MPI_FLOAT, 0, 23, MPI_COMM_WORLD);
        }
        counter++;
    }
    end = MPI_Wtime();
    //printf("Latency: %lf\n", ((end-start)/(2*N))* 1e9);
    printf("Latency: %lf\n", ((end-start)/(2*N)));
    MPI_Finalize();
    return 0;
}

