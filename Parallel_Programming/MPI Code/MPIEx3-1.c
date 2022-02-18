/*
MPI Bandwidth Test
*/

#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define N 20

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double start, end;
    long currentSize = 1024;
    MPI_Status stat;
    for(int l = 0; l <= 17; l++) { 
    	int counter = 0;
        unsigned long transferData = 0;
	
	void* data = malloc(currentSize);
    	start = MPI_Wtime();
    	while (counter < N) {
            if(rank == 0) {
                MPI_Ssend(data, currentSize, MPI_BYTE, 1, 17, MPI_COMM_WORLD);
            } else if(rank == 1) {
        	MPI_Recv( data, currentSize, MPI_BYTE, 0, 17, MPI_COMM_WORLD, &stat);
            }
            counter++;
    	}
    	end = MPI_Wtime();
	free(data);
	double bw = ((currentSize*N) / (end-start)) / (1024*1024); 
	if(currentSize / 1024 < 1)
	    printf("%4.d byte Bandwidth: %3.lf MiB/sec\n", currentSize , bw);
	else if(currentSize / (1024*1024) >= 1)
	    printf("%4.d MiB  Bandwidth: %3.lf MiB/sec\n", currentSize / (1024*1024), bw);
	else 
	    printf("%4.d KiB  Bandwidth: %3.lf MiB/sec\n", currentSize / 1024, bw);
	currentSize *= 2;
    }
    
    
    MPI_Finalize();
    return 0;
}

