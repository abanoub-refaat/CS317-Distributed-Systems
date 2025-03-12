#include <mpi.h>
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

int main(int argc, char **argv)
{
    int myid, np;
    int n;
    int accum;
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &myid); // my id in the whole group
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    if (myid == 0)
    {
        printf("Enter the value of n: ");
        cin >> n;
        for (int i = 1; i < np; i++)
        {
            MPI_Send(&n, 1, MPI_INT, i, 17, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(&n, 1, MPI_INT, 0, 17, MPI_COMM_WORLD, &status);
    }

    int sum = 0;
    int startval = n * myid / np + 1;
    int endval = n * (myid + 1) / np;

    for (int i = startval; i <= endval; i = i + 1)
    {
        sum = sum + i;
    }

    MPI_Finalize();
    return 0;
}