#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]){
	MPI_Comm comm=MPI_COMM_WORLD;
	
	MPI_Status status;

	// Number of processes
	int world_size;
	MPI_Comm_size( MPI_COMM_WORLD, &world_size );
	
	int nranks,rank=-1,ierr, irec=-1;
	ierr=MPI_Init(&argc, &argv);
	ierr=MPI_Comm_size(comm,&nranks);
	ierr=MPI_Comm_rank(comm, &rank);

	// Initialize the random number generator
	srand((int)(rank*(double)RAND_MAX/world_size));
	// compute a random number
	double randomfraction = (rand() / (double)RAND_MAX);
		
	//ierr=MPI_Recv(&irec, 1,MPI_INT, i,9,comm,&status);
	printf("iam=%d, received=%d\n",rank,randomfraction);
		
	ierr=MPI_Finalize();
	return 0;
} 
