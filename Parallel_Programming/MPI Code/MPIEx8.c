/* 
Code of class 17.01.2022
SetView and Writing on File

mpicc MPIIO3a.c -o MPIIO3a
mpirun -np 8 -npernode 1 --machinefile machines ./MPIIO3a

test the output file: less my_test_file
*/
#include <stdio.h>
#include <mpi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv) {
	int rank, size, i;
	int ndims, array_of_sizes[1], array_of_subsizes[1];
	int array_of_starts[1], order;
	MPI_File fh;
	MPI_Datatype etype;
	MPI_Datatype filetype;
	MPI_Offset disp;
	MPI_Status status;
	char buf;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	etype = MPI_CHAR;
	ndims = 1;
	array_of_sizes[0] = size; 
	array_of_subsizes[0] = 1;
	array_of_starts[0] = rank;
	order = MPI_ORDER_C;
	MPI_Type_create_subarray(ndims, array_of_sizes, array_of_subsizes, array_of_starts, order, etype, &filetype);
	MPI_Type_commit(&filetype);

	char* filename = "my_test_file";
	MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);
	disp = 0;
	MPI_File_set_view(fh, disp, etype, filetype, "native", MPI_INFO_NULL);

	for(int i=0; i<5; i++){
		buf = '0' + (char)rank;
		MPI_File_write(fh, &buf, 1, etype, &status);
		//MPI_Offset off = rank + i*size;
		//MPI_File_write_at(fd, off, &buf, 1, MPI_CHAR, MPI_STATUS_IGNORE);
		// Put a newline
	}
	MPI_File_close(&fh);
	printf("PE%d\n", rank);
	MPI_Finalize();
	return 0;
}
