#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){
	MPI_Comm comm=MPI_COMM_WORLD;
	
	MPI_Status status;
	
	int nranks,rank=-1,ierr, irec=-1;
	ierr=MPI_Init(&argc, &argv);
	ierr=MPI_Comm_size(comm,&nranks);
	ierr=MPI_Comm_rank(comm, &rank);

	if(rank==0)
		ierr=MPI_Send(&rank,1,MPI_INT,1,9,comm);
	if(rank==1)
		ierr=MPI_Recv(&irec, 1,MPI_INT, 0,9,comm,&status);
	
	ierr=MPI_Finalize();
	printf("iam=%d, received=%d\n",rank,irec);
} 
