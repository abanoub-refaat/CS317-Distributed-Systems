#include <mpi.h>
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

int main(int argc, char **argv)
{
    int myid, np;
    int n = 100;
    int accum;

    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &myid); // my id in the whole group
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int sum = 0;
    int startval = n * myid / np + 1;
    int endval = n * (myid + 1) / np;

    for (int i = startval; i <= endval; i = i + 1)
    {
        sum = sum + i;
    }

    if (myid != 0)
    {
        MPI_Send(&sum, 1, MPI_INT, 0, 17, MPI_COMM_WORLD);
    }
    else
    {
        for (int i = 1; i < np; i++)
        {
            MPI_Recv(&accum, 1, MPI_INT, i, 17, MPI_COMM_WORLD, &status);
            sum += accum;
        }
        printf("The sum is: %d\n", sum);
    }

    MPI_Finalize();
    return 0;
}