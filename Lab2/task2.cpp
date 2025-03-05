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

    cout << argc<< endl;

    MPI_Finalize();
    return 0;
}