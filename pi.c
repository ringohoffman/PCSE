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
    double x,y;
    int i;
    int count=0;
    double z;
    double pi;
    srand(time(NULL));
    clock_t start, end;

    start = clock(); 
    //main loop    
    for (i = 0; i < n / nranks; ++i)
    {
        //get random points
        x = (double)random()/RAND_MAX;
        y = (double)random()/RAND_MAX;
        z = sqrt((x*x)+(y*y));
        //check to see if point is in unit circle
        if (z<=1)
            ++count;
    }
    int sum;
    ierr=MPI_Reduce(&count, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    end = clock();
    double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    pi = ((double)sum/n)*4.0;
    if(rank == 0){
        printf("Pi: %f\n", pi);
        printf("%d nodes took %f seconds to execute %.0lf calculations\n", nranks, time_taken, n);
    }
    
    ierr=MPI_Finalize();
}
