#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<strings.h>
#include <stdlib.h>

#define REPEATATION 100
#define KILO 1024
#define MEGA 1024 * KILO

int main(int argc, char** argv) {
        double start, end;
        int rank;
        MPI_Init(&argc,&argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        char* msg = (char*) malloc(MEGA*16);
        char hname[128];
        gethostname(hname, 128);
        printf("testing on host: %s\n", hname);


        if(rank==0){
                MPI_Send(msg, 1, MPI_BYTE, 1, 1234, MPI_COMM_WORLD);
                MPI_Recv(msg, 1, MPI_BYTE, 1, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for(int s=1; s<=MEGA*16; s*=2){
                        start = MPI_Wtime();
                        for(int i=0; i<REPEATATION; i++){
							MPI_Ssend(msg, s, MPI_BYTE, 1, 1234, MPI_COMM_WORLD);
							MPI_Recv(msg, s, MPI_BYTE, 1, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                }
				end = MPI_Wtime();
				printf("Latency: %lf\n", ((end-start)/REPEATATION)/2.0);
                printf("Bandwidth: %lf\n", s*((end-start)/REPEATATION)/2.0);
		
                }
        } else if(rank == 1){
                MPI_Recv(msg, 1, MPI_BYTE, 0, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(msg, 1, MPI_BYTE, 0, 1234, MPI_COMM_WORLD);
                for(int s=1; s<=MEGA*16; s*=2){
                        for(int i=0; i<REPEATATION; i++){
							MPI_Recv(msg, s, MPI_BYTE, 0, 1234, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
							MPI_Ssend(msg, s, MPI_BYTE, 0, 1234, MPI_COMM_WORLD);
                        }
                }

        } else {
                ;
        }

        MPI_Finalize();
        return 0;
}
