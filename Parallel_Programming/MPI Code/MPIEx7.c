/* Code of class 10.01.2022
	MPI IO and MPI_File_write_at()
*/

#include <stdio.h>
#include <mpi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv) {
	MPI_Init(NULL, NULL);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	char* filename = "MPI_IO_Testfile.bin";
	MPI_File fd;
	MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fd);	
	if(fd < 0) {
		fprintf(stderr, "Error: Cannot create file ... exit\n");
		return 1;
	}

	char buf = (char)(rank+((int)'0'));
	for(int i=0; i<5; i++){
		MPI_Offset off = rank + i*size;
		MPI_File_write_at(fd, off, &buf, 1, MPI_CHAR, MPI_STATUS_IGNORE);
	}
	MPI_File_close(&fd);
	MPI_Finalize();
	return 0;
}
