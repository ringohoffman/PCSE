#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]){
	MPI_Comm comm=MPI_COMM_WORLD;
	
	MPI_Status status;
	
	int nranks,rank=-1,ierr, irec=-1;
	ierr=MPI_Init(&argc, &argv);
	ierr=MPI_Comm_size(comm,&nranks);
	ierr=MPI_Comm_rank(comm, &rank);
	
	// Initialize the random number generator
	srand((int)(rank*(double)RAND_MAX/nranks));
	// compute a random number
	double randomfraction = (rand() / (double)RAND_MAX);
	double max;
	printf("rank: %d   num:%f\n",rank,randomfraction);
	ierr=MPI_Allreduce(&randomfraction,&max,1,MPI_DOUBLE, MPI_MAX,MPI_COMM_WORLD);
	
	if(randomfraction == max)
		printf("\nThread producing the max random number:\nrank: %d   num:%f\n",rank,randomfraction);
		
	ierr=MPI_Finalize();
} 
