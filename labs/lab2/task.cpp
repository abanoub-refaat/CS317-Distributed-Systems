#include <mpi.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char ** argv) {
    int myid,  np;
    int n;
    MPI_Init (&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid); // my id in the whole group
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    if(myid == 0){
        printf("prrocessor %d My master node\n", myid);
        
    } else if (myid%2 == 0){
        printf("prrocessor %d my even worker node\n", myid);
    } else {
        printf("prrocessor %d my odd worker node\n", myid);
    }
    
    MPI_Finalize();
    return 0;
}