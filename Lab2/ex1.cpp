#include <mpi.h>
#include <iostream>
#include <unistd.h>
using namespace std;

// mpic++ filename.cpp -o outfile.out
// mpiexec -n 5 ./filename

int main(int argc, char ** argv) {
    int myid,  np;
    int n;
    MPI_Init (&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid); // my id in the whole group
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    printf("prrocessor %d of %d yalla bena!\n", myid, np);
    MPI_Finalize();
    return 0;
}