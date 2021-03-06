#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>

void main(int argc, char* argv[]){
    MPI_Comm comm=MPI_COMM_WORLD;
    MPI_Status status;

    int nranks,rank=-1,ierr, irec=-1;
    ierr=MPI_Init(&argc, &argv);
    ierr=MPI_Comm_size(comm,&nranks);
    ierr=MPI_Comm_rank(comm, &rank);
   
    // Number of processes
    int world_size;
    MPI_Comm_size( MPI_COMM_WORLD, &world_size );
    

    double n = atoi(argv[1]);
    double x2,result = 0;
    int i;
    clock_t start, end;
    double d2 = 1 / n / n;
    
    start = clock(); 
    //main loop    
    for (i=rank; i<n; i+=nranks){
         x2 = d2 * i * i;
         result += sqrt(1 - x2);
    }
    double sum;
    ierr=MPI_Reduce(&result, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    end = clock();
    double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    if(rank == 0){
        printf("Pi: %f\n", 4*sum/n);
        printf("%d nodes took %f seconds to execute %.0lf calculations\n", nranks, time_taken, n);
    }
    
    ierr=MPI_Finalize();
}
