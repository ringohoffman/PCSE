#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){
	MPI_Comm comm=MPI_COMM_WORLD;
	
	MPI_Status status;
	
	int nranks,rank=-1,ierr, irec=-1;
	ierr=MPI_Init(&argc, &argv);
	ierr=MPI_Comm_size(comm,&nranks);
	ierr=MPI_Comm_rank(comm, &rank);
	
	if(rank < 8){	
		for(int i = 0; i < 8; i++){
			if(i == rank)
				continue;
		
			ierr=MPI_Send(&rank,1,MPI_INT,i,9,comm);
			ierr=MPI_Recv(&irec, 1,MPI_INT, i,9,comm,&status);
			printf("iam=%d, received=%d\n",rank,irec);
		}
	}
		
	ierr=MPI_Finalize();
	return 0;
} 
